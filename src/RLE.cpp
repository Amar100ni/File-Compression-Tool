#include "RLE.h"
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>

// Compress a string using RLE
std::string RLE::compress(const std::string& input) {
    std::ostringstream compressed;
    int n = input.size();
    for (int i = 0; i < n; i++) {
        int count = 1;
        while (i + 1 < n && input[i] == input[i + 1]) {
            i++;
            count++;
        }
        compressed << input[i] << count;
    }
    return compressed.str();
}

// Decompress a string using RLE
std::string RLE::decompress(const std::string& input) {
    std::ostringstream decompressed;
    int n = input.size();
    for (int i = 0; i < n; i++) {
        char c = input[i];
        std::string countStr;
        while (i + 1 < n && isdigit(input[i + 1])) {
            countStr += input[++i];
        }
        int count = std::stoi(countStr);
        decompressed << std::string(count, c);
    }
    return decompressed.str();
}

// Compress a file using RLE
bool RLE::compressFile(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream in(inputFile, std::ios::binary);
    if (!in) return false;

    std::ostringstream ss;
    ss << in.rdbuf();
    std::string input = ss.str();
    in.close();

    std::string compressed = compress(input);

    std::ofstream out(outputFile, std::ios::binary);
    if (!out) return false;
    out << compressed;
    out.close();
    return true;
}

// Decompress a file using RLE
bool RLE::decompressFile(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream in(inputFile, std::ios::binary);
    if (!in) return false;

    std::ostringstream ss;
    ss << in.rdbuf();
    std::string input = ss.str();
    in.close();

    std::string decompressed = decompress(input);

    std::ofstream out(outputFile, std::ios::binary);
    if (!out) return false;
    out << decompressed;
    out.close();
    return true;
}
