#include <QApplication>
#include <QImage>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <iostream>
#include "ImageAnalyzer.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    // Create a test image with some content
    QImage testImage(400, 300, QImage::Format_RGB32);
    testImage.fill(Qt::white);
    
    // Draw some test content
    QPainter painter(&testImage);
    painter.setRenderHint(QPainter::Antialiasing);
    
    // Draw some lines and shapes
    QPen pen(Qt::black, 3);
    painter.setPen(pen);
    
    // Draw some lines
    painter.drawLine(50, 50, 200, 100);
    painter.drawLine(100, 150, 250, 200);
    painter.drawLine(300, 50, 350, 150);
    
    // Draw some rectangles
    painter.setBrush(QBrush(Qt::gray));
    painter.drawRect(50, 200, 80, 60);
    painter.drawRect(200, 50, 60, 80);
    
    // Draw some circles
    painter.setBrush(QBrush(Qt::darkGray));
    painter.drawEllipse(300, 200, 50, 50);
    
    painter.end();
    
    std::cout << "Test image created: " << testImage.width() << "x" << testImage.height() << std::endl;
    
    // Test the ImageAnalyzer
    ImageAnalyzer analyzer;
    
    std::cout << "\nStarting window analysis..." << std::endl;
    analyzer.analyzeWindows(testImage);
    
    std::cout << "\nFinding ideal window size..." << std::endl;
    int idealSize = analyzer.findIdealWindowSize();
    std::cout << "Ideal window size: " << idealSize << "x" << idealSize << std::endl;
    
    std::cout << "\nGenerating report..." << std::endl;
    analyzer.generateReportMd("test_report.md");
    
    std::cout << "\nAnalysis complete! Check 'test_report.md' for detailed results." << std::endl;
    
    return 0;
}
