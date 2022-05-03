#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <vector>
#include <array>

#include "opencv_qoi.h"

using namespace cv;
using namespace std;

int main()
{
	//set video file path or camera index here//
	std::string vid_path = "./test0.mp4";
	VideoCapture cap(vid_path.c_str());
	Mat imgBGR;

	cap >> imgBGR;
	if (imgBGR.empty()) {
		cout << "Invalid video file" << endl;
		return -1;
	}

	const int width = imgBGR.cols;
	const int height = imgBGR.rows;
	const int channels = imgBGR.channels();

	OCV_QOI qoi_util;
	qoi_util.setImgDimensions(width, height, channels);
	//qoi_util(width, height, channels); //overloaded alternative

	int framenum = 1;

	char filename[300];

	double t1, t2, timeElapsed, totalTimeTaken=0.0f;

	while (1){
		
		t1 = getTickCount();

		//Comment out and benchmark as needed//

		//Sample QOI write//
		sprintf_s(filename, "dumpQOI/frame%06d.qoi", framenum);
		qoi_util.imwriteQOI(filename, imgBGR);
			   
		//opencv imwrite for PNG/JPG//
		/*sprintf_s(filename, "dumpPNG/frame%06d.png", framenum);
		imwrite(filename, imgBGR);*/

		t2 = getTickCount();
		timeElapsed = (t2 - t1) / getTickFrequency();
		totalTimeTaken += timeElapsed;

		printf("Frame%d, time elapsed: %.4fsec\n",framenum, timeElapsed);

		cap >> imgBGR;
		if (imgBGR.empty()) break;
		framenum++;
	}
	printf("Total time elapsed for encoding: %.4f sec over %d frames\n\n", totalTimeTaken, framenum);


	//Sample QOI decode & playback with imshow//
	totalTimeTaken = 0.0f;
	for (int i = 1; i < framenum; i++) {

		//Comment out and benchmark as needed//

		t1 = getTickCount();

		sprintf_s(filename, "dumpQOI/frame%06d.qoi", i);
		Mat out = qoi_util.imreadQOI(filename);
		//Mat out = qoi_util.imreadQOI(filename,0); // read as grayscale simialr to cv::imread(file_path,0);

		/*sprintf_s(filename, "dumpPNG/frame%06d.jpg", i);
		Mat out = imread(filename);*/

		t2 = getTickCount();
		timeElapsed = (t2 - t1) / getTickFrequency();
		totalTimeTaken += timeElapsed;
		//printf("Frame%d, Imread time elapsed: %.4fsec\n", i, timeElapsed);

		imshow("Disp", out);
		waitKey(1);
	}
	printf("Total time elapsed for decoding: %.4f sec over %d frames\n", totalTimeTaken, framenum);

	return 0;
}