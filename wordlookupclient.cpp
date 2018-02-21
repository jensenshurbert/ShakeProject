//Jensen Shurbert
//Shakespeare Lookup wordlookupclient.cpp
//Spring 2018

#include <iostream>
// Stuff for AJAX
#include "cgicc/Cgicc.h"
#include "cgicc/HTTPHTMLHeader.h"
#include "cgicc/HTMLClasses.h"

//Stuff for pipes
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include "fifo.h"
#include "index.h"
#include "wordStem/english_stem.h"
#include <sstream>


using namespace std;
using namespace cgicc; // Needed for AJAX functions.

const string path = "/home/class/SoftDev/Shakespeare/";
const string lastFile = path+"Shakespeare.txt";

void printLines(vector<int> list);
vector<int> pars(string reply);

// Possible values returned by results_select
#define WORD  "Word"

//Convert the words to uppercase
std::string StringToUpper(std::string myString)
{
  const int length = myString.length();
  for(int i=0; i!=length ; ++i)
    {
      myString[i] = std::toupper(myString[i]);
    }
  return myString;
}

// fifo for communication
string receive_fifo = "Wordreply";
string send_fifo = "Wordrequest";

//Stemming the searched word
stemming::english_stem<char, std::char_traits<char> > StemEnglish;
ifstream ssfile;

int main() {
  Cgicc cgi;    // Ajax object
  char *cstr;
  // Create AJAX objects to recieve information from web page.
  form_iterator itname = cgi.getElement("shake");
  
  // create the FIFOs for communication
  Fifo recfifo(receive_fifo);
  Fifo sendfifo(send_fifo);

  // Call server to get results
	string shake = **itname;
  shake = StringToUpper(shake);
  sendfifo.openwrite();
  sendfifo.send(shake);
  
  /* Get a message from a server */
  recfifo.openread();
  string results = recfifo.recv();
  recfifo.fifoclose();
  sendfifo.fifoclose();
  
  cout << "Content-Type: text/plain\n\n";

  
  //cout << "TEST" << endl;
  printLines(pars(results));

  
return 0;
}


	 //parse through comma delimitated list 
    vector<int> pars(string reply){
    	vector<int> result;
    	stringstream ss(reply);
    	int i;
    	char c;
    	
    	//cout << "TEST HERE" << endl;
    	
    	while(ss>>i){
    	
    		result.push_back(i);
    		//cout << i << " ";
    		ss >> c;
    	}
    	
    	
    	return result;
    }
    	//prints lines 
    	void printLines(vector<int> list){
		string pos;
		ssfile.close();
		ssfile.open(lastFile);
  
  		//outputs the lines where each searched word appears in the file
		for (int i=0; i<list.size(); i++){
			//cout << list[i]<< ": ";
			ssfile.seekg(list[i]);
			getline(ssfile,pos);
			cout << pos << "<br>";
		}
		}
		
	
