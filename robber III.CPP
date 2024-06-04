#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct node {
	int data;
	struct node*left, *right;
	
}node;

int max(int a, int b) {
	return a>b?a:b;
}

node*addNode(int data) {
	node*newNode=(node*)malloc(sizeof(node));
	newNode->data=data;
	newNode->left=NULL;
	newNode->right=NULL;
	return newNode;
}



int*dfs(node*root) {
	int*result=(int*)malloc(sizeof(int)*2);	
	if(root==NULL) {
		result[0]=0;
		result[1]=0;
		return result;
	}
	
	int*left=dfs(root->left);
	int*right=dfs(root->right);
	result[0]=root->data+left[1]+right[1];
	result[1]=max(left[0],left[1])+max(right[0],right[1]);
	free(left);
	free(right);
	return result;
}


int rob(node*root) {
	int*result=dfs(root);
	return max(result[0], result[1]);
}


int main () {
	node*root = addNode(3);
    root->left = addNode(2);
    root->right = addNode(10);
    root->left->right = addNode(3);
    root->right->left = addNode(1);

    /*  The above code constructs this tree
 
                 3
             /       \
            2        10
            \      /  
            3     1   	
	   */ 
	int max_profit=rob(root);
	printf("%d", max_profit);
}