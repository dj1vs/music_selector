#include "disk.h"

Disk::Disk(const QJsonObject& obj)
{
    disk_type = to_disk_type(obj.value("type").toString());
    photo_path = obj.value("photo_path").toString();
    place = obj.value("place").toString();
}

Disk::operator QString()
{
    QString result;

    result += from_disk_type(disk_type) + '\n';
    result += place + '\n';
    result += photo_path + '\n';
    result += QString(album);

    return result;
}

Disk::operator QJsonObject()
{
    QJsonObject object;
    object["type"] = from_disk_type(disk_type);
    object["place"] = place;
    object["photo_path"] = photo_path;
    object["album_id"] = album.id;

    return object;
}

DiskType to_disk_type(const QString &str)
{
    static const QMap <QString, DiskType> str_to_type = {
        {"cd", DiskType::CD},
        {"tape",  DiskType::Tape},
        {"vinyl", DiskType::Vinyl},
        {"lp", DiskType::Vinyl},
        {"disk", DiskType::CD}
    };

    if (str_to_type.find(str) != str_to_type.end())
    {
        return str_to_type[str];
    }

    return DiskType::None;
}

QString from_disk_type(DiskType type)
{
    switch (type)
    {
    case DiskType::CD:
        return "cd";
        break;
    case DiskType::Tape:
        return "tape";
        break;
    case DiskType::Vinyl:
        return "vinyl";
        break;
    case DiskType::None:
        return "unspecified";
        break;
    }
}
