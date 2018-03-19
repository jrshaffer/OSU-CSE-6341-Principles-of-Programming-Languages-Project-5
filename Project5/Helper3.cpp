#include "Helper3.h"
#include "node.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <cstddef>
#include <climits>

using namespace std;

//string check = "";
//node *condCheck = new node;

int listnodeLength(node *n) {
	int length = 0;
	//while (n != NULL) {
	while(n->value != "NIL") {
		if (n->left != NULL) {
			length++;
		}
		n = n->right;
	}
	return length;
}

bool listAtom(node *n) {	
	//node *temp = n;
	if (n->typeCheck == "True" || n->typeCheck == "False" || n->typeCheck == "AnyBool" || n->typeCheck == "AnyNat") {
		return true;
	} else if (n->typeCheck == "List[>=k]") {
		return false;
	} else {
		cout << "EMPTY LIST ERROR: Undefined Input Type to Atom Function" << endl;
		exit(10);
	}
	//return temp;
}

node *listisNull1(node *n) {
	node *temp = n;
	if (n->typeCheck == "List[>=k]") {
		if (n->k == 0) {
			temp->typeCheck = "AnyBool";
		} else if (n->k > 0) {
			temp->typeCheck = "False";
		}
		return temp;
	} else {
		cout << "EMPTY LIST ERROR: Undefined INPUT Type for NULL Function. Expected List[>=k]" << endl;
		exit(10);
	}
	return temp;
}

bool listisInteger(node *n) {
	//node *temp = n;
	if (n->typeCheck == "True" || n->typeCheck == "False" || n->typeCheck == "List[>=k]" || n->typeCheck == "AnyBool") {
		return false;
	} else if (n->typeCheck == "AnyNat") {
		return true;
	} else {
		cout << "EMPTY LIST ERROR: Undefined Input Type for INT Function" << endl;
		exit(10);
	}
	//return temp;
}

node *listcar1(node *n) {
	node *temp = n;
	if (n->typeCheck == "List[>=k]" && n->k > 0) {
		temp->typeCheck = "AnyNat";
		return temp;
	} else if(n->typeCheck == "List[>=k]" && n->k == 0) {
		cout << "EMPTY LIST ERROR: Undefined Type Input for CAR FUNCTION. Expected List[>=k] with k > 0" << endl;
		exit(10);
	} else {
		cout << "EMPTY LIST ERROR: Undefined Type for CAR Function" << endl;
		exit(10);
	}
	return temp;
}

node *listcdr1(node *n) {
	node *temp = n;
	if (n->typeCheck == "List[>=k]" && n->k == 0) {
		cout << "EMPTY LIST ERROR: Undefined Type Input for CDR Function. Expected List[>=k] with k > 0" << endl;
		exit(10);
	} else if(n->typeCheck == "List[>=k]" && n->k > 0) {
		temp->typeCheck = "List[>=k]";
		temp->k = n->k - 1;
		return temp;
	} else {
		cout << "EMPTY LIST ERROR: Undefined Type Input for CDR Function" << endl;
		exit(10);
	}
	return temp;
}

int listcons1(node *left, node *right) {
	//node *temp = new node;
	if (left->typeCheck != "AnyNat") {
		cout << "EMPTY LIST ERROR: s1 Type Expression is not AnyNat" << endl;
		exit(10);
	} else if (right->typeCheck != "List[>=k]") {
		cout << "EMPTY LIST ERROR: s2 Type Expression is not List[>=k]" << endl;
		exit(10);
	} else {
		return right->k + 1;
	}
}

node *listcons(node *left, node *right) {
	node *root = new node;
	if (left == NULL) {
		root = right;
	} else if (right == NULL) {
		root = left;
	} else {
		root->left = left;
		root->right = right;
	}
	//root->list = true;
	return root;
}

bool listPLUS(node *left, node *right) {
	if (left->typeCheck != "AnyNat") {
		cout << "EMPTY LIST ERROR: s1 Expression Type is not a AnyNat" << endl;
		exit(10);
	} else if (right->typeCheck != "AnyNat") {
		cout << "EMPTY LIST ERROR: s2 Expression Type is not a AnyNat" << endl;
		exit(10);
	} else {
		return true;
	}
	return false;
}


bool listeq(node *left, node *right) {
	if (left->typeCheck != "AnyNat") {
		cout << "EMPTY LIST ERROR: s1 Expression Type is not a AnyNat" << endl;
		exit(10);
	} else if (right->typeCheck != "AnyNat") {
		cout << "EMPTY LIST ERROR: s2 Expression Type is not a AnyNat" << endl;
		exit(10);
	} else {
		return true;
	}
	return false;
}

bool listLESS(node *left, node *right) {
	if (left->typeCheck != "AnyNat") {
		cout << "EMPTY LIST ERROR: s1 Expression Type is not a AnyNat" << endl;
		exit(10);
	} else if (right->typeCheck != "AnyNat") {
		cout << "EMPTY LIST ERROR: s2 Expression Type is not a AnyNat" << endl;
		exit(10);
	} else {
		return true;
	}
	return false;
}


node *listeval(node *root) {
	//cout << root->value << endl;
	node *temp = NULL;
	//cout << root->value << endl;
	if(root->type == "Atom" && root != NULL) {
		if (root->value == "T") {
			root->typeCheck = "True";
		} else if (root->value == "F") {
			root->typeCheck = "False";
		} else if(root->atom == "Numeric") {
			root->typeCheck = "AnyNat";
		} else if(root->value == "NIL") {
			root->typeCheck = "List[>=k]";
			root->k = 0;
		} else {
			cout << "EMPTY LIST ERROR: Undefined Atom for Eval Function" << endl;
			exit(10);
		}
		//root->list = false;
		temp = root;
	} else {
		if (listcar(root)->value == "COND") {
			try { 
				
				temp = listcond(listcdr(root), false, listcdr(root));	
				string t = temp->typeCheck;
				int i;
				if (t == "List[>=k]") {			
					i = temp->k;
				}
				temp = listcons(listcar(root), listcdr(root));
				//temp->list = false;
				if (t == "List[>=k]") {			
					temp->k = i;
				}
				temp->typeCheck = t;
			} catch(exception& e) {
				cout << "EMPTY LIST ERROR: Unkown Error in COND Function" << endl;
				exit(10);
			}
			
			
		} else {
			temp = listapply(listcar(root), listevalList(listcdr(root)));
			temp->list = false;
		}
	}
	//temp = root;
	return temp;
}

bool listcheckCond(node *root, bool check) {
	//cout << check << endl;	
	if (check) {
		return true;
	} else if (root->value == "NIL") {
		cout << "EMPTY LIST ERROR: Undefined Input to COND Function. All Boolean Expressions are False" << endl;
		exit(10);
	} else if (listeval(listcar(listcar(root)))->typeCheck == "False") {
		return listcheckCond(listcdr(root), check);
	} else if (listeval(listcar(listcar(root)))->typeCheck == "True" || listeval(listcar(listcar(root)))->typeCheck == "AnyBool") {
		return listcheckCond(listcdr(root), true);
	} else {
		cout << "EMPTY LIST ERROR: Undefined Input to COND Function. Boolean Expression Type is not True or False" << endl;
		exit(10);
	}
}


node *listAnyBool(node *root, string type, int min) {
	if (root->value == "NIL") {
		node *n = new node;
		n->typeCheck = type;
		if (type == "List[>=k]") {
			n->k = min;
		}
		return n;
	}
	node *temp = listeval(listcar(listcar(root)));
	if (temp->typeCheck != "True" && temp->typeCheck != "False" && temp->typeCheck != "AnyBool") {
		cout << "EMPTY LIST ERROR: Undefined Input Type for Boolean Expression in COND Function. Expected Type True, False, or AnyBool" << endl;
		exit(10);
	} else {
		node *eval = listeval(listcar(listcdr(listcar(root))));
		if (type == "") {
			type = eval->typeCheck;
			if (type == "List[>=k]") {
				min = eval->k;
			}
		} else {
			if (type == "AnyNat") {
				if (eval->typeCheck != type) {
					cout << "EMPTY LIST ERROR: Undefined Type Mismatch in COND Function. Expected eval(ei) Type to be AnyNat" << endl;
					exit(10);
				}
			} else if (type == "True" || type == "False" || type == "AnyBool") {
				if (eval->typeCheck != "True" && eval->typeCheck != "False" && eval->typeCheck != "AnyBool") {
					cout << "EMPTY LIST ERROR: Undefined Type Mistmatch in COND FUNCTION. Expected eval(ei) Type to be True, False, or AnyBool" << endl;	
					exit(10);
				} else if (eval->typeCheck != type) {
					type = "AnyBool";
				}
			} else if (type == "List[>=k]") {
				if (eval->typeCheck != type) {
					cout << "EMPTY LIST ERROR: Undefined Type Mismatch in COND Function. Expected eval(ei) Type to be List[>=k]" << endl;
					exit(10);
				} 
				if (eval->k < min) {
					min = eval->k;
				}
			} else {
				cout << "EMPTY LIST ERROR: Undefined eval(ei) Type in COND Function. Expected AnyNat, True, False, AnyBool, or List[>=k]" << endl;
				exit(10);
			}
		}
		return listAnyBool(listcdr(root), type, min);
	}
}

bool findAnyBool(node *root) {
	if (root->value == "NIL") {	
		return false;
	} else if (listeval(listcar(listcar(root)))->typeCheck == "AnyBool") {
		return true;
	} else {
		return findAnyBool(listcdr(root));
	}
}
	

node *listcond(node *root, bool check, node *n) {
	if(listeval(listcar(listcar(root)))->typeCheck == "AnyBool") {
		return listAnyBool(n, "", INT_MAX);
	} else if(listeval(listcar(listcar(root)))->typeCheck == "False") {
		if (check == false) {		
			if (listcheckCond(listcdr(root), false)) {
				check = true;
			}
		} 
		return listcond(listcdr(root), check, n);
	} else if(listeval(listcar(listcar(root)))->typeCheck == "True") {
		if (findAnyBool(n)) {
			return listAnyBool(n, "", INT_MAX);
		} else {
			return listeval(listcar(listcdr(listcar(root))));
		}	
	} else {
		cout << "EMPTY LIST ERROR: Undefined Type Input to COND Function. Boolean Expression Type is not True or False" << endl;
		exit(10);
	}
}

node *listevalList(node *root) {
	if(listisNull(root)) {
		node *temp = new node;
		temp->type = "Atom";
		temp->value = "NIL";
		temp->typeCheck = "List[>=k]";
		temp->k = 0;
		return temp;
	} else {
		return listcons(listeval(listcar(root)), listevalList(listcdr(root)));
	}
}

bool listcommand(node *root) {
	string functions[14] = {"ATOM", "INT", "NULL", "CAR", "CDR", "CONS", "PLUS", "LESS", "EQ", "COND"};
	int i;
	for(i = 0; i < 14; i++) {
		if (functions[i] == root->value) {
			return true;
		} 
	}
	return false;
}

node *listapply(node *function, node *parameters) {
	int length;
	length = listnodeLength(parameters);
	node *temp = new node;
	if (listcommand(function) == false) {
		cout << "EMPTY LIST ERROR: Function Undefined; First Element of s is not ATOM, INT, NULL, CAR, CDR, CONS, PLUS, LESS, EQ, or COND" << endl;
		exit(10);
	}
	if (function->value == "ATOM") {
		if (length != 1) {
			cout << "EMPTY LIST ERROR: more than 1 parameter found for ATOM function; Only 1 parameter expected" << endl;
			exit(10);
		}
		temp = listcons(function, parameters);
		if (listAtom(listcar(parameters))) {
			temp->typeCheck = "True";
		} else {
			temp->typeCheck = "False";
		}
			
		//temp->list = false;
	} else if(function->value == "NULL") {
		if (length != 1) {
			cout << "EMPTY LIST ERROR: more than 1 parameter found for NULL function; Only 1 parameter expected" << endl;
			exit(10);
		}
		//temp->list = true;
		temp = listisNull1(listcar(parameters));
		string check = temp->typeCheck;
		temp = listcons(function, temp);
		//temp->list = false;
		temp->typeCheck = check;
	} else if(function->value == "INT") {
		if (length != 1) {
			cout << "EMPTY LIST ERROR: more than 1 parameter found for INT function; Only 1 parameter expected" << endl;
			exit(10);
		}
		temp = listcons(function, parameters);
		if (listisInteger(listcar(parameters))) {
			temp->typeCheck = "True";
		} else {
			temp->typeCheck = "False";
		}
	} else if(function->value == "PLUS") {
		if (length != 2) {
			cout << "EMPTY LIST ERROR: Only 2 parameters expected for PLUS function" << endl;
			exit(10);
		}
		if (listPLUS(listcar(parameters), listcar(listcdr(parameters)))) {
			temp = parameters;
			temp->typeCheck = "AnyNat";
		}
		//temp->list = true;
		temp = listcons(function, temp);
		//temp->list = false;
		temp->typeCheck = "AnyNat";
	} else if(function->value == "EQ") {
		if (length != 2) {
			cout << "EMPTY LIST ERROR: Only 2 parameters expected for EQ function" << endl;
			exit(10);
		}
		if (listeq(listcar(parameters), listcar(listcdr(parameters)))) {
			temp = parameters;
			temp->typeCheck = "AnyBool";
		}
		//temp->list = true;
		temp = listcons(function, temp);
		//temp->list = false;
		temp->typeCheck = "AnyBool";
	} else if(function->value == "LESS") {
		if (length != 2) {
			cout << "EMPTY LIST ERROR: Only 2 parameters expected for LESS function" << endl;
			exit(10);
		}
		if (listLESS(listcar(parameters), listcar(listcdr(parameters)))) {
			temp = parameters;
			temp->typeCheck = "AnyBool";
		}
		//temp->list = false;
		temp = listcons(function, temp);
		//temp->list = true;
		temp->typeCheck = "AnyBool";
	} else if(function->value == "CAR") {
		if (length != 1) {
			cout << "EMPTY LIST ERROR: Only 1 parameter expected for CAR function" << endl;
			exit(10);
		}
		temp = listcar1(listcar(parameters));
		//temp->list = true;
		temp = listcons(function, temp);
		//temp->list = false;
		temp->typeCheck = "AnyNat";
	} else if (function->value == "CDR") {
		if (length != 1) {
			cout << "EMPTY LIST ERROR: Only 1 parameter expected for CDR function" << endl;
			exit(10);
		}
		temp = listcdr1(listcar(parameters));
		int i = temp->k;
		temp = listcons(function, temp);
		//temp->list = false;
		temp->typeCheck = "List[>=k]";
		temp->k = i;
	} else if(function->value == "CONS") {
		if (length != 2) {
			cout << "EMPTY LIST ERROR: Only 2 parameters expected for CONS function" << endl;
			exit(10);
		}
		int i = listcons1(listcar(parameters), listcar(listcdr(parameters)));
		//temp->list = true;
		temp = listcons(function, parameters);
		//temp->list = true;		
		temp->typeCheck = "List[>=k]";
		temp->k = i;
	} else {
		//cout << "Function " << function->value;
		return function;
	}
	//cout << temp->left->value << endl;
	//temp->list = true;
	return temp;
}


bool listisNull(node *n) {
	if (n->type == "Atom" && n->value == "NIL") {
		return true;
	} 
	return false;
}


node *listcar(node *n) {
	node *root = n;
	if (n != NULL) {
		if (n->type == "Atom") {
			cout << "EMPTY LIST ERROR: CAR function cannot be performed on atom" << endl;
			exit(10);
		} else {
			if (n->left != NULL) {
				root = n->left;
			} else {
				cout << "EMPTY LIST ERROR: unexpected error in CAR function" << endl;
				exit(10);
			}
		}
	} else {
		cout << "EMPTY LIST ERROR: undefined arguments in CAR function" << endl;
		exit(10);
	}
	return root;
}

node *listcdr(node *n) {
	node *root = n;
	if (!listisNull(n)) {
		if (n->type == "Atom") {
			cout << "EMPTY LIST ERROR: CDR function cannot be performed on atom" << endl;
			exit(10);
		} else {
			if (n->right != NULL) {
				root = n->right;
			} else {
				cout << "EMPTY  ERROR: unexpected error in CDR function" << endl;
				exit(10);
			}
		}
	} 
	return root;
}
