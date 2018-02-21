#ifndef INDEX_H
#define INDEX_H
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include <vector>

using namespace std;

class bookIndex {
public:
	bookIndex();
	void addWord(string word, int p);
    vector<int> lookup(string word);
    int size();

private:
    map<string, vector<int> > index;
};

#endif /* INDEX_H */
