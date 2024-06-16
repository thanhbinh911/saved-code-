#include<stdio.h>
#include<stdlib.h>

typedef struct node{
	int val;
	struct node*left, *right;
}node;

node*create_node(int val) {
	node*newNode=(node*)malloc(sizeof(node));
	newNode->val=val;
	newNode->left=NULL;
	newNode->right=NULL;
	return newNode;
}

node*insert(node*root, int val) {
	if(root==NULL)
		return create_node(val);
	if(root->val==val)
		return root;
	else if(root->val>val)
		root->left=insert(root->left,val);
	else 
		root->right=insert(root->right,val);
	return root;
}

// result struture holds the result of the recursive LCA search,
//including the node and flags indicating if p ang q were found
typedef struct result{
	node*ptr;
	int foundP;
	int foundQ;
}Result;

result*create_result(node*ptr, int foundP, int foundQ) {
	Result*result=(Result*)malloc(sizeof(Result));
	result->ptr=ptr;
	result->foundP=foundP;
	result->foundQ=foundQ;
	return result;
}

result*LCA_Find(node*root, node*p, node*q) {
	if(root==NULL) {
		return create_result(NULL,0,0);
	}
	result*left_result=LCA_Find(root->left,p,q);
// if we already find the lca in the left subtree, we can return this result immediatiely
//--> short-circut recursion
	if(left_result->ptr!=NULL)
		return left_result;
	result*right_result=LCA_Find(root->right,p,q);
//similarly for right subtree	
	if(right_result->ptr!=NULL)
		return right_result;
	int foundP=left_result->foundP || right_result->foundP ||root==p;
	int foundQ=left_result->foundQ || right_result->foundQ ||root==q;
	node*ptr=NULL;
	if(foundP && foundQ)
		ptr=root;
	return create_result(ptr,foundP,foundQ);
}


node* LCA(node*root, node*p, node*q ) {
	Result*result=LCA_Find(root, p, q);
	if(result->foundP && result->foundQ)
		return result->ptr;
	else
		return NULL;
}

int main () {
	node*root=NULL;
	root=insert(root, 3);
	root=insert(root, 5);
	root=insert(root, 1);
	root=insert(root, 6);
	root=insert(root, 2);
	root=insert(root, 0);
	root=insert(root, 8);
	root=insert(root, 7);
	root=insert(root, 4);
	node*p=root->left->left;
	node*q=root->left->right;
	node* lca = LCA(root, p, q);
    if (lca != NULL) {
        printf("LCA of %d and %d is %d\n", p->val, q->val, lca->val);
    } else {
        printf("LCA not found\n");
    }
}