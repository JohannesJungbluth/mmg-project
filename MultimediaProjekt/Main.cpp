#include "OpLib.h"
#include	"stdio.h"
#include	"omp.h"

/*int main(int argc, char ** argv){
	/*DynamicList * l= new DynamicList();
	l->addElement("popo");
	l->addElement("pipi");
	printf("%s\n",(l->getElement<const char *>(0)));
	printf("%s\n",(l->getElement<const char *>(1)));
	delete l;
	getchar();//
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
	getchar();
}*/