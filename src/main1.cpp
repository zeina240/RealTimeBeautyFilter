#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;
Mat applyGaussianSmoothing(const Mat &src)
{
    Mat smooth;
    GaussianBlur(src, smooth, Size(9, 9), 0); // Smooth skin
    return smooth;
}

Mat applyHistogramEqualization(const Mat &src)
{
    Mat ycrcb;
    cvtColor(src, ycrcb, COLOR_BGR2YCrCb);

    vector<Mat> channels;
    split(ycrcb, channels);

    equalizeHist(channels[0], channels[0]); // Only for brightness (Y channel)

    Mat equalized;
    merge(channels, equalized);
    cvtColor(equalized, equalized, COLOR_YCrCb2BGR);

    return equalized;
}
Mat enhanceSkinTone(const Mat &src)
{
    Mat ycrcb;
    cvtColor(src, ycrcb, COLOR_BGR2YCrCb);

    vector<Mat> channels;
    split(ycrcb, channels);
    channels[0] += 20;
    threshold(channels[0], channels[0], 255, 255, THRESH_TRUNC);
    channels[1] += 10;
    threshold(channels[1], channels[1], 255, 255, THRESH_TRUNC);

    Mat enhanced;
    merge(channels, enhanced);
    cvtColor(enhanced, enhanced, COLOR_YCrCb2BGR);

    return enhanced;
}
Mat processPipeline(const Mat &frame)
{
    Mat smoothed = applyGaussianSmoothing(frame);
    Mat equalized = applyHistogramEqualization(smoothed);
    Mat skinEnhanced = enhanceSkinTone(equalized);
    return skinEnhanced;
}
int main()
{
    VideoCapture cap(0);
    if (!cap.isOpened())
    {
        cout << "Error: Cannot open webcam\n";
        return -1;
    }

    bool savedFirstFrame = false;
    double fps = 0.0;
    int count = 0;
    double t0 = (double)getTickCount();

    while (true)
    {
        Mat frame;
        cap >> frame;
        if (frame.empty())
            break;

        Mat result = processPipeline(frame);
        if (!savedFirstFrame)
        {
            string savePath = "enhanced_frame.png";
            imwrite(savePath, result);
            cout << "Saved first frame to: " << savePath << endl;
            savedFirstFrame = true;
        }
        Mat combined;
        hconcat(frame, result, combined);
        count++;
        if (count % 10 == 0)
        {
            double t1 = (double)getTickCount();
            fps = 10.0 / ((t1 - t0) / getTickFrequency());
            t0 = t1;
        }

        putText(combined, "FPS: " + to_string((int)fps),
                Point(10, 30), FONT_HERSHEY_SIMPLEX, 0.8,
                Scalar(255, 255, 255), 2);

        imshow("Beauty Enhancement Pipeline", combined);

        char key = (char)waitKey(1);
        if (key == 27)
            break;
    }

    return 0;
}