#ifndef DISKWIDGET_H
#define DISKWIDGET_H

#include "disk.h"

namespace Ui {
class DiskWidget;
}

class DiskWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DiskWidget(QWidget *parent = nullptr);
    DiskWidget(const DiskWidget&);
    ~DiskWidget();

    void load(const Disk &disk);

    Disk get_disk() const;

private:
    Ui::DiskWidget *ui;
};

#endif // DISKWIDGET_H
