//============================================================================
// Name        : AlvarezA9P2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;
#include "AlvarezA9P2.h"

int main(){
	BST <int> mytree;
	int i;
	bool b;
	// start with this small tree and test code
	// will be easier to debug
	/*
	i=5;
	mytree.insert(i);
	i=8;
	mytree.insert(i);
	i=3;
	mytree.insert(i);
	i=12;
	mytree.insert(i);
	i=9;
	mytree.insert(i);
	*/
	// malik p 622
	int array[14] = {60,50,70,30,53,80,35,57,75,32,40,77,48,45};
	for (int i=0;i<14;i++){
		mytree.insert(array[i]);
	}
	cout << "******************************************" << endl;
	cout << "original tree" << endl;
	cout << "height of original tree " << mytree.height() << endl;
	mytree.print2D();
	mytree.setallBF();
	cout << "******************************************" << endl;
	cout << "tree after setallBF" << endl;
	mytree.print2D();
	cout <<"largest BF " << mytree.getLargestBF() << endl;
	cout << "******************************************" << endl;
	cout << "now trying delete 35, then delete 45" << endl;
	i = 35;
	mytree.udelete (i);
	i = 45;
	mytree.udelete (i);
	mytree.setallBF();
	mytree.print2D();
	cout <<" largest BF " << mytree.getLargestBF() << endl;
	return 0;
}
