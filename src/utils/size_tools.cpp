#include "size_tools.h"

#include <QString>
#include <QVector>

QString getSizeWithUnit(const qint64 sizeB)
{
    return getSizeWithUnit(sizeB, 2);
}

QString getSizeWithUnit(const qint64 sizeB, const int precision)
{
    auto size = static_cast<double>(sizeB);
    int i = 0;
    while (size >= static_cast<double>(1024) && i + 1 < units.size()) {
        size /= static_cast<double>(1024);
        i++;
    }
    return QString::number(size, 'f', precision) + " " + units[i];
}