#include <stdexcept>
#include <iostream>
#include "map.h"
using namespace std;

template<typename K, typename V>
class BstMap:public Map<K, V> {
private:  
  class Node {
    public:  
    K key;
    V value;
    Node * left;
    Node * right;
    Node(const K & k, const V & v):key(k), value(v), left(NULL), right(NULL){}
  };
  Node * root;

public:
  //constructor
 BstMap():root(NULL){}
  //copy constructor
 BstMap(const BstMap & rhs) : root(NULL) {root = copy(rhs.root);}

  Node * copy(Node * current){
    if (current == NULL) {
      return NULL;
    }
    Node * root = new Node(current->key, current->value);
    root->left = copy(current->left);
    root->right = copy(current->right);
    return root;
  }
  BstMap & operator=(const BstMap & rhs) {
    if (this != &rhs) {
      destroy(root);
      root = copy(rhs.root);
    }
    return *this;
  }

  virtual void add(const K & key, const V & value){
    root = add(root, key, value);
  }
  Node * add(Node * cur, const K & key, const V & value){
    if (cur == NULL){
      Node * ans = new Node(key, value);
      return ans;
    }
    else {
      if (key < cur->key) {
	cur->left = add(cur->left, key, value);
      }
      else if (key > cur->key) {
	cur->right = add(cur->right, key, value);
      }
      else {
	cur->value = value;
      }
      return cur;  
    }
  }

  virtual const V & lookup(const K& key) const throw (std::invalid_argument){
    Node * cur = root;
    while (cur != NULL) {
      if (key == cur->key){
	return cur->value;
      }
      else if (key < cur->key){
	cur = cur->left;
      }
      else {
	cur = cur->right;
      }
    }
    throw std::invalid_argument("error");
  }

  virtual void remove(const K& key){
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
          (*cur)->value = (*temp)->value;         
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
  virtual ~BstMap<K,V>() {
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
