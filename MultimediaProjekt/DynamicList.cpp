#pragma once

#include	"stdlib.h"
#include	"stdio.h"

/*!
*	Models a linked list.
*
*/

class DynamicList{

private:
	struct node{
		void * value;
		node * next;
		node * previous;
	};


	int size;	//0 by default
	class input_type;
	node * first;
	node * last;

	void deleteNode(node * n){
		delete n->value;

		if (n->previous!=NULL)			//n is not first
			n->previous->next=n->next;
		else
			first=n->next;
		
		if (n->next!=NULL)				//n is not last
			n->next->previous=n->previous;
		else
			last=n->previous;
		delete n;
		size--;
	}
	
public:
	DynamicList(){
		size=0;
		first =NULL;
		last =NULL;
	}

	/**	Add element at last position.
	*	@param	Pointer to an element (has to be created with new before).
	*	@returns	false if elemnt is already in the list
	*/
	bool addElement(void * element){
		if (contains(element))
			return false;
		node * n=new node;
		n->next=NULL;
		n->value=element;
		if (first==NULL)
		{
			first=n;
			n->previous=NULL;
		}
		else{
			last->next=n;
			n->previous=last;
		}
		last=n;
		size++;
		return true;
	}

	int getSize(){
		return size;
	}

	void bla (int ** in){
#pragma omp parallel for
		for (int x=0; x<100; x++){
			for (int y=0; y<100; y++){
				in[x][y]=0;
			}
		}

	}


	bool contains(void * element){
		node * act=first;
		while (act!=NULL){
			if (act->value==element)
				return true;
			act=act->next;
		}
		return false;
	}

	~DynamicList(){
		while (first!=NULL)
			deleteElement(0);
	}

	/**	Delete element.
	*	@param	Element element.
	*	@returns false if element is not in the list.
	*/

	bool deleteElement(void * element){
		node * act=first;
		while (act!=NULL){
			printf("b");
			fflush(stdout);
			if (act->value==element)
				goto found;
			act=act->next;
		}
		return false;		//act==NULL, element not in list
found:
		deleteNode(act);
		return true;
	}

	/**	Delete element at position n.
	*	@param	Position n.
	*	@returns false if element is not in the list.
	*/

	bool deleteElement(int pos){
		node * act=first;
		for (int i=0; i<pos; i++){
			if (act!=NULL)
				act=act->next;
			else
				return false;
		}
		deleteNode(act);
	}

	/**	Get element at position n.
	*	@param	Position n.
	*	@returns NULL if IndexOutOfBounds, the pointer to the element otherwise.
	*
	*/
	template <class type>
	type * getElement(int n){
		node * act=first;
		for (int i=0; i<n; i++){
			if (act!=NULL)
				act=act->next;
		}
		if (act==NULL)
			return NULL;
		else
			return (type *)act->value;
	}

};