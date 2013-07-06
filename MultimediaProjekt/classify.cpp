#include "Classify.h"

using namespace cv;
using namespace std;

namespace Classify
{
	//	TRAINER
	void		createClassificator(float window_feature[], cv::Rect window_rect, cv::Rect positive_rects[])
	{

	}

	//	SVM
	void		train()
	{

	}

	void		classify()
	{

	}

	//	AnnotatedImageComposer
	void		deleteOverlappingPositiveHits(){

	}

	void		composeImage(cv::Mat final_image)
	{

	}






	void showAndAnnotateImg(string filepath, string text)
	{
		// find number of objects in image
		int strStart = (int)text.find("#Obj: ") + 6;
		int strEnd = (int)text.find(" _ Object")-1;
		string str = text.substr(strStart, strEnd);
		int objInImg = stoi(str);

		ostringstream stream;
		string tmp = text;
		strEnd = (int)text.length();

		for(int i = 1; i <= objInImg; i++)
		{	
			stream.str("");
			stream << i;

			strStart = (int)tmp.find(" Object"+stream.str()) + (10 + (int)(i/10));

			stream.str("");
			stream << i+1;
			if(objInImg!=1)
			{
				if(objInImg >= i+1)
					strEnd = (int)tmp.find(" Object"+stream.str());
				else
					strEnd = (int)tmp.length();
			}

			str = tmp.substr(strStart,strEnd);
			tmp = tmp.substr(strEnd, tmp.length()-1);

			// x and y min
			string point = str.substr((int)str.find('('), (int)str.find(')')-(int)str.find('(')+1);
			int x = stoi(point.substr(1, ((int)point.find(','))-1));
			int y = stoi(point.substr(((int)point.find(','))+2, (int)point.find(')')-1));
			Point p1 = Point(x,y);
		
			// x and y max
			point = str.substr((int)str.find('-')+2, str.length()-1);
			x = stoi(point.substr(1, ((int)point.find(','))-1));
			y = stoi(point.substr(((int)point.find(','))+2, (int)point.find(')')-1));
			Point p2 = Point(x,y);
		
			Mat input = imread(filepath, 1);

			Scalar red = Scalar(0,0,255);
			putText(input, str, Point(p1.x+2, p1.y+10), 2, 0.3, red, 1, 16);
	
			line(input, p1, Point(p2.x, p1.y), red, 1, 8, 0);
			line(input, p1, Point(p1.x, p2.y), red, 1, 8, 0);
			line(input, p2, Point(p2.x, p1.y), red, 1, 8, 0);
			line(input, p2, Point(p1.x, p2.y), red, 1, 8, 0);
	
			imshow("input", input);
	
			waitKey();
		}
	}
	
	void writeFile(string text, string path)
	{
		// find filename
		string filename;
		int strStart = (int)text.find("filename: ") + 10 + (int)path.length();
		int strEnd = (int)text.find(".png");
		string str = text.substr(strStart, strEnd-strStart);
		filename = "new_" + str.substr(0, (int)str.find('"')) + ".txt"; 
		cout << "write file: " << filename << endl;

		// write text in file
		ofstream file (filename);
		if (file.is_open())
		{
			file << text;
			file.close();
		}
		else cout << "Unable to open file"; 
	}
	
/*	string format:	filename: bla.png _ #Obj: X _ ObjectY: (Xmin, Ymin) - (Xmax, Ymax) _ ObjectZ: (Xmin, Ymin) - (Xmax, Ymax)
*/
	string readFile(string filepath)
	{
		string result;
		string text;
		ifstream file (filepath);
		if (file.is_open())
		{
			while (file.good())
			{
				getline (file,text);
				result += text;
			}
			file.close();

			text = result;
			
			// find filename
			int strStart = (int)text.find("Image filename : ") + 17;
			string str = text.substr(strStart+1, text.length());
			result = "filename: " + str.substr(0, (int)str.find('"')) + " _ "; 

			// find number of objects in image
			strStart = (int)text.find("Objects with ground truth : ") + 27;
			str = text.substr(strStart, strStart+1);
			int objInImg = stoi(str);
			int strEnd = (int)text.length();
			ostringstream stream;
			stream << objInImg;
			result += "#Obj: " + stream.str();
			text = text.substr((int)text.find("# Details for object")+20,strEnd);

			for(int i = 1; i <= objInImg; i++)
			{
			// find position i
				stream.str("");
				stream << i;
				result += " _ Object"+stream.str()+": ";
				
				strStart = (int)text.find(" (Xmin, Ymin) - (Xmax, Ymax) : ") + 31;
				if(objInImg != 1)
					strEnd = (int)text.find("# Details for")-1;
				str = text.substr(strStart, strEnd-strStart);

				result += str;
				if(objInImg != 1)
					text = text.substr(strEnd, text.length());
			}
		}
		else cout << "Unable to open file"; 

		cout << "read file:" << result << endl;

		return result;
	}
}