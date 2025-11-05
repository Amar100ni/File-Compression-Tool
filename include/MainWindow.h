#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "CompressionManager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // UI button slots
    void on_selectFileButton_clicked();
    void on_compressButton_clicked();
    void on_decompressButton_clicked();
    void on_viewReportsButton_clicked();
    void on_clearButton_clicked();
    
    // Menu action slots
    void on_actionSelect_File_triggered();
    void on_actionExit_triggered();
    void on_actionAbout_triggered();
    
    // Compression manager slots
    void handleProgressUpdated(int percentage);
    void handleOperationCompleted(const CompressionResult& result);

private:
    Ui::MainWindow *ui;
    CompressionManager *compressionManager;
    QString selectedFilePath;
    
    void setupConnections();
    void updateFileInfo();
    void updateResults(const CompressionResult& result);
    void clearResults();
    void showError(const QString& message);
    void showSuccess(const QString& message);
    void setButtonsEnabled(bool enabled);
    void showAboutDialog();
};

#endif