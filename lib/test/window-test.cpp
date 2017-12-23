//  (C) Copyright Rodrigo Moraes 2017.

#include <iostream>
#include "lib/head/window.hpp"
#include "lib/head/grabber.hpp"

int main(int argc, char **argv) {
  Grabber grab("../resource/image/27.jpg");

  Window *window = new Window();

  cv::Mat *frame = grab.GetFrameFromImage();

  window->Show(frame);

  return 0;
}
