/***************************************************************************
 * wordservercpp  -  Program to serve of shakespeare word statistics
 *
 * Jensen SHurbert
 *
 * This program runs as a background server to a CGI program, providinging data on Shakespeare words.
 * 
 * 
 *
 ***************************************************************************/
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <map>
#include "fifo.h"
#include "index.h"
#include "wordStem/english_stem.h"
#include <sstream>


using namespace std;

const string path = "/home/class/SoftDev/Shakespeare/";
const string lastFile = path+"Shakespeare.txt";
ifstream ssfile;

/* Fifo names */
string receive_fifo = "Wordrequest";
string send_fifo = "Wordreply";

/* Name of name data files */
// Files with the name data

vector<string> getwords(string line);
string removeSpecials(string str);
void createIndex(bookIndex &index);

stemming::english_stem<char, std::char_traits<char> > StemEnglish;


/* Server main line,create name MAP, wait for and serve requests */
int main() {
cout << "start!" << endl;
  string inMessage, shake;
  int pos;

  // Build the name maps
  //NameMap lastMap(lastFile);
  //NameMap femaleMap(femaleFile);
  //NameMap maleMap(maleFile);
  //vector<NameEntry> matchList; // place to stare the matches
  
	//ifstream ssfile;

	bookIndex index;
	int p=ssfile.tellg();
	cout << "create index" << endl;
	createIndex(index);
	//cout << "index:" << index.size() << endl;
  

  // create the FIFOs for communication
  Fifo recfifo(receive_fifo);
  Fifo sendfifo(send_fifo);

  while (1) {

    /* Get a message from a client */
    cout << "Ready to read" << endl;
    recfifo.openread();
    inMessage = recfifo.recv();
    cout << "Read:" << inMessage << endl;
    /* Parse the incoming message */
    /* Form:  $type*name  */
    pos=inMessage.find_first_of("*");
    if (pos!=string::npos) {
      inMessage.substr(0,pos);
      pos++;
    } else {
      pos = 0;
    }
    shake = inMessage.substr(pos,2000);
    //cout << "Message: " << " : " << shake << endl;
      
      //stem inputted word, code from Skon
	transform(shake.begin(), shake.end(), shake.begin(), ::toupper);
	StemEnglish(shake);
      
    vector<int> list=index.lookup(shake);
	string results;
	ssfile.close();
	ssfile.open(lastFile);
	
	//cout << "HELLO: " << shake << ":" << list.size() << endl;

    for (int i = 0; i < list.size(); i++) {
    	//cout << "Test: " <<list[i] << ":" << i << endl;
		results += to_string(list[i]) + ",";
		//cout << list[i];
    }

    cout << " Results: " << results << endl;

    sendfifo.openwrite();
    sendfifo.send(results);
    sendfifo.fifoclose();
    recfifo.fifoclose();
    
  }
}



    //gets words out of the line, creates string vector of words
    vector<string> getwords(string line){
    	istringstream iss(line);
    	vector<string> words;
    	string s;
    	do{
    		iss >> s;
    		if (s.length() > 0 && s != " "){
    			words.push_back(s);
    		}
    		s = "";
    	} while(iss);
    	return words;
    }
    
    
   
    
    //removes special characters
    string removeSpecials(string str){
    	int i=0, len = str.length();
    	while (i < len) {
    		char c = str[i];
    		if(((c >= '0')&&(c <= '9')) || ((c >= 'A')&&(c <= 'Z')) || ((c >= 'a')&&(c <= 'z')) || c == '/' || c == ' ') {
    			if ((c >= 'A')&&(c <= 'Z')) str[i] += 32;
    			i++;    		
    		} else{
    			str.erase(i, 1);
    			--len;
    		}
    	}
    	return str;
    }
    
    //creates index
	void createIndex(bookIndex &index){
		//open Shakespeare File
    	//ifstream ssfile;
    	ssfile.open(lastFile);
    
    	//bookIndex index;
		int p=ssfile.tellg();
    
		//creating the index of the stemmed words
		while(!ssfile.eof()){
			string line;
			getline(ssfile,line);
			vector<string> words = getwords(line);
		
			//adds each word into the index
			for(int i=0; i<words.size(); i++){
		
				//stemming the words into the index, code from Skon
				transform(words[i].begin(), words[i].end(), words[i].begin(), ::toupper);
				string stemWord = words[i];
				StemEnglish(words[i]);
			
				//adding stemmed words to index
				index.addWord(words[i],p);
			}
			p=ssfile.tellg();
		}
		}
