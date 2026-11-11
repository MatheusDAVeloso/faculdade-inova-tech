#ifndef ROLLED_PAPER_DETECTOR_H
#define ROLLED_PAPER_DETECTOR_H

#include "ICigaretteDetector.h"

class RolledPaperDetector : public ICigaretteDetector {
public:
  std::vector<Detection> detect(const cv::Mat& frame) override;
};

#endif  // ROLLED_PAPER_DETECTOR_H
