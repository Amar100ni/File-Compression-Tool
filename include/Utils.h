#ifndef UTILS_H
#define UTILS_H

#include <string>

namespace Utils {
    std::string getFileName(const std::string& path);
    long long getFileSize(const std::string& filename);
    double calculateCompressionRatio(long long originalSize, long long compressedSize);
    std::string getCurrentTimestamp();
}

#endif
