#include <string>

#include "Token.h"
#include "node.h"


using namespace std;


// reads file input
void readFile();

// gets each token from the input file
Token getNextToken();

// initializes current token
void Init();

// Returns current token
Token GetCurrent();

// moves current token to next token
void MoveToNext();


// calls ParseExpr and Print until eof token
void ParseStart();

// creates tree from token objects
node *ParseExpr();

// prints out tree
void Print(node *root);


