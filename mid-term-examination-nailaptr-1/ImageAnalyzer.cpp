#include "ImageAnalyzer.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QDateTime>
#include <cmath>
#include <algorithm>

ImageAnalyzer::ImageAnalyzer()
    : m_brightnessThreshold(30.0)  // Pixels with intensity below this are considered "empty"
    , m_varianceThreshold(50.0)    // Minimum variance to consider window non-empty
{
    // Initialize test window sizes as specified in requirements
    m_testSizes = {16, 32, 48, 64};
}

ImageAnalyzer::~ImageAnalyzer()
{
}

void ImageAnalyzer::analyzeWindows(const QImage &image)
{
    if (image.isNull()) {
        qDebug() << "Error: Image is null or invalid";
        return;
    }
    
    m_analyzedImage = image;
    m_windowResults.clear();
    
    qDebug() << "Starting window analysis for image size:" << image.width() << "x" << image.height();
    
    // Test each window size
    for (int size : m_testSizes) {
        int nonEmptyCount = 0;
        int totalWindows = 0;
        
        qDebug() << "Analyzing windows of size:" << size << "x" << size;
        
        // Slide window across the image
        for (int y = 0; y <= image.height() - size; y += size) {
            for (int x = 0; x <= image.width() - size; x += size) {
                QRect window(x, y, size, size);
                totalWindows++;
                
                if (isWindowNonEmpty(image, window)) {
                    nonEmptyCount++;
                }
            }
        }
        
        m_windowResults[size] = nonEmptyCount;
        qDebug() << "Window size" << size << "x" << size << ":" << nonEmptyCount << "non-empty windows out of" << totalWindows << "total";
    }
}

bool ImageAnalyzer::isWindowNonEmpty(const QImage &image, const QRect &window)
{
    // Calculate average intensity
    double avgIntensity = calculateAverageIntensity(image, window);
    
    // Calculate color variance
    double variance = calculateColorVariance(image, window);
    
    // A window is considered non-empty if:
    // 1. Average intensity is above threshold (not too dark)
    // 2. Color variance is above threshold (has some variation)
    return (avgIntensity > m_brightnessThreshold) && (variance > m_varianceThreshold);
}

double ImageAnalyzer::calculateAverageIntensity(const QImage &image, const QRect &window)
{
    double totalIntensity = 0.0;
    int pixelCount = 0;
    
    for (int y = window.top(); y < window.bottom(); ++y) {
        for (int x = window.left(); x < window.right(); ++x) {
            if (x >= 0 && x < image.width() && y >= 0 && y < image.height()) {
                QRgb pixel = image.pixel(x, y);
                
                // Convert RGB to grayscale intensity using standard formula
                int r = qRed(pixel);
                int g = qGreen(pixel);
                int b = qBlue(pixel);
                int intensity = static_cast<int>(0.299 * r + 0.587 * g + 0.114 * b);
                
                totalIntensity += intensity;
                pixelCount++;
            }
        }
    }
    
    return pixelCount > 0 ? totalIntensity / pixelCount : 0.0;
}

double ImageAnalyzer::calculateColorVariance(const QImage &image, const QRect &window)
{
    double avgIntensity = calculateAverageIntensity(image, window);
    double variance = 0.0;
    int pixelCount = 0;
    
    for (int y = window.top(); y < window.bottom(); ++y) {
        for (int x = window.left(); x < window.right(); ++x) {
            if (x >= 0 && x < image.width() && y >= 0 && y < image.height()) {
                QRgb pixel = image.pixel(x, y);
                
                // Convert RGB to grayscale intensity
                int r = qRed(pixel);
                int g = qGreen(pixel);
                int b = qBlue(pixel);
                int intensity = static_cast<int>(0.299 * r + 0.587 * g + 0.114 * b);
                
                double diff = intensity - avgIntensity;
                variance += diff * diff;
                pixelCount++;
            }
        }
    }
    
    return pixelCount > 0 ? variance / pixelCount : 0.0;
}

int ImageAnalyzer::findIdealWindowSize()
{
    if (m_windowResults.isEmpty()) {
        qDebug() << "No analysis results available. Run analyzeWindows() first.";
        return -1;
    }
    
    // Find the window size with the most non-empty windows
    // This indicates the best balance between detail detection and noise reduction
    int bestSize = -1;
    int maxNonEmpty = -1;
    
    for (auto it = m_windowResults.begin(); it != m_windowResults.end(); ++it) {
        if (it.value() > maxNonEmpty) {
            maxNonEmpty = it.value();
            bestSize = it.key();
        }
    }
    
    qDebug() << "Ideal window size determined:" << bestSize << "x" << bestSize << "with" << maxNonEmpty << "non-empty windows";
    return bestSize;
}

void ImageAnalyzer::generateReportMd(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Error: Could not create report file:" << filename;
        return;
    }
    
    QTextStream out(&file);
    
    // Write markdown report header
    out << "# Image Window Analysis Report\n\n";
    out << "**Generated on:** " << QDateTime::currentDateTime().toString() << "\n\n";
    
    // Image information
    out << "## Image Information\n\n";
    out << "- **Image Size:** " << m_analyzedImage.width() << " x " << m_analyzedImage.height() << " pixels\n";
    out << "- **Total Pixels:** " << (m_analyzedImage.width() * m_analyzedImage.height()) << "\n\n";
    
    // Analysis parameters
    out << "## Analysis Parameters\n\n";
    out << "- **Brightness Threshold:** " << m_brightnessThreshold << "\n";
    out << "- **Variance Threshold:** " << m_varianceThreshold << "\n";
    out << "- **Tested Window Sizes:** ";
    for (int i = 0; i < m_testSizes.size(); ++i) {
        out << m_testSizes[i] << "x" << m_testSizes[i];
        if (i < m_testSizes.size() - 1) out << ", ";
    }
    out << "\n\n";
    
    // Results table
    out << "## Analysis Results\n\n";
    out << "| Window Size | Non-Empty Windows | Total Windows | Percentage |\n";
    out << "|-------------|-------------------|---------------|------------|\n";
    
    for (int size : m_testSizes) {
        int nonEmpty = m_windowResults.value(size, 0);
        int totalWindows = ((m_analyzedImage.width() / size) * (m_analyzedImage.height() / size));
        double percentage = totalWindows > 0 ? (double(nonEmpty) / totalWindows) * 100.0 : 0.0;
        
        out << "| " << size << "x" << size << " | " << nonEmpty << " | " << totalWindows 
            << " | " << QString::number(percentage, 'f', 2) << "% |\n";
    }
    
    // Ideal window size analysis
    int idealSize = findIdealWindowSize();
    out << "\n## Optimal Window Size Analysis\n\n";
    
    if (idealSize > 0) {
        int idealNonEmpty = m_windowResults.value(idealSize, 0);
        int idealTotal = ((m_analyzedImage.width() / idealSize) * (m_analyzedImage.height() / idealSize));
        double idealPercentage = idealTotal > 0 ? (double(idealNonEmpty) / idealTotal) * 100.0 : 0.0;
        
        out << "**Chosen Ideal Window Size:** " << idealSize << "x" << idealSize << "\n\n";
        out << "**Reasoning:**\n";
        out << "- This window size detected " << idealNonEmpty << " non-empty windows out of " << idealTotal << " total windows\n";
        out << "- This represents " << QString::number(idealPercentage, 'f', 2) << "% of all windows\n";
        out << "- This size provides the best balance between detail detection and noise reduction\n\n";
        
        // Analysis of why this size is optimal
        out << "**Why this size is optimal:**\n";
        out << "1. **Maximum Detection:** This window size identified the most non-empty regions\n";
        out << "2. **Balanced Granularity:** Not too small (avoiding noise) and not too large (avoiding missed details)\n";
        out << "3. **Computational Efficiency:** Provides good coverage while maintaining reasonable processing requirements\n";
        
        // Compare with other sizes
        out << "\n**Comparison with other sizes:**\n";
        for (int size : m_testSizes) {
            if (size != idealSize) {
                int otherNonEmpty = m_windowResults.value(size, 0);
                out << "- " << size << "x" << size << ": " << otherNonEmpty << " non-empty windows ";
                if (otherNonEmpty < idealNonEmpty) {
                    out << "(detected " << (idealNonEmpty - otherNonEmpty) << " fewer regions)";
                } else {
                    out << "(detected " << (otherNonEmpty - idealNonEmpty) << " more regions)";
                }
                out << "\n";
            }
        }
    } else {
        out << "**Error:** Could not determine ideal window size. No analysis results available.\n";
    }
    
    out << "\n## Conclusion\n\n";
    out << "The window analysis successfully identified the optimal window size for this image. ";
    out << "The chosen size provides the best balance between detecting meaningful content ";
    out << "and avoiding false positives from noise or artifacts.\n\n";
    out << "---\n";
    out << "*Report generated by Computer Graphics Image Analyzer*";
    
    file.close();
    qDebug() << "Report generated successfully:" << filename;
}

int ImageAnalyzer::getNonEmptyWindowsCount(int windowSize) const
{
    return m_windowResults.value(windowSize, -1);
}

QMap<int, int> ImageAnalyzer::getAllResults() const
{
    return m_windowResults;
}
