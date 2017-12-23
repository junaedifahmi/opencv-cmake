//  (C) Copyright Rodrigo Moraes 2017.

#include "lib/head/window.hpp"

Window::Window()
    : Window(WINDOW_POS_X, WINDOW_POS_Y, WINDOW_WIDTH, WINDOW_HEIGHT,
             WINDOW_TITLE) {}

Window::~Window() { cvDestroyWindow(this->title.c_str()); }

Window::Window(std::__cxx11::string new_title)
    : Window(WINDOW_POS_X, WINDOW_POS_Y, WINDOW_WIDTH, WINDOW_HEIGHT,
             new_title) {}

Window::Window(int new_width, int new_height, std::__cxx11::string new_title)
    : Window(WINDOW_POS_X, WINDOW_POS_Y, new_width, new_height, new_title) {}

Window::Window(int new_pos_x, int new_pos_y, int new_width, int new_height,
               std::__cxx11::string new_title) {
  this->posX = new_pos_x;
  this->posY = new_pos_y;
  this->width = new_width;
  this->height = new_height;
  this->title = new_title;

  cv::namedWindow(this->title.c_str(), cv::WINDOW_NORMAL);
  cv::resizeWindow(this->title.c_str(), this->width, this->height);
  cv::moveWindow(this->title.c_str(), this->posX, this->posY);
}

int Window::Show(cv::Mat *frame) { return this->ShowWithDelay(frame, 0); }

int Window::ShowWithDelay(cv::Mat *frame, int delay_miliseconds) {
  imshow(this->title.c_str(), *frame);
  int code_key = cv::waitKey(delay_miliseconds) & 0xFF;

  return code_key;
}
