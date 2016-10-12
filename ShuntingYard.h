#include <stack>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include "Token.h"
#include <iostream>

const int precedence[5][3] = {
	{'^', 4, 0},
	{'*', 3, 1},
	{'/', 3, 1},
	{'+', 2, 1},
	{'-', 2, 1}
};



class Shuntingyard {
public:
char * _string;
	
Shuntingyard(char * s) {
	_string = strdup(s);
}

~Shuntingyard() {
	delete _string;
}



std::vector<Token> infixToPostfix() {
	vector<Token> myVector;
	stack<Token> tempStack;//for transferring to a new stack
	stack<Token> opStack;
	stack<Token> tempStack2;
	char * str;
	str = new char[strlen(_string)];
	strcpy(str, _string);
	int i = 0;
	while(str[i] != '\0'){ //string to stack
		if(str[i] == ' '){
			i++;
			continue;
		}
		if(str[i] >= '0' && str[i] <= '9'){
			int n = str[i] - '0';
			while(str[i + 1] >= '0' && str[i + 1] <= '9'){
				n = (n * 10) + (str[i + 1] - '0');
				i++;
			}
			Token t(n);
			tempStack.push(t);//
		}
		else{
			Token t(str[i]);
			tempStack.push(t);//
		}
		i++;
	}
	while(!tempStack.empty()){//transfer to a new stack in reverse order
		Token temp = tempStack.top();
		tempStack2.push(temp);
		tempStack.pop();
	}
	while(!tempStack2.empty()){//SHUNTING YARD ALGO!
		Token t = tempStack2.top();
		tempStack2.pop();
		if((t.elementType == integer) || (t.elementType == identifier)){//if Token = INTEGER OR IDENTIFIER
			myVector.push_back(t);
		}
		else if(t.elementType == operation){//if Token = OPERATOR
			if((t._op != '(') && (t._op != ')')){
				int prec1, assoc;
				for(int j = 0; j < 5; j++){//find op1 precedence
					if(t._op == precedence[j][0]){
						prec1 = precedence[j][1];
						assoc = precedence[j][2];
					}
				}
				while((!opStack.empty()) && (opStack.top().elementType == operation) && (opStack.top()._op != '(') && (opStack.top()._op != ')')){
					int prec2;
					for(int k = 0; k < 5; k++){//find op2 precedence
						if(opStack.top()._op == precedence[k][0])	prec2 = precedence[k][1];
					}
					if(((assoc == 1) && (prec1 <= prec2)) || ((assoc == 0) && (prec1 < prec2))){
						myVector.push_back(opStack.top());
						opStack.pop();
					}
					else{
						break;
					}
				}
				opStack.push(t);
			}
			else if(t._op == '('){
				opStack.push(t);
			}
			else if(t._op == ')'){
				while((!opStack.empty()) && (opStack.top().elementType == operation)){
					while(opStack.top()._op != '('){
						myVector.push_back(opStack.top());
						opStack.pop();
					}
					if(opStack.top()._op == '(')	
						opStack.pop();
					//throw an EXCEPTION here if the opStack runs out without finding a '(' => MISMATCHED PARENTHESIS
				}
			}
		}
	}
	while(!opStack.empty()){
//		if((opStack.top().elementType == operation) && (opStack.top()._op == '('))
			//throw an EXCEPTION here if the opStack HAS a '(' => MISMATCHED PARENTHESIS
		myVector.push_back(opStack.top());
		opStack.pop();
	}
	return myVector;
}
};
