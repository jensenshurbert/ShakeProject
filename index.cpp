#include "index.h"

//constructor
bookIndex::bookIndex(){
}


void bookIndex::addWord(string word, int p){
	index[word].push_back(p);

}

vector<int> bookIndex::lookup(string word){	
	cout << "lookup:" << word << ":" << index[word].size() << endl; 
	return index[word];
}

//int bookIndex::size() {
//	return index.size();
//}

