#include "node.h"

Node *  buildTree(uint64_t * counts) {
  //WRITE ME!
  priority_queue_t pq;
  for (size_t i = 0; i < 257; i++) {
    if (counts[i] != 0)
      pq.push(new Node(i, counts[i]));
  }

  while (pq.size() >= 2) {
    Node * first = pq.top();
    pq.pop();
    Node * second = pq.top();
    pq.pop();
    Node * new_node = new Node(first, second);
    pq.push(new_node);
  }
  return pq.top();
}  
