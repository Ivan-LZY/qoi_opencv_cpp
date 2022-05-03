#include "opencv_qoi.h"

void OCV_QOI::imwriteQOI(const std::string dst_save_path, const cv::Mat ocv_mat, bool update_dimensions) {

	if (!update_dimensions){
			if ((ocv_mat.rows != img_ht) || (ocv_mat.cols != img_wid) || (ocv_mat.channels() != img_chl)) { //double check with class params
				printf("Mismatch in image dimension, image not saved! (Expected Size: Wid %d, Ht %d, Chl %d || Input Mat Size: Wid %d, Ht %d, Chl %d)\n",
				img_wid, img_ht, img_chl, ocv_mat.cols, ocv_mat.rows, ocv_mat.channels());
				return;
			}
	}
	else {
		setImgDimensions(ocv_mat.cols, ocv_mat.rows, ocv_mat.channels());
	}
	pixel_vec = ocv_mat.reshape(1, vec_size);
	qoi_encoded_pixels = qoi::encode(pixel_vec, img_wid, img_ht, img_chl);
	qoi::utils::write_binary(dst_save_path, qoi_encoded_pixels);
}

cv::Mat OCV_QOI::imreadQOI(std::string qoi_filepath, bool read_color, int mat_type) {
	const auto decoded_image = qoi::utils::read_binary(qoi_filepath);
	const auto header = qoi::get_header(decoded_image);
	imread_output_pixels = qoi::decode(decoded_image);
	cv::Mat imread_output(header.height, header.width, mat_type, imread_output_pixels.data());
	if (mat_type == CV_8UC3) cvtColor(imread_output, imread_output, cv::COLOR_RGB2BGR);
	if (mat_type == CV_8UC4) cvtColor(imread_output, imread_output, cv::COLOR_RGBA2BGRA);

	if (!read_color) {
		if (mat_type == CV_8UC3) cvtColor(imread_output, imread_output, cv::COLOR_BGR2GRAY);
		if (mat_type == CV_8UC4) cvtColor(imread_output, imread_output, cv::COLOR_BGRA2GRAY); 
	}
	return imread_output.clone();
}