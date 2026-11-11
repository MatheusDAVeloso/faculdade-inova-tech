#ifndef I_CIGARETTE_DETECTOR_H
#define I_CIGARETTE_DETECTOR_H

#include <vector>

#include <opencv2/core/mat.hpp>

#include "Detection.h"

class ICigaretteDetector {
public:
  virtual ~ICigaretteDetector() = default;

  /** Finds possible cigarette-shaped objects in a frame. */
  virtual std::vector<Detection> detect(const cv::Mat& frame) = 0;
};

#endif  // I_CIGARETTE_DETECTOR_H
