#include<stdio.h>
#include<stdlib.h>

typedef struct node{
		int data;
		struct node*link;
}node;


int readNode() {
	int data;
	scanf("%d", &data);
	return data;
}

node* makeNewNode() {
	node*new1=(node*)malloc(sizeof(node));
	new1->data=readNode();
	new1->link=NULL;
	return new1;
}

void add_at_end(node*head) {
	node*new1=makeNewNode();
	if(head==NULL) {
		head=new1;
	}
	node*ptr=head;
	while(ptr->link!=NULL) {
		ptr=ptr->link;
	}
	ptr->link=new1;

}

node* add_at_beg(node*head) {
	node*new1=makeNewNode();
	new1->link=head;
	head=new1;
	return head;
}

void insert_certain_pos(node* head, int pos) {
	node*new1=makeNewNode();
	node*ptr=head;
	pos--;
	while(pos!=1) {
		ptr=ptr->link;
		pos--;
	}
	new1->link=ptr->link;
	ptr->link=new1;
}

node* del_at_certain_pos(node*head, int pos) {
	node*prev=head;
	node*cur=head;
	if(head==NULL)
		printf("the list is already empty");
	else if(pos==1) {
		head=cur->link;
		free(cur);
		cur=NULL;
		return head;
	}
	else {
	pos--;
	while(pos!=1) {
		prev=prev->link;
		pos--;
	}
	cur=prev->link;
	prev->link=cur->link;
	free(cur);
	cur=NULL;
	return head;
	}
}


void count_of_nodes_and_print(node*head) {
	int cnt=0;
	if(head==NULL)
		printf("Linked list is empty\n"); 
	node*ptr=NULL;
	ptr=head;
	while(ptr != NULL) {
		cnt++;
		printf("%d\n", ptr->data);
		ptr=ptr->link;
	}
	printf("%d", cnt);
}

node* delete_at_beg(node*head) {
	if(head==NULL) 
		printf("The linked list is already empty");
	node*ptr=head;
	head=head->link;
	free(ptr);
	ptr=NULL;
	return head;
}

node* delete_at_end(node*head) {
	if(head==NULL) {
		printf("the list is already empty");
	}
	else if(head->link==NULL) {
		free(head);
		head=NULL;
	}
	else {
	node*temp=NULL;
	temp=head;
	while(temp->link->link !=NULL) {
		temp=temp->link;
	}
	free(temp->link);
	temp->link=NULL;
	}
	return head;
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

void reverse_recursion(node*p,node**head) {
	if(p->link==NULL) {
		*head=p;
		return ;
	}
	reverse_recursion(p->link,head);
	p->link->link=p;
	p->link=NULL;
}
	
int main () {
	node*head=NULL;
	head=(node*)malloc(sizeof(node));
	head->data=45;
	head->link=NULL;
	node*current=(node*)malloc(sizeof(node));
	current->data=98;
	current->link=NULL;
	head->link=current;
	current=(node*)malloc(sizeof(node));
	current->data=3;
	current->link=NULL;
	head->link->link=current; 
//	add_at_end(head);
//	head=add_at_beg(head);
//	insert_certain_pos(head,3);
//	head=delete_at_beg(head);
//	head=delete_at_end(head);
//	head=del_at_certain_pos(head,1);
//	head=delete_all(head);
//	if(head==NULL)
//		printf("linked list is deleted completely successfully\n");
	reverse_recursion(head, &head);
	count_of_nodes_and_print(head);
}
