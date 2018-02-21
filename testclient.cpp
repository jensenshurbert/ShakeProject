#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "fifo.h"
#include <sstream>


using namespace std;
string receive_fifo = "Wordreply";
string send_fifo = "Wordrequest";


vector<int> pars(string reply);
void printLines(vector<int> list);

const string path = "/home/class/SoftDev/Shakespeare/";
const string lastFile = path+"Shakespeare.txt";
ifstream ssfile;


int main() {
  string message, shake;
  string reply;

  while (1) {
	cout << "Enter a word:";
	cin >>  shake;
	transform(shake.begin(), shake.end(), shake.begin(), ::toupper);

	
	// create the FIFOs for communication
	Fifo recfifo(receive_fifo);
	Fifo sendfifo(send_fifo);

	message = "$WORD*" + shake;
	cout << "Send:" << message << endl;
	sendfifo.openwrite();
	sendfifo.send(message);

	/* Get a message from a server */
	recfifo.openread();
	reply = recfifo.recv();
	
	recfifo.fifoclose();
	sendfifo.fifoclose();
	cout << "Server sent: " << reply << endl;
	
	printLines(pars(reply));

  }


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
    	
    	cout << "Resulting list of integers: " << endl;
    	
    	for(i=0;i<result.size();i++){
    		cout << result.at(i)<< endl;
    	}
    	return result;
    }
    
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
