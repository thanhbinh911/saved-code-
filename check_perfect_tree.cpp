#include<stdio.h>
#include<stdlib.h>


/* Program to check whether the given binary tree is perfect or not
Approach:+)level size check(before processing nodes at each level): using level_order traversal to check the number 0f nodes at each level (size)
equal the the expected number of nodes for that level( stored at level variable)
+) node processing: for each node at the current level, we enqueue its children(if they exist)
which will become nodes for the next level 
*/
typedef struct node{
	int data;
	struct node*left,*right;
}node;


node*newNode(int data) {
	node*ptr=(node*)malloc(sizeof(node));
	ptr->data=data;
	ptr->left=NULL;
	ptr->right=NULL;
	return ptr;
}

bool check_perfect_tree(node* root) {
	// an empty tree is perfect tree
	if(root==NULL) 
		return true;
	node*queue[100];
	int front=0,rear=0;
	queue[rear++]=root;
	int level=1;
	bool valid=true;
	int *level_values;
	while(front!=rear && valid) {
		int size=rear-front;
		if (size!=level) {
			valid=false;
			break;
		}
		for(int i=0; i<size; i++) {
			node*temp=queue[front++];
			if(temp->left!=NULL)
				queue[rear++]=temp->left;
			if(temp->right!=NULL)
				queue[rear++]=temp->right;
		}
		level=level*2;
	}
	return valid;
}

int main () {
	node*root=newNode(7);
	root->left=newNode(4);
	root->right=newNode(9);
	root->left->left=newNode(1);
	root->left->right=newNode(2);
	root->right->left=newNode(3);
	root->right->right=newNode(10);
	bool isPerfect=check_perfect_tree(root);
	if(isPerfect)
		printf("YES");
	else
		printf("NO");
}
