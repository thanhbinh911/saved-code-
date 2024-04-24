#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct node{
		int data;
		struct node*link;
}node;


node* makeNewNode(int k) {
	node*new1=(node*)malloc(sizeof(node));
	new1->data=k;
	new1->link=NULL;
	return new1;
}

node* find(node*head, int e) {
	node*p=head;
		for(p==head; p!=NULL; p=p->link ) {
			if(p->data==e)
				return p;
		}
		return NULL;
}
node* add_at_end(node*head, int k) {
	node*new1=makeNewNode(k);
	if(head==NULL) {
		head=new1;
		return head;
	}
	else {
	node*ptr=head;
	while(ptr->link!=NULL) {
		ptr=ptr->link;
	}
	ptr->link=new1;
	return head;
	}
}

node* add_at_beg(node*head, int k) {
	node*new1=makeNewNode(k);
	new1->link=head;
	head=new1;
	return head;
}

node* reverse(node*head) {
	node*prev=NULL;
	node*next=head; 
	while(head!=NULL) {
		next=head->link;
		head->link=prev;
		prev=head;
		head=next;
	}      
	head=prev;
	return head;
}


node* addAfter(node*head, int u, int v){
	if(head==NULL) 
		return NULL;
	if(head->data==v) {
		node*q=makeNewNode(u);
		q->link=head->link;
		head->link=q;
		return head;
	}
	head->link=addAfter(head->link,u,v);
	return head;
}

node* addBefore(node*head, int u, int v){
	if(head==NULL)
		return NULL;
	if(head->data==v) {
		node*q=makeNewNode(u);
		q->link=head;
		return q;
	}
	head->link=addBefore(head->link, u,v);
	return head;
}

void traversal(node*head) {
	node*ptr=head;
	while(ptr!=NULL) {
		printf("%d ", ptr->data);
		ptr=ptr->link;
	}	
	printf("\n");
}

node* delete_all(node*head) {
	node*ptr=head;
	while(ptr!=NULL) {
		ptr=ptr->link;
		free(head);
		head=ptr;
	}
	return head;
}

node* delete_node(node*head, int k) {
	node*prev=head;
	node*cur=head;
	if(head==NULL)
		return NULL;
	else if(head->data==k) {
		head=cur->link;
		free(cur);
		cur=NULL;
		return head;
	}
	else { 
	for(prev=head; prev!=NULL; prev=prev->link) {
		if(prev->link->data==k) {
	cur=prev->link;
	prev->link=cur->link;
	free(cur);
	cur=NULL;
	return head;
			}
		}
	}
}


node* solve(node*head) {
	int n,i;
	scanf("%d", &n);
	for(int i=1; i<=n; i++) {
		int k;
		scanf("%d", &k);
		head=add_at_end(head,k);
	}
	while(1) {
		char cmd[256];
		scanf("%s", cmd);
		if(strcmp(cmd, "#")==0) 
			break;
		if(strcmp(cmd,"addlast")==0) {
			int k;
			scanf("%d", &k);
			if(find(head,k)==NULL)
				head=add_at_end(head,k);
}
		else if(strcmp(cmd, "addfirst")==0) {
			int k;
			scanf("%d", &k);
			if(find(head,k)==NULL)
				head=add_at_beg(head,k);
		}
		else if(strcmp(cmd,"addafter")==0) {
			int u,v;
			scanf("%d %d", &u,&v);
			if(find(head,u)==NULL && find(head,v) !=NULL)
				head=addAfter(head,u,v);
		}
		else if(strcmp(cmd,"addbefore")==0) {
			int u,v;
			scanf("%d%d", &u,&v);
			if(find(head,u)==NULL && find(head,v) !=NULL)
				head=addBefore(head,u,v);
			}
		else if(strcmp(cmd,"remove")==0) {
			int k;
			scanf("%d", &k);
			if(find(head,k)!=NULL)
				head=delete_node(head,k);
		}
		else if(strcmp(cmd,"reverse")==0) 
			head=reverse(head);
	}
	return head;	
}
int main () {
	node*head=NULL;
	head=solve(head);
	traversal(head);
	delete_all(head);
}