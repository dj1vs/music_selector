#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "diskwidget.h"
#include "newdiskdialog.h"
#include "parseconfig.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    try
    {
        auto disks = get_disks_from_config("/home/dmitriy/Pictures/physical_music_collection/disks.json");

        QWidget *disks_widget = new QWidget;
        disks_widget->setAttribute(Qt::WA_DeleteOnClose, true);
        QVBoxLayout *layout = new QVBoxLayout(disks_widget);

        foreach(const Disk& disk, disks)
        {
            DiskWidget* widget = new DiskWidget(this);
            widget->load(disk);
            layout->addWidget(widget);
        }

        ui->scrollArea->setWidget(disks_widget);
    }
    catch (const std::exception &e)
    {
        QMessageBox::warning(this, "warning", e.what());
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_random_btn_clicked()
{
    QVBoxLayout *disks_layout = dynamic_cast<QVBoxLayout*>(ui->scrollArea->widget()->layout());

    auto disks_amount = disks_layout->count();

    auto random_disk = QRandomGenerator::global()->bounded(0, disks_amount);

    DiskWidget *dw = new DiskWidget(*dynamic_cast<DiskWidget*>(disks_layout->itemAt(random_disk)->widget()));

    QDialog *dial = new QDialog;
    QVBoxLayout *layout = new QVBoxLayout(dial);
    dial->setAttribute(Qt::WA_DeleteOnClose, true);
    layout->addWidget(new QLabel("Your random choice is:"));
    layout->addWidget(dw);

    dial->exec();
}


void MainWindow::on_new_disk_clicked()
{
    NewDiskDialog dial;
    if (dial.exec() == QDialog::Accepted)
    {

    };
}

