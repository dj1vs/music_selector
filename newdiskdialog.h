#ifndef NEWDISKDIALOG_H
#define NEWDISKDIALOG_H

#include <QDialog>
#include "disk.h"

namespace Ui {
class NewDiskDialog;
}

class NewDiskDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewDiskDialog(QWidget *parent = nullptr);

    Disk get_disk();

    ~NewDiskDialog();

private:
    Ui::NewDiskDialog *ui;
};

#endif // NEWDISKDIALOG_H
