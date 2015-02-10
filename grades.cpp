// grades.cpp
// CSCI 455 PA5
// Name:Chenyan Geng
// Loginid:cgeng
// 
/*
 * A program to test the Table class.
 * How to run it:
 *      grades [hashSize]
 * 
 * the optional argument hashSize is the size of hash table to use.
 * if it's not given, the program uses default size (Table::HASH_SIZE)
 *
 */

#include "Table.h"

// cstdlib needed for call to atoi
#include <cstdlib>

void printCmdSummary() {
      cout<< "Valid commands are i name score(insert), l name(lookup), c name newscore(change), " << endl;
      cout<< "r name(remove) , p(print all elements), n(print number of entries), h(help),  "  << endl;
	  cout<< "s(print statistics of table) , q(quit). "  << endl;
}

int main(int argc, char * argv[]) {

  // gets the hash table size from the command line

  int hashSize = Table::HASH_SIZE;

  if (argc > 1) {
    hashSize = atoi(argv[1]);  // atoi converts c-string to int

    if (hashSize < 1) {
      cout << "Command line argument (hashSize) must be a positive number" 
	   << endl;
      exit(1);
    }
  }


  Table grades(hashSize);

  grades.hashStats(cout);

  // add more code here
char c;
bool keepgoing = true;
string name;
int score;
bool check;
int *val;

while(keepgoing){
 cout << "\nPlease enter a command [b, i, a, s, p, h, q]: ";
 cin >> c; 
 
  if(c=='i'){
	  cin>>name>>score;
      check = grades.insert(name, score);
	  if(!check){
	   cout<< "Already exists in the talbe"<<endl;
	  }
    }
  else if(c=='c'){
      cin>>name>>score;
	  check = grades.remove(name);
	  if(!check){
	   cout<< "Not exists in the talbe"<<endl;
	  }
	  else{
	   grades.insert(name, score);
	  }
    }
  else if(c=='r'){
      cin>>name;
	  check = grades.remove(name);
	  if(!check){
	   cout<< "Not exists in the talbe"<<endl;
	  }
    }
  else if(c=='l'){
      cin>>name;
	  val = grades.lookup(name);
	  if(val==NULL){
	   cout<< "Not exists in the talbe"<<endl;
	  }
	  else{
	   cout<<"The score is: "<<(*val)<<endl;
	  }
    }
  else if(c=='p'){
      grades.printAll();
    }
  else if(c=='n'){
      cout<<"The number of entries in table is: "<<grades.numEntries()<<endl;
    }
  else if(c=='s'){
      cout << "Hash stats: " << endl;
      grades.hashStats(cout);
    }
  else if(c=='h'){
      printCmdSummary();
    }
  else if(c=='q'){
      keepgoing = false;
      }
  else{
      printCmdSummary();
	  keepgoing = false;
      }
 	  
}

  return 0;
}
