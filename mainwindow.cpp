#include "mainwindow.h"
#include <random>
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mean->setVisible(false);
    ui->stddev->setVisible(false);
    ui->meanline->setVisible(false);
    ui->stddevline->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool mode;

void MainWindow::on_uniform_pressed()
{
    mode = false;
    ui->mean->setVisible(false);
    ui->stddev->setVisible(false);
    ui->meanline->setVisible(false);
    ui->stddevline->setVisible(false);
}

void MainWindow::on_normal_pressed()
{

    mode = true;
    ui->mean->setVisible(true);
    ui->stddev->setVisible(true);
    ui->meanline->setVisible(true);
    ui->stddevline->setVisible(true);
}

void MainWindow::on_run_clicked()
{
    int high = ui->upper->text().toInt();
    int low = ui->lower->text().toInt();
    int result;
    std::random_device rd;
    std::mt19937 gen(rd());
    if (!mode) {
        std::uniform_int_distribution<> dist(low, high);
        result = dist(gen);
    } else {
        int mean = ui->mean->text().toInt();
        int stddev = ui->stddev->text().toInt();

        std::normal_distribution<> dist(mean, stddev);

        do {
            result = static_cast<int>(dist(gen));
        } while (result < low || result > high);
    }
    ui->result->setText(QString::number(result));
}
