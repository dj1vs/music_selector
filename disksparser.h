#ifndef DISKSPARSER_H
#define DISKSPARSER_H

#include <QObject>
#include "disk.h"

class DisksParser : public QObject
{
    Q_OBJECT
public:
    DisksParser(QObject *parent = nullptr);

    QVector<Disk> get_disks_from_config(QString config_file_path);

signals:
};

#endif // DISKSPARSER_H
