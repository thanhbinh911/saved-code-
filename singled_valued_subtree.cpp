#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

/* Note: the tree itself is consider a subtre, convention: a empty tree(NULL) is set to be true for checking   */
/*APPROACH: do bottom-up manner, we check that at every node if exits single valued subtree or not
(condition: right_subtree and left_subtree are both single_value subtree
+) case1: either left_subtree or right_subtree is not singled_value_subtree
-->so is the subtree at cur node 
+) case2: both left and right subtree are empty
--> the subtree at cur is singled_value_subtree
+) case3: if either left or right subtree is empty, check the value of cur_node with the value of the root of the subtree which is not empty
--> if equal -> subtree at cur node is singled... otherwise it is not
+) case 4: both left and right subtree are not empty and singled valued subtree
--> check simlilarly for case 3
*/

typedef struct node{
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
/*
If either the left or right subtree is not single-valued, return false.
If the left subtree exists and its value does not match the current node's value, return false.
If the right subtree exists and its value does not match the current node's value, return false.
If all the conditions are met, 
increment the count and return true indicating the subtree rooted at the current node is single-valued.
*/

bool single_valued_subtree(node*root,int*cnt) {
	if(root==NULL)
		return true;
	bool left_check=single_valued_subtree(root->left,cnt);
	bool right_check=single_valued_subtree(root->right,cnt);
	if(!(left_check) || (!right_check))
		return false;
	if(root->left!=NULL && root->left->data!=root->data)
		return false;
	if(root->right!=NULL && root->right->data!=root->data)
		return false;
	(*cnt)++;
	return true;
}


int count_subtree(node*root) {
	int count=0;
	single_valued_subtree(root, &count);
	return count;
}

int main () {
	node*root=newNode(5);
	root->left=newNode(4);
	root->right=newNode(5);
	root->left->left=newNode(4);
	root->left->right=newNode(4);
	root->right->right=newNode(5);
	int nums=count_subtree(root);	
	printf("%d", nums);
}