#include <iostream>
#include <opencv2/opencv.hpp>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <utility>
#include <time.h>
using namespace std;
using namespace cv;

Scalar dice_score(Mat gt, Mat pred);


int main(void)
{
    /*
        원래대로면 gt, pred의 크기가 서로 같겠지만,
        지금은 그냥 아무 이미지나 두 장 가져온거라 둘다 같은 사이즈로 resizing 한 것.
        이 김에 resizing하는 방법도 보면 좋잖아여 ㅎㅎ
    */

    Mat gt = imread("/Users/k-now/workspace/OpenCV/OpenCV/image1.jpeg");
    Mat gt_resize;
    resize(gt, gt_resize, Size(512, 512));
    gt_resize = gt_resize / 255;
    imshow("gt", gt_resize*255);
    cout << "==========gt==========" << "\n";
    cout << "resizing 이전." << gt.size() << "\n";
    cout << "resizing 후" << gt_resize.size() << "\n";

    Mat pred = imread("/Users/k-now/workspace/OpenCV/OpenCV/image2.jpeg");
    Mat pred_resize;
    resize(pred, pred_resize, Size(512, 512));
    pred_resize = pred_resize / 255;
    imshow("pred", pred_resize*255);
    cout << "==========pred==========" << "\n";
    cout << "resizing 이전" << pred.size() << "\n";
    cout << "resizing 후" << pred_resize.size() << "\n";
    

    /*
        겹친구간 구하기 놀이.
    */
    clock_t start, end;
    
    Mat intersection;
    multiply(gt_resize, pred_resize, intersection);
    
    imshow("intersection", intersection*255);
    start = clock();
    double overlap = gt_resize.dot(pred_resize);
    
    Scalar dsc = 2 * overlap / (sum(gt_resize) + sum(pred_resize));
    end = clock();
    double result = (double)(end-start);
    cout << "======dsc======" << "\n";
    cout << "time : " << result << "\n";
    cout << dsc << "\n";
    
    dsc = dice_score(gt_resize, pred_resize);
    cout << "my dice : " << dsc[0] << "\n";

    waitKey();
    return 0;
}

Scalar dice_score(Mat gt, Mat pred)
{
    double overlap=0;
    Scalar union_sum=0;
    for (int i = 0; i<gt.cols; i++){
        overlap += gt.row(i).dot(pred.row(i));
        union_sum += (sum(gt.row(i)) + sum(pred.row(i)));
    }
    
    return 2 * overlap/union_sum;
}
