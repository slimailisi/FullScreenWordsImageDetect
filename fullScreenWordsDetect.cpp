#include "fullScreenWordsDetect.h"
using namespace std;

FullScreenWordsDetect::FullScreenWordsDetect(float areaTh, uint wordNumTh, float alpha):m_areaTh(areaTh),m_wordNumTh(wordNumTh),m_alpha(alpha)
{
	m_imageArea = 0.0f;
	m_wordNum = 0;
	m_wordArea = 0.0f;
}

FullScreenWordsDetect::~FullScreenWordsDetect()
{

}

void FullScreenWordsDetect::Initiate(const ImgOCRResult& ocrResult)
{
	m_ocrResult.locs.clear();
	m_ocrResult.words.clear();
	m_ocrResult.name = ocrResult.name;
	m_ocrResult.height = ocrResult.height;
	m_ocrResult.width = ocrResult.width;
	m_ocrResult.locs.assign(ocrResult.locs.begin(), ocrResult.locs.end());
	m_ocrResult.words.assign(ocrResult.words.begin(), ocrResult.words.end());
//	cout<<m_ocrResult.locs[0].width<< "  "<<m_ocrResult.locs[0].height<<endl;
//	cout<<m_ocrResult.words[0]<<endl<<endl;
}



bool FullScreenWordsDetect::IsFullScreenWords()
{
	m_imageArea = m_ocrResult.height * m_ocrResult.width;
	m_wordNum = m_ocrResult.locs.size();
	for(int i=0; i<m_wordNum; i++)
	{
		m_wordArea += m_ocrResult.locs.at(i).width * m_ocrResult.locs.at(i).height;
	}

	bool flag = false;
    cout<<"image name:"<<m_ocrResult.name<<endl;
    cout<<"word num: "<<m_wordNum<<endl;
    cout<<"area ratio: "<< m_wordArea/m_imageArea<<endl;
    //    cout<<m_areaTh<<endl;
	if((m_wordArea > (m_areaTh*m_imageArea)) && (m_wordNum>m_wordNumTh))
	{
		flag = true;
	}
	else
	{
		flag = false;
	}
	return flag;
}


bool FullScreenWordsDetect::IsFullScreenWordsV1()
{
	float a = sqrt(alpha);
	float a1 = (1-a)/2;
	float a2 = (1+a)/2;
	int left = int(a1*m_ocrResult.width);
	int top = int(a1*m_ocrResult.height);
	int right = int(a2*m_ocrResult.width);
	int bottom = int(a2*m_ocrResult.height);

	int n = m_ocrResult.locs.size();
	int left_new, right_new, top_new, bottom_new;
	for(int i=0; i<n; i++)
	{
		left_new = max(left, m_ocrResult.locs.at(i).left); 
		top_new = max(top, m_ocrResult.locs.at(i).top);
		right_new = min(right, m_ocrResult.locs.at(i).left + m_ocrResult.locs.at(i).width);
		bottom_new = min(bottom, m_ocrResult.locs.at(i).top + m_ocrResult.locs.at(i).height);
		if(left_new < right_new && top_new < bottom_new)
		{
			m_wordNum++;
			m_wordArea += (right_new - left_new)*(bottom_new - top_new);
		}
	}

	m_imageArea = m_alpha * m_ocrResult.height * m_ocrResult.width;
	bool flag = false;
    cout<<"image name:"<<m_ocrResult.name<<endl;
    cout<<"word num: "<<m_wordNum<<endl;
    cout<<"area ratio: "<< m_wordArea/m_imageArea<<endl;
    //    cout<<m_areaTh<<endl;
	if((m_wordArea > (m_areaTh*m_imageArea)) && (m_wordNum>m_wordNumTh))
	{
		flag = true;
	}
	else
	{
		flag = false;
	}
	return flag;
}
