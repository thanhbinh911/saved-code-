#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX_SIZE 100
#define MODULE 1000

typedef struct node{
	char key[15];
	struct node*left,*right;
}node;

typedef struct hashmap {
	node*buckets[MAX_SIZE];
}hashmap;

void initial_hashmap(hashmap*map);
node*insert_BST(node*root, char*key);
int insert_hash(hashmap*map,char*key);
node*FindBST(node*root, char*key);
int Find(hashmap*map, char*key);


node*makeNode(char*key) {
	node*newNode=(node*)malloc(sizeof(node));
	if(newNode==NULL) {
		printf("memory allocation failed\n");
		exit(1);
	}
	strcpy(newNode->key,key);
	newNode->left=NULL;
	newNode->right=NULL;
	return newNode;
}

hashmap*initial_hashmap() {
	hashmap*newhash=(hashmap*)malloc(sizeof(hashmap));
	for(int i=0; i<MAX_SIZE; i++ )
		newhash->buckets[i]=NULL;
	return newhash;
}

int hash_code(char*str) {
	int length=strlen(str);
	int code=0;
	for(int i=0; i<length; i++) 
		code=(code*256+str[i])%MODULE;
	return code;
}


node*FindBST(node*root, char*key) {
	if(root==NULL) 
		return NULL;
	if(strcmp(root->key,key)==0)
		return root;
	else if(strcmp(root->key,key)>0)
		return FindBST(root->left,key);
	else 
		return FindBST(root->right,key);
}

int Find(hashmap*map, char*key) {
	int idx=hash_code(key);
	node*ptr=FindBST(map->buckets[idx], key);
	return ptr? 1:0;
}

node*insert_BST(node*root, char*key) {
	if(root==NULL) 
		return makeNode(key);
	if(strcmp(root->key,key)>0)
		root->left=insert_BST(root->left,key);
	else if(strcmp(root->key,key)<0)
		root->right=insert_BST(root->right,key);
	else
		return root;
	return root;	
}

int insert_hash(hashmap*map,char key[]) {
	int idx=hash_code(key);
	if(FindBST(map->buckets[idx],key)!=NULL)
		return 0;//k already existed
	map->buckets[idx]=insert_BST(map->buckets[idx],key);
	return 1;
}


int main () {
	hashmap*map=initial_hashmap();
	char str[20];
	char buffer[10];
	while(1) {
	scanf("%s", str);
	if(strcmp(str, "*")==0)
			break;
	insert_hash(map, str);
	}
	while(1) {
		scanf("%s", buffer);
		if(strcmp(buffer,"***")==0)
			break;
		else if(strcmp(buffer,"find")==0) {
			scanf("%s",str);
			printf("%d\n", Find(map, str));
		}	
		else if(strcmp(buffer,"insert")==0) {
			scanf("%s", str);	
			printf("%d\n", insert_hash(map,str));
		}
	}
}

