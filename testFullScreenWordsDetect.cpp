#include "readJson.h"
#include "fullScreenWordsDetect.h"
using namespace std;

void usage()
{
	cout<<"******************Usage*******************"<<endl;
	cout<<"Perform full screen words detect."<<endl;
	cout<<"usage:"<<endl;
	cout<<"./testFullScreenWordsDetect --jsons_path jsons_path --images_path images_path --area_threshold areaTh --word_num_threshold wordNumTH --area_ratio alpha"<<endl;
	cout<<"For example:"<<endl;
	cout<<"./testFullScreenWordsDetect --jsons_path /jsons/path --images_path /images/path --area_threshold 0.25 --word_num_threshold 5 --area_ratio 0.66"<<endl;
	cout<<"if the area_threshold and word_num_threshold are ignorded, the default parameters (0.25 and 5) are set."<<endl;
	cout<<"******************************************"<<endl;
	
}

int main(int argc, char** argv)
{
	string jsons_path = "";
	string imgDB = "";
	float areaTh = 0.25;
	uint wordNumTh = 5;
	float alpha = 1;
	float ratio = 0;
	vector<ImgOCRResult> ocrResults;

	if(argc < 7)
	{
		cout <<"wrong usage!!!"<<endl;
		cout <<"*******************************"<<endl;
		cout <<"*******************************"<<endl;
		cout <<"*******************************"<<endl;
		cout <<"See usage below:" <<endl;
		usage();
		exit(0);
	}
	else
	{
		for(int count_arg = 1; count_arg < argc; count_arg++)
		{
			if(!strcmp(argv[count_arg],"--jsons_path"))
			{
				jsons_path = string(argv[++count_arg]);
//				cout<<jsons_path<<endl;
			}
			else if(!strcmp(argv[count_arg],"--images_path"))
			{
				imgDB = string(argv[++count_arg]);
//				cout<<imgDB<<endl;
			}
			else if(!strcmp(argv[count_arg],"--area_threshold"))
			{
				areaTh = atof(argv[++count_arg]);
//				cout<<areaTh<<endl;
			}
			else if(!strcmp(argv[count_arg],"--word_num_threshold"))
			{
				wordNumTh = atoi(argv[++count_arg]);
//				cout<<wordNumTh<<endl;
			}
			else if(!strcmp(argv[count_arg],"--area_ratio"))
			{
				alpha = atof(argv[++count_arg]);
//				cout<<wordNumTh<<endl;
			}
			else
			{
				cout<<"Unrecognized argument" <<argv[count_arg]<<", quitting..."<<endl;
				exit(0);
			}
		}
	}

	if(jsons_path == "")
	{
		cout<<"jsons_path argument was not provided...see usage below:"<<endl;
		usage();
		exit(0);
	}

	if(imgDB == "")
	{
		cout<<"images_path argument was not provided...see uasge below:"<<endl;
		usage();
		exit(0);
	}

	read_jsons(jsons_path,imgDB,ocrResults);
	int n = ocrResults.size();
	cout<<n<<endl;
	ofstream fout("test_detect.txt");
	FullScreenWordsDetect full_screen_detect(areaTh,wordNumTh,alpha);
	for(int i=0; i<n; i++)
	{
		full_screen_detect.Initiate(ocrResults.at(i));
		bool isFullScreenWords = full_screen_detect.IsFullScreenWordsV1(ratio);

		fout<<"id: " << i << endl;
		fout<<ocrResults.at(i).name<<endl;
		fout<<ocrResults.at(i).height<<"  "<<ocrResults.at(i).width<<endl;
		for(int j=0;j<ocrResults.at(i).locs.size();j++)
		{
			fout<< ocrResults.at(i).words.at(j)<<" "<<ocrResults.at(i).locs.at(j).left <<" "<< ocrResults.at(i).locs.at(j).top <<" "<<ocrResults.at(i).locs.at(j).width <<" "<<ocrResults.at(i).locs.at(j).height <<" " <<endl;
		}
		fout<<"is full screen words:  "<<isFullScreenWords<<endl<<endl;
        cout<<"ID: "<<i<<"    is full screen words:"<<isFullScreenWords<<endl<<endl;


	}
	return 0;
}
