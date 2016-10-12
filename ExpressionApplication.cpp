#include "ExpressionApplication.h"
#include "ShuntingYard.h"
#include <iostream>
/////I added iostream

using namespace std;

TreeNode * solve(TreeNode * tnp);
TreeNode * copy(TreeNode * pointer);
TreeNode * diff(bool isPowerOp, char target, TreeNode * tnp);

BinaryTree *
ExpressionApplication::buildExpressionTree(vector<Token> &v) {
	vector<Token> vec(v);
	if(_expression->_root == NULL){
		_expression->_root = new TreeNode(vec.back());
		vec.pop_back();
	}	
	TreeNode * tnp = _expression->_root;
	while(tnp != NULL){
		if(tnp->t->elementType == operation){
//		cout<<tnp->t->_op<<" ";
			if(tnp->_right == NULL){
				tnp->_right = new TreeNode(vec.back());
				vec.pop_back();
				tnp->_right->_parent = tnp;
				tnp = tnp->_right;
				continue;
			}
			else if(tnp->_left == NULL){
				tnp->_left = new TreeNode(vec.back());
				vec.pop_back();
				tnp->_left->_parent = tnp;
				tnp = tnp->_left;
				continue;
			}
			else{
				if(tnp != _expression->_root)
					tnp = tnp->_parent;
				else
					break;
			}
		}
		else{
//			if(tnp->t->elementType == integer)	cout<<tnp->t->_num<<" ";
//			if(tnp->t->elementType == identifier)	cout<<tnp->t->_id<<" ";
			tnp = tnp->_parent;
		}
	}
	return _expression;
}

ExpressionApplication::ExpressionApplication(vector<Token> &v) {
	_expression = new BinaryTree;
	 buildExpressionTree(v);
}

ExpressionApplication::~ExpressionApplication() {
	delete _expression;
}


TreeNode * 
ExpressionApplication::differentiate(bool isPowerOp, char target) {
	TreeNode * tnp = _expression->_root;
	TreeNode * rnp = diff(isPowerOp, target, tnp);
	return rnp;
}

BinaryTree *
ExpressionApplication::simplify() {// one of the methods is to actuallt traverse the tree and count the number of operators...and then run the loop that many times...
	//other one is the recursive method....
/*	BinaryTree * bTree = new BinaryTree;
	if(bTree->_root == NULL){
		bTree->_root = _expression->_root;
	}*/
	BinaryTree * bTree = new BinaryTree;
//	TreeNode * tn = _expression->_root;
//	bTree->_root = new TreeNode(*_expression->_root->t);
//	bTree->_root->_left = solve(tn->_left);
//	bTree->_root->_left->_parent = bTree->_root;
//	bTree->_root->_right = solve(tn->_right);
//	bTree->_root->_right->_parent = bTree->_root;
	TreeNode * abc = this->differentiate(false, 'x'); 	
	bTree->_root = solve(abc);
	return bTree;
}

TreeNode * solve(TreeNode * p){
//	TreeNode * p = tnp;
	
	if(p == NULL)	return NULL;
	TreeNode * returnPointer;
	TreeNode * p1 = new TreeNode(*p->t);
	if(p->t->elementType != operation)	return p1;
	///From here onwards 'p' IS an operation............----------------------------------HAS TO HAVE A LEFT AND RIGHT------------------------------
//	if(p->_right->t->elementType == operation){	
	p1->_right = solve(p->_right);	
	if(p1->_right != NULL)				p1->_right->_parent = p1;
//	if(p->_left->t->elementType == operation){	
	p1->_left = solve(p->_left);	
	if(p1->_left != NULL)				p1->_left->_parent = p1;
	if((p1->_right->t->elementType == integer) && (p1->_left->t->elementType == integer)){
		TreeNode * p2;
//		if(p1->t->_op == '+' && (p1->_right->t->_num == p1->_left->t->_num)){
//			int num1 = 2 * p1->_left->t->_num;
//			Token tk(num1);
//			p2 = new TreeNode(tk);
//			cout<<"\nLLLLLLL\n";
//		}
//		else{
			int num2 = p1->_right->t->_num;
			int num1 = p1->_left->t->_num;
			if(p1->t->_op == '+'){		Token tk(num1 + num2);	p2 = new TreeNode(tk);}
			else if(p1->t->_op == '-'){	Token tk(num1 - num2);	p2 = new TreeNode(tk);}
			else if(p1->t->_op == '*'){	Token tk(num1 * num2);	p2 = new TreeNode(tk);}
			else if(p1->t->_op == '/'){	Token tk(num1 / num2);	p2 = new TreeNode(tk);}
			else{
				int num3 = 1;
				for(int i = 0; i < num2; i++)
					num3 *= num1;
				Token tk(num3);
				p2 = new TreeNode(tk);
			}
//		}
		returnPointer = p2;
		delete p1;
	}
	else if((p1->_right->t->elementType == integer) && (p1->_right->t->_num == 0)){
		if(p1->t->_op == '+' || p1->t->_op == '-'){
			TreeNode * p2 = p1->_left;
			returnPointer = p2;
			delete p1;
		}
		else if(p1->t->_op == '*'){
			Token tk(0);
			TreeNode * p2 = new TreeNode(tk);			
			returnPointer = p2;
			delete p1;
		}
		else if(p1->t->_op == '/'){
			///throw an exception
		}
		else{
			Token tk(1);
			TreeNode * p2 = new TreeNode(tk);
			returnPointer = p2;
			delete p1;
		}
	}
	else if((p1->_left->t->elementType == integer) && (p1->_left->t->_num == 0)){
		if(p1->t->_op == '+' || p1->t->_op == '-'){
			TreeNode * p2 = p1->_right;
			returnPointer = p2;
			delete p1;
		}
		else{
			Token tk(0);
			TreeNode * p2 = new TreeNode(tk);
			returnPointer = p2;
			delete p1;
		}
	}
	else if((p1->_right->t->elementType == integer) && (p1->_right->t->_num == 1)){
		if(p1->t->_op == '*' || p1->t->_op == '/' || p1->t->_op == '^'){
			TreeNode * p2 = p1->_left;			
			returnPointer = p2;
			delete p1;
		}
	}
	else if((p1->_left->t->elementType == integer) && (p1->_left->t->_num == 1)){
		if(p1->t->_op == '*'){
			TreeNode * p2 = p1->_right;
			returnPointer = p2;
			delete p1;
		}
		else if(p1->t->_op == '^'){
			Token tk(1);
			TreeNode * p2 = new TreeNode(tk);
			returnPointer = p2;
			delete p1;
		}
	}
	else{
		returnPointer = p1;
	}
	returnPointer->_parent = NULL;
}

TreeNode * diff(bool isPowerOp, char target, TreeNode * tnp){
	if(tnp == NULL)	return NULL;
	if(tnp->t->elementType != operation){
		if(tnp->t->elementType == identifier && tnp->t->_id == target){
			Token tk(1);
			TreeNode * returnNode = new TreeNode(tk);
			return returnNode;
		}
		else{
			Token tk(0);
			TreeNode * returnNode = new TreeNode(tk);
			return returnNode;
		}
	}
//------------------------------------------------------------------------------------------------------------------------------
	if(tnp->t->_op == '+' || tnp->t->_op == '-'){
		TreeNode * p1 = new TreeNode(*tnp->t);
		p1->_right = diff(false, target, tnp->_right);		p1->_right->_parent = p1;
		p1->_left = diff(false, target, tnp->_left);		p1->_left->_parent = p1;
		return p1;
	}
	else if(tnp->t->_op == '*'){
		Token tk('+');
		TreeNode * p1 = new TreeNode(tk);
		Token tk1('*');
		p1->_left = new TreeNode(tk1);					p1->_left->_parent = p1;
		p1->_right = new TreeNode(tk1);					p1->_right->_parent = p1;
		p1->_left->_left = copy(tnp->_left);				p1->_left->_left->_parent = p1->_left;
		p1->_left->_right = diff(false, target, tnp->_right);		p1->_left->_right->_parent = p1->_left;
		p1->_right->_left = diff(false, target, tnp->_left);		p1->_right->_left->_parent = p1->_right;
		p1->_right->_right = copy(tnp->_right);				p1->_right->_right->_parent = p1->_right;
		return p1;
	}
	else if(tnp->t->_op == '/'){
		Token tk('/');
		TreeNode * p1 = new TreeNode(tk);		
		Token tk2('^');
		p1->_right = new TreeNode(tk2);					p1->_right->_parent = p1;
		p1->_right->_left = copy(tnp->_right);				p1->_right->_left->_parent = p1->_right;
		Token tk3(2);
		p1->_right->_right = new TreeNode(tk3);				p1->_right->_right->_parent = p1->_right;
		Token tk4('-');
		p1->_left = new TreeNode(tk4);					p1->_left->_parent = p1;
		Token tk5('*');
		p1->_left->_left = new TreeNode(tk5);				p1->_left->_left->_parent = p1->_left;
		p1->_left->_right = new TreeNode(tk5);				p1->_left->_right->_parent = p1->_left;
		p1->_left->_left->_left = diff(false, target, tnp->_left);	p1->_left->_left->_left->_parent = p1->_left->_left;
		p1->_left->_left->_right = copy(tnp->_right);			p1->_left->_left->_right->_parent = p1->_left->_left;
		p1->_left->_right->_left = diff(false, target, tnp->_right);	p1->_left->_right->_left->_parent = p1->_left->_right;
		p1->_left->_right->_right = copy(tnp->_left);			p1->_left->_right->_right->_parent = p1->_left->_right;
		return p1;
	}
	else{
//		Token tk1('^');
//		TreeNode * p1 = new TreeNode(tk1);
//		Token tk2('*');
//		p1->_left = new TreeNode(tk2);				p1->_left->_parent = p1;
//		Token tk3('-');
//		p1->_right = new TreeNode(tk3);				p1->_right->_parent = p1;
//		p1->_left->_left = new TreeNode(*tnp->_right);		p1->_left->_left->_parent = p1->_left;
//		p1->_right->_left = new TreeNode(*tnp->_right);		p1->_right->_left->_parent = p1->_right;
//		Token tk4(1);
//		p1->_right->_right = new TreeNode(tk4);			p1->_right->_right->_parent = p1->_right;
////		p1->_left->_right = copy(tnp->_left);			p1->_left->_right->_parent = p1->_left;
//		return p1;
		Token tk1('*');
		TreeNode * p1 = new TreeNode(tk1);
		p1->_left = copy(tnp->_right);				p1->_left->_parent = p1;
		Token tk2('^');
		p1->_right = new TreeNode(tk2);				p1->_right->_parent = p1;
		
		if(tnp->_left->t->_id == target){
			p1->_right->_left = copy(tnp->_left);		p1->_right->_left->_parent = p1->_right;
		}
		else{
			Token tk6(0);
			p1->_right->_left = new TreeNode(tk6);		p1->_right->_left->_parent = p1->_right;
		}

		Token tk3('-');
		p1->_right->_right = new TreeNode(tk3);			p1->_right->_right->_parent = p1->_right;
		p1->_right->_right->_left = copy(tnp->_right);		p1->_right->_right->_left->_parent = p1->_right->_right;
		Token tk4(1);
		p1->_right->_right->_right = new TreeNode(tk4);		p1->_right->_right->_right->_parent = p1->_right->_right;
		return p1;
	}
}

TreeNode * copy(TreeNode * pointer){
	if(pointer == NULL)	return NULL;
	TreeNode * returnPointer = new TreeNode(*pointer->t);
	if(returnPointer->t->elementType == operation){	
		returnPointer->_left = copy(pointer->_left);		returnPointer->_left->_parent = returnPointer;
		returnPointer->_right = copy(pointer->_right);		returnPointer->_right->_parent = returnPointer;
	}
	else{
		return returnPointer;
	}
}
