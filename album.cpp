#include "album.h"

Album::Album(const QJsonObject &obj)
{
    id = obj.value("id").toInt();

    album_type = to_album_type(obj.value("type").toString());

    auto artists_variantlist = obj.value("artists").toArray().toVariantList();
    foreach (const QVariant &artist_variant, artists_variantlist)
    {
        artists.push_back(artist_variant.toString());
    }

    title = obj.value("title").toString();
}

Album::operator QString()
{
    QString result;

    result += from_album_type(album_type) + '\n';
    result += title + '\n';

    foreach (const QString &artist, artists)
    {
        result += artist + ';';
    }
    result += '\n';

    return result;
}

Album::operator QJsonObject()
{
    QJsonObject obj;
    obj["id"] = id;
    obj["type"] = from_album_type(album_type);
    obj["title"] = title;

    QJsonArray artists_arr;
    foreach (const QString &artist, artists)
    {
        artists_arr.append(artist);
    }
    obj["artists"] = artists_arr;

    return obj;
}

AlbumType to_album_type(const QString &str)
{
    static const QMap <QString, AlbumType> str_to_type = {
        {"single", AlbumType::Single},
        {"album",  AlbumType::Album},
        {"mixtape", AlbumType::Mixtape},
        {"ep", AlbumType::EP}
    };

    if (str_to_type.find(str) != str_to_type.end())
    {
        return str_to_type[str];
    }

    return AlbumType::None;
}

QString from_album_type(AlbumType type)
{
    switch (type)
    {
    case AlbumType::Album:
        return "album";
        break;
    case AlbumType::Compilation:
        return "compilation";
        break;
    case AlbumType::EP:
        return "ep";
        break;
    case AlbumType::Mixtape:
        return "mixtape";
        break;
    case AlbumType::Single:
        return "single";
        break;
    case AlbumType::None:
        return "unspecified";
        break;
    }
}
