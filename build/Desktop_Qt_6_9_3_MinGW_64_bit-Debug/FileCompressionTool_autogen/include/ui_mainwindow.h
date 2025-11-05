/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionSelect_File;
    QAction *actionExit;
    QAction *actionAbout;
    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QGroupBox *fileGroup;
    QHBoxLayout *fileLayout;
    QLabel *fileLabel;
    QPushButton *selectFileButton;
    QGroupBox *algorithmGroup;
    QHBoxLayout *algorithmLayout;
    QLabel *algorithmLabel;
    QComboBox *algorithmComboBox;
    QSpacerItem *horizontalSpacer;
    QGroupBox *operationGroup;
    QHBoxLayout *operationLayout;
    QPushButton *compressButton;
    QPushButton *decompressButton;
    QPushButton *viewReportsButton;
    QPushButton *clearButton;
    QGroupBox *progressGroup;
    QVBoxLayout *progressLayout;
    QProgressBar *progressBar;
    QLabel *progressLabel;
    QGroupBox *resultsGroup;
    QVBoxLayout *resultsLayout;
    QTextEdit *resultsText;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuHelp;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 650);
        MainWindow->setStyleSheet(QString::fromUtf8("QMainWindow {\n"
"    background-color: #2b2b2b;\n"
"    color: #ffffff;\n"
"}\n"
"QGroupBox {\n"
"    color: #ffffff;\n"
"    font-weight: bold;\n"
"    border: 2px solid #555555;\n"
"    border-radius: 8px;\n"
"    margin-top: 1ex;\n"
"    padding-top: 10px;\n"
"}\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top center;\n"
"    padding: 0 8px;\n"
"    background-color: #2b2b2b;\n"
"    color: #ffffff;\n"
"}\n"
"QPushButton {\n"
"    background-color: #404040;\n"
"    color: white;\n"
"    border: 1px solid #555555;\n"
"    border-radius: 5px;\n"
"    padding: 8px 16px;\n"
"    font-weight: bold;\n"
"    min-height: 20px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #4a4a4a;\n"
"    border: 1px solid #666666;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #2a82da;\n"
"}\n"
"QPushButton:disabled {\n"
"    background-color: #333333;\n"
"    color: #666666;\n"
"}\n"
"QProgressBar {\n"
"    border: 1px solid #555555;\n"
"    border-radius: 5px;\n"
" "
                        "   text-align: center;\n"
"    color: white;\n"
"    background-color: #353535;\n"
"}\n"
"QProgressBar::chunk {\n"
"    background-color: #2a82da;\n"
"    border-radius: 4px;\n"
"}\n"
"QComboBox {\n"
"    background-color: #353535;\n"
"    color: white;\n"
"    border: 1px solid #555555;\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"    min-height: 25px;\n"
"}\n"
"QComboBox:disabled {\n"
"    background-color: #2a2a2a;\n"
"    color: #666666;\n"
"}\n"
"QTextEdit {\n"
"    background-color: #1a1a1a;\n"
"    color: #00ff00;\n"
"    border: 1px solid #555555;\n"
"    border-radius: 5px;\n"
"    font-family: 'Courier New', monospace;\n"
"    font-size: 10pt;\n"
"    selection-background-color: #2a82da;\n"
"}\n"
"QLabel {\n"
"    color: #ffffff;\n"
"}\n"
""));
        actionSelect_File = new QAction(MainWindow);
        actionSelect_File->setObjectName("actionSelect_File");
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName("actionExit");
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName("actionAbout");
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName("centralWidget");
        mainLayout = new QVBoxLayout(centralWidget);
        mainLayout->setSpacing(15);
        mainLayout->setObjectName("mainLayout");
        mainLayout->setContentsMargins(20, 20, 20, 20);
        fileGroup = new QGroupBox(centralWidget);
        fileGroup->setObjectName("fileGroup");
        fileLayout = new QHBoxLayout(fileGroup);
        fileLayout->setSpacing(10);
        fileLayout->setObjectName("fileLayout");
        fileLabel = new QLabel(fileGroup);
        fileLabel->setObjectName("fileLabel");
        fileLabel->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    padding: 8px;\n"
"    border: 1px solid #555555;\n"
"    border-radius: 4px;\n"
"    background-color: #353535;\n"
"    color: #cccccc;\n"
"}"));
        fileLabel->setAlignment(Qt::AlignCenter);
        fileLabel->setMinimumSize(QSize(0, 30));

        fileLayout->addWidget(fileLabel);

        selectFileButton = new QPushButton(fileGroup);
        selectFileButton->setObjectName("selectFileButton");
        selectFileButton->setMinimumSize(QSize(0, 35));
        selectFileButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #2a82da;\n"
"    color: white;\n"
"    font-weight: bold;\n"
"    font-size: 10pt;\n"
"}"));

        fileLayout->addWidget(selectFileButton);


        mainLayout->addWidget(fileGroup);

        algorithmGroup = new QGroupBox(centralWidget);
        algorithmGroup->setObjectName("algorithmGroup");
        algorithmLayout = new QHBoxLayout(algorithmGroup);
        algorithmLayout->setSpacing(15);
        algorithmLayout->setObjectName("algorithmLayout");
        algorithmLabel = new QLabel(algorithmGroup);
        algorithmLabel->setObjectName("algorithmLabel");
        QFont font;
        font.setBold(true);
        algorithmLabel->setFont(font);

        algorithmLayout->addWidget(algorithmLabel);

        algorithmComboBox = new QComboBox(algorithmGroup);
        algorithmComboBox->addItem(QString());
        algorithmComboBox->addItem(QString());
        algorithmComboBox->setObjectName("algorithmComboBox");
        algorithmComboBox->setMinimumSize(QSize(0, 35));
        QFont font1;
        font1.setPointSize(10);
        algorithmComboBox->setFont(font1);

        algorithmLayout->addWidget(algorithmComboBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        algorithmLayout->addItem(horizontalSpacer);


        mainLayout->addWidget(algorithmGroup);

        operationGroup = new QGroupBox(centralWidget);
        operationGroup->setObjectName("operationGroup");
        operationLayout = new QHBoxLayout(operationGroup);
        operationLayout->setSpacing(10);
        operationLayout->setObjectName("operationLayout");
        compressButton = new QPushButton(operationGroup);
        compressButton->setObjectName("compressButton");
        compressButton->setMinimumSize(QSize(0, 40));
        compressButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #2a82da;\n"
"    color: white;\n"
"    font-weight: bold;\n"
"    font-size: 11pt;\n"
"}"));

        operationLayout->addWidget(compressButton);

        decompressButton = new QPushButton(operationGroup);
        decompressButton->setObjectName("decompressButton");
        decompressButton->setMinimumSize(QSize(0, 40));
        decompressButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #2a82da;\n"
"    color: white;\n"
"    font-weight: bold;\n"
"    font-size: 11pt;\n"
"}"));

        operationLayout->addWidget(decompressButton);

        viewReportsButton = new QPushButton(operationGroup);
        viewReportsButton->setObjectName("viewReportsButton");
        viewReportsButton->setMinimumSize(QSize(0, 40));
        viewReportsButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #5a5a5a;\n"
"    color: white;\n"
"    font-size: 10pt;\n"
"}"));

        operationLayout->addWidget(viewReportsButton);

        clearButton = new QPushButton(operationGroup);
        clearButton->setObjectName("clearButton");
        clearButton->setMinimumSize(QSize(0, 40));
        clearButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #da2a2a;\n"
"    color: white;\n"
"    font-size: 10pt;\n"
"}"));

        operationLayout->addWidget(clearButton);


        mainLayout->addWidget(operationGroup);

        progressGroup = new QGroupBox(centralWidget);
        progressGroup->setObjectName("progressGroup");
        progressLayout = new QVBoxLayout(progressGroup);
        progressLayout->setSpacing(10);
        progressLayout->setObjectName("progressLayout");
        progressBar = new QProgressBar(progressGroup);
        progressBar->setObjectName("progressBar");
        progressBar->setValue(0);
        progressBar->setMinimumSize(QSize(0, 25));
        progressBar->setAlignment(Qt::AlignCenter);

        progressLayout->addWidget(progressBar);

        progressLabel = new QLabel(progressGroup);
        progressLabel->setObjectName("progressLabel");
        progressLabel->setAlignment(Qt::AlignCenter);
        progressLabel->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    font-weight: bold;\n"
"    color: #cccccc;\n"
"}"));

        progressLayout->addWidget(progressLabel);


        mainLayout->addWidget(progressGroup);

        resultsGroup = new QGroupBox(centralWidget);
        resultsGroup->setObjectName("resultsGroup");
        resultsLayout = new QVBoxLayout(resultsGroup);
        resultsLayout->setObjectName("resultsLayout");
        resultsText = new QTextEdit(resultsGroup);
        resultsText->setObjectName("resultsText");
        resultsText->setMinimumSize(QSize(0, 200));
        resultsText->setStyleSheet(QString::fromUtf8("QTextEdit {\n"
"    background-color: #1a1a1a;\n"
"    color: #00ff00;\n"
"    font-family: 'Courier New';\n"
"    font-size: 10pt;\n"
"    border: 1px solid #444444;\n"
"    border-radius: 5px;\n"
"    padding: 8px;\n"
"}"));

        resultsLayout->addWidget(resultsText);


        mainLayout->addWidget(resultsGroup);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 800, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName("menuFile");
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName("menuHelp");
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName("statusBar");
        statusBar->setStyleSheet(QString::fromUtf8("QStatusBar {\n"
"    background-color: #353535;\n"
"    color: white;\n"
"}"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionSelect_File);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuHelp->addAction(actionAbout);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "File Compression Tool - DAA Project", nullptr));
        actionSelect_File->setText(QCoreApplication::translate("MainWindow", "Select File", nullptr));
#if QT_CONFIG(shortcut)
        actionSelect_File->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        actionExit->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
#if QT_CONFIG(shortcut)
        actionExit->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Q", nullptr));
#endif // QT_CONFIG(shortcut)
        actionAbout->setText(QCoreApplication::translate("MainWindow", "About", nullptr));
        fileGroup->setTitle(QCoreApplication::translate("MainWindow", "File Selection", nullptr));
        fileLabel->setText(QCoreApplication::translate("MainWindow", "No file selected", nullptr));
        selectFileButton->setText(QCoreApplication::translate("MainWindow", "Select File", nullptr));
        algorithmGroup->setTitle(QCoreApplication::translate("MainWindow", "Compression Algorithm", nullptr));
        algorithmLabel->setText(QCoreApplication::translate("MainWindow", "Select Algorithm:", nullptr));
        algorithmComboBox->setItemText(0, QCoreApplication::translate("MainWindow", "Huffman Coding", nullptr));
        algorithmComboBox->setItemText(1, QCoreApplication::translate("MainWindow", "Run-Length Encoding", nullptr));

        operationGroup->setTitle(QCoreApplication::translate("MainWindow", "Operations", nullptr));
        compressButton->setText(QCoreApplication::translate("MainWindow", "Compress", nullptr));
        decompressButton->setText(QCoreApplication::translate("MainWindow", "Decompress", nullptr));
        viewReportsButton->setText(QCoreApplication::translate("MainWindow", "View Reports", nullptr));
        clearButton->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        progressGroup->setTitle(QCoreApplication::translate("MainWindow", "Progress", nullptr));
        progressLabel->setText(QCoreApplication::translate("MainWindow", "Ready", nullptr));
        resultsGroup->setTitle(QCoreApplication::translate("MainWindow", "Results & Log", nullptr));
        resultsText->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Courier New'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" color:#00ff00;\">File Compression Tool - DAA Project</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" color:#00ff00;\">================================</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" color:#00ff00;\">Ready. Select a file to start compression or decompression.</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:12p"
                        "x; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"</body></html>", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("MainWindow", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
