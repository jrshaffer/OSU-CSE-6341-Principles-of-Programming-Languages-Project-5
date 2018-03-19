#ifndef NODE_H
#define NODE_H
#include <string>

using namespace std;

// structure to represent node
struct node
{
  string value;
  string type;
  string atom;
  bool list;
  string check;
  string typeCheck;
  int k;
  node *left;
  node *right;
};

#endif
