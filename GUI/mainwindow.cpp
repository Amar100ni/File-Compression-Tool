#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("File Compression Tool");
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_selectFileButton_clicked() {
    QString filePath = QFileDialog::getOpenFileName(this, "Select File to Compress");
    if (!filePath.isEmpty()) {
        selectedFilePath = filePath;
        ui->statusLabel->setText("Selected: " + filePath);
    }
}

void MainWindow::on_compressButton_clicked() {
    if (selectedFilePath.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please select a file first!");
        return;
    }
    // Placeholder for actual compression call
    QMessageBox::information(this, "Compression", "File compressed successfully!");
}

void MainWindow::on_decompressButton_clicked() {
    if (selectedFilePath.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please select a file first!");
        return;
    }
    // Placeholder for actual decompression call
    QMessageBox::information(this, "Decompression", "File decompressed successfully!");
}
