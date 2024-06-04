#include<stdio.h>
#include<stdlib.h>



typedef struct node {
	int data;
	struct node*left, *right;
}node;


node*addNode(int data) {
	node*newNode=(node*)malloc(sizeof(node));
	newNode->data=data;
	newNode->left=NULL;
	newNode->right=NULL;
	return newNode;
}


//function to actually count the number of path with the starting point from the given node
int count_path(node*root, int cur_sum, int target_sum) {
	if(root==NULL)
		return 0;
	cur_sum+=root->data;
	int path;
	if(cur_sum==target_sum)
		path=1;
	else
		path=0;
	path+=count_path(root->left,cur_sum,target_sum);
	path+=count_path(root->right, cur_sum,target_sum);
	return path;
}


//traverse the whole tree and call the function to count numbers of path possibily start from every node 
int count_from_node(node*root, int target_sum) {
	if(root==NULL)
		return 0;
	//count path starting from current node;	
	int path_from_here=count_path(root,0,target_sum);
	int path_from_left_child=count_from_node(root->left,target_sum);
	int path_from_right_child=count_from_node(root->right,target_sum);
	return path_from_here+path_from_left_child+path_from_right_child;
}




int main () {
	node*root = addNode(1);
    root->left = addNode(5);
    root->right = addNode(-3);
    root->left->left = addNode(3);
    root->left->right = addNode(2);
    root->right->left = addNode(6);
    root->left->left->left=addNode(3);
    root->left->left->right=addNode(-2);
    root->left->right->right=addNode(-1);
 	
    /*  The above code constructs this tree
 
                1
             /       \
           5         -3
          /  \      /  
         3   2     6   
       	/ \   \
       3  -2  -1	
	   */ 
	int targetSum=6;
	int path=count_from_node(root,targetSum);
	printf("%d", path);
}