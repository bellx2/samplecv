#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

#include <opencv2/opencv.hpp>
#include <glib.h>

#include "cmdline.h"

using namespace cv;
using namespace std;

cmdline::parser p;

GMainLoop *loop;
guint timer = 0;

static gboolean
on_timeout(gpointer data)
{
  guint *timer = (guint*) data;

  (*timer)++; /* Increase the timer */

  if ((*timer)%10 == 0) {
		cout << "...x" << endl;
  }
  return TRUE; /* FALSE removes the event source */
}

cv::Mat frame;

static gboolean
single_capture(gpointer data)
{
  cv::VideoCapture *cap = (cv::VideoCapture *)data;
	// cv::Mat frame;
	
	if(cap->read(frame)){
		// cv::imshow("win", frame);
		cv::imwrite("img.png", frame);
	};

	cout << ".x." << endl;

  return TRUE; /* FALSE removes the event source */
}

int main(int argc, char* argv[]) {

	p.add<int>("camno", 'c', "Camera Number", false, 1);
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

	g_timeout_add(200, single_capture, &cap);

	// guint timer = 0;	
  /* Call 'on_timeout()' every second */
  // g_timeout_add(1000, on_timeout, &timer);

  /* Start the main loop */
  loop = g_main_loop_new(NULL, FALSE);
  g_main_loop_run(loop);

	 /* Free resources */
  g_main_loop_unref(loop);

  return 0;



	// cv::Mat frame;				// 元画像
	// cv::Mat frame_gray;		// 処理用(Gray)
	// while(cap.read(frame)){
	// 	const int key = cv::waitKey(1);
	// 	if(key == 'q') break;
	// 	if(key == 's') cv::imwrite("img.png", frame);
	// 	cvtColor(frame, frame_gray, COLOR_RGB2GRAY);
	// 	cv::imshow("win", frame);
	// }
	// cv::destroyAllWindows();



}

