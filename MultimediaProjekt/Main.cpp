#include "OpLib.h"
#include "stdio.h"
#include "omp.h"
#include "Classify.h"


#define FILEPATH1 "crop_000010.txt"
#define FILEPATH2 "person_050.txt"
#define FILEPATH1I "crop_000010.png"
#define FILEPATH2I "person_050.png"

#define PATH "Train/pos/"


using namespace std;
using namespace cv;

int main(int argc, char ** argv){

	string text = Classify::readFile(FILEPATH1);
	Classify::writeFile(text, PATH);
	Classify::showAndAnnotateImg(FILEPATH1I, text);

	text = Classify::readFile(FILEPATH2);
	Classify::writeFile(text, PATH);
	Classify::showAndAnnotateImg(FILEPATH2I, text);

	getchar();

	return 0;
}