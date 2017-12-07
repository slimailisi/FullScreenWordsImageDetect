#include "readJson.h"
using namespace std;
using json = nlohmann::json;


string base_name(const string& path)
{
        size_t pos1 = path.find_last_of("/\\");
   
        string name1 = path.substr(pos1+1);
        size_t pos2 = name1.find_last_of('.');
//        cout<<name1<<endl;
        string name = name1.substr(0,pos2);
 //      cout<<name<<endl;
        return name;
}

std::vector<std::string> glob_vector(const std::string& pattern){
	glob_t glob_result;
	glob(pattern.c_str(), GLOB_TILDE, NULL, &glob_result);
	std::vector<std::string> files;
	for (unsigned int i = 0; i<glob_result.gl_pathc; ++i){
		auto tmp = std::string(glob_result.gl_pathv[i]);
		files.push_back(tmp);
	}
	std::sort(files.begin(), files.end());
	globfree(&glob_result);
	return files;
}

/*
jsons_path: path of json file
imgDB: path of image file
*/
void read_jsons(string jsons_path, string imgDB, vector<ImgOCRResult>& ocrResults)
{
	std::vector<std::string> json_files = glob_vector(jsons_path + "*");

	// read a JSON file
	for (int i = 0; i < json_files.size(); i++){
		std::ifstream jfs(json_files.at(i));
		json jsonFile;
		jfs >> jsonFile;
		//std::cout << std::setw(4) << jsonFile << std::endl;

		ImgOCRResult ocrResult;
		ocrResult.name = jsonFile.at("_id");
   //             cout<<json_files.at(i)<<endl;
		std::string imgName = base_name(json_files.at(i));
     //           cout<<imgName<<endl;
		cv::Mat img = cv::imread(imgDB + "/" + imgName + ".jpg", 1);
		ocrResult.height = img.rows;
		ocrResult.width = img.cols;
		int w = img.cols;
		int h = img.rows; 
        float alpha = sqrt(2/3.0);
		float a1 = (1-alpha)/2;
        float a2 = (1+alpha)/2;
		cv::rectangle(img,cv::Point(int(a1*w),int(a1*h)),cv::Point(int(a2*w),int(a2*h)),cv::Scalar(0,255,0),2); 
	
		ocrResult.words.clear();
		ocrResult.locs.clear();

		// load json
		for (int i = 0; i < jsonFile.at("result").size(); i++){
			Location loc;
			loc.top = jsonFile.at("result").at(i).at("location").at("top");
			loc.left = jsonFile.at("result").at(i).at("location").at("left");
			loc.width = jsonFile.at("result").at(i).at("location").at("width");
			loc.height = jsonFile.at("result").at(i).at("location").at("height");
			std::string word = jsonFile.at("result").at(i).at("words");
			ocrResult.words.push_back(word);
			ocrResult.locs.push_back(loc);
			cv::rectangle(img,cv::Point(loc.left,loc.top),cv::Point(loc.left+loc.width,loc.top+loc.height),cv::Scalar(0,0,255),1);
		}


		ocrResults.push_back(ocrResult);
		cv::imwrite(imgDB+"/"+imgName+"_ocr.jpg",img);
		}
}

void read_jsons1(string jsons_path, string imgDB, vector<ImgOCRResult>& ocrResults)
{
	std::vector<std::string> json_files = glob_vector(jsons_path + "*");
 
	// read a JSON file
	for (int i = 0; i < json_files.size(); i++){
		std::ifstream jfs(json_files.at(i));
		json jsonFile;
		jfs >> jsonFile;
		//std::cout << std::setw(4) << jsonFile << std::endl;

		ImgOCRResult ocrResult;
		ocrResult.name = jsonFile.at("frameResult").at(0).at("frameId");
   //             cout<<json_files.at(i)<<endl;
		std::string imgName = base_name(json_files.at(i));
     //           cout<<imgName<<endl;
		cv::Mat img = cv::imread(imgDB + "/" + imgName + ".jpg", 1);
	//	float max_size = max(img.rows,img.cols);
	//	float min_size = min(img.rows,img.cols);
	//	float scale = min(1000/max_size,600/min_size);
	//	cv::resize(img,img,cv::Size(0,0),1/scale,1/scale)
		ocrResult.height = img.rows;
		ocrResult.width = img.cols;
               
		int w = img.cols;
		int h = img.rows; 
        float alpha = sqrt(2/3.0);
		float a1 = (1-alpha)/2;
        float a2 = (1+alpha)/2;
		cv::rectangle(img,cv::Point(int(a1*w),int(a1*h)),cv::Point(int(a2*w),int(a2*h)),cv::Scalar(0,255,0),2); 
		ocrResult.words.clear();
		ocrResult.locs.clear();

		// load json
		for (int i = 0; i < jsonFile.at("frameResult").at(0).at("result").size(); i++){
			Location loc;
			loc.top = jsonFile.at("frameResult").at(0).at("result").at(i).at("location").at("top");
			loc.left = jsonFile.at("frameResult").at(0).at("result").at(i).at("location").at("left");
			loc.width = jsonFile.at("frameResult").at(0).at("result").at(i).at("location").at("width");
			loc.height = jsonFile.at("frameResult").at(0).at("result").at(i).at("location").at("height");
//			std::string word = jsonFile.at("frameResult").at(0).at("result").at(i).at("words");
            string word = "unknown";
    		ocrResult.words.push_back(word);
			ocrResult.locs.push_back(loc);
			cv::rectangle(img,cv::Point(loc.left,loc.top),cv::Point(loc.left+loc.width,loc.top+loc.height),cv::Scalar(0,0,255),1);
	
		}

		ocrResults.push_back(ocrResult);
		cv::imwrite(imgDB+"/"+imgName+"_ocr.jpeg",img);
		}
	
}


