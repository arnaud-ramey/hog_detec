// OpenCV
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <stdio.h>

cv::HOGDescriptor hog;

int process_image(cv::Mat & input_img) {
  std::vector<cv::Rect> found_rectangles;
  hog.detectMultiScale(input_img, found_rectangles);
  for (unsigned int rec_idx = 0; rec_idx < found_rectangles.size(); ++rec_idx)
    cv::rectangle(input_img, found_rectangles[rec_idx], CV_RGB(255,0,0), 2);
  cv::imwrite("input_img.png", input_img);
  cv::imshow("input_img", input_img);
} // end process_image()

int main(int argc, char *argv[]) {
  hog.setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector());
  //hog.setSVMDetector(cv::HOGDescriptor::getDaimlerPeopleDetector());

  cv::Mat input_img;
  if (argc == 2) {
    //printf("Usage %s [file]\n", argv[0]);
    // return -1;
    std::string file(argv[1]);
    input_img = cv::imread(file, CV_LOAD_IMAGE_COLOR);
    process_image(input_img);
    cv::waitKey(0);
  }

  //cv::VideoCapture cap(0);
  cv::VideoCapture cap;
  cap.open("/home/arnaud/Desktop/Baudet-Rob.mp4");
  if (!cap.isOpened()) {
        printf("Cannot open camera!"); return -1;
  }

  while(true) {
    cap >> input_img;
    cv::resize(input_img, input_img, cv::Size(320, 240));
    process_image(input_img);
    cv::waitKey(15);
  }
  return 0;
}
