#include "MainWindow.h"
#include "ui_mainwindow.h"
#include "CompressionManager.h"
#include "Utility.h"
#include "ReportGenerator.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDesktopServices>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , compressionManager(nullptr)
    , selectedFilePath("")
{
    ui->setupUi(this);
    
    compressionManager = new CompressionManager(this);
    setupConnections();
    
    setWindowTitle("File Compression Tool - DAA Project");
    resize(800, 650);
    
    // Initially disable buttons until file is selected
    setButtonsEnabled(false);
    
    // Add welcome message to results
    ui->resultsText->clear();
    ui->resultsText->append("File Compression Tool - DAA Project");
    ui->resultsText->append("===================================");
    ui->resultsText->append("Ready. Select a file to start compression or decompression.");
    ui->resultsText->append("");
}

MainWindow::~MainWindow()
{
    delete compressionManager;
    delete ui;
}

void MainWindow::setupConnections()
{
    // Connect UI buttons
    /*connect(ui->selectFileButton, &QPushButton::clicked, this, &MainWindow::on_selectFileButton_clicked);
    connect(ui->compressButton, &QPushButton::clicked, this, &MainWindow::on_compressButton_clicked);
    connect(ui->decompressButton, &QPushButton::clicked, this, &MainWindow::on_decompressButton_clicked);
    connect(ui->viewReportsButton, &QPushButton::clicked, this, &MainWindow::on_viewReportsButton_clicked);
    connect(ui->clearButton, &QPushButton::clicked, this, &MainWindow::on_clearButton_clicked);
    */
    // Connect menu actions
    connect(ui->actionSelect_File, &QAction::triggered, this, &MainWindow::on_selectFileButton_clicked);
    connect(ui->actionExit, &QAction::triggered, this, &QMainWindow::close);
    connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::on_actionAbout_triggered);
    
    // Connect compression manager signals
    connect(compressionManager, &CompressionManager::progressUpdated, this, &MainWindow::handleProgressUpdated);
    connect(compressionManager, &CompressionManager::operationCompleted, this, &MainWindow::handleOperationCompleted);
}

void MainWindow::on_selectFileButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Select File", "", "All Files (*.*)");
    
    if (!filePath.isEmpty()) {
        selectedFilePath = filePath;
        updateFileInfo();
        setButtonsEnabled(true);
        
        ui->resultsText->append("File selected: " + selectedFilePath);
        ui->resultsText->append("File size: " + Utility::formatFileSize(Utility::getFileSize(selectedFilePath)));
        ui->resultsText->append("---");
    }
}

void MainWindow::on_compressButton_clicked()
{
    if (selectedFilePath.isEmpty()) {
        showError("Please select a file first");
        return;
    }
    
    // Get selected algorithm from combo box
    CompressionAlgorithm algorithm;
    if (ui->algorithmComboBox->currentIndex() == 0) {
        algorithm = CompressionAlgorithm::HUFFMAN;
    } else {
        algorithm = CompressionAlgorithm::RUN_LENGTH;
    }
    
    ui->progressBar->setValue(0);
    ui->progressLabel->setText("Compressing...");
    setButtonsEnabled(false);
    
    ui->resultsText->append("Starting compression with " + 
                           CompressionManager::algorithmToString(algorithm) + "...");
    
    compressionManager->compressFile(selectedFilePath, algorithm);
}

void MainWindow::on_decompressButton_clicked()
{
    if (selectedFilePath.isEmpty()) {
        showError("Please select a file first");
        return;
    }
    
    ui->progressBar->setValue(0);
    ui->progressLabel->setText("Decompressing...");
    setButtonsEnabled(false);
    
    ui->resultsText->append("Starting decompression...");
    
    compressionManager->decompressFile(selectedFilePath);
}

void MainWindow::on_viewReportsButton_clicked()
{
    QString reportsDir = ReportGenerator::getReportsDirectory();
    if (Utility::fileExists(reportsDir)) {
        QDesktopServices::openUrl(QUrl::fromLocalFile(reportsDir));
        ui->resultsText->append("Opened reports directory: " + reportsDir);
    } else {
        showError("Reports directory does not exist yet. Run some operations first.");
    }
}

void MainWindow::on_clearButton_clicked()
{
    clearResults();
}

void MainWindow::on_actionSelect_File_triggered()
{
    on_selectFileButton_clicked();
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_actionAbout_triggered()
{
    showAboutDialog();
}

void MainWindow::handleProgressUpdated(int percentage)
{
    ui->progressBar->setValue(percentage);
}

void MainWindow::handleOperationCompleted(const CompressionResult& result)
{
    ui->progressBar->setValue(100);
    ui->progressLabel->setText("Completed");
    setButtonsEnabled(true);
    
    updateResults(result);
}

void MainWindow::updateFileInfo()
{
    ui->fileLabel->setText(selectedFilePath);
    
    QString fileInfo = "File: " + Utility::getFileBaseName(selectedFilePath);
    fileInfo += " | Size: " + Utility::formatFileSize(Utility::getFileSize(selectedFilePath));
    
    // Update status bar
    ui->statusBar->showMessage(fileInfo);
    
    // Update window title with current file
    setWindowTitle("File Compression Tool - " + Utility::getFileBaseName(selectedFilePath));
}

void MainWindow::updateResults(const CompressionResult& result)
{
    if (result.success) {
        ui->resultsText->append("✓ " + result.message);
        ui->resultsText->append("Output file: " + result.outputFile);
        
        if (result.operationType == "Compression") {
            ui->resultsText->append(QString("Original size: %1 | Compressed size: %2")
                                   .arg(Utility::formatFileSize(result.originalSize))
                                   .arg(Utility::formatFileSize(result.compressedSize)));
            ui->resultsText->append(QString("Space saved: %1%")
                                   .arg(100.0 - result.compressionRatio, 0, 'f', 2));
        } else {
            ui->resultsText->append(QString("Compressed size: %1 | Decompressed size: %2")
                                   .arg(Utility::formatFileSize(result.compressedSize))
                                   .arg(Utility::formatFileSize(result.originalSize)));
        }
        
        ui->resultsText->append("Execution time: " + QString::number(result.executionTime) + " ms");
        ui->resultsText->append("Report generated in: " + ReportGenerator::getLastReportPath());
        ui->resultsText->append("---");
        
        showSuccess(result.operationType + " completed successfully!");
        
        // Update status bar
        ui->statusBar->showMessage(result.operationType + " completed successfully!");
    } else {
        ui->resultsText->append("✗ " + result.message);
        ui->resultsText->append("---");
        showError(result.operationType + " failed!");
        
        // Update status bar
        ui->statusBar->showMessage(result.operationType + " failed!");
    }
}

void MainWindow::clearResults()
{
    ui->resultsText->clear();
    ui->progressBar->setValue(0);
    ui->progressLabel->setText("Ready");
    ui->statusBar->showMessage("Ready");
    
    ui->resultsText->append("File Compression Tool - DAA Project");
    ui->resultsText->append("===================================");
    ui->resultsText->append("Results cleared. Select a file to start.");
    ui->resultsText->append("");
}

void MainWindow::showError(const QString& message)
{
    QMessageBox::critical(this, "Error", message);
}

void MainWindow::showSuccess(const QString& message)
{
    QMessageBox::information(this, "Success", message);
}

void MainWindow::setButtonsEnabled(bool enabled)
{
    ui->compressButton->setEnabled(enabled);
    ui->decompressButton->setEnabled(enabled);
    ui->algorithmComboBox->setEnabled(enabled);
    
    // Visual feedback
    if (enabled) {
        ui->compressButton->setStyleSheet("QPushButton { background-color: #2a82da; color: white; font-weight: bold; font-size: 11pt; }");
        ui->decompressButton->setStyleSheet("QPushButton { background-color: #2a82da; color: white; font-weight: bold; font-size: 11pt; }");
    } else {
        ui->compressButton->setStyleSheet("QPushButton { background-color: #555; color: #888; }");
        ui->decompressButton->setStyleSheet("QPushButton { background-color: #555; color: #888; }");
    }
}

void MainWindow::showAboutDialog()
{
    QMessageBox::about(this, "About File Compression Tool",
        "<h3>File Compression Tool</h3>"
        "<p><b>Version 1.0</b></p>"
        "<p>Data Structures and Algorithms (DAA) Course Project</p>"
        "<p>This tool implements lossless compression algorithms:</p>"
        "<ul>"
        "<li>Huffman Coding - Optimal prefix coding for lossless compression</li>"
        "<li>Run-Length Encoding (RLE) - Efficient for repetitive data</li>"
        "</ul>"
        "<p><b>Features:</b></p>"
        "<ul>"
        "<li>Compression and decompression operations</li>"
        "<li>Compression ratio calculation</li>"
        "<li>Execution time measurement</li>"
        "<li>Detailed operation reports</li>"
        "<li>Professional GUI with dark theme</li>"
        "</ul>"
        "<hr>"
        "<p>Built with Qt 6 and C++17</p>"
        "<p>Project demonstrates core DAA concepts including:</p>"
        "<ul>"
        "<li>Priority queues and binary trees (Huffman)</li>"
        "<li>Data encoding and decoding</li>"
        "<li>File I/O operations</li>"
        "<li>Algorithm analysis and metrics</li>"
        "</ul>");
}