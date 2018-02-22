#include "index.h"
//AP is changing your code for the github HW assignment
//constructor
bookIndex::bookIndex(){
}


void bookIndex::addWord(string word, int p){
	index[word].push_back(p);
	//ap
}

vector<int> bookIndex::lookup(string word){	
	cout << "lookup:" << word << ":" << index[word].size() << endl; 
	return index[word];
}

//int bookIndex::size() {
//	return index.size();
//}

