#pragma once
#include <QList>
#include <QString>

inline const QVector<QString> units = {
    "B", "KiB", "MiB", "GiB", "TiB", "PiB"
};
QString getSizeWithUnit(qint64 sizeB);
QString getSizeWithUnit(qint64 sizeB, int precision);