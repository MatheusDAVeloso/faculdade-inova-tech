#ifndef DETECTION_H
#define DETECTION_H

#include <opencv2/core/types.hpp>

struct Detection {
  cv::Rect bounds;
  float score;
};

#endif  // DETECTION_H
