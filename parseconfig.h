#ifndef PARSECONFIG_H
#define PARSECONFIG_H

#include "disk.h"
#include "album.h"

QJsonObject load_json_obj(const QString &file_path, const QString &file_name)
{
    QFile file(file_path);
    if (!file.open(QIODevice::ReadOnly))
    {
        throw std::runtime_error("Can't open file " + file_name.toStdString() + ": " + file.errorString().toStdString());
    }

    QByteArray file_data = file.readAll();

    QJsonParseError parse_error;
    QJsonDocument file_doc(QJsonDocument::fromJson(file_data, &parse_error));
    if (file_doc.isEmpty())
    {
        throw std::runtime_error("Json Document for " + file_name.toStdString() + " is empty:\n" + parse_error.errorString().toStdString() + '\n' + QString::number(parse_error.offset).toStdString());
    }
    else if (!file_doc.isObject())
    {
        throw std::runtime_error("Json Document for " + file_name.toStdString() + " is not Json object!");
    }

    QJsonObject file_obj = file_doc.object();
    if (file_obj.empty())
    {
        throw std::runtime_error("Json Object for " + file_name.toStdString() + "is empty!");
    }

    return file_obj;
}

void check_existing_value(QJsonValue::Type type, const QJsonValue &val, const QString &val_name)
{
    if (val == QJsonValue::Undefined)
    {
        throw std::runtime_error("Empty value: " + val_name.toStdString());
    }
    if (val.type() != type)
    {
        throw std::runtime_error("Wrong type for value: " + val_name.toStdString());
    }
}

static QVector<Disk> get_disks_from_config(QString config_file_path)
{
    auto disks_obj = load_json_obj(config_file_path, "disks config");

    auto disks_arr_val = disks_obj.value("disks");
    check_existing_value(QJsonValue::Array, disks_arr_val, "disks array");
    auto disks_arr = disks_arr_val.toArray();

    auto albums_config_path = disks_obj.value("albums_config");
    check_existing_value(QJsonValue::String, albums_config_path, "albums config path");

    auto albums_obj = load_json_obj(albums_config_path.toString(), "albums config");

    auto albums_arr_val = albums_obj.value("albums");
    check_existing_value(QJsonValue::Array, albums_arr_val, "albums array");
    auto albums_arr = albums_arr_val.toArray();

    QVector <Album> file_albums;
    for (const auto album_val: albums_arr)
    {
        QJsonObject album_obj = album_val.toObject();

        file_albums.push_back(album_obj);
    }

    QVector<Disk> result_disks;
    for (const auto disk_val : disks_arr)
    {
        QJsonObject disk_obj = disk_val.toObject();

        Disk disk(disk_obj);

        auto album_id = disk_obj.value("album_id").toInt();
        foreach (const Album &album, file_albums)
        {
            if (album.id == album_id)
            {
                disk.album = album;
                break;
            }
        }
        result_disks.push_back(disk);
    }

    return result_disks;
}


#endif // PARSECONFIG_H
