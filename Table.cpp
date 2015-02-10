// Table.cpp  Table class implementation
// CSCI 455 PA5
// Name:
// Loginid:

/*
 * Modified 11/22/11 by CMB
 *   changed name of constructor formal parameter to match .h file
 */

#include "Table.h"

#include <iostream>
#include <string>
#include <cassert>

//*************************************************************************
// Node class definition and member functions
//     You don't need to add or change anything in this section

// Note: we define the Node in the implementation file, because it's only
// used by the Table class; not by any Table client code.

struct Node {
  string key;
  int value;

  Node *next;

  Node(const string &theKey, int theValue);

  Node(const string &theKey, int theValue, Node *n);
};

Node::Node(const string &theKey, int theValue) {
  key = theKey;
  value = theValue;
  next = NULL;
}

Node::Node(const string &theKey, int theValue, Node *n) {
  key = theKey;
  value = theValue;
  next = n;
}

typedef Node * ListType;

//*************************************************************************
static bool listRemove(ListType &list, string target);
static bool listInsert(ListType &list, string targetKey, int targetValue);
static int* listLookup(ListType &list, string target);
static void listPrint(ListType list);
static bool listEqual(ListType list1, ListType list2);
static int listNum(ListType list);

ListType *data;
int x;

Table::Table() {
 data = new ListType[HASH_SIZE];
  hashSize = HASH_SIZE;
 for(x=0;x<hashSize;x++){
  data[x] = NULL;
 }
}


Table::Table(unsigned int hSize) {
 data = new ListType[hSize];
 hashSize = hSize;
 cout<<"in the table hSize, and arrlength= "<<arrlength;
 for(x=0;x<hashSize;x++){
  data[x] = NULL;
 }
}


int * Table::lookup(const string &key) {
  return listLookup(data[hashCode(key)], key);   // dummy return value for stub
}

bool Table::remove(const string &key) {
  return listRemove(data[hashCode(key)], key);  // dummy return value for stub
}

bool Table::insert(const string &key, int value) {
  return listInsert(data[hashCode(key)], key, value);  // dummy return value for stub
}

int Table::numEntries() const {
  int i;
  int sum = 0;
  for(i=0; i<arrlength;i++){
   sum = sum + listNum(data[i]);
  }
  int re = sum;
  return re;      // dummy return value for stub
}


void Table::printAll() const {
 int i;
 for(i=0; i<arrlength; i++){
  listPrint(data[i]);
 }
}

void Table::hashStats(ostream &out) const {
 int i;
 int count = 0;
 int num = 0;
 int longest = 0;
 out<<"number of buckets: "<<arrlength<<endl; 
 out<<"number of entries: "<<numEntries()<<endl;
 for(i=0; i<arrlength; i++){
  if(data[i] != NULL){
   count++;
   num = listNum(data[i]);
   if(num>longest){
    longest = num;
   }
  }
 }
 out<<"number of non-empty buckets: "<<count<<endl;
 out<<"longest chain: "<<longest<<endl; 
}


// add definitions for your private methods here


 
static int* listLookup(ListType &list, string target){
 ListType l = list;
 while(l != NULL){
  if(l->key == target){
   return &(l->value);
   }
  l = l->next;
 }
 return NULL;
}

static bool listEqual(ListType list1, ListType list2){
 if(((list1->key)==(list2->key))&&((list1->value)==(list2->value))){
  return true;
 }
 else{
  return false;
  }
}

static bool listInsert(ListType &list, string targetKey, int targetValue){
 ListType p = new Node(targetKey, targetValue);
 ListType l = list;
 if(list == NULL){ //empty case
  list = p;
  return true;
 }
 if(list->next == NULL){  //only one element in list
  if(listEqual(p, list)){
   return false;
  }
 }
 while(l->next != NULL){
  if(listEqual(p, l)){
   return false;
  }
  l = l->next;
 }
 l->next = p;
 return true;
}

static bool listRemove(ListType &list, string target){
 ListType l = list;
 if(list == NULL){  //empty case
  return false;
 } 
 if(list->key == target){ //delete first one
  ListType dead = list;
  list = dead->next;
  delete dead;
  return true;
 }
 while(l->next != NULL){
  if(l->next->key == target){
   ListType dead = l->next;
   l->next = dead->next;
   delete dead;	
   return true;   
  }
  l = l->next;
 }
 return false; 
}

static void listPrint(ListType list){
 ListType l = list;
 if(list == NULL) {
 // cout << "<empty>"<<endl;
 return;
 }
 while (l != NULL) {
  cout << l->key << " "<<l->value<<endl;
  l = l->next;
  }
}

static int listNum(ListType list){
 int count = 0;
 ListType l = list;
 while(l != NULL){
  count++;
  l = l->next;
 }
 return count;
} 
