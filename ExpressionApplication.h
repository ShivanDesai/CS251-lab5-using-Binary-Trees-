#include "BinaryTree.h"
#include <vector>
#include <stdio.h>
#include <stack>
#include <string>
#include <sstream>

using namespace std;

class ExpressionApplication {
public:
	BinaryTree * _expression;
	
	ExpressionApplication(vector<Token> &v);
	~ExpressionApplication();
	TreeNode * differentiate(bool isPowerOp, char target);
	BinaryTree * simplify();
	BinaryTree * buildExpressionTree(vector<Token> &v);
};
