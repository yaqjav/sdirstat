#include "scanner.h"
#include <QDirListing>
#include <QPromise>

void scanFolder(QPromise<ScanResult>& promise ,const QString& path)
{
    using F = QDirListing::IteratorFlag;
    QDirListing entries(path, F::FilesOnly | F::IncludeHidden | F::Recursive);

    qint64 fileCount = 0, totalSizeb = 0;

    for (const auto& entry : entries)
    {
        if (promise.isCanceled()) return;
        totalSizeb += entry.size();
        fileCount++;
    }

    promise.addResult(ScanResult{.fileCount = fileCount, .totalBytes = totalSizeb});
}
