#ifndef ALBUM_H
#define ALBUM_H

class QJsonObject;

enum class AlbumType
{
    None,
    Single,
    Mixtape,
    Album,
    Compilation,
    EP
};

AlbumType to_album_type(const QString &str);
QString from_album_type(AlbumType type);


class Album
{
public:
    Album() = default;
    Album(const QJsonObject& obj);

    operator QString();
    operator QJsonObject();
public:
    int id;
    AlbumType album_type;
    QString title;
    QStringList artists;

signals:
};

#endif // ALBUM_H
