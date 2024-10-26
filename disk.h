#ifndef DISK_H
#define DISK_H

#include "album.h"

class QJsonObject;

enum class DiskType
{
    None,
    CD,
    Vinyl,
    Tape
};

DiskType to_disk_type(const QString &str);
QString from_disk_type(DiskType type);

class Disk
{
public:
    Disk() = default;
    Disk(const QJsonObject& obj);

    operator QString();
    operator QJsonObject();
public:
    DiskType disk_type;
    QString place;
    QString photo_path;
    Album album;

signals:
};

#endif // DISK_H
