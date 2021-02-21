#include <iostream>
#include <opencv2/opencv.hpp>
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
	/*
		원래대로면 gt, pred의 크기가 서로 같겠지만, 
		지금은 그냥 아무 이미지나 두 장 가져온거라 둘다 같은 사이즈로 resizing 한 것.
		이 김에 resizing하는 방법도 보면 좋잖아여 ㅎㅎ
	*/

	Mat gt = imread("gt.jpg");
	Mat gt_resize;
	resize(gt, gt_resize, Size(512, 512));
	gt_resize = gt_resize / 255;
	imshow("gt", gt_resize*255);
	cout << "==========gt==========" << "\n";
	cout << "resizing 이전." << gt.size() << "\n";
	cout << "resizing 후" << gt_resize.size() << "\n";

	Mat pred = imread("pred.jpg");
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
	Mat intersection;
	multiply(gt_resize, pred_resize, intersection);
	imshow("intersection", intersection*255);

	double overlap = gt_resize.dot(pred_resize);
	
	Scalar dsc = 2 * overlap / (sum(gt_resize) + sum(pred_resize));

	cout << "======dsc======" << "\n";
	cout << dsc;
	
	waitKey();
	return 0;
}