//  (C) Copyright Rodrigo Moraes 2017.

#ifndef LIB_HEAD_GRABBER_HPP_
#define LIB_HEAD_GRABBER_HPP_

#include <opencv2/highgui/highgui.hpp>
#include "lib/constants.h"

class Grabber {
 public:
  Grabber();
  explicit Grabber(int new_camera_selector);
  explicit Grabber(std::__cxx11::string new_image_path);
  ~Grabber();

  bool set_camera(int new_camera_selector);
  void set_path(std::__cxx11::string new_image_path);
  bool CameraIsOn();
  cv::Mat *GetFrameFromCamera();
  cv::Mat *GetFrameFromImage();

 private:
  std::__cxx11::string image_path;
  int camera_selector;
  cv::VideoCapture *camera;
  cv::Mat frame;
  bool InitCamera(int new_camera_selector);
};

#endif  // LIB_HEAD_GRABBER_HPP_
