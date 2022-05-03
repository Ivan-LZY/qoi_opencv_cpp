#pragma once
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <vector>
#include "qoi.hpp"

class OCV_QOI {

private:

	//for encoding
	int img_wid=640;
	int img_ht=480;
	int img_chl=3;
	int vec_size = img_wid * img_ht*img_chl;
	std::vector<unsigned char> pixel_vec;
	std::vector<unsigned char> qoi_encoded_pixels;

	//for decoding
	std::vector<uchar> imread_output_pixels; 
	
public:
	OCV_QOI(){};

	~OCV_QOI(){};

	OCV_QOI(int img_width, int img_height, int img_c) { //use this for saving frames from a camera/videofile where dimensions are known and fixed.
		setImgDimensions(img_width, img_height, img_c); 
	}

	cv::Mat imreadQOI(std::string qoi_filepath, bool read_color = true, int mat_type = CV_8UC3);

	void imwriteQOI(const std::string dst_save_path, const const cv::Mat ocv_mat, bool update_dimensions = false); 

	void setImgDimensions(const int w, const int h, const int c) {
		img_wid = w;
		img_ht = h;
		img_chl = c;
		vec_size = w*h*c;
		pixel_vec.resize(vec_size);
		pixel_vec.reserve(vec_size+1);
		qoi_encoded_pixels.resize(vec_size);
		qoi_encoded_pixels.reserve(vec_size+1);
	}
};


