#include <QApplication>
#include <QStyle>
#include <QStyleFactory>
#include <QPalette>
#include "MainWindow.h"

void setDarkTheme(QApplication& app) {
    app.setStyle(QStyleFactory::create("Fusion"));
    
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(25, 25, 25));
    darkPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);
    
    app.setPalette(darkPalette);
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    // Application properties
    app.setApplicationName("File Compression Tool");
    app.setApplicationVersion("1.0");
    app.setOrganizationName("DAA Project");
    app.setApplicationDisplayName("File Compression Tool - Huffman & RLE");
    
    // Set dark theme
    setDarkTheme(app);
    
    MainWindow window;
    window.setWindowTitle("File Compression Tool - DAA Project");
    window.show();
    
    return app.exec();
}