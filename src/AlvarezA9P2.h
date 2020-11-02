/*
 * AlvarezA9P2.h
 *
 *  Created on: May 13, 2020
 *      Author: Enrique Alvarez
 */

#ifndef ALVAREZA9P2_H_
#define ALVAREZA9P2_H_

template <class T>
struct Treenode {
	T nodeValue;
	Treenode <T> * Lchild;
	Treenode <T> * Rchild;
	int BF;
	int heightL;
	int heightR;
};



template <class T>
class BST{

public:

Treenode <T> * treeRoot = nullptr;
bool search(T &);  //searches if a specific value is present, returns true if found -- done
void insert (T &); //inserts a specified value into the correctly ordered spot
void udelete(T &); //starts at the root and compares to every child, once found calls func to delete and fix tree
void print2D();
void traverseInOrder();
void traversePreOrder();
void traversePostOrder();
void setallBF();
int getLargestBF();
int height();


protected:

private:

void print2DInternal(Treenode<T> *, int);
void deleteInternal(Treenode<T> * &);
void traverseInOrder(Treenode <T> *);
void traversePreOrder(Treenode<T> *);
void traversePostOrder(Treenode<T> *);
void setallBFInternal(Treenode<T> *);
int heightInternal(Treenode<T> *);
int getLargestBFInternal(Treenode<T> *);




};

template <class T>
bool BST<T>::search(T & target){
	bool located; 		//found flag
	Treenode <T> * current; //the node we are viewing
	if(treeRoot == nullptr){ //root contains no values so it is empty
		throw("the tree is empty!");
	}
	else
	{
		located = false;   //since its not empty located is false while we search
		current = treeRoot;        // start at the top of the tree
		while(current != nullptr && !located){		// while there is data  and we have not found target
			if(current ->nodeValue == target){	//check our current node
				located = true;
			}
			else if(current -> nodeValue > target){ //if our target is smaller we go left
				current = current ->Lchild;
			}
			else{							// if our target is larger we go right
				current = current ->Rchild;
			}
		}
	}
	return located;
}

template <class T>
void BST<T>::insert(T & value){
	Treenode <T> * current; //node we are viewing
	Treenode <T> * trailing;//node we just viewed
	Treenode <T> * temp;


	temp = new Treenode<T>;      // temp is a new node with a value but no children
	temp -> nodeValue = value;
	temp -> Lchild = nullptr;
	temp -> Rchild = nullptr;
	if(treeRoot == nullptr){	// if we have a completely empty tree, our value is not the root
		treeRoot = temp;
	}
	else{
		current = treeRoot;		//otherwise start our search for the correct spot from the root
		while(current != nullptr){		//while not at an end node
			trailing = current;			// do this to remember where we came from
			if(current->nodeValue == value){ //error of value already present
				throw("Duplicate");
			}
			else if(current -> nodeValue > value){ //if our value is smaller than our current location, we go left
				current = current -> Lchild;
			}
			else{				// if value is bigger we go right
				current = current -> Rchild;
			}
		}
		//now our current is a nullptr, meaning we are at an end node
		if(trailing-> nodeValue > value){  //If our value is smaller than current value we make the current left pointer point to our node of value
			trailing -> Lchild = temp;
		}
		else{ // if it is greater we make the right child point to node with value
			trailing -> Rchild = temp;
		}
	}
}

template <class T>
void BST<T>::udelete(T & value){

	Treenode <T> * current = treeRoot;
	Treenode <T> * trailing = treeRoot;
	bool found = false;

	if(treeRoot == nullptr){	// cant delete whats not there
		throw ("error empty tree");
	}
	else{					//tree is non empty
		current = treeRoot;
		trailing = treeRoot;
		while(current != nullptr && !found){  // while there is stil nodes to traverse and we dont have a match
			if(current -> nodeValue == value){		//exits while if we find our target
				found = true;
			}
			else{
				trailing = current;		//keep track of trail before we look at its children
				if(current ->nodeValue > value){	//if our target is less than current value we go left andrepeat
					current = current-> Lchild;
				}
				else{		// if our target is greater than current val we go right
					current = current->Rchild;
				}
			}
		}
		if(current == nullptr){				// we have reached the bottom of the tree without finding our target
			cout << "not found error" << endl;
		}
		else{
			if(current == treeRoot){	// if our target is the root then we will delete that
				deleteInternal(treeRoot);
			}
			else if(trailing -> nodeValue > value){ // checks which way we just went with trailing so we can delete correct pointer
				deleteInternal(trailing->Lchild);
			}
			else{
				deleteInternal(trailing->Rchild);
			}
		}
	}
}




template <class T>
void BST<T>::traverseInOrder(){
	traverseInOrder(treeRoot);
}

template <class T>
void BST<T>::traversePreOrder(){
	traversePreOrder(treeRoot);
}

template <class T>
void BST<T>::traversePostOrder(){
	traversePostOrder(treeRoot);

}

template <class T>
void BST<T>::print2D(){
	print2DInternal(treeRoot, 0);
}

template <class T>
void BST<T>::deleteInternal(Treenode<T> * & node){
	Treenode<T> * current;			//pointer to traverse
	Treenode <T> * trailCurrent;		//pointer to trail current
	Treenode <T> * temp; 			//pointer to delete node

	if( node == nullptr){			//error passing a node with nothing to delete
		throw length_error("Target node is null");
	}
	else if(node -> Lchild == nullptr){ //parent node of target has nullptr as left link
		temp = node;					//copy pointer to node to delete
		node = temp -> Rchild;			// connect the gap to replace our deleted value
		delete temp;					//deallocate mem
	}
	else if(node -> Rchild == nullptr){
		temp  = node;					//same as above but for opposite child
		node = temp ->Lchild;
		delete temp;
	}
	else{								// if we are not deleting an end node
		current = node -> Lchild;		//grab the child of target
		trailCurrent = nullptr;

		while (current -> Rchild != nullptr){	// while loop as long as children still have data travels right
			trailCurrent = current;
			current = current -> Rchild;
		}
		node -> nodeValue = current -> nodeValue; // overwrite the target data with the following data
		if(trailCurrent == nullptr){
			node -> Lchild = current -> Lchild;   //if the trail is an end node we replace the child of target with our current left child
		}
		else{											// otherwise we use our trails children to overwrite
			trailCurrent -> Rchild = current -> Lchild;
		}
		delete current;					//deallocates the mem
	}
}

template <class T>
void BST<T>:: traverseInOrder(Treenode <T> * node){
	if(node != nullptr){			//if not at an end node
		traverseInOrder(node->Lchild);  // traverse left subtree recursively
		cout << node ->nodeValue << " "; // prints data
		traverseInOrder(node -> Rchild); // traverse the right subtree
	}
}

template <class T>
void BST<T>::traversePreOrder(Treenode<T> * node){
	if(node != nullptr){		//if not at an end node
		cout << node ->nodeValue << " "; // prints the data
		TraversePreOrder(node -> Lchild); // traverse the left subtree
		TraversePreOrder(node -> Rchild); // traveerse the right subtree
	}
}

template <class T>
void BST<T>::traversePostOrder(Treenode<T> * node){
	if(node != nullptr){		//if not at an end node
		traversePostOrder(node -> Lchild); // traverse left subtree
		traversePostOrder(node -> Rchild); // traverse right subtree
		cout << node -> nodeValue << " "; // prints data
	}

}

template <class T>
void BST<T>::print2DInternal(Treenode<T> *node, int space){
	int COUNT = 5;
	if(node == nullptr){		// does nothing if there is no data to print
		return;
	}
	space += COUNT;
	print2DInternal(node-> Rchild, space);  //we go right first since we print out sideways
	cout << endl;
	for(int i = COUNT; i < space; i++){   // spaces to get them on the same column
		cout << " ";
	}
	cout << node -> nodeValue << "(" << node->BF << ")" << "\n";
	print2DInternal(node -> Lchild, space);
}



template <class T>
int BST<T>:: height(){
	return heightInternal(treeRoot);
}

template <class T>
int BST<T>:: heightInternal(Treenode<T> * node){

	if(node !=nullptr){
		node->heightL = heightInternal(node->Lchild);    //recursibvely call height to continue down the children and increment height by 1
		node->heightR = heightInternal(node->Rchild);
		if(node->heightL > node->heightR){
			return node->heightL + 1;
		}
		else{
			return node->heightR + 1;
		}
	}
	else{
		return -1;
	}
}

template <class T>
void BST<T>::setallBF(){
	setallBFInternal(treeRoot);
}

template <class T>
void BST<T>::setallBFInternal(Treenode<T> * node){
	if(node!= nullptr){

		node ->heightL = heightInternal(node->Lchild);       //call for the heights, which is how we determine BF
		node->heightR = heightInternal(node->Rchild);
		node->BF =  node->heightR - node->heightL;         //set  BF of each node, which is difference of heights
		setallBFInternal(node->Lchild);              //recursively set height
		setallBFInternal(node->Rchild);
		return;
	}
	else{
		return;
	}
}
template<class T>
int BST<T>::getLargestBF(){
	return getLargestBFInternal(treeRoot);
}

template <class T>
int BST<T>::getLargestBFInternal(Treenode<T> * node){
	if(node != nullptr){
		int LLarge = getLargestBFInternal(node->Lchild); //recursively calls getBF, going down every nodes child
		int RLarge = getLargestBFInternal(node->Rchild);
		if(abs(node->BF)> abs(LLarge)){			//we keep a left and right large, updating if we find a larger one
			LLarge = node->BF;
		}
		else if(abs(node->BF)> abs(RLarge)){
			RLarge = node->BF;
		}
		if(abs(LLarge) > abs(RLarge)){  //once we have checked all the BFs we compare the left and right to have the largest BF
			return LLarge;
		}
		else{
			return RLarge;
		}
	}
	else{
		return 0;
	}
}




#endif /* ALVAREZA9P2_H_ */
