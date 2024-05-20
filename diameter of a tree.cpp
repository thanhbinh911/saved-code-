/* PROGREAM TO COMPUTE THE DIAMETER OF a binary tree

Diameter/width of a tree: number of nodes on the longest path between two leaves(end nodes)
*/
#include<stdlib.h>
#include<stdio.h>

int max(int a, int b) {
	return a>b?a:b;
}

typedef struct node{
	int data;
	struct node*left,*right;
}node;

node*create_node(int data) {
	node*ptr=(node*)malloc(sizeof(node));
	ptr->data=data;
	ptr->left=NULL;
	ptr->right=NULL;
	return ptr;
}

/*Approach: the diameter of a tree is the largest of the following
+)the diameter of T's Left subtree.
+)the diameter T's right subtree.
+) the longest path between leaves that goes through the root of T
(this can be computed from the heights of the subtrees of T)
*/

int height_of_node(node*x) {
	if(x==NULL)
		return 0;
	return 1+max(height_of_node(x->left), height_of_node(x->right));
}



int diameter(node* root) {
	if(root==NULL)
		return 0;
	int l_height=height_of_node(root->left);
	int r_height=height_of_node(root->right);
	
	int l_diameter=diameter(root->left);
	int r_diameter=diameter(root->right);
	return max(1+r_height+l_height, max(l_diameter,r_diameter))	;
}
int main (){
	
	node*root=create_node(1);
	root->left=create_node(2);
	root->right=create_node(3);
	root->left->left=create_node(4);
	root->left->right=create_node(5);
	printf("%d", diameter(root));
}