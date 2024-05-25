#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<climits>

/*RECALL:
A binary search tree(BST) is a node-based binary tree datastructure
Properties:
+) the left subtree of a node contains only nodes with key less than the node's key
+) the right subtree of a node contains only nodes with keys greater than the node's key
+) both the left and right subtrees must also be binary search trees
+) each node(item in the tree) has distinct key
*/	
typedef struct node{
	int data;
	struct node*left,*right;
}node;

node* newNode(int data) {
	node*ptr=(node*)malloc(sizeof(node));
	ptr->data=data;
	ptr->left=NULL;
	ptr->right=NULL;
	return ptr;
}


bool isBST(node*root, int max, int min) {
	if(root==NULL)
		return true;	
	if(root->data>max || root->data<min)
		return false;
	return(isBST(root->left, root->data-1, min) && isBST(root->right, max, root->data+1));
}




bool isBST_call(node*root) {
	bool valid=isBST(root, INT_MAX, INT_MIN);
	return valid;
}

int main () {	
	node* root = newNode(6);
    root->left = newNode(3);
    root->right = newNode(9);
    root->left->left = newNode(2);
    root->left->right = newNode(5);
    if(isBST_call(root))
    	printf("YES");
    else
    	printf("NO");
    return 0;
}

