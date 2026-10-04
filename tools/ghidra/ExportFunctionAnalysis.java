import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.nio.charset.StandardCharsets;
import java.util.HashMap;
import java.util.Map;

import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionIterator;
import ghidra.program.model.listing.FunctionManager;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.symbol.ReferenceIterator;
import ghidra.program.model.symbol.SourceType;

public class ExportFunctionAnalysis extends GhidraScript {
    @Override
    protected void run() throws Exception {
        String[] scriptArgs = getScriptArgs();
        if (scriptArgs.length < 2) {
            throw new IllegalArgumentException("expected output directory, symbol map, and optional function addresses");
        }

        File outputDir = new File(scriptArgs[0]);
        if (!outputDir.isDirectory() && !outputDir.mkdirs()) {
            throw new IOException("could not create output directory: " + outputDir);
        }

        FunctionManager functionManager = currentProgram.getFunctionManager();
        Map<Long, String> symbols = readSymbols(new File(scriptArgs[1]));
        for (Map.Entry<Long, String> symbol : symbols.entrySet()) {
            Address address = toAddr(symbol.getKey());
            Function function = functionManager.getFunctionAt(address);
            if (function == null) {
                function = functionManager.getFunctionContaining(address);
            }
            if (function == null) {
                function = createFunction(address, null);
            }
            if (function == null) {
                throw new IOException("no function found or created for symbol "
                    + symbol.getValue() + " at " + address);
            }
            function.setName(symbol.getValue(), SourceType.USER_DEFINED);
        }

        File referencesFile = new File(outputDir, "references.csv");
        try (PrintWriter writer = new PrintWriter(referencesFile, StandardCharsets.UTF_8)) {
            writer.println("callee,address,callsite,caller_address,caller");
            for (Map.Entry<Long, String> symbol : symbols.entrySet()) {
                Address target = toAddr(symbol.getKey());
                ReferenceIterator references = currentProgram.getReferenceManager().getReferencesTo(target);
                while (references.hasNext()) {
                    Reference reference = references.next();
                    if (!reference.getReferenceType().isCall()) {
                        continue;
                    }
                    Function caller = functionManager.getFunctionContaining(reference.getFromAddress());
                    String callerAddress = caller == null ? "" : caller.getEntryPoint().toString();
                    String callerName = caller == null ? "" : caller.getName();
                    writer.printf("%s,%s,%s,%s,%s%n",
                        csv(symbol.getValue()), csv(target.toString()),
                        csv(reference.getFromAddress().toString()), csv(callerAddress), csv(callerName));
                }
            }
        }

        File inventory = new File(outputDir, "functions.csv");
        try (PrintWriter writer = new PrintWriter(inventory, StandardCharsets.UTF_8)) {
            writer.println("address,name,size_bytes");
            FunctionIterator functions = functionManager.getFunctions(true);
            while (functions.hasNext()) {
                Function function = functions.next();
                String name = function.getName().replace("\"", "\"\"");
                writer.printf("\"%s\",\"%s\",%d%n",
                    function.getEntryPoint(), name, function.getBody().getNumAddresses());
            }
        }

        DecompInterface decompiler = new DecompInterface();
        decompiler.openProgram(currentProgram);
        try {
            for (int index = 2; index < scriptArgs.length; index++) {
                String value = scriptArgs[index].replaceFirst("^0[xX]", "");
                Address address = toAddr(Long.parseUnsignedLong(value, 16));
                Function function = functionManager.getFunctionAt(address);
                if (function == null) {
                    function = functionManager.getFunctionContaining(address);
                }
                if (function == null) {
                    function = createFunction(address, null);
                }
                if (function == null) {
                    throw new IOException("no function found or created at " + address);
                }

                DecompileResults result = decompiler.decompileFunction(function, 60, monitor);
                if (!result.decompileCompleted() || result.getDecompiledFunction() == null) {
                    throw new IOException("decompilation failed at " + function.getEntryPoint()
                        + ": " + result.getErrorMessage());
                }

                String entry = function.getEntryPoint().toString();
                File source = new File(outputDir, "sub_" + entry + ".c");
                try (PrintWriter writer = new PrintWriter(source, StandardCharsets.UTF_8)) {
                    writer.print(result.getDecompiledFunction().getC());
                }
                println("decompiled " + function.getName() + " at " + entry + " -> " + source);
            }
        }
        finally {
            decompiler.dispose();
        }

        println("function inventory -> " + inventory);
    println("call references -> " + referencesFile);
    }

    private Map<Long, String> readSymbols(File file) throws IOException {
        Map<Long, String> symbols = new HashMap<>();
        try (BufferedReader reader = new BufferedReader(new FileReader(file, StandardCharsets.UTF_8))) {
            String line;
            while ((line = reader.readLine()) != null) {
                line = line.trim();
                if (line.isEmpty() || line.startsWith("#")) {
                    continue;
                }
                String[] entry = line.replace(";", "").split("=", 2);
                if (entry.length != 2) {
                    throw new IOException("invalid symbol mapping: " + line);
                }
                String address = entry[1].trim().replaceFirst("^0[xX]", "");
                symbols.put(Long.parseUnsignedLong(address, 16), entry[0].trim());
            }
        }
        return symbols;
    }

    private String csv(String value) {
        return "\"" + value.replace("\"", "\"\"") + "\"";
    }
}