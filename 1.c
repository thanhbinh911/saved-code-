#include<stdio.h>
#include<stdlib.h>

typedef struct node{
	int data;
	struct node* link;
}node;

node*top=NULL;

void push(int val) {
	node*ptr=(node*)malloc(sizeof(node));
	if(ptr==NULL) {
		printf("stack overflow");
		exit(1);
	}
	ptr->data=val;
	ptr->link=top;
	top=ptr;
}

int pop() {
	if(top==NULL) {
		printf("stack underflow");
		exit(1);
	}
	int val=top->data;
	node*ptr=top;
	top=top->link;
	free(ptr);
	ptr=NULL;
	return val;
}

int isEmpty() {
	if(top==NULL)
		return 1;
	return 0;
}

int peek() {
	if(isEmpty()) {
		printf("stack underflow");
		exit(1);
	}
	return top->data;
}


void print() {
	if(top==NULL) {
		printf("stack underflow");
		exit(1);
	}
	node*ptr=top;
	printf("the stack elements are: ");
	while(ptr!=NULL) {
		printf("%d ", ptr->data);
		ptr=ptr->link;
	}
	printf("\n");
}


int main () {
	int choice,data;
	while(1) {
		printf("1. Push\n");
		printf("2. Pop\n");
		printf("3. Print the top element\n");
		printf("4. Print all the elements of the stack\n");
		printf("5. Quit\n");
		printf("Please enter your choice: ");	
		scanf("%d", &choice);
		switch(choice) {
			case 1:
				printf("enter the element to be pushed: ");
				scanf("%d", &data);
				push(data);
				break;
			case 2:
				data=pop();
				printf("Deleted element is %d\n", data );
				break;
			case 3:
				printf("the topmost element of the stack is: %d\n",peek());
				break;
			case 4:
				print();
				break;
			case 5:
				exit(1);
			default:
				printf("Wrong choice, try again\n");
		}
	}
	return 0;
}