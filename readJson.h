#ifndef READ_JSON_H
#define READ_JSON_H

#include "json.hpp"
#include <glob.h>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>


#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using json = nlohmann::json;

using namespace std;

typedef struct Location {
	uint32_t left;
	uint32_t top;
	uint32_t width;
	uint32_t height;
} Location;

typedef struct ImgOCRResult {
	std::string name;
	int height;
	int width;
	std::vector<Location> locs;
	std::vector<std::string> words;
} ImgOCRResult;

std::vector<std::string> glob_vector(const std::string& pattern);

/*
jsons_path: path of json file
imgDB: path of image file
*/
void read_jsons(string jsons_path, string imgDB, vector<ImgOCRResult>& ocrResults);
void read_jsons1(string jsons_path, string imgDB, vector<ImgOCRResult>& ocrResults);


string base_name(const string& path);

#endif
