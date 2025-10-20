#ifndef IMAGEANALYZER_H
#define IMAGEANALYZER_H

#include <QImage>
#include <QString>
#include <QVector>
#include <QMap>
#include <QRect>

/**
 * @brief The ImageAnalyzer class analyzes images using sliding window technique
 * 
 * This class implements the window analysis functionality for Computer Graphics project.
 * It tests multiple window sizes and determines the optimal window size for image analysis.
 */
class ImageAnalyzer
{
public:
    /**
     * @brief Constructor
     */
    ImageAnalyzer();
    
    /**
     * @brief Destructor
     */
    ~ImageAnalyzer();
    
    /**
     * @brief Analyze the image using multiple window sizes
     * @param image The QImage to analyze
     */
    void analyzeWindows(const QImage &image);
    
    /**
     * @brief Find the ideal window size based on analysis results
     * @return The optimal window size
     */
    int findIdealWindowSize();
    
    /**
     * @brief Generate a markdown report with analysis results
     * @param filename The output filename (default: "report.md")
     */
    void generateReportMd(const QString &filename = "report.md");
    
    /**
     * @brief Get the analysis results for a specific window size
     * @param windowSize The window size to query
     * @return Number of non-empty windows for the given size
     */
    int getNonEmptyWindowsCount(int windowSize) const;
    
    /**
     * @brief Get all analysis results
     * @return Map of window sizes to non-empty window counts
     */
    QMap<int, int> getAllResults() const;

private:
    /**
     * @brief Check if a window contains significant content
     * @param image The image to analyze
     * @param window The window rectangle to check
     * @return True if the window is considered non-empty
     */
    bool isWindowNonEmpty(const QImage &image, const QRect &window);
    
    /**
     * @brief Calculate the average intensity of a window
     * @param image The image to analyze
     * @param window The window rectangle to analyze
     * @return Average intensity value (0-255)
     */
    double calculateAverageIntensity(const QImage &image, const QRect &window);
    
    /**
     * @brief Calculate the color variance of a window
     * @param image The image to analyze
     * @param window The window rectangle to analyze
     * @return Color variance value
     */
    double calculateColorVariance(const QImage &image, const QRect &window);
    
    // Member variables
    QMap<int, int> m_windowResults;  // Window size -> non-empty window count
    QVector<int> m_testSizes;        // Window sizes to test
    double m_brightnessThreshold;    // Threshold for considering a window non-empty
    double m_varianceThreshold;      // Threshold for color variance
    QImage m_analyzedImage;          // Store the analyzed image
};

#endif // IMAGEANALYZER_H
