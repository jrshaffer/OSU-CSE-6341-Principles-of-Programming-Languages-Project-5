#ifndef TOKEN_H
#define TOKEN_H
#include <string>

using namespace std;

// Token class to store the different types of tokens
class Token {

private:
	string type, atom, value;
public: 
	void setType(const string & tokenType); // 5 types Open Parentheses, closed parentheses, numerical and literal, Error, EOF
	void setAtom(const string & atomType); // Literal or Numberical
	void setValue(const string & count); // count or sum of tokens
	// Returns each attribute of the token
	string getType() const;
	string getAtom() const;
	string getValue() const;
};

#endif
