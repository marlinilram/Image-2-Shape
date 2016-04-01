#ifndef ImageUtility_H
#define ImageUtility_H

#include <cv.h>
#include "BasicHeader.h"
#include "LgMeshTypes.h"

namespace ImageUtility
{
  struct MouseArgs{
    IplImage* img;
    CvPoint p_start;
    CvPoint p_end;
    CvSeq* seq;
    CvMemStorage* storage;
    int points;
    // init
    MouseArgs():img(0),points(0){
      p_start = cvPoint(-1,-1);
      p_end = cvPoint(-1,-1);
      storage = cvCreateMemStorage(0);
      seq = cvCreateSeq( CV_32SC2,sizeof(CvSeq),sizeof(CvPoint), storage );
    }
    // destroy
    void Destroy(){
      if(!img)
        cvReleaseImage(&img);
      cvReleaseMemStorage(&storage );
      seq = NULL;
      img = NULL;
    }
  };

  void MouseDraw(int event,int x,int y,int flags,void* param);
  bool generateMask(cv::Mat& img_in, cv::Mat& mask_out);
  void generateMultiMask(cv::Mat& img_in, cv::Mat& mask_out);

  void generateMaskedMatVec(std::vector<cv::Mat>& mat_vec_in, std::vector<cv::Mat>& mat_vec_out, cv::Mat& mask);
  void mergeMatVecFromMask(std::vector<cv::Mat>& mat_vec_src, std::vector<cv::Mat>& mat_vec_tar, cv::Mat& mask);

  void exportMatVecImage(std::vector<cv::Mat>& mat_vec, std::string fname);

  bool meetZero(std::vector<int>& vec);
}

#endif // !ImageUtility_H