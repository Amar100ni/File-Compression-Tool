#include "ReportGenerator.h"
#include <fstream>
#include <filesystem>
#include <chrono>
#include <ctime>

namespace ReportGenerator {

    void generateReport(const std::string& reportPath,
                        const std::string& operation,
                        const std::string& algorithm,
                        const std::string& inputPath,
                        const std::string& outputPath,
                        bool success,
                        double ratio,
                        double timeTaken) {

        std::filesystem::create_directories(std::filesystem::path(reportPath).parent_path());

        std::ofstream report(reportPath);
        if (!report.is_open()) return;

        // Timestamp
        auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::string timeStr = std::ctime(&now);
        timeStr.pop_back();

        report << "==============================\n";
        report << "  File Compression Report\n";
        report << "==============================\n";
        report << "Operation       : " << operation << "\n";
        report << "Algorithm       : " << algorithm << "\n";
        report << "Input File      : " << inputPath << "\n";
        report << "Output File     : " << outputPath << "\n";
        report << "Status          : " << (success ? "Success" : "Failed") << "\n";
        report << "Time Taken (s)  : " << timeTaken << "\n";

        if (operation == "Compression")
            report << "Compression Ratio : " << ratio << " %\n";

        report << "Generated At    : " << timeStr << "\n";
        report << "==============================\n";

        report.close();
    }

}
