//#include <stdlib.h>
#include <vector>
#include <iterator>


namespace OpLib{

	class HierElement{

	private:
		std::vector<HierElement *> lower_level;
		HierElement * higher_level;

		bool	worked_on;

	public:
		HierElement(){
			higher_level=NULL;
			std::vector<HierElement *> lower_level(0);
			worked_on=false;
		}

		HierElement(HierElement * higher_level){
			HierElement();
			this->higher_level=higher_level;
		}

		/*!	Will destroy all lower branch elements too!
		*	Never use by yourself, use collapseBranch or setFinished instead.
		*/

		~HierElement(){
			if (higher_level!=NULL){
				higher_level->removeLower(this);
			}
		}

		/*!	Resets the higher level to NULL.
		*
		*/

		void resetHigherLevel(){
			higher_level=NULL;
		}

		void collapseBranch(){
			for (int i=0; i<lower_level.size(); i++){
				lower_level[i]->resetHigherLevel();
				collapseBranch();
			}
			delete this;
		}

		/*!	always use when element isd no longer needed
		*	will eventually delete the element and all lower elements if they aren't needed too.
		*	@returns	true if the element was deleted.
		*/

		bool setFinished (){
			worked_on=false;
			if (checkDispose()){
				delete this;
			}
		}


		bool checkDispose(){
			for (int i=0; i<lower_level.size(); i++){
				if (!lower_level[i]->checkDispose())
					return false;
			}
			return worked_on;
		}

		/*!	intern function
		*	@returns	true if removed
		*/

		bool removeLower(HierElement * lower){
			for (int i=0; i<lower_level.size(); i++){
				if (lower_level.at(i)==lower){
					lower_level.erase(lower_level.begin()+i);
					checkDispose();
					return true;
				}
			}
			return false;
		}


		void addLowerElement(HierElement * lower){
			lower_level.push_back(lower);
		}

		std::vector<HierElement *> getLowerElements(){
			return lower_level;
		}
	};
}