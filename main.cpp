#include <iostream>
#include <string>
#include "RLE.h"
#include "Huffman.h"
#include "Logger.h"
#include "ReportGenerator.h"
#include "Utils.h"

using namespace std;

void printMenu() {
    cout << "\n========== File Compression Tool ==========" << endl;
    cout << "1. Compress File" << endl;
    cout << "2. Decompress File" << endl;
    cout << "3. Exit" << endl;
    cout << "===========================================" << endl;
    cout << "Enter choice: ";
}

void printAlgorithmMenu() {
    cout << "\nSelect Compression Algorithm:" << endl;
    cout << "1. Run-Length Encoding (RLE)" << endl;
    cout << "2. Huffman Coding" << endl;
    cout << "Enter choice: ";
}

int main() {
    Logger::clear(); // Clear old logs at program start
    Logger::log("Program started at " + Utils::getCurrentTimestamp());

    int choice = 0;
    while (true) {
        printMenu();
        cin >> choice;

        if (choice == 3) {
            Logger::log("Program exited by user.\n");
            cout << "Goodbye!" << endl;
            break;
        }

        if (choice != 1 && choice != 2) {
            cout << "Invalid option. Try again." << endl;
            continue;
        }

        string inputFile, outputFile;
        cout << "Enter input file path: ";
        cin >> inputFile;
        cout << "Enter output file path: ";
        cin >> outputFile;

        printAlgorithmMenu();
        int algoChoice;
        cin >> algoChoice;

        bool success = false;
        string algorithmName;
        long long beforeSize = Utils::getFileSize(inputFile);
        long long afterSize = -1;

        if (choice == 1) { // Compress
            if (algoChoice == 1) {
                algorithmName = "RLE";
                success = RLE::compressFile(inputFile, outputFile);
            } else if (algoChoice == 2) {
                algorithmName = "Huffman";
                success = Huffman::compressFile(inputFile, outputFile);
            } else {
                cout << "Invalid algorithm choice." << endl;
                continue;
            }

            afterSize = Utils::getFileSize(outputFile);
            double ratio = Utils::calculateCompressionRatio(beforeSize, afterSize);
            string status = success ? "Success" : "Failed";

            Logger::log("Compression - Algorithm: " + algorithmName +
                        ", Input: " + inputFile +
                        ", Output: " + outputFile +
                        ", Ratio: " + to_string(ratio) +
                        "%, Status: " + status);

            if (success) {
                cout << "\n✅ Compression Successful!" << endl;
                cout << "Compression Ratio: " << ratio << "%" << endl;
                ReportGenerator::generateReport(inputFile, outputFile, ratio, algorithmName);
            } else {
                cout << "\n❌ Compression Failed!" << endl;
            }
        }

        else if (choice == 2) { // Decompress
            if (algoChoice == 1) {
                algorithmName = "RLE";
                success = RLE::decompressFile(inputFile, outputFile);
            } else if (algoChoice == 2) {
                algorithmName = "Huffman";
                success = Huffman::decompressFile(inputFile, outputFile);
            } else {
                cout << "Invalid algorithm choice." << endl;
                continue;
            }

            Logger::log("Decompression - Algorithm: " + algorithmName +
                        ", Input: " + inputFile +
                        ", Output: " + outputFile +
                        ", Status: " + (success ? "Success" : "Failed"));

            if (success) cout << "\n✅ Decompression Successful!" << endl;
            else cout << "\n❌ Decompression Failed!" << endl;
        }
    }

    return 0;
}
