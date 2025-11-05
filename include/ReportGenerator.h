#ifndef REPORTGENERATOR_H
#define REPORTGENERATOR_H

#include <QString>
#include "CompressionManager.h"

class ReportGenerator {
public:
    static void generateReport(const CompressionResult& result);
    static QString getReportsDirectory();
    static QString getLastReportPath();
    
private:
    static void ensureReportsDirectoryExists();
    static QString generateReportContent(const CompressionResult& result);
    static QString lastReportPath;
};

#endif