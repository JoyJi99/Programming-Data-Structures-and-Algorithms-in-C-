#include <iostream>
#include "set.h"
using namespace std;

template<typename T>
class BstSet:public Set<T> {
private:
  class Node {
  public:
    T key;
    Node * left;
    Node * right;
    Node(const T & k):key(k), left(NULL), right(NULL){}
  };
  Node * root;

public:
  //constructor
 BstSet():root(NULL){}
  //copy constructor
 BstSet(const BstSet & rhs) : root(NULL) {root = copy(rhs.root);}

  Node * copy(Node * current){
    if (current == NULL) {
      return NULL;
    }
    Node * root = new Node(current->key);
    root->left = copy(current->left);
    root->right = copy(current->right);
    return root;
  }
  BstSet & operator=(const BstSet & rhs) {
    if (this != &rhs) {
      destroy(root);
      root = copy(rhs.root);
    }
    return *this;
  }

  virtual void add(const T & key){
    root = add(root, key);
  }
  Node * add(Node * cur, const T & key){
    if (cur == NULL){
      Node * ans = new Node(key);
      return ans;
    }
    else {
      if (key < cur->key) {
	cur->left = add(cur->left, key);
      }
      else if (key > cur->key) {
	cur->right = add(cur->right, key);
      }
    return cur;
    }
  }

  virtual bool contains(const T & key) const{
    Node * cur = root;
    while (cur != NULL) {
      if (key == cur->key){
	return true;
      }
      else if (key < cur->key){
	cur = cur->left;
      }
      else {
	cur = cur->right;
      }
    }
    return false;
  }

  virtual void remove(const T & key){
    Node ** cur = &root;
    while(*cur != NULL){
      if((*cur)->key == key){
	if((*cur)->left == NULL){
	  Node *temp = (*cur)->right;
          delete *cur;
          *cur = temp;
        }
	else if((*cur)->right == NULL){
	  Node *temp = (*cur)->left;
          delete *cur;
          *cur = temp;
        }
	else{
	  Node **temp = &((*cur)->right);
          while ((*temp)->left != NULL){
	    temp =&((*temp)->left);
          }
          (*cur)->key = (*temp)->key;
          Node *rightChild = (*temp)->right;
          delete (*temp);
          *temp = rightChild;
        }
      }
      else if((*cur)->key > key){
	cur = &((*cur)->left);
      }
      else{
        cur = &((*cur)->right);
      }
   }
  }

  void destroy(Node * node){
    if(node != NULL){
      destroy(node->left);
      destroy(node->right);
      delete node;
    }
  }
  virtual ~BstSet<T>() {
    destroy(root);
    root = NULL;
  }

  void in(){
    inOrderTraverse(root);
  }
  void inOrderTraverse(Node * node){
    if(node != NULL){
      inOrderTraverse(node->left);
      cout << node->key << endl;
      inOrderTraverse(node->right);
    }
  }
};
