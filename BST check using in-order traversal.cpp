#include<stdio.h>
#include<stdlib.h>
#include<climits>
/*
APPROACH: in case of BST, in-order traversal gives nodes in non-decreasing order
--> traverse the given tree in-order fashion and chek if the sequence of nodes is increasing

*/


typedef struct node {
	int data;
	struct node*left, *right;
}node;


node*newNode(int data) {
	node*ptr=(node*)malloc(sizeof(node));
	ptr->data=data;
	ptr->left=NULL;
	ptr->right=NULL;
	return ptr;
}



// we nead a way to remember the previous node we visited, 
// we can do this using a reference to a pointer( double ponter).
bool isBST(node*root,node**prev) {
	//base case, empty tree is a BST
	if(root==NULL)
		return true;
	if(!isBST(root->left, prev))
		return false;
	if(*prev!=NULL && root->data<= (*prev)->data)
		return false;
	*prev=root;
	return isBST(root->right,prev);
}

bool isBST_wrapper(node*root) {
	node*prev=NULL;
	return isBST(root, &prev);
}


int main (){
	node*root=newNode(6);
	root->left=newNode(3);
	root->right=newNode(9);
	root->left->left=newNode(2);
	root->left->right=newNode(5);
	bool valid=isBST_wrapper(root);
	if(valid)
		printf("YES");
	else
		printf("NO");
}