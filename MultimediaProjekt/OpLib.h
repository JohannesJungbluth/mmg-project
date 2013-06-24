#ifndef	_OP_LIB_H
#define	_OP_LIB_H


#include "DynamicList.cpp"
#include <stdlib.h>

/**	OpLib contains standart operations like isOverlapping()
*	and standart classes for data handling like WorkObject or
*	top level abstract classes like DynHierObject
*/
namespace OpLib{

	/**	Top level abstract class for data handling.
	*	SynHierObjects are memory dynamical and organized in a tree structure.
	*	As soon as an SynHierObjects worked_on_flag is set to true and isFinishedBeingWorkedOn returns true
	*	and true for all sub elements lower in the hierarchy, it is deleted.
	*/
	class SynHierObject{

		//omp critical locks: elements

	private:
		/**
		*	Lower level objects. Should be dynamical.
		*/
		DynamicList * lower_elements;

		/**
		*	Higher level element.
		*/
		SynHierObject * higher_element;

		/**
		*	Describes, if this object still is needed, e.g. if it's been worked on.
		*	True by default.
		*/
		bool worked_on_flag;

		/**	Notifies the higher element that this element is no longer needed and requests 
		*	a check for disposing.
		*/
		void notifyHigher(){
			
		}

		/**	Disposes this element and all it's sub elements.
		*
		*/
		void dispose(){
			for (int i=0; i<lower_elements->getSize(); i++){
				lower_elements->getElement<SynHierObject>(i)->dispose();
			}
			delete lower_elements;
			lower_elements=NULL;
		}

		void init(){
			worked_on_flag=true;
			this->lower_elements=new DynamicList();
		}

		bool checkIfDisposable(){
			if (worked_on_flag)
				return false;
			if (lower_elements==NULL)
				return true;
			for (int i=0; i<lower_elements->getSize(); i++){
				if (!(lower_elements->getElement<SynHierObject>(i))->checkIfDisposable())
					return false;
			}
			return true;
		}

	public:

		SynHierObject(){
			this->higher_element=NULL;
			init();
		}

		SynHierObject(SynHierObject * higher_element){
			this->higher_element=higher_element;
			init();
		}

		//test

		/**	Always call when this element is no longer needed.
		*	Eventually disposes of this element and all other related
		*	elements which are no longer needed.
		*	@returns true if it was disposed.
		*/
		bool finishWorking(){
			worked_on_flag=false;
			if (checkIfDisposable()){
				dispose();
			}
		}

	};
}
#endif