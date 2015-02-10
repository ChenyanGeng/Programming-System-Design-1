#include "Table.h"

#include <iostream>
#include <string>
#include <cassert>
#include <string>
#include <cctype>

using namespace std;

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

static bool listRemove(ListType &list, string target);
static bool listInsert(ListType &list, string targetKey, int targetValue);
static int* listLookup(ListType &list, string target);
static void listPrint(ListType list);
static bool listEqual(ListType list1, ListType list2);
static int listNum(ListType list);
 
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
 if(listEqual(p, l)){
   return false;
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
  cout << "<empty>"<<endl;
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




int main (){
 ListType mylist = NULL;
 listInsert(mylist, "elephant", 1);
 listInsert(mylist, "dog", 1);
 listInsert(mylist, "fish", 3);
 listInsert(mylist, "dog", 1);
 listInsert(mylist, "burger", 1);
 if(listInsert(mylist, "snake", 1)){
 cout<<"snake inserted"<<endl;
 }
 listInsert(mylist, "dog", 2);
 listPrint(mylist);
 cout<<"listNum is "<<listNum(mylist)<<endl;
 if(listRemove(mylist, "burger")){
 cout<<"burger removed"<<endl;
 }
 if(listRemove(mylist, "dumpling")){
 cout<<"dumpling removed"<<endl;
 }
 if(listRemove(mylist, "elephant")){
 cout<<"elephant removed"<<endl;
 }
 
 cout<<"The list is now: "<<endl;
 listPrint(mylist);
 cout<<"listNum is "<<listNum(mylist)<<endl;
 int *p1 = listLookup(mylist, "fish");
 int *p2 = listLookup(mylist, "snake");
 int *p3 = listLookup(mylist, "curry");
 cout<<"fish is at "<<*p1<<endl;
 cout<<"snake is at"<<*p2<<endl;
 if(p3 == NULL){  
  cout<<"curry is not here"<<endl;
 } 
 return 0;
}


