//
//  Main.cpp
//  opencv_test
//
//  Created by Kyuri Kim on 2021/02/20.
//
//#include "Main.hpp"
#include <iostream>
#include <opencv4/opencv2/opencv.hpp>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <utility>
using namespace std;
using namespace cv;


int main(void)
{
    Mat gt = imread("/Users/kyurikim/Desktop/code/_c++/src/01.Dice_Score/gt.jpg");
    Mat gt_resize;
    resize(gt, gt_resize, Size(512, 512));
    gt_resize = gt_resize / 255;
    imshow("gt", gt_resize*255);
    cout << "==========gt==========" << "\n";
    cout << "resizing 이전" << gt.size() << "\n";
    cout << "resizing 후" << gt_resize.size() << "\n";

    Mat pred = imread("/Users/kyurikim/Desktop/code/_c++/src/01.Dice_Score/pred.jpg");
    Mat pred_resize;
    resize(pred, pred_resize, Size(512, 512));
    pred_resize = pred_resize / 255;
    imshow("pred", pred_resize*255);
    cout << "=========pred=========" << "\n";
    cout << "resizing 이전" << pred.size() << "\n";
    cout << "resizing 후" << pred_resize.size() << "\n";


    /*
        겹친구간 구하기 (Multiply)
     */
    Mat intersection;
    multiply(gt_resize, pred_resize, intersection);
    imshow("intersection", intersection*255);

    double overlap = gt_resize.dot(pred_resize);
    Scalar dsc = 2 * overlap / (sum(gt_resize) + sum(pred_resize));
    cout << "Multiply DSC:" << dsc << "\n";

    
    /*
        겹친구간 구하기 (Flatten)
     */
    double overlap_f = 0;
    Scalar union_sum = 0;
    for(int i = 0; i < gt_resize.rows; i++){

        const double* Mi = gt_resize.ptr<double>(i);  //gt pointer
        const double* Ni = pred_resize.ptr<double>(i);  //pred pointer
        for(int j=0;j<gt_resize.cols;j++){
            overlap_f += Mi[j]*Ni[j];
            union_sum += (sum(Mi[j]) + sum(Ni[j]));
        }
    }
    cout << "Flatten DSC:" << 2 * overlap/union_sum << "\n";

    waitKey();
    return 0;
}
