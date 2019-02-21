
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <string>
#include "worldVector.h"
using namespace cv;
using namespace std;
Mat rvec, tvec, kamera, distcoeffs, T, R;

extern "C"
{
    int test(int x)
    {
        return x*x;
    }
    int ReadExtrinsics()
    {
        string path = "data/extrinsic.txt";
        FileStorage fs(path, FileStorage::READ);
        fs["rvec"] >> rvec;
        fs["tvec"] >> tvec;
        fs["K"] >> kamera;
        fs["D"] >> distcoeffs;
        fs["T"] >> T;
        fs["R"] >> R;
        fs.release();
        return 0;
    }

    int readParams()
    {
        ReadExtrinsics();
        return 0;
    }

    Mat undistortuv2world(Mat undistortuv)
    {
        cv::Mat C = cv::Mat::eye(3, 3, CV_64FC1);
        C.at<double>(0, 2) = -T.at<double>(0);
        C.at<double>(1, 2) = -T.at<double>(1);
        C.at<double>(2, 2) = -T.at<double>(2);
        Mat M = kamera * R * C;
        Mat xy;
        perspectiveTransform(undistortuv, xy, M.inv());
        return xy;
    }

    Mat uv2undistortuv(Mat uv)
    {
        Mat undistortuv;
        undistortPoints(uv, undistortuv, kamera, distcoeffs, noArray(), kamera);
        return undistortuv;
    }

    int uv2world(int u, int v, float *x, float *y)
    {
        Mat uv = Mat(1, 1, CV_32FC2);
        Mat undistortuv, xy;
        uv.at<Point2f>(0, 0) = Point2f(u, v);
        undistortuv = uv2undistortuv(uv);
        xy = undistortuv2world(undistortuv);
        *x = xy.at<float>(0, 0);
        *y = xy.at<float>(0, 1);
        return 0;
    }
}
