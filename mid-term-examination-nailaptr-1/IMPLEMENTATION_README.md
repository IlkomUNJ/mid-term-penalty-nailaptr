# Computer Graphics Project - Milestone 1 & 2 Implementation

## Overview
This implementation provides a complete solution for analyzing images using sliding window technique with multiple window sizes (16×16, 32×32, 48×48, 64×64) to determine the optimal window size for content detection.

## Features Implemented

### 1. ImageAnalyzer Class
- **File**: `ImageAnalyzer.h` and `ImageAnalyzer.cpp`
- **Purpose**: Core analysis engine for window-based image analysis
- **Key Methods**:
  - `analyzeWindows(const QImage &image)`: Tests multiple window sizes
  - `findIdealWindowSize()`: Determines the best window size
  - `generateReportMd(const QString &filename)`: Creates detailed markdown report

### 2. Integration with DrawingCanvas
- **Modified Files**: `drawingcanvas.h`, `drawingcanvas.cpp`
- **New Method**: `analyzeImageWindows()` - Captures canvas and performs analysis
- **Button Integration**: Added "Analyze Windows" button to the main interface

### 3. Main Window Integration
- **Modified Files**: `mainwindow.h`, `mainwindow.cpp`
- **New Button**: "Analyze Windows" button connected to analysis functionality

## How to Use

### Method 1: Using the GUI Application
1. **Build and run** the Qt application
2. **Draw content** on the canvas using mouse clicks
3. **Click "Draw Lines"** to connect points with lines
4. **Click "Analyze Windows"** to perform window analysis
5. **Check console output** for analysis results
6. **Find "report.md"** file in the project directory for detailed report

### Method 2: Using the Test Program
1. **Compile the test program**:
   ```bash
   mkdir build_test
   cd build_test
   cmake -f ../CMakeLists_test.txt ..
   make
   ```
2. **Run the test**:
   ```bash
   ./TestAnalyzer
   ```
3. **Check "test_report.md"** for results

## Analysis Algorithm

### Window Detection Criteria
A window is considered "non-empty" if it meets both criteria:
1. **Brightness Threshold**: Average intensity > 30 (out of 255)
2. **Variance Threshold**: Color variance > 50

### Window Sizes Tested
- 16×16 pixels
- 32×32 pixels  
- 48×48 pixels
- 64×64 pixels

### Optimal Size Selection
The algorithm selects the window size that detects the **most non-empty windows**, indicating the best balance between:
- Detail detection (not missing content)
- Noise reduction (avoiding false positives)

## Output Files

### Console Output
```
Starting window analysis...
Image size: 400x300
Analyzing windows of size: 16x16
Window size 16x16: 45 non-empty windows out of 375 total
Analyzing windows of size: 32x32
Window size 32x32: 28 non-empty windows out of 96 total
...
Ideal window size: 16x16
Analysis complete! Report generated as 'report.md'
```

### Markdown Report (report.md)
The generated report includes:
- **Image Information**: Dimensions and pixel count
- **Analysis Parameters**: Thresholds and tested sizes
- **Results Table**: Detailed statistics for each window size
- **Optimal Size Analysis**: Reasoning for the chosen size
- **Comparison**: How other sizes performed
- **Conclusion**: Summary of findings

## Technical Details

### Dependencies
- Qt 6 (Widgets module)
- C++17 standard
- CMake 3.16+

### Key Classes
- **ImageAnalyzer**: Core analysis logic
- **DrawingCanvas**: Canvas with analysis integration
- **MainWindow**: GUI with analysis button

### Memory Management
- Proper RAII with destructors
- Smart pointer usage where appropriate
- Qt's parent-child widget system

## Compilation Notes

### For Qt Creator
1. Open the project in Qt Creator
2. The CMakeLists.txt has been updated to include new files
3. Build and run normally

### For Command Line
```bash
mkdir build
cd build
cmake ..
make
```

## Testing

The implementation includes comprehensive testing:
- **Unit testing** through the test program
- **Integration testing** through the GUI
- **Edge case handling** for empty images and invalid data
- **Console output** for debugging and verification

## Future Enhancements

Potential improvements for future milestones:
1. **Adaptive thresholds** based on image characteristics
2. **Additional window sizes** (8×8, 128×128, etc.)
3. **Different analysis metrics** (edge detection, texture analysis)
4. **Real-time analysis** with live preview
5. **Export functionality** for analysis results

## Troubleshooting

### Common Issues
1. **"Image is null"**: Ensure canvas has content before analysis
2. **No report generated**: Check file permissions in project directory
3. **Compilation errors**: Ensure Qt 6 is properly installed and configured

### Debug Information
- All analysis steps output to console
- Detailed logging in ImageAnalyzer class
- Error handling for edge cases

---

**Implementation Status**: ✅ Complete
**Milestone 1**: ✅ Window analysis with multiple sizes
**Milestone 2**: ✅ Optimal size determination and report generation
