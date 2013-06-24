#include "opencv\cv.h"
#include "opencv\highgui.h"
#include "opencv2\imgproc\imgproc.hpp"

#include <iostream>
#include <fstream>
#include <string.h>

#define FILENAME "imgData.txt"
#define FILEPATH "lena.jpg"

using namespace cv;
using namespace std;

void showAndAnnotateImg(string text);
void writeFile(Point p1, Point p2);
string readFile();

int main (int argc, const char * argv[]) {

	writeFile(Point(1,1), Point(100,100));
	string text = readFile();
	showAndAnnotateImg(text);

	return 0;
}

//namespace classify{

	void showAndAnnotateImg(string text){
		Mat input = imread(FILEPATH, 1);
		
		string point = text.substr(0, (int)text.find('-')-1);
		int x = stoi(point.substr(1, ((int)point.find(','))-1));
		int y = stoi(point.substr(((int)point.find(','))+2, (int)point.find(']')-1));
		Point p1 = Point(x,y);
		
		point = text.substr((int)text.find('-')+1, text.length()-1);
		x = stoi(point.substr(1, ((int)point.find(','))-1));
		y = stoi(point.substr(((int)point.find(','))+2, (int)point.find(']')-1));
		Point p2 = Point(x,y);
		
		Scalar red = Scalar(0,0,255);
		putText(input, text, Point(p1.x+2, p1.y+10), 2, 0.3, red, 1, 16);
	
		line(input, p1, Point(p2.x, p1.y), red, 1, 8, 0);
		line(input, p1, Point(p1.x, p2.y), red, 1, 8, 0);
		line(input, p2, Point(p2.x, p1.y), red, 1, 8, 0);
		line(input, p2, Point(p1.x, p2.y), red, 1, 8, 0);
	
		imshow("input", input);
	
		waitKey();
	}
	
	void writeFile(Point p1, Point p2){
		ofstream file (FILENAME);
		
		if (file.is_open())  {
			file << p1 << "-" << p2;
			file.close();
		}
		else cout << "Unable to open file"; 
	}
	
	string readFile(){
		string result;
		string line;
		ifstream file (FILENAME);
		if (file.is_open())	{
			while ( file.good() )	{
				getline (file,line);
				result += line;
			}
			file.close();
		}
		else cout << "Unable to open file"; 
	
		return result;
	}
//}