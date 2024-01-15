#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include <QDialog>
#include <QGraphicsScene>
#include <QImage>
#include <QGraphicsView>
#include <QSize>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>

using namespace cv;

/* 基于OpenCV的图像处理算子封装，主要包括如下几种情况:
 * 1. 图像预处理/图像锐化(image sharpening)
 * - 灰度处理(Gray())
 * - 灰度直方图
 * - 灰度均衡
 * - 梯度锐化
 * - USM锐化增强算法(Unsharpen Mask)
 * - 拉普拉斯锐化
 * 2. 滤波
 * - 均值滤波
 * - 中值滤波
 * - 边窗滤波
 * - 形态学滤波
 * - 高斯滤波
 * 3. 添加噪声
 * - 椒盐噪声
 * - 高斯噪声
 * 4. 边缘检测
 * - Roberts算子
 * - Sobel算子
 * - Laplace算子
 * - Prewitt算子
 * - Canny算子
 * - Krisch算子
 * 5.特征明显操作
 * - LBP
 * - 直方图检测
 * - 模板匹配
 * - 颜色匹配
 * - Gabor滤波
 * 6. 特征提取
 * - SIFT算法
 * - ORB算法
 * - 坐标点SVM
 * - Haar算法
 * 7. 图像变换
 * - 仿射变换
 * - 透视变换
 * 8. 背景处理
 * - 实现阈值分割
 * - OSTU和Kittler静态阈值分割
 * - 帧间差分和高斯混合背景
 * 9. 摄像标定
 * - 摄像机标定
 * - 立体匹配
*/
class ImageProcessing
{
public:
    ImageProcessing();
    ~ImageProcessing();

    // 灰度化
    QImage Gray(QImage &image);
    // 均值滤波
    QImage MeanFilter(QImage &image);
    // 边缘检测
    QImage EdgeDetection(QImage &image);
    // 伽马变换
    QImage GammaTransform(QImage &image);
    // 亮度调整
    void Dimming(int value);
    // Canny算子
    QImage Canny(QImage &image);
};

#endif // IMAGEPROCESSING_H
