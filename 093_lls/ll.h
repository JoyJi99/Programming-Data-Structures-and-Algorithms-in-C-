#ifndef __LL_HPP__
#define __LL_HPP__

#include <assert.h>

#include <cstdlib>
#include <exception>

//YOUR CODE GOES HERE
using namespace std;

class MyException : public exception {
  const char * what () const throw (){
    return "Invalid Index!";
  }
};


template<typename T>
class LinkedList {
private:
  class Node {
  public:
    T data;
    Node * next;
    Node * prev;
    Node(const T & d) : data(d), next(NULL), prev(NULL){}
    Node(const T & d, Node * n, Node * p) : data(d), next(n), prev(p){}
  };
  Node * head;
  Node * tail;
  int size;
public:
  LinkedList() : head(NULL), tail(NULL), size(0){}
  void addFront(const T &item){
    head = new Node(item, head, NULL);
    if (tail == NULL) {
      tail = head;
    }
    else {
      head->next->prev = head;
    }
    size++;
  }
  void addBack(const T &item){
    tail = new Node(item, NULL, tail);
    if (head == NULL) {
      head = tail;
       }
    else {
      tail->prev->next = tail;
    }
    size++;
  }
  bool remove(const T &item){
    Node * cur = head;
    while(cur != NULL){
      if(cur->data == item){
        if(cur == head && cur == tail){
          head = NULL;
          tail = NULL;
        }
        else if (cur == head){
          head = cur->next;
          head->prev = NULL;
        }
        else if(cur == tail){
          tail = cur->prev;
          tail->next = NULL;
        }
        else{cur->prev->next = cur->next;
          cur->next->prev = cur->prev;
        }
        delete cur;
        --size;
        return true;
      }
      cur = cur->next;
    }
    return false;
  }
  T& operator[](int index){
    if(index + 1 > size){
      throw MyException();
    }
    else{
      Node *cur = head;
      for (int i = 0; i < index; i++){
        cur = cur->next;
      }
      return cur->data;
    }
  }
  const T& operator[](int index) const{
    if(index + 1 > size){
      throw MyException();
    }
    else{
      Node *cur = head;
      for (int i = 0; i < index; i++){
        cur = cur->next;
      }
      return cur->data;
    }
  }
  int find(const T &item) const{
    Node *cur = head;
    for (int i = 0; i < size; i++){
      if(cur->data == item){
        return i;
      }
      else {
        cur = cur->next;
      }
    }
    return -1;
  }
  LinkedList(const LinkedList & rhs):head(NULL), tail(NULL), size(0){
    Node *cur = rhs.head;
    while(cur != NULL){
      addBack(cur->data);
      cur = cur->next;
    }
  }
  LinkedList & operator = (const LinkedList & rhs){
    if(this != &rhs) {
      // copy to a new linkedlist
      LinkedList tempList(rhs);
      // delete old linkedList
      while(head != NULL) {
        Node * tempNode = head->next;
        delete head;
        head = tempNode;
      }
      head = tempList.head;
      tail = tempList.tail;
      size = tempList.getSize();
      tempList.head = NULL;
      tempList.tail = NULL;
    }
    return *this;
    }
  ~LinkedList(){
    while (head != NULL) {
      Node * temp = head->next;
      delete head;
      head = temp;
    }
  }
  int getSize() const{
    return size;
  }


};

#endif
