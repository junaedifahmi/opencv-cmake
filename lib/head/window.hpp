//  (C) Copyright Rodrigo Moraes 2017.

#ifndef LIB_HEAD_WINDOW_HPP_
#define LIB_HEAD_WINDOW_HPP_

#include <opencv2/highgui/highgui.hpp>
#include "lib/constants.h"

class Window {
 public:
  Window();
  explicit Window(std::__cxx11::string);
  Window(int new_width, int new_height, std::__cxx11::string new_title);
  Window(int new_pos_x, int new_pos_y, int new_width, int new_height,
         std::__cxx11::string new_title);
  ~Window();
  int Show(cv::Mat *frame);
  int ShowWithDelay(cv::Mat *frame, int delay_miliseconds);

 private:
  std::__cxx11::string title;
  int width;
  int height;
  int posX;
  int posY;
};

#endif  // LIB_HEAD_WINDOW_HPP_
