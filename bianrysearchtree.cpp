//BINARY TREE IMPLEMENTATION
#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
	int key;
	struct Node*left,*right,*parent;
}node;
// if the tree is empty then create a new node with key k and return the pointer to the node
// if k=key of the root node then return the pointer of the root node
// if k> key of root node then insert k into the right subtree(recursion)
// if k< key of root node then insert k into left subtree(recursion)


node*create_node(int key, node*parent) {
	node*newNode=(node*)malloc(sizeof(node));
	newNode->key=key;
	newNode->left=NULL;
	newNode->right=NULL;
	newNode->parent=parent;
	return newNode;
}

node*find(node*root, int key) {
	if (root==NULL)
		return NULL;
	if(root->key==key)
		return root;
	if(root->key<key)
		return find(root->right, key);
	else
		return find(root->left, key); 
}


//node*insert(node*root, int key) {
//	if(root==NULL)
//		return create_node(key);
//	if(root->key==key)
//		return root;
//	if(root->key<key) {
//		root->right=insert(root->right, key);
//	}
//	else
//		root->left=insert(root->left, key);	
//	return root;
//}

node* insert(node*root, int key) {
	if(root==NULL)
		return create_node(key, NULL);
	node*parent=NULL;
	node*cur=root;
	while(cur!=NULL) {
		parent=cur;
		if(cur->key>key)
			cur=cur->left;
		else if(cur->key<key)
			cur=cur->right;
		else 
			return root;	// duplicate keys are not allowed
	}
	node*newNode=create_node(key, parent);
	if(parent->key>key)
		parent->left=newNode;
	else 
		parent->right=newNode;
	return root;	
} 


// function to remove the root node of a binary search tree
//+) if the root node does not have a right child node 
//+)--> return the pointer to the left child node
// if the root node has a right child node then find the node having the smallest
//key on the right subtree to replace

//return value: return the pointer to the new root of the BST after remove the current root
node*remove_root(node*root) {
	if(root==NULL)
		return NULL;
	node*tmp=root;
	// if the BST doesn't contain the right subtree
	if(root->right==NULL) {
		root=root->left;
		if(root)
			root->parent=tmp->parent;
		free(tmp);
		return root;
	}
	// right child has no left child
//(which mean that the smallest value lies at the right child)
	node*p=root->right;
	if(p->left==NULL) {
		root->key=p->key;
		root->right=p->right;
		if(p->right!=NULL)
				p->right->parent=root;
		free(p);
		return root;
	}
	
	// right subtree has left child
	node*pp=root;
	while(p->left!=NULL) {
		pp=p;
		p=p->left;
	}
	pp->left=p->right;
	if(p->right!=NULL)
		p->right->parent=pp;
	root->key=p->key;
	free(p);
	return root;
}

//remove a key from a binary search tree
//+) if the tree is empty => return NULL
//+) if k > key of root => remove k from the right subtree(recusion)
//+) if k< key of root => remove k from the left subtree (recusion)
//+) if k= key of the root node
//-> find the node having the largest key in the left sub tree or the node having 
// the smallest key in the right subtree to replace the root node

node*remove(node*root,int key) {
	if(root==NULL)
		return NULL;
	if(root->key==key) 
		return remove_root(root);
	else if(root->key<key)
		root->right=remove(root->right,key);
	else 
		root->left=remove(root->left,key);
	return root;	
}


/*Predecessor of node x is node y such that key[y] is the largest key <key[x]
-> predecessor of the node with smallest key is NULL
Successor of node is node y sucht that key[y] is the smallest key >key[x]
-> Successor of the node with largest key is NULL

NOTE:
find predecessor/successor of a node on BST without doing comparisons on keys
1. Predecessor:
+) case1: if there exists its left subtree 
--> the predessor is : the rightmost node in its left subtree
+) case2: if not exists its left subtree 
--> the predecessor of x is the closest ancestor having the right child which is either x or ancestor of x
2. Successor:
+) case 1: if there exists it right subtree:
--> the successor is : the the leftmost node in its right subtree
+) case 2: if not exists its right subtree:
--> the successor of x is the closet ancestor having the left child which is either x or ancestor x
*/

node*find_max(node*root) {
	if(root==NULL)
		return NULL;
	while(root->right!=NULL)
		root=root->right;
	return root;
}

node*find_min(node*root) {
	if(root==NULL)
		return NULL;
	while(root->left!=NULL)
		root=root->left;
	return root;
}


node*Predecessor(node*x) {
	if(x->left !=NULL) {
		return find_max(x->left);
	}
	node*p=x->parent;
	while(p!=NULL && x==p->left) {
		x=p;
		p=p->parent;
	}
	//note: when x contain the smallest key in tree, p will gradully point to the root node then point to NULL
	// so that the return value is NULL
	return p;
}

node*Successor(node*x) {
	if(x->right!=NULL)
		return find_min(x->right);
	node*p=x->parent;
	while(p!=NULL && x==p->right) {
		x=p;
		p=p->parent;
	}
	//note when x contain the largest key in tree, p will gradually point to the root node then NULL
	return p;
}

void inorder(node*root) {
	if(root==NULL)
		return;
	inorder(root->left);
	printf("%d ", root->key);
	inorder(root->right);
}
int main() {
    node* root = NULL;
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 70);
    root = insert(root, 60);
    root = insert(root, 80);

    printf("Inorder traversal before deletion:\n");
    inorder(root);
    printf("\n");

    root = remove(root, 50);  // Removing root node

    printf("Inorder traversal after deletion:\n");
    inorder(root);
    printf("\n");
    node*pre=Predecessor(root->right->right);
	printf("%d", pre->key);
}



