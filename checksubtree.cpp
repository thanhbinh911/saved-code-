#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>


/*APPROACH: 
+) traverse the tree T in Preorder fahsion;
+) for every visited node in the traversal, see if the subtree rooted with this node is identiccal to S
+) To check the subtree is identical or not <-- traverse on the tree S and T simultaneously
+) if a visited node is not equal then return false 
else continue traversing the whole tree S is traversed
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

/* 
a utility function to check whether 
trees with roots as root1 and root 2 are identical or not 	
approach:  we traverse on the tree S and T simultaneously and correspondingly
(i.e: check left_child with left_child, right_child with right_child)
*/
bool areIdentical(node*root1, node*root2) {
	// base case:
	if(root1==NULL && root2==NULL)
		return true;
	if(root1==NULL || root2==NULL) 
		return false;
    /* Check if the data of both roots is same and data of
       left and right subtrees are also same */
	return(root1->data == root2->data && areIdentical(root1->left,root2->left) && areIdentical(root1->right, root2->right));
}

//THIS function check if S is a subtree of T
bool isSubtree(node*T, node*S) {
	//if S is NULL by default
	if(S==NULL)
		return true;
	//if T is NULL by default or S is not a subtree of T then we will traverse all node of T
	// and T become NULL 
	if(T==NULL) 
		return false;
	if(areIdentical(T,S))
		return true;
	return (isSubtree(T->left,S) || isSubtree(T->right, S));
}



int main () {
    // TREE 1
    /* Construct the following tree
              26
            /   \
          10     3
        /    \     \
      4      6      3
       \
        30
    */
    struct node* T = newNode(26);
    T->right = newNode(3);
    T->right->right = newNode(3);
    T->left = newNode(10);
    T->left->left = newNode(4);
    T->left->left->right = newNode(30);
    T->left->right = newNode(6);
 
    // TREE 2
    /* Construct the following tree
          10
        /    \
      4      6
       \
        30
    */
    struct node* S = newNode(10);
    S->right = newNode(6);
    S->left = newNode(4);
    S->left->right = newNode(30);
    if(isSubtree(T,S))
    	printf("Tree S is subtree of Tree T");
    else 
    	printf("Tree S is not a subtree of Tree T");
}


/*
if one of the conditions in the chain connected by && is false,
the recursive part (or any subsequent conditions) will not be checked.
This short-circuit evaluation helps in avoiding unnecessary computations 
and can be particularly beneficial in recursive functions to prevent deep and redundant recursion. */