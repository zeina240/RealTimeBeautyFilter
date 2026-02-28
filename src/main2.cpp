#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

vector<pair<uchar, int>> RLE_Compress_Channel(const Mat &channel)
{
    vector<pair<uchar, int>> compressed;
    for (int r = 0; r < channel.rows; r++)
    {
        const uchar *row = channel.ptr<uchar>(r);
        int count = 1;
        for (int c = 1; c < channel.cols; c++)
        {
            if (row[c] == row[c - 1])
                count++;
            else
            {
                compressed.push_back({row[c - 1], count});
                count = 1;
            }
        }
        compressed.push_back({row[channel.cols - 1], count});
    }
    return compressed;
}

int calculateRLESize(const vector<pair<uchar, int>> &data)
{
    return data.size() * (1 + 4);
}

int main()
{

    // string path = "C:\\Users\\MK\\OneDrive\\Pictures\\zzeina.png";//RBG IMAGE

    string path = "C:\\Users\\MK\\Downloads\\proimage.png"; // binary image

    Mat img = imread(path, IMREAD_UNCHANGED);

    if (img.empty())
    {
        cout << "Error: Cannot load image!\n";
        return -1;
    }

    int channels = img.channels();
    if (channels == 4)
    {
        Mat imgBGR;
        cvtColor(img, imgBGR, COLOR_BGRA2BGR);
        img = imgBGR;
        channels = 3;
    }

    cout << "Image loaded successfully.\n";

    int originalSize = img.rows * img.cols * channels * sizeof(uchar);

    int compressedSize = 0;

    if (channels == 1)
    {
        // Grayscale image
        vector<pair<uchar, int>> rle = RLE_Compress_Channel(img);
        compressedSize = calculateRLESize(rle);
    }
    else if (channels == 3)
    {
        // Color image (BGR)
        vector<Mat> bgr;
        split(img, bgr);
        for (int i = 0; i < 3; i++)
        {
            vector<pair<uchar, int>> rle = RLE_Compress_Channel(bgr[i]);
            compressedSize += calculateRLESize(rle);
        }
    }
    else
    {
        cout << "Unsupported number of channels: " << channels << endl;
        return -1;
    }

    double compressionRatio = (double)originalSize / compressedSize;
    double redundancy = 1.0 - (1.0 / compressionRatio);

    cout << "\n------- Compression Results -------\n";
    cout << "Original Size       : " << originalSize << " bytes\n";
    cout << "Compressed Size     : " << compressedSize << " bytes\n";
    cout << "Compression Ratio   : " << compressionRatio << endl;
    cout << "Redundancy (%)      : " << redundancy * 100 << "%\n";
    cout << "----------------------------------\n";

    return 0;
}
