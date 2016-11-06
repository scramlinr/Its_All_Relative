/*
Ryan Scramlin
Program 2
10/31/2016

User inputs a child and its parent.  User continues to input combonations, when no.student no.advisor is input, the user
can than queary relationships of the members.  The user inputs a pair, p q, and displayed is "p is the child, parent, grand parent 
great, great... grandparent or grand child, cousin, or no relation.



*/



# include <iostream>
# include <string>
# include <vector>


using namespace std;

 struct Node
{
	string name;
	Node * parent;
	vector< Node *> children;
	Node(string n = "", Node * p = nullptr) // constructor
	{
		name = n; parent = p;
	}
};
 class Tree
 {
 private:
	 Node * root;
	 Node* retPtr = nullptr;
	 int retLvl= 0;
	
	 void printTree(Node * ptr, int level) {
		/*
		Post:
		Function Prints the family tree.  It takes the root of the tree and a level of 0.  Doing a pre-order traversal of the family tree
		 ,as it drops down a level it prints 5 blankspaces before the name and number of children (5 spaces for each level, i.e. 
		 level 3 has 15 spaces).	 
		 */

		 Node *advisor = ptr;
			 for (int i = 0; i < level * 5; ++i){
				 cout << " ";
	 }
			 cout << advisor->name << " " << advisor->children.size() << endl;

		 if (!advisor->children.empty()) {

		for(int i = 0; i < advisor->children.size(); i++) {
				 printTree(advisor->children[i], level+1);
		
			}
		 }
	
	 
	 
	 };// private version of print

	 Node * find(Node * name, string target) {
		/*
		post:
		in this version of find, the first child of the root gets passed in, along with the name
		of the target.  Each Node is checked for a match, if it matches, retPtr gets set to
		that node, and it is returned. The search continues using a preorder traversal until all nodes of the tree are searched.  If
		the target isn't found, a nullptr is returned.
		
		*/
		 
		 Node *ptr = name;
		 Node* childPtr = nullptr;
		 Node*returnPtr = nullptr;
		 int i = 0;
		 if (ptr->name == target) {
			 retPtr = ptr;
			 return retPtr;
		 }
		 else if (!ptr->children.empty()) {

			 while (i < ptr->children.size()) {

				 if (ptr->children[i]->name == target) {
					 retPtr = ptr->children[i];
					 return ptr->children[i];

				 }
				 else {
					 find(ptr->children[i], target);
				 }
				 i++;
			 }

	 }
				 return ptr;
		 
		 
		
		 
	 }				 // private version of find

 public:
		 
	 Tree(Node * rt = nullptr) {
		/*
		Post:
		Sets the root of the tree.
		*/
		 root = rt;



	 }	
	
	 
	 string getName() {
	/*
	Post: 
	Returns the name of the root of the tree
	
	
	*/
		 return root->name;

	 }

	 void printTree() // public print
	/*
	Post:
	Passes the root and 0 to the private version of printTree
	*/
	 
	 { 
				printTree(root, 0);

	 }

	 void resetPtr() {
		/*
		Post:
		Turns retPtr back to nullPtr to prevent any interference the next time it is used.
		*/
		 
		 retPtr = nullptr;
	 }
	Node * find(string target) // public find
	/*
	Post:
	This version of find checks itself for a match to the target.  If not a match, it passes it's first child to the pivate version 
	of find. It continues to pass children until each one of their sub-trees have been searched.  If no match is found, a nullptr is returned, 
	otherwise the matching node is returned.	
	*/
	
	
	{
		 Node * ptr = nullptr;
		 Node * returnPtr = nullptr;
		 
		 if (target == root->name) {
			 return root;
		 }
		 else {
			 for (int i = 0; i < root->children.size(); i++) {
				 if (root->children[i]->name == target) {
					 return root->children[i];
				 }
				 else {
					 ptr = find(root->children[i],target);
					 
				 }
				 
				  if(ptr != nullptr && ptr->name == target) {
					
					  returnPtr = retPtr;
					  return retPtr;
					
				 }

			 }
		 }

		 
			 return retPtr;
	
	 }


	Node * getRoot() {
	/*
	Post: 
	Returns a pointer to the root
	*/	
		Node * ptr = new Node;
		ptr = root;
		return ptr;
	}



};




	 class Forest
	 {
	 private:
		 vector< Tree > trees;
	 public:
		 bool found = false;
		 int finalLevel = 0;
	
		 
	int getLevel(Node* ptr, string target, int level)
	/*
	Post: 
	Post order traversal through the tree.  Each time the search drops down to the parents children, level is increased by one.  if the target
	is found finalLevel gets set to the current level.  The target should always be found.  This function is only called when the target IS in the 
	tree
	*/	
	
	{
			 if (ptr->name == target) {
				 finalLevel = level;
				 return finalLevel;
			 }

			 if (!ptr->children.empty()) {
				 for (int i = 0; i < ptr->children.size(); i++) {
					
					 if (!ptr->children[i]->children.empty()) {
						 getLevel(ptr->children[i], target, level+1);
					 }
					 else {
						 getLevel(ptr->children[i], target, level+1);
					 }
				 }
			}
		
			 return finalLevel;
		 }
			 
	void print() {
/* 
	Post:
	Sends a tree to be printed.  Each tree is itereated through and printed.

*/

			 for (int i = 0; i < trees.size(); i++) {
				 trees[i].printTree();
				 cout << "\n\n";

			 }

		 }

	void resetFound() {
		/*
		Post:
		Resets found to false;

		*/	
		
		
		found = false;
		 }

	Node * find(string target) {
		/*
		Post:
		Iterates through each tree, and searches for target.  Target is passed up to the trees version of find.  If match is found, for loop breaks
		else a nullptr is returned.
		*/	
		Node * advisPtr = nullptr;
			 
			 
			 for (int i = 0; i < trees.size(); i++) {
				
				 trees[i].resetPtr();
				 advisPtr = trees[i].find(target);
				 if (advisPtr != nullptr && advisPtr->name == target) {
					 return advisPtr;
				 }
		}
				 return advisPtr;
		
		 };

	int getTreeInt(string name) {
		/*
		Post:
		Searches for the tree with the root the same name as the target and returns element.
		*/	
		
		for (int i = 0; i < trees.size(); i++) {
				 if (trees[i].getName() == name) {

					 return i;
					 
				}
			 }
			 return 0;
		 }

	bool familyMemberCheck(Node* name1, Node* name2) {
		/*
		Post: 
		Checks to see if two members have the same common ancestor, thus coming from the same family.  Traces up the family tree by setting the
		value of the node to its parent  until nullptr is reached.  Then, both are checked for a match.
		
		*/	
		
		
		string parent1 = " ";
		string parent2 = " ";

			while (name1->parent != nullptr) {
				name1 = name1->parent;
			}
			parent1 = name1->name;

			while (name2->parent != nullptr) {
				name2 = name2->parent;
			}
			parent2 = name2->name;
			if (parent1 == parent2) {
					return true;
			}
			else {
				return false;
			}
		
		}

	bool checkChild(Node* name1, Node* name2) {			
		/*
		Post: Checks to see if the name2 is a child of name1.  Each child of name1 is iterated through searching for the child.
		If a match is found true is returned.
		
		*/	
		
		if (!name1->children.empty()) {
				  for (int i = 0; i < name1->children.size(); i++) {
					  checkChild(name1->children[i], name2);
				  }
			  
				
			 }
			   if(name1->name == name2->name) {
				 found = true;
			 }	 

			  
			 return found;
		 
		 
		 }

	void relationShip(string name1, string name2) {
			/*
			Post: 
			Each string is searched for and their nodes are returned.  If one == nullptr, they do not exist in any family tree, and are 
			therefore considered not related.  if both nodes arent null then next, they are check to see if they are a child or a parent of one another. 
			If a child - parent relationship exist, the level of the relationship is determined and a message is printed out matching that relationship
			Then they are checked to see if they are from the same tree.  If nothing returns true, it is assumed they must be cousins.
			
			*/
		
		
			Node* first = nullptr;
			 Node* second = nullptr;
			
			 first = find(name1);
			 second = find(name2);
			 int level = 0;

			 if ((first == nullptr || second == nullptr) || (first ->parent==nullptr && second->parent ==nullptr)) {
				 cout <<"no relation" << endl;
			}
			
			
			 else if (checkChild(first, second) == true){
				
				
				 level = getLevel(first, name2, 0);
				
			  if (level == 2) {
				  cout << "grand parent" << endl;
			 }

			 else if (level > 1) {
				
					 for (int i = 0; i < level-2; i++) {
						 cout << "great ";

					 }

					 cout << "grand parent"  << endl;
				 }
				 else {
					 cout << "parent" << endl;
				 }
				 
				 resetFound();
			 }
			 else if (checkChild(second, first) == true) {						//Child Check
				 level = getLevel(second, name1, 0);
				

				 if (level == 2) {
					 cout  << "grand child" << endl;
				 }

				 else if (level > 2) {
					 for (int i = 0; i < level-2; i++) {
						 cout << "great ";
						 
					 }

					cout << "grand child" << endl;
				 }
				 else {
					 cout <<"child"<< endl;
				 }
					 
				
				 resetFound();
			 }
			 else if ((first->parent != nullptr && second->parent != nullptr) && (first->parent->name == second->parent->name)) {			//Parent check
				 cout << "sibling" << endl;
			 }
			 else if (familyMemberCheck(first, second) == false) {
				 cout << "no relation" << endl;
			 }
			 else {
				 cout << "cousin" << endl;

			 }



		 }

	void insert(string name1, string name2) {
		/*
		Post: 
		Four cases are considered in this function.
		1. If both advisor and student do not exists.  They are added to the database.
		2. If the advisor exists, but the student does not; the student is added to the advisors children
		3. If the student exists, but not the advisor.  A new node is created and the student is added to the advisors children.
		4. Both Exist. The student is added to the advisor, and the students old tree is deleted.
		
		*/
			 Node* advisor = find(name2);
			 Node * student = find(name1);

			 if (advisor != nullptr && advisor->name != name2) {
				 advisor = nullptr;
			 }
			 if (student != nullptr && student->name != name1) {
				 student = nullptr;
			 }


			 if (trees.empty()) {
				 Node *advisor = new Node(name2, nullptr);			//Case 1: Forest is empty
				 Node *student = new Node(name1, advisor);
				 advisor->children.push_back(student);

				 Tree treeOne(advisor);
				 trees.push_back(treeOne);

			 }
			 else if (student == nullptr && advisor != nullptr) {
				 
				 Node *student = new Node(name1, advisor);
				 advisor->children.push_back(student);

			 }
			 else if (student != nullptr && advisor == nullptr) {			//Case 4 student exists but advisor does not
				 advisor = new Node(name2, nullptr);
				 advisor->children.push_back(student);
			 }


			 else if (advisor == nullptr && student == nullptr) {			//Case 2: Advisor and student do not exist in data base

				 Node *advisor = new Node(name2, nullptr);
				 Node *student = new Node(name1, advisor);
				 advisor->children.push_back(student);

				 Tree treeOne(advisor);
				 trees.push_back(treeOne);
			 }
			 else if (student != nullptr && advisor != nullptr) {		// Case 3: Both student and advisor in database
				 int i = 0;
				 Node *studentPtr = new Node(name1, advisor);
				 student->parent = advisor;
				 advisor->children.push_back(student);
				 i = getTreeInt(student->name);


				 trees.erase(trees.begin() + i);

			 }
			}
		
	bool insert_UnitTest() {
		/*
		Test to check if roots are being properly added and children are being pushed back.
		
		*/
		
		Forest homeTest;
		Node* testPtr;
		bool test = false;
		
		homeTest.insert("franklin", "owl");
		homeTest.insert("bear", "daniel");
		
		if (homeTest.trees[0].getName() == "owl") {					//root added
			test = true;
		}else {
			test = false;
		}
		
		if (homeTest.trees[1].getName() == "daniel" && test ==true) {
			test = true;
		}
		else {
			test = false;
		} 
		
		testPtr = homeTest.trees[0].getRoot();
		
		if ((testPtr->children[0]->name == "franklin") && (test == true)) {
			test = true;
		}
		else {
			test = false;
		}
		
		testPtr = homeTest.trees[1].getRoot();

		if ((testPtr->children[0]->name == "bear") && (test == true)) {
			test = true;
		}
		else {
			test = false;
		}

	
		return test;
	}

	bool find_UnitTest() {
		Forest homeTest;
		string student;
		string advisor;
		bool test = true;
		vector <string> names = { "franklin", "owl"
			,"beaver", "franklin"
			,"littleBear", "franklin"
			,"baby", "littleBear"
			,"gopher", "baby"
			,"woodchuck", "gopher"
			,"monkey", "owl"
			,"mouse", "bear"
			,"otter", "owl"
			,"duck", "otter"
			,"cat", "otter"
			,"hen", "duck"
			,"bird", "duck"
			,"flea", "rat"
		};

		for (int i = 0; i < names.size(); i++) {
			student = names[i];
			i++;
			advisor = names[i];
			homeTest.insert(student, advisor);
		}

		if (homeTest.find("owl")->name == homeTest.find("owl")->name) {
			test = true;
		}
		else {
			test = false;
		}

		if ((homeTest.find("hen")->name == homeTest.find("hen")->name) && (test == true)) {
			test = true;
		}
		else {
			test = false;
		}
		if ((homeTest.find("franklin")->name == homeTest.find("owl")->children[0]->name) && (test == true)) {

			test = true;
		}
		else {
			test = false;
		}
		if ((homeTest.find("bear")->name == homeTest.find("bear")->name) && (test == true)) {
			test = true;
		}
		else {
			test = false;
		}if ((homeTest.find("mouse")->name == homeTest.find("hen")->name) && (test == true)) {
			test = false;
		}
		else {
			test = true;
		}


		return test;

	}


};

	int main() {
		Forest home;
		string student = "";
		string advisor = "";
		/*
		while (student != ("no.student") || advisor != "no.advisor") {
			cin >> student;
			cin >> advisor;
			if (student != ("no.student") || advisor != "no.advisor") {
				home.insert(student, advisor);
			}
		}
		student = " ";
		advisor = " ";
		cout << endl;

		while (student != "no.student" || advisor != "no.advisor") {
			cin >> student;
			cin >> advisor;
			if (student != ("no.student") || advisor != "no.advisor") {
				home.relationShip(student, advisor);
			}

		}

*/

		if (home.find_UnitTest() == true) {
			cout << "Find is working properly" << endl;
		}
		else {
			cout << "Find is not working properly" << endl;
		}



		if (home.insert_UnitTest() == true) {
			cout << "insert is working properly" << endl;
		}
		else {
			cout << "insert is not working properly" << endl;
		}
	
		 };