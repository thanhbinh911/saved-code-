#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>


//typedef struct Treenode{
//	int data;
//	struct Treenode*left,*right;
//}node;
//
//node*createNode(int data) {
//	node*newNode=(node*)malloc(sizeof(node));
//	newNode->left=NULL;
//	newNode->right=NULL;
//	newNode->data=data;
//	return newNode;
//}
//
//bool isLeaf(node*root) {
//	if(root->left==NULL && root->right==NULL)
//		return true;
//	return false;
//}
//
//
//void sum_left_leaves(node*root, int*sum) {
//	if(root!=NULL) {
//		if(isLeaf(root->left)) 
//			*sum+=root->left->data;
//		else 
//			sum_left_leaves(root->left, sum);
//		sum_left_leaves(root->right,sum);
//	}
//}
//
//
//int main () {
//	
////    Create first tree:    1
////                        /   \.
////                       3     2
////                      / \	  /
////                     5  7	 10	
////						 /   
////						15	
//    node*root= createNode(1);
//    root->left = createNode(3);
//    root->right = createNode(2);
//    root->left->left = createNode(5);
//    root->right->left=createNode(10);
//    root->left->right=createNode(7);
//    root->left->right->left=createNode(15);
//    int sum=0;
//    sum_left_leaves(root, &sum);
//    printf("%d", sum);
//}

//APPROACH2: USING QUEUE OF PAIRS 
//DEF: queue of pairs: a container containing pairs as the elements of the queue.
//The first element is referred to as first and the second element is refered to as second
// their relative order is fixed in the form of {first,second}  


//definition for a binary tree node
typedef struct TreeNode{
	int val;
	struct TreeNode*left,*right;
}TreeNode;

//definition for a queue node(each node contain a tree_node together with 
// the indicator to know whether it is left child or not and pointer to the next queue node)

typedef struct QueueNode {
	TreeNode*node;
	int isLeft;
	struct QueueNode*next;
}QueueNode;

//function to create a new treenode
TreeNode* newTreeNode(int val) {
	TreeNode*node=(TreeNode*)malloc(sizeof(TreeNode));
	node->val=val;
	node->left=NULL;
	node->right=NULL;
	return node;
}

// function to create a new queuenode 
QueueNode* newQueueNode(TreeNode*node, int isLeft) {
	QueueNode*qnode=(QueueNode*)malloc(sizeof(QueueNode));
	qnode->node=node;
	qnode->isLeft=isLeft;
	qnode->next=NULL;
	return qnode;
}

// function to add a node to the queue

void enqueue(QueueNode**front, QueueNode**rear, TreeNode*node, int Isleft) {
	QueueNode*newqnode=newQueueNode(node,Isleft);
	if(*rear==NULL) 
		*rear=*front=newqnode;
	else {
		(*rear)->next=newqnode;
		*rear=newqnode;	
	}
}

//function to remove a node from the queue
QueueNode*dequeue(QueueNode**front, QueueNode**rear) {
	if(*front==NULL)
		return NULL;
	QueueNode*temp=*front;
	*front=(*front)->next;
	if(*front==NULL) 
		*rear=NULL;
	return temp;
}

//Function to compute the sum of left leaves(using breadth_first_search with the heap of queue data structure)
int sum_left_leaves(TreeNode*root) {
	if(root==NULL)
		return 0;
	int sum=0;
	//the root is not a left child
	QueueNode*front;
	QueueNode*rear;
	front=rear=newQueueNode(root,0);
	while(front!=NULL) {
		QueueNode*temp=dequeue(&front,&rear);
		TreeNode*node=temp->node;
		if(node->left==NULL && node->right==NULL && temp->isLeft)
			sum+=node->val;
		if(node->left!=NULL) 
			enqueue(&front,&rear,node->left,1);
		if(node->right!=NULL) 
			enqueue(&front,&rear,node->right,0);	
		free(temp);
	}
	return sum;	
}

void free_memory(TreeNode*root) {
	if(root==NULL)
		return;
	free_memory(root->left);
	free_memory(root->right);
	free(root);
}


int main () {
    // Creating a sample tree:
    //        1
    //       / \
    //      2   3
    //     / \   \
    //    4   5   6
    // Left leaf nodes: 4
    TreeNode*root = newTreeNode(1);
    root->left = newTreeNode(2);
    root->right = newTreeNode(3);
    root->left->left = newTreeNode(4);
    root->left->right = newTreeNode(5);
    root->right->right = newTreeNode(6);
    root->right->left= newTreeNode(12);
    int sum=sum_left_leaves(root);
    printf("%d", sum);
    free_memory(root);
}