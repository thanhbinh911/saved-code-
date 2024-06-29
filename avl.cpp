#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
	int key;
	struct Node*left;
	struct Node*right;
	// this field to help to compute balance factor(height of left_sub_tree-height_of right_sub tree)
	int height;
}node;

int Height(node*n) {
	if(n==NULL)
		return 0;
	return n->height;
}


node*create_node(int key) {
	node* newNode=(node*)malloc(sizeof(node));
	newNode->key=key;
	newNode->left=NULL;
	newNode->right=NULL;
	// newNode is initally added at leaf
	newNode->height=1;
	return newNode;	
}

int max(int a, int b) {
	return a>b?a:b;
}

int getBalance(node*n) {
	if(n==NULL)
		return 0;
	return Height(n->left)-Height(n->right);
}

node*leftRotation(node* x) {
	node* y=x->right;
	node* temp=y->left;
	
	//perform rotation
	y->left=x;
	x->right=temp;
	
	//update heights 
	x->height=max(Height(x->left),Height(x->right))+1;
	y->height=max(Height(y->left),Height(y->right))+1;
	// return new root 
	return y;
}

node*rightRotation(node*y) {
	node*x=y->left;
	node*temp=x->right;
	
	//perform rotation
	x->right=y;
	y->left=temp;
	
	y->height=max(Height(y->left),Height(y->right))+1;
	x->height=max(Height(x->left),Height(x->right))+1;
	//return the new root
	return x;
}

node*insert(node* root, int key) {
	
	//1 perform the normal BST insertion
	if(root==NULL)
		return create_node(key);
	if(root->key>key)
		root->left=insert(root->left,key);
	else if(root->key<key)
		root->right=insert(root->right,key);
	else
	//not allow duplicate key
		return root;
		
	//update the height of this ancestor node
	root->height=1+max(Height(root->left),Height(root->right));
	// get the balance factor of this ancestor node to check whether this node became unbalanced or not 
	int balance=getBalance(root);
	//left left case 
	if(balance>1 && root->left->key>key)
		return rightRotation(root);
	//left right case
	if(balance>1 && root->left->key<key) {
		root->left=leftRotation(root->left);
		return rightRotation(root);
	}
	//right right case
	if(balance<-1 && root->right->key<key)
		return leftRotation(root);
	//right left case
	if(balance<-1 && root->right->key>key) {
		root->right=rightRotation(root->right);
		return leftRotation(root);
	}
	//if this ancestor node is balance  then return the unchanged node pointer 
	return root;
}

// given a non_empty BST, return the node with minimum key value found in that tree

node*minValueNode(node* root) {
	node*cur=root;
	while(cur->left!=NULL)
		cur=cur->left;
	return cur;
}

//recursive function to delete a node with given key 
// from subtree with given root. It returns root of the modified subtree

node*deleteNode(node*root, int key) {
	//step1: Perform standard BST delete
	
	if(root==NULL)
		return NULL;
	if(key< root->key)
		root->left=deleteNode(root->left,key);
	else if(key> root->key)
		root->right=deleteNode(root->right,key);
	//this is the node to be deleted
	else {
		//node with only one child or no child
		if(root->left==NULL || root->right==NULL) {
			node*temp=root->left?root->left:root->right;
			
			// no child case
			if(temp==NULL) {
				temp=root;
				root=NULL;
			}
			else // one child case
			*root=*temp; // copy the contents of the non_empty child
			
			free(temp);
			temp=NULL;
		}
		else {
			// replace the node with the successor(smallest in the right subtree)
			node*temp=minValueNode(root->right);
			root->key=temp->key;
			
			// delete the successor
			root->right=deleteNode(root->right, temp->key);
		}
	}
	// if the tree have only one node then return 
	 
	if(root==NULL)
		return root;
	//STEP 2: UPDATE height of the current node
	root->height=1+max(Height(root->left),Height(root->right));
	
	//STEP 3: get the balance factor of this node
	
	int balance=getBalance(root);
	//LEFT LEFT Case
	if(balance>1 && getBalance(root->left)>=0)
		return rightRotation(root);
	//LEFT RIGHT Case
	if(balance>1 && getBalance(root->left)<0) {
		root->left=leftRotation(root->left);
		return rightRotation(root);
	}
	if(balance<-1 && getBalance(root->right)<=0)
		return leftRotation(root);
	//right left case
	if(balance<-1 && getBalance(root->right)>0) {
		root->right=leftRotation(root->right);
		return leftRotation(root);
	}
	return root;
}

void preOrder(node*root) {
	if(root==NULL) {
		return;
	}
	printf("%d ", root->key);
	preOrder(root->left);
	preOrder(root->right);
}

int main () {
  node *root = NULL; 
/* Constructing tree given in the above figure */
    root = insert(root, 9);
    root = insert(root, 5);
    root = insert(root, 10);
    root = insert(root, 0);
    root = insert(root, 6);
    root = insert(root, 11);
    root = insert(root, -1);
    root = insert(root, 1);
    root = insert(root, 2);
 
    /* The constructed AVL Tree would be
            9
           /  \
          1    10
        /  \     \
       0    5     11
      /    /  \
     -1   2    6
    */
 
    printf("Preorder traversal of the constructed AVL "
           "tree is \n");
    preOrder(root);
 
    root = deleteNode(root, 10);
 
    /* The AVL Tree after deletion of 10
            1
           /  \
          0    9
        /     /  \
       -1    5     11
           /  \
          2    6
    */
 
    printf("\nPreorder traversal after deletion of 10 \n");
    preOrder(root);
 
    return 0;
} 