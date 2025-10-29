#ifndef BACKEND_INTERFACE_H
#define BACKEND_INTERFACE_H

#include <string>

namespace Backend {

    // Compress file using the chosen algorithm ("RLE", "Huffman", etc.)
    bool compressFile(const std::string& algorithm,
                      const std::string& inputPath,
                      const std::string& outputPath);

    // Decompress file using the chosen algorithm
    bool decompressFile(const std::string& algorithm,
                        const std::string& inputPath,
                        const std::string& outputPath);

    // Generates a report file after compression or decompression
    std::string generateReport(const std::string& operation,
                               const std::string& algorithm,
                               const std::string& inputPath,
                               const std::string& outputPath,
                               bool success,
                               double ratio = 0.0,
                               double timeTaken = 0.0);

    // Returns the last generated report’s full file path
    std::string getLastReportPath();

}

#endif
