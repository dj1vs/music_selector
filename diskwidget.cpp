#include "diskwidget.h"
#include "ui_diskwidget.h"

#include "disk.h"
#include "album.h"

DiskWidget::DiskWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DiskWidget)
{
    ui->setupUi(this);
}

DiskWidget::DiskWidget(const DiskWidget &dw)
{
    ui = new Ui::DiskWidget;
    ui->setupUi(this);
    ui->image_label->setPixmap(dw.ui->image_label->pixmap());
    ui->place_label->setText(dw.ui->place_label->text());
}

DiskWidget::~DiskWidget()
{
    delete ui;
}

void DiskWidget::load(const Disk &disk)
{
    ui->image_label->setPixmap(QPixmap::fromImage(QImage(disk.photo_path)).scaled(QSize(256, 256)));

    QString artists_str;
    foreach(const QString &artist, disk.album.artists)
    {
        artists_str += artist + ';';
    }
    artists_str.removeAt(artists_str.size() - 1);
    ui->place_label->setText(disk.place);
    ui->type_label->setText(from_disk_type(disk.disk_type));
    ui->album_id_label->setText(QString::number(disk.album.id));
}

