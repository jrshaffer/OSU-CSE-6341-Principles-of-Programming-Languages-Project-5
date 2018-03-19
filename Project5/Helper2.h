#include "node.h"

using namespace std;

int nodeLength(node *n);

node *Atom(node *n);

node *isNull1(node *n);

node *isInteger(node *n);

node *car1(node *n);

node *cdr1(node *n);

bool cons1(node *left, node *right);

node *cons(node *left, node *right);

bool PLUS(node *left, node *right);

bool eq(node *left, node *right);

bool LESS(node *left, node *right);

node *eval(node *root);

void checkCond(node *root, string check);

void condType(node *root);

node *cond(node *root);

node *evalList(node *root);

bool command(node *root);

node *apply(node *function, node *parameters);

bool isNull(node *n);

node *car(node *n);

node *cdr(node *n);
