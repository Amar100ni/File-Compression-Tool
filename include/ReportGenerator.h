#ifndef REPORT_GENERATOR_H
#define REPORT_GENERATOR_H

#include <string>

namespace ReportGenerator {

    // Generates a detailed compression/decompression report
    void generateReport(const std::string& reportPath,
                        const std::string& operation,
                        const std::string& algorithm,
                        const std::string& inputPath,
                        const std::string& outputPath,
                        bool success,
                        double ratio,
                        double timeTaken);

}

#endif
