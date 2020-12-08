#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

#include <opencv2/opencv.hpp>

#include "cmdline.h"

using namespace cv;
using namespace std;

cmdline::parser p;

int main(int argc, char* argv[]) {

	p.add<int>("camno", 'c', "Camera Number", false, 0);
	p.add<string>("device", 0, "Capture Device", false, "");
	p.add("help", 0, "Print help");
	p.parse_check(argc, argv);

	if (p.exist("help")){
		cout << p.error_full() << p.usage();
		exit(0);
	}

	cv::VideoCapture cap;
	if (p.exist("device")){
		cap.open(p.get<string>("device"));
	} else {
		cap.open(p.get<int>("camno"));
	};
	if (!cap.isOpened()){
		cout << "Camera Open Error" << endl;
		exit(1);
	};

	cv::Mat frame;				// 元画像
	cv::Mat frame_gray;		// 処理用(Gray)
	while(cap.read(frame)){
		const int key = cv::waitKey(1);
		if(key == 'q') break;
		if(key == 's') cv::imwrite("img.png", frame);
		cvtColor(frame, frame_gray, COLOR_RGB2GRAY);
		cv::imshow("win", frame);
	}
	cv::destroyAllWindows();
}

