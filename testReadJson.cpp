#include "readJson.h"

using namespace std;

int main()
{
	string jsons_path = "../ocr_words1/small_jsons/";
	string imgDB = "../ocr_words1/small_images/";
	vector<ImgOCRResult> ocrResults;
	read_jsons(jsons_path,imgDB,ocrResults);
	int n = ocrResults.size();
	ofstream fout("../test_read_json.txt");
	for(int i=0; i<min(n,2); i++)
	{
		fout<<ocrResults.at(i).name<<endl;
		fout<<ocrResults.at(i).height<<"  "<<ocrResults.at(i).width<<endl;
		for(int j=0;j<ocrResults.at(i).locs.size();j++)
		{
			fout<< ocrResults.at(i).words.at(j)<<" "<<ocrResults.at(i).locs.at(j).left <<" "<< ocrResults.at(i).locs.at(j).top <<" "<<ocrResults.at(i).locs.at(j).width <<" "<<ocrResults.at(i).locs.at(j).height <<" " <<endl;
		}
                cout<<i<<endl;
	}
	return 0;
}
