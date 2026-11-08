#ifndef SDIRSTAT_SCANNER_H
#define SDIRSTAT_SCANNER_H

#include <QString>
#include <QPromise>

struct ScanResult {
    qint64 fileCount = 0;
    qint64 totalBytes = 0;
};

void scanFolder(QPromise<ScanResult>& promise ,const QString& path);

#endif //SDIRSTAT_SCANNER_H
