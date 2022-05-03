# The “Quite OK Image” format for OpenCV Cpp
This is a C++ class wrapper to read and write .qoi formatted images with OpenCV's cv::Mat. As of writing (May 2022), OpenCV does not natively support reading and writing of qoi images. This repo seeks to provide a temporary solution.

# About
The [QOI format](https://phoboslab.org/log/2021/11/qoi-fast-lossless-image-compression) is a fast, lossless image compression created by Dominic Szablewski. Sample usage of the wrapper class and benchmarking code can be found in main.cpp

# Benchmarks
Benchmarking was done using the class wrapper's imreadQOI/imwriteQOI against OpenCV's imread/imwrite with .PNG and .JPG image formats. Each benchmark was ran 3 times and the average time is taken. The code was ran on a x86 system with AMD Ryzen 3700x, Windows 10, OpenCV 4.1.1 with MSVS2017.

A sample 1920x1080 video with 1052 frames was used for this benchmark.

## Encoding Speed
| Image Format  | Average time taken to encode all frames |
| --- | --- |
| QOI | 26.8 sec |
| OpenCV PNG  | 71.8 sec |
| OpenCV JPG  | 32.6 sec  |

## Decoding Speed
| Image Format  | Average time taken to decode all frames|
| --- | --- |
| QOI | 21.4 sec |
| OpenCV PNG  | 35.5 sec |
| OpenCV JPG  | 19.3 sec  |

# Credits
The implementation of qoi was ported from [libqoi](https://github.com/ShadowMitia/libqoi) with minor edits to qoi.cpp to accomodate OpenCV's conventional BGR format.
