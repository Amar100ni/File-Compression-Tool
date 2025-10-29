#include "Utils.h"
#include <filesystem>
#include <chrono>
#include <iomanip>
#include <sstream>

namespace fs = std::filesystem;

namespace Utils {

    std::string getFileName(const std::string& path) {
        return fs::path(path).filename().string();
    }

    long long getFileSize(const std::string& filename) {
        try {
            return fs::file_size(filename);
        } catch (...) {
            return -1;
        }
    }

    double calculateCompressionRatio(long long originalSize, long long compressedSize) {
        if (originalSize <= 0) return 0.0;
        return (1.0 - (double)compressedSize / originalSize) * 100.0;
    }

    std::string getCurrentTimestamp() {
        auto now = std::chrono::system_clock::now();
        std::time_t t = std::chrono::system_clock::to_time_t(now);
        std::stringstream ss;
        ss << std::put_time(std::localtime(&t), "%Y-%m-%d %H:%M:%S");
        return ss.str();
    }
}
