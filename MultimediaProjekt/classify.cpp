#include "Classify.h"

using namespace cv;
using namespace std;

namespace Classify{

	void showAndAnnotateImg(string filepath, string text){
		cout << filepath;
		Mat input = imread(filepath, 1);
		
		// x and y min
		string point = text.substr((int)text.find('('), (int)text.find(')')-(int)text.find('(')+1);
		int x = stoi(point.substr(1, ((int)point.find(','))-1));
		int y = stoi(point.substr(((int)point.find(','))+2, (int)point.find(')')-1));
		Point p1 = Point(x,y);
		
		// x and y max
		point = text.substr((int)text.find('-')+2, text.length()-1);
		x = stoi(point.substr(1, ((int)point.find(','))-1));
		y = stoi(point.substr(((int)point.find(','))+2, (int)point.find(')')-1));
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
	
	string readFile(string filepath){
		string result;
		string text;
		ifstream file (filepath);
		if (file.is_open())	{
			while ( file.good() )	{
				getline (file,text);
				result += text;
			}
			file.close();

			text = result;
			
			// find filename
			string str = text.substr((int)text.find('"')+1, text.length()-1);
			str = str.substr(0, (int)str.find('"')); 
			if(str != ""){
				result = "";
				result += str;
			}

			result += " : ";

			// find position
			str = string(text.rbegin(),text.rend());
			str = str.substr(0, (int)str.find('x')-4);
			str = string(str.rbegin(),str.rend());
			if(str != ""){
				result += str;
			}
		}
		else cout << "Unable to open file"; 
	
		return result;
	}
}