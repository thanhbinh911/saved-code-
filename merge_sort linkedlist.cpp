#include<stdio.h>
#include<stdlib.h>


typedef struct node{
	int data;
	struct node*next;
}node;


node*makeNode(int data) {
	node*newNode=(node*)malloc(sizeof(node));
	newNode->data=data;
	newNode->next=NULL;
	return newNode;
}


void add_at_end(node**head, int data){
	node*newNode=makeNode(data);
	if(*head==NULL) {
		*head=newNode;
		return;
	}
	node*temp=*head;
	while(temp->next!=NULL)
		temp=temp->next;
	temp->next=newNode;
}


void traverse_linkedlist(node*head){
	if(head==NULL)
		return;
	while(head!=NULL) {
		printf("%d ", head->data);
		head=head->next;
	}
}

//function to merge 2 sorted lists 

node* merge(node*left, node*right) {
	node dummy;
	node*tail=&dummy;
	while(left!=NULL && right!= NULL) {
		if(left->data<=right->data) {
			tail->next=left;
			left=left->next;
		}
		else {
			tail->next=right;
			right=right->next;
		}
		// after modify dummy->next, now tail is independently of dummy
		tail=tail->next;
	}
	if(left!=NULL)
		tail->next=left;
	else
		tail->next=right;
	return dummy.next;
}


// function to find the middle node of a linked list with >=2 node
node*find_middle(node*head) {
	node*slow = head;
	node*fast = head->next;
	// head!=NULL To handle case odd number node
	//head->next!=NULL to handlle case even number node
	while(fast != NULL && fast->next != NULL) {
		slow = slow->next;
		fast = fast->next->next;
	}
	return slow;
}


node*sort_list(node* head) {
	// head=NULL to handle empty linked list case
	// head->next=NULL to handle 1 node case
	if(head==NULL || head->next==NULL)
		return head;
	node*middle=find_middle(head);
	node*right=middle->next;
	
	//split the list into two halves.
	middle->next=NULL;
	
	//recursive sort 2 halves
	head = sort_list(head);
	right = sort_list(right);
	
	//merge the 2 sorted halves
	return merge(head, right);
	// return the pointer to the merged sorted list
}




int main () {
	node*head=NULL;
	add_at_end(&head,-1);
	add_at_end(&head,-5);
	add_at_end(&head,3);
	add_at_end(&head,4);
	add_at_end(&head,0);
	traverse_linkedlist(head);
	printf("\n");
	head=sort_list(head);
	traverse_linkedlist(head);
}