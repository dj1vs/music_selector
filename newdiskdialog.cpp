#include "newdiskdialog.h"
#include "ui_newdiskdialog.h"

NewDiskDialog::NewDiskDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::NewDiskDialog)
{
    ui->setupUi(this);
}

Disk NewDiskDialog::get_disk()
{
    Disk disk;
    disk.disk_type = to_disk_type(ui->type_edit->text());
    disk.album.id = ui->album_id_edit->text().toInt();
    disk.photo_path = ui->photo_path_edit->text();
    disk.place = ui->place_edit->text();

    return disk;
}

NewDiskDialog::~NewDiskDialog()
{
    delete ui;
}
