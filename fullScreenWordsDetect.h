#ifndef FULL_SCREEN_WORDS_DETECT
#define FULL_SCREEN_WORDS_DETECT

#include "readJson.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

typedef unsigned int uint;
using namespace std;

class FullScreenWordsDetect{

public:
 FullScreenWordsDetect(float areaTh=0.0f, uint wordNumTh=0, float alpha = 1);
 ~FullScreenWordsDetect();
 void Initiate(const ImgOCRResult& ocrResult);
 bool IsFullScreenWords(float& ratio);
 bool IsFullScreenWordsV1(float& ratio);
 bool IsFullScreenWordsV2(float& ratio);

private:
 ImgOCRResult m_ocrResult;
 float m_imageArea;
 uint m_wordNum;
 float m_wordArea;
 float m_areaTh;
 uint m_wordNumTh;
 float m_alpha;
};

#endif
