#include "BackendInterface.h"
#include "RLE.h"
#include "Huffman.h"
#include "ReportGenerator.h"
#include "Logger.h"
#include <chrono>
#include <filesystem>
#include <iostream>

namespace Backend {

    static std::string lastReportPath;

    bool compressFile(const std::string& algorithm,
                      const std::string& inputPath,
                      const std::string& outputPath) {
        auto start = std::chrono::high_resolution_clock::now();

        bool success = false;
        if (algorithm == "RLE")
            success = RLE::compressFile(inputPath, outputPath);
        else if (algorithm == "Huffman")
            success = Huffman::compressFile(inputPath, outputPath);
        else
            std::cerr << "[ERROR] Unknown algorithm: " << algorithm << std::endl;

        auto end = std::chrono::high_resolution_clock::now();
        double duration = std::chrono::duration<double>(end - start).count();

        double ratio = 0.0;
        if (success && std::filesystem::exists(inputPath) && std::filesystem::exists(outputPath)) {
            auto origSize = std::filesystem::file_size(inputPath);
            auto compSize = std::filesystem::file_size(outputPath);
            ratio = (origSize != 0) ? (100.0 * compSize / origSize) : 0.0;
        }

        lastReportPath = generateReport("Compression", algorithm, inputPath, outputPath, success, ratio, duration);
        Logger::log("Compression [" + algorithm + "] " + (success ? "succeeded" : "failed"));
        return success;
    }

    bool decompressFile(const std::string& algorithm,
                        const std::string& inputPath,
                        const std::string& outputPath) {
        auto start = std::chrono::high_resolution_clock::now();

        bool success = false;
        if (algorithm == "RLE")
            success = RLE::decompressFile(inputPath, outputPath);
        else if (algorithm == "Huffman")
            success = Huffman::decompressFile(inputPath, outputPath);
        else
            std::cerr << "[ERROR] Unknown algorithm: " << algorithm << std::endl;

        auto end = std::chrono::high_resolution_clock::now();
        double duration = std::chrono::duration<double>(end - start).count();

        lastReportPath = generateReport("Decompression", algorithm, inputPath, outputPath, success, 0.0, duration);
        Logger::log("Decompression [" + algorithm + "] " + (success ? "succeeded" : "failed"));
        return success;
    }

    std::string generateReport(const std::string& operation,
                               const std::string& algorithm,
                               const std::string& inputPath,
                               const std::string& outputPath,
                               bool success,
                               double ratio,
                               double timeTaken) {
        std::string reportDir = "reports";
        std::filesystem::create_directories(reportDir);

        std::string fileName = reportDir + "/" + operation + "_" + algorithm + "_Report.txt";

        ReportGenerator::generateReport(fileName, operation, algorithm, inputPath, outputPath, success, ratio, timeTaken);
        return fileName;
    }

    std::string getLastReportPath() {
        return lastReportPath;
    }

}
