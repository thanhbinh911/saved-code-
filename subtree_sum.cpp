#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<climits>

int sum;

typedef struct node{
	int data;
	struct node*left,*right;
	
}node;


node*newnode(int data) {
	node*ptr=(node*)malloc(sizeof(node));
	ptr->data=data;
	ptr->left=NULL;
	ptr->right=NULL;
	return ptr;
}


bool sum_Subtree_check(int*cur_sum, node*root ) {
	if(root==NULL) {
		*cur_sum=0;
		return false;
	}	
	int sum_left=0,sum_right=0;
	bool left_check=sum_Subtree_check(&sum_left, root->left);
	bool right_check=sum_Subtree_check(&sum_right,root->right);
	return left_check || right_check || (*cur_sum=root->data+sum_left+sum_right)==sum;
}


int wrapper_func(node*root) {
	int cur_sum=0;
	return sum_Subtree_check(&cur_sum, root);
}


int main () {
	
	/*
			 8
		   /   \
		  5	    4
		 / \     \
		9  7     11
		  / \    /
		 1  12  3
		     \
		      2
	*/
	node*root = newnode(8); 
    root->left    = newnode(5); 
    root->right   = newnode(4); 
    root->left->left = newnode(9); 
    root->left->right = newnode(7); 
    root->left->right->left = newnode(1); 
    root->left->right->right = newnode(12); 
    root->left->right->right->right = newnode(2); 
    root->right->right = newnode(11); 
    root->right->right->left = newnode(3); 
    scanf("%d" ,&sum); 
    if(wrapper_func(root))
    	printf("Exist");
    else
    	printf("non_exist");
    return 0;
}