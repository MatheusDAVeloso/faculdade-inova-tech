#include "RolledPaperDetector.h"

#include <algorithm>
#include <cmath>

#include <opencv2/imgproc.hpp>

std::vector<Detection> RolledPaperDetector::detect(const cv::Mat& frame) {
  std::vector<Detection> detections;
  if (frame.empty() || (frame.channels() != 1 && frame.channels() != 3 &&
                        frame.channels() != 4)) {
    return detections;
  }

  cv::Mat bgrFrame;
  if (frame.channels() == 1) {
    cv::cvtColor(frame, bgrFrame, cv::COLOR_GRAY2BGR);
  } else if (frame.channels() == 4) {
    cv::cvtColor(frame, bgrFrame, cv::COLOR_BGRA2BGR);
  } else {
    bgrFrame = frame;
  }

  cv::Mat hsvFrame;
  cv::cvtColor(bgrFrame, hsvFrame, cv::COLOR_BGR2HSV);

  cv::Mat mask;
  cv::inRange(hsvFrame, cv::Scalar(0, 0, 150), cv::Scalar(180, 90, 255), mask);

  const cv::Mat morphologyKernel = cv::getStructuringElement(
      cv::MORPH_RECT, cv::Size(5, 3));
  cv::morphologyEx(mask, mask, cv::MORPH_OPEN, morphologyKernel);
  cv::morphologyEx(mask, mask, cv::MORPH_CLOSE, morphologyKernel);

  std::vector<std::vector<cv::Point>> contours;
  cv::findContours(mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

  const double imageArea = static_cast<double>(frame.rows) * frame.cols;
  for (const std::vector<cv::Point>& contour : contours) {
    const double contourArea = cv::contourArea(contour);
    const cv::Rect bounds = cv::boundingRect(contour);
    const int shorterSide = std::min(bounds.width, bounds.height);
    const int longerSide = std::max(bounds.width, bounds.height);
    if (shorterSide == 0) {
      continue;
    }

    const double areaRatio = contourArea / imageArea;
    const double aspectRatio =
        static_cast<double>(longerSide) / shorterSide;
    const double fillRatio =
        contourArea / static_cast<double>(bounds.area());

    if (areaRatio < 0.0002 || areaRatio > 0.04 || aspectRatio < 2.0 ||
        aspectRatio > 10.0 || fillRatio < 0.35) {
      continue;
    }

    const double aspectScore =
        std::max(0.0, 1.0 - std::abs(aspectRatio - 4.0) / 6.0);
    const double fillScore = std::min(1.0, fillRatio / 0.75);
    const float score = static_cast<float>(0.6 * aspectScore + 0.4 * fillScore);
    detections.push_back({bounds, score});
  }

  return detections;
}
