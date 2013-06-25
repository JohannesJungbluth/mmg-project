#include "OpLib.h"
#include "stdio.h"
#include "omp.h"
#include "Classify.h"

#define FILEPATH1 "crop_000010.txt"
#define FILEPATH2 "crop_000603.txt"
#define FILEPATH3 "person_044.txt"
#define FILEPATH4 "person_050.txt"
#define FILEPATH1I "crop_000010.png"
#define FILEPATH2I "crop_000603.png"
#define FILEPATH3I "person_044.png"
#define FILEPATH4I "person_050.png"

using namespace cv;
using namespace std;

int main(int argc, char ** argv){
	/*DynamicList * l= new DynamicList();
	l->addElement("popo");
	l->addElement("pipi");
	printf("%s\n",(l->getElement<const char *>(0)));
	printf("%s\n",(l->getElement<const char *>(1)));
	delete l;
	getchar();
	int a=0;
	printf("Num procs: %i\n", omp_get_num_procs());
#pragma omp parallel num_threads(300)
	{
		a++;
#pragma omp critical(are_a)
		{
			printf("Hello from Thread %i, a is %i\n", omp_get_thread_num(),a);
		}
	}
	getchar();*/

	//Classify::writeFile(Point(1,1), Point(100,100));

	stringstream ss;
	
	string text = Classify::readFile(FILEPATH1);
	Classify::showAndAnnotateImg(FILEPATH1I, text);

	text = Classify::readFile(FILEPATH2);
	Classify::showAndAnnotateImg(FILEPATH2I, text);

	text = Classify::readFile(FILEPATH3);
	Classify::showAndAnnotateImg(FILEPATH3I, text);

	text = Classify::readFile(FILEPATH4);
	Classify::showAndAnnotateImg(FILEPATH4I, text);

	return 0;
}