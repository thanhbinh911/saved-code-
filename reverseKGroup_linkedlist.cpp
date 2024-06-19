#include<stdio.h>
#include<stdlib.h>

struct ListNode{
	int val;
	struct ListNode*next;
};


struct ListNode*create_node(int val) {
	struct ListNode*newNode=(struct ListNode*)malloc(sizeof(struct ListNode));
	newNode->val=val;
	newNode->next=NULL;
	return newNode;
}


void insert(struct ListNode**head, int val) {
	struct ListNode*newNode=create_node(val);
	if(*head==NULL)
		*head=newNode;
	else {
	struct ListNode*tmp=*head;
	while(tmp->next!=NULL)
		tmp=tmp->next;
	tmp->next=newNode;
	}
}

//function to reverse a portion of the linked list 
struct ListNode*reverse(struct ListNode*head, int k) {
	struct ListNode*prev=NULL;
	struct ListNode*cur=head;
	struct ListNode*next=NULL;
	while(k>0) {
		next=cur->next;
		cur->next=prev;
		prev=cur;
		cur=next;
		k--;
	}
	// new root struct ListNode after reverse
	return prev;
}
struct ListNode*reverseKGroup(struct ListNode*head, int k) {
	if(head==NULL || k==1)
		return head;
	int length=0;
	struct ListNode*temp=head;
	while(temp!=NULL) {
		length++;
		temp=temp->next;
	}
	//store the new head of the list
	struct ListNode*newHead=NULL;
	// to store the end of the previous group
	struct ListNode*prevGroupEnd=NULL;
	// the head struct ListNode of the part of list we want to reverse
	struct ListNode*current=head;
	while(length>=k) {	
		struct ListNode*groupStart=current;
		struct ListNode*groupEnd=current;
		//modify the groupend to point to the last struct ListNode of current group 
		for(int i=0; i<k-1; i++)
			groupEnd=groupEnd->next;
		struct ListNode*nextGroupStart=groupEnd->next;
		// temporarily end the list 
		groupEnd->next=NULL;
		//reverse the current group
		struct ListNode*reverseGroupHead=reverse(groupStart, k);
		//update the newhead if it's the first group to be reversed
		if(newHead==NULL)
			newHead=groupEnd;
		//linked the reversed group's end to the remaining part of the list
		groupStart->next=nextGroupStart;
		// We need to check condition because if we modify the first group,
		// then it has no prev group to connect to, 
		if(prevGroupEnd!=NULL)
			prevGroupEnd->next=groupEnd;
		prevGroupEnd=groupStart;
		current=nextGroupStart;
		length-=k;
	}
	// return the newHEAD if exist at least 1 group is reverse else, reverse the original root  
	return newHead?newHead:head;
}
void linkedlist_traversal(struct ListNode*head) {
	while(head!=NULL) {
		printf("%d -> ", head->val);
		head=head->next;
	}
	printf("NULL\n");
}

int main () {
	struct ListNode*head=NULL;
	insert(&head, 1);
	insert(&head, 2);
	insert(&head, 3);
	insert(&head, 4);
	insert(&head, 5);
	linkedlist_traversal(head);
	head=reverseKGroup(head,2);
	linkedlist_traversal(head);
}

