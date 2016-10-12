#include "BinaryTree.h"
#include <iostream>
/// I addded iostream

BinaryTree::BinaryTree() {
	_root = NULL;
}


BinaryTree::~BinaryTree() {
	delete _root;///include checks
}

void printTree(TreeNode * root) {
	if(root == NULL) return;
	if(root -> t -> elementType == operation) {
		std::cout<<"(";
		putchar('(');
		fflush(stdout);
	}
	printTree(root -> _left);
	root -> t -> print();
	printTree(root -> _right);
	if(root -> t -> elementType == operation) {
		std::cout<<")";
		putchar(')');
		fflush(stdout);
	}
}

void
BinaryTree::print() {
	printTree(_root);
	putchar('\n');
}
