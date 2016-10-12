#include "ExpressionApplication.h"
#include "ShuntingYard.h"
#include <stdio.h>
#include <string.h>
#include <iostream>

void test_io() {
/*	char buf[1000];
	char * p = buf;
	int c;
	while((c = getchar()) != EOF) {
		*p++ = c;
	}
	*p = 0;
	Shuntingyard s(buf);
	std::vector<Token> v = s.infixToPostfix();
	printf("Shunting Yard Output:\n");
	for (int j=0;j<v.size();j++){
		v[j].print();
	}
	fflush(stdout);
	ExpressionApplication e(v);
	printf("\nOriginal Tree:\t\t");
	fflush(stdout);
	e._expression -> print();
	printf("Differentiated Tree:\t");
	fflush(stdout);
	BinaryTree * ret = e.differentiate('x');
	ret -> print();
	printf("Simplified Tree:\t");
	fflush(stdout);
	ret = e.simplify();
	ret -> print();
	*/
}

void test1(){
	/*
	Test for Shunting Yard
	*/
	char buf[] = "x^3+y^2+x*y+5";	
	Shuntingyard s(buf);
	std::vector<Token> v = s.infixToPostfix();
	cout<<"\nShunting Yard Output:\n";

	for (int j = 0; j < v.size(); j++){	
		v[j].print();
	}
	cout<<"\n\nExpected Output:\n";
	cout<<"x3^y2^+xy*+5+\n";
}

void test2(){
	/*
	Test for Building Tree 
	*/
	char buf[] = "x^3+y^2+x*y+5";
	Shuntingyard s(buf);
	cout<<"\nbkabakbak\n";
	std::vector<Token> v = s.infixToPostfix();
	printf("\nTree Build Output:\n");
	ExpressionApplication e(v);
	cout<<"\nHHHHHHHHHHAAAAAAAAAHAHHA\n";
	e._expression -> print();
	fflush(stdout);
	printf("\nExpected Output:\n");
	printf("((((x^3)+(y^2))+(x*y))+5)\n");
}

void test3(){
	/*
	Test for Differentiation Without Simplification 
	*/
	char buf[] = "x^3+y^2+x*y+5";
	Shuntingyard s(buf);
	std::vector<Token> v = s.infixToPostfix();
	printf("\nDifferentiated Tree Output:\n");
	ExpressionApplication e(v);
	BinaryTree * ret = new BinaryTree;
	ret->_root = e.differentiate(false, 'x'); // differentiate wrt x
	ret -> print();
	fflush(stdout);
	printf("\nExpected Output:\n");
	printf("((((3*(x^2))+(2*(0^1)))+((1*y)+(x*0)))+0)\n");
	
}

void test4(){
	/*
	Test for Differentiation With Simplification 
	*/
	char buf[] = "x^3+y^2+x*y+5";
	Shuntingyard s(buf);
	std::vector<Token> v = s.infixToPostfix();
	printf("\nDifferentiated Tree Output:\n");
	ExpressionApplication e(v);
	BinaryTree * ret = e.simplify(); // Assume for simplify() - first differentiate wrt x then simplify
	ret -> print();
	fflush(stdout);
	printf("\nExpected Output:\n");
	printf("((3*(x^2))+y)\n");
}

int main(int argc, char* argv[]){
	if (argc == 1) {
		test_io(); // std io for manual testing
	}
	else{
		if ( !strcmp(argv[1], "test1")) {
			test1();
		}
		else if ( !strcmp(argv[1], "test2")) {
			test2();
		}
		else if ( !strcmp(argv[1], "test3")) {
			test3();
		}
		else if ( !strcmp(argv[1], "test4")) {
			test4();
		}
	}
}
