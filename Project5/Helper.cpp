#include "Token.h"
#include "Helper.h"
#include "Helper2.h"
#include "Helper3.h"
#include "node.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <cstddef>

using namespace std;

// global variables input and index help with finding next token
string input;
int index(0);

// global variable current keeps track of current token
Token current;


// adds each line of file to input string
void readFile() {
	string buffer;
	while (getline(cin, buffer)) {
		input += buffer + " ";
	}
}


// Gets and determines the type of token 
// Removed parameters input and index for project 2
Token getNextToken() {
	Token token;
	try {
		// for EOF tokens
		if (input.length() == (unsigned) index) {
			token.setType("EOF");
			token.setValue("\0");
			return token;
		// Moves past spaces
		} else if (input[index] == 32) {
			index++;
			return getNextToken();
		// For open parentheses
		} else if (input[index] == '(') {
			index++;
			token.setType("Open");
			token.setValue("(");
			return token;
		// For closed parentheses
		} else if (input[index] == ')') {
			index++;
			token.setType("Close");
			token.setValue(")");
			return token;
		// for Literal Atoms if first char is capital letter
		} else if (input[index] >= 'A' && input[index]<= 'Z') {
			string s = string(1, input[index]);
			int t = index;
			// stores any following letters or capitals
			while ((input[++t] >= 'A' && input[t] <= 'Z') || (input[t] >= '0' && input[t] <= '9')) {
				s += input[t];
			}
			index = t;
			token.setType("Atom");
			token.setAtom("Literal");
			token.setValue(s);
			return token;
		// for numerical atoms if first char is number
		} else if (input[index] >= '0' && input[index] <= '9') {
			string s = string(1, input[index]);
			int t = index;
			// adds following numbers and captial letters
			while ((input[++t] >= 'A' && input[t] <= 'Z') || (input[t] >= '0' && input[t] <= '9')) {
				s += input[t];
			} 
			index = t;
			char c;
			// creates error token if letter follows after number
			for (unsigned i = 0; i < s.length(); i++) {
				c = s[i];
				if (c >= 'A' && c <= 'Z') {
					token.setType("ERROR");
					token.setValue(s);
					return token;
				}
			}
			token.setType("Atom");
			token.setAtom("Numeric");
			token.setValue(s);
			return token;
		}
	}
	catch (exception& e) {
 		cout << "An exception was caught with message '" << e.what() << "'" << endl;
	}
	token.setType("EOF");
	return token;
}

// initializes current token to first token from getNextToken function
void Init() {
	current = getNextToken();
}

// returns the current token
Token GetCurrent() {
	return current;
}

// finds and returns the next token and sets current to that token
void MoveToNext() {
	current = getNextToken();
}

// ParseStart starts the ParseExpr() function each time the token is not the eof
// also calls the print function to print the resulting tree and tokens from the ParseExpr function
void ParseStart() {
	if (GetCurrent().getType() == "EOF") {
		cout << "ERROR: File is Empty" << endl;
		exit(10);
	}
	while(GetCurrent().getType() != "EOF") {
		if (GetCurrent().getType() == "ERROR") {
			cout << GetCurrent().getType() << ": Invalid token: " << GetCurrent().getValue() << endl;
			exit(0);
		}
		// << "Test: " << GetCurrent().getValue() << endl;
		node *print = ParseExpr();
		//Print(print);
		node *print1 = eval(print);
		print1 = listeval(print);
		//cout << print->right->left->value << endl;
		Print(print);
			
		cout << endl;
	}
}

// returns pointer to node(tree of tokens) created from parsing from the current token
node *ParseExpr() {
	node *root = new node;
	node *temp = root; // moves temp node to the root of tree
	// if token is an atom then there is no list
	if (GetCurrent().getType() == "Atom") {
		temp->list = false;
		temp->value = GetCurrent().getValue();
		temp->type = GetCurrent().getType();
		temp->atom = GetCurrent().getAtom();
		MoveToNext(); // consume token
	// if token is open parentheses then we have a list
	} else if (GetCurrent().getType() == "Open") {
		MoveToNext(); // consume token
		temp->list = true;
		while (GetCurrent().getType() != "Close") {
			temp->left = ParseExpr(); // parse and return left side of sub-tree
			temp->right = new node;
			temp = temp->right;
		}
		// Error if we do not have ")" when type is closed parantheses
		if (GetCurrent().getValue() != ")") {
			cout << "Closing Parentheses was expected" << endl;
			exit(10);
		} else {
			temp->value = "NIL";
			temp->list = false;
			temp->type = "Atom";
		}
		MoveToNext(); // consume token
	} else {
		// Error checking for current token
		if (GetCurrent().getType() == "ERROR") {
			cout << GetCurrent().getType() << " Token ERROR found: " << GetCurrent().getValue() << endl;
			exit(10);
		} else if (GetCurrent().getValue() == "(") {
			cout << "Error: Open Parentheses not expected" << endl;	
			exit(10);
		} else if (GetCurrent().getValue() == ")") {
			cout << "Error: Closed Parethenses not expected" << endl;
			exit(10);
		} else {
			cout << "Parsing Error: Unknown" << endl;
			exit(10);
		}
	}
	return root; // returns root of tree
}

/*void Print(node *root) {
	cout << "(";
	node *temp = root;
	while (temp->left != NULL) {
		if (temp->left->left != NULL) {
			Print(temp->left);
		} else {
			cout << temp->left->value;
		}
		if (temp->right->value != "NIL") {
			cout << " ";
		}
		temp = temp->right;
	}
	if (temp->value != "NIL") {
		cout << " . " << temp->value << ")";
	} else {
 		cout << ")";
	}
}*/

// Recursively prints out tree
void Print(node *root) {
	if (root == NULL) {
		return;
	} 
	if (root->type == "Atom") {
		cout << root->value;
		return;
	}
	if (root->list == true) {
		cout << "(";
		if(root->left != NULL) {
			Print(root->left);
		}
		while(root->right != NULL  && root->value != "NIL") {
			root = root->right;
			if(root->right != NULL && root->value != "NIL") {
				cout << " ";
			}
			if (root->value != "NIL" && root != NULL) {
				Print(root->left);
			}
		}
		if(root->value != "NIL") {
			cout << "()";
			Print(root);
		}
		cout << ")";
		return;
	}
	cout << "(";
	if (root->left != NULL) {
		Print(root->left);
	}
	cout << " ";
	if(root->right != NULL) {
		Print(root->right);
	}
	cout << ")";
	return;
} 




