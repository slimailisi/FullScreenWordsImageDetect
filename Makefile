OPENCV_DIR = /home/lvyue/env/opencv-3.3.1

CXX=g++
CXXFLAGS = -std=c++0x -O3 -g -Wall -fmessage-length=0 -I$(OPENCV_DIR)/include
LDFLAGS = -L$(OPENCV_DIR)/lib -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs

all: testReadJson testFullScreenWordsDetect

readJson.o: readJson.h readJson.cpp
	$(CXX) $(CXXFLAGS) -c readJson.cpp -o readJson.o

testReadJson.o: testReadJson.cpp
	$(CXX) $(CXXFLAGS) -c testReadJson.cpp -o testReadJson.o 

testReadJson: readJson.o testReadJson.o
	$(CXX) $(CXXFLAGS)  -o testReadJson testReadJson.o readJson.o $(LDFLAGS)

fullScreenWordsDetect.o: fullScreenWordsDetect.cpp
	$(CXX) $(CXXFLAGS) -c fullScreenWordsDetect.cpp -o fullScreenWordsDetect.o

testFullScreenWordsDetect.o: testFullScreenWordsDetect.cpp
	$(CXX) $(CXXFLAGS) -c testFullScreenWordsDetect.cpp -o testFullScreenWordsDetect.o

testFullScreenWordsDetect: testFullScreenWordsDetect.o fullScreenWordsDetect.o readJson.o 
	$(CXX) $(CXXFLAGS) -o testFullScreenWordsDetect testFullScreenWordsDetect.o fullScreenWordsDetect.o readJson.o $(LDFLAGS)

clean:
	rm -f readJson.o testReadJson.o testReadJson fullScreenWordsDetect.o testFullScreenWordsDetect.o testFullScreenWordsDetect
