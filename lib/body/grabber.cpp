//  (C) Copyright Rodrigo Moraes 2017.

#include "lib/head/grabber.hpp"

Grabber::Grabber() : Grabber(CAMERA_SELECTOR_DEFAULT) {}

Grabber::Grabber(int new_camera_selector) {
  this->InitCamera(new_camera_selector);
}

Grabber::Grabber(std::__cxx11::string new_image_path) {
  this->image_path = new_image_path;
  this->camera_selector = CAMERA_SELECTOR_DEFAULT;
  this->camera = NULL;
}

Grabber::~Grabber() { delete this->camera; }

bool Grabber::set_camera(int new_camera_selector) {
  delete this->camera;

  bool result = this->InitCamera(new_camera_selector);

  return result;
}

void Grabber::set_path(std::__cxx11::string new_image_path) {
  this->image_path = new_image_path;
}

bool Grabber::CameraIsOn() {
  if (this->camera_selector == CAMERA_SELECTOR_DEFAULT) return false;
  return this->camera->open(this->camera_selector);
}

cv::Mat *Grabber::GetFrameFromCamera() {
  if (this->camera_selector != CAMERA_SELECTOR_DEFAULT) {
    (*this->camera) >> this->frame;
    return &(this->frame);
  }

  return NULL;
}

cv::Mat *Grabber::GetFrameFromImage() {
  this->frame = cv::imread(this->image_path, CV_LOAD_IMAGE_COLOR);

  if (this->frame.data) return &(this->frame);

  return NULL;
}

bool Grabber::InitCamera(int new_camera_selector) {
  this->image_path = "";
  this->camera_selector = new_camera_selector;
  this->camera = new cv::VideoCapture(new_camera_selector);

  if (!this->CameraIsOn()) {
    this->camera_selector = CAMERA_SELECTOR_DEFAULT;
    this->camera = NULL;
    return false;
  }

  return true;
}
