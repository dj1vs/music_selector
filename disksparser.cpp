#include "disksparser.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValueRef>

#include "disk.h"
#include "album.h"

DisksParser::DisksParser(QObject *parent)
    : QObject{parent}
{}

QVector<Disk> DisksParser::get_disks_from_config(QString config_file_path)
{
    QFile disks_file(config_file_path);
    if (!disks_file.open(QIODevice::ReadOnly))
    {
        throw std::runtime_error("Can't open config file: " + disks_file.errorString().toStdString());
    }

    QByteArray disks_data = disks_file.readAll();

    QJsonDocument disks_doc(QJsonDocument::fromJson(disks_data));

    auto main_obj = disks_doc.object();
    if (main_obj.empty())
    {
        throw std::runtime_error("Empty JSON object for config file!");
    }

    auto disks_arr_val = main_obj.value("disks");
    if (disks_arr_val == QJsonValue::Undefined)
    {
        throw std::runtime_error("No disks key in config JSON file!");
    }

    if (!disks_arr_val.isArray())
    {
        throw std::runtime_error("disks key value in config JSON is not an array!");
    }

    auto disks_arr = disks_arr_val.toArray();

    auto albums_config_path = main_obj.value("albums_config");
    if (albums_config_path == QJsonValue::Undefined)
    {
        throw std::runtime_error("No albums_config key specified in config JSON file!");
    }
    if (!albums_config_path.isString())
    {
        throw std::runtime_error("albums_config key in config JSON file is not a string!");
    }

    QFile albums_file(albums_config_path.toString());
    if (!albums_file.open(QIODevice::ReadOnly))
    {
        throw std::runtime_error("Can't open albums config file: " + albums_file.errorString().toStdString());
    }

    QByteArray albums_data = albums_file.readAll();

    QJsonDocument albums_doc(QJsonDocument::fromJson(albums_data));

    auto albums_obj = albums_doc.object();
    if (albums_obj.empty())
    {
        throw std::runtime_error("Empty JSON object for albums config file!");
    }

    auto albums_arr_val = albums_obj.value("albums");
    if (albums_arr_val == QJsonValue::Undefined)
    {
        throw std::runtime_error("No albums key in albums config JSON file!");
    }

    if (!albums_arr_val.isArray())
    {
        throw std::runtime_error("albums key value in albums config JSON is not an array!");
    }

    auto albums_arr = albums_arr_val.toArray();

    QMap <int, Album> file_albums;

    for (const auto album_val: albums_arr)
    {
        QJsonObject album_obj = album_val.toObject();

        int id = album_obj.value("id").toInt();

        file_albums[id] = Album(album_obj);
    }

    QVector<Disk> result_disks;

    for (const auto disk_val : disks_arr)
    {
        QJsonObject disk_obj = disk_val.toObject();

        Disk disk(disk_obj);
        disk.album = file_albums[disk_obj.value("album_id").toInt()];

        result_disks.push_back(disk);
    }

    return result_disks;
}
