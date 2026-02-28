# RealTimeBeautyFilter ✨
Real-time image enhancement and compression using smart filters for skin smoothing, brightness, and tone adjustment.


Enhance and compress images in real-time using a smart pipeline for skin smoothing, brightness adjustment, and skin tone enhancement. Works with live webcam input and supports image compression via Run-Length Encoding (RLE).

## Features
- **Live Image Enhancement:** Applies Gaussian blur, histogram equalization, and skin-tone enhancement for smoother and brighter skin.
- **Real-Time Webcam Feed:** Compare original and enhanced frames side by side.
- **Skin Tone Adjustment:** Adds warmth and vibrancy to skin while preserving natural colors.
- **Image Compression:** Analyze redundancy and compress images using Run-Length Encoding (RLE).
- **Metrics & Analysis:** Calculates compression ratio, redundancy, and efficiency of RLE.

## Technical Highlights
- **Language & Library:** Python with OpenCV
- **Pipeline Steps:** Gaussian smoothing → Histogram Equalization → Skin Tone Enhancement
- **Compression:** Run-Length Encoding (grayscale & color images)
- **Output:** Enhanced live video feed, saved images, and compression statistics

## Usage
1. Run the script.
2. Allow webcam access.
3. View the original and enhanced video feed side by side.
4. Optionally, compress images and check metrics.

## Tools 
- **OpenCV:** Real-time image processing
