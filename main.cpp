#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

#define BLOCK 60

int main(int argc, char **argv) {
    if (argc <= 1) {
        fprintf(stderr, "Error: missing image file\n");
        return 1;
    }
    string image_file = argv[1];

    cout << "Processing " << image_file << std::endl;
    Mat frame = imread(image_file, IMREAD_GRAYSCALE);

    int cx = frame.cols/2;
    int cy = frame.rows/2;

    // Go float
    Mat fImage;
    frame.convertTo(fImage, CV_32F);

    // FFT
    cout << "Direct transform...\n";
    Mat fourierTransform;
    dft(fImage, fourierTransform, DFT_SCALE|DFT_COMPLEX_OUTPUT);

    //center low frequencies in the middle
    //by shuffling the quadrants.
    Mat q0(fourierTransform, Rect(0, 0, cx, cy));       // Top-Left - Create a ROI per quadrant
    Mat q1(fourierTransform, Rect(cx, 0, cx, cy));      // Top-Right
    Mat q2(fourierTransform, Rect(0, cy, cx, cy));      // Bottom-Left
    Mat q3(fourierTransform, Rect(cx, cy, cx, cy));     // Bottom-Right

    Mat tmp;                                            // swap quadrants (Top-Left with Bottom-Right)
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);

    q1.copyTo(tmp);                                     // swap quadrant (Top-Right with Bottom-Left)
    q2.copyTo(q1);
    tmp.copyTo(q2);

    // Block the low frequencies
    // #define BLOCK could also be a argument on the command line of course
    fourierTransform(Rect(cx-BLOCK,cy-BLOCK,2*BLOCK,2*BLOCK)).setTo(0);

    //shuffle the quadrants to their original position
    Mat orgFFT;
    fourierTransform.copyTo(orgFFT);
    Mat p0(orgFFT, Rect(0, 0, cx, cy));       // Top-Left - Create a ROI per quadrant
    Mat p1(orgFFT, Rect(cx, 0, cx, cy));      // Top-Right
    Mat p2(orgFFT, Rect(0, cy, cx, cy));      // Bottom-Left
    Mat p3(orgFFT, Rect(cx, cy, cx, cy));     // Bottom-Right

    p0.copyTo(tmp);
    p3.copyTo(p0);
    tmp.copyTo(p3);

    p1.copyTo(tmp);                                     // swap quadrant (Top-Right with Bottom-Left)
    p2.copyTo(p1);
    tmp.copyTo(p2);

    // IFFT
    cout << "Inverse transform...\n";
    Mat invFFT;
    dft(orgFFT, invFFT, DFT_INVERSE|DFT_REAL_OUTPUT);

    //img_fft = 20*numpy.log(numpy.abs(img_fft))
    Mat logFFT;
    cv::abs(invFFT);
    cv::log(invFFT,logFFT);
    logFFT *= 20;

    //result = numpy.mean(img_fft)
    cv::Scalar result= cv::mean(logFFT);
    cout << "Result : "<< result.val[0] << endl;

    // show if you like
    Mat finalImage;
    logFFT.convertTo(finalImage, CV_8U);    // Back to 8-bits
    imshow("Input", frame);
    imshow("Result", finalImage);
    cv::waitKey();
    // end show if you like

    return 0;
}
