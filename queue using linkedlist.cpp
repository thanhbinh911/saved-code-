#include<stdio.h>
#include<stdlib.h>


// A linked list (LL) node to store a queue entry
typedef struct Qnode {
	int data;
	struct Qnode*next;
}qnode;

// The queue, front stores the front node of LL and rear
// stores the last node of LL
typedef struct Queue {
	qnode*front,*rear;
}queue;

//a utility function to create a new linkedlist node
qnode* newnode(int k) {
	qnode*temp=(qnode*)malloc(sizeof(qnode));
	temp->data=k;
	temp->next=NULL;
	return temp;
}

// a utility function to create an empty queue
queue* queue_create() {
	queue*q=(queue*)malloc(sizeof(queue));
	q->front=q->rear=NULL;
	return q;
}

// the function to add a key k to q 

void enqueue(queue*q, int k) {
	qnode*temp=newnode(k);
	if(q->rear==NULL) 
		q->rear=q->front=temp;
	else {
		q->rear->next=temp;
		q->rear=temp; 
	}
}


void dequeue(queue*q) {
	if(q->front==NULL)
		exit(1);
	qnode*temp=q->front;
	q->front=q->front->next;
	if(q->front==NULL){
		q->rear=NULL;
	}
	free(temp);
}

void queue_display(queue*q) {
	if(q->front==NULL)
		printf("\n the queue is empty");
	else {
		qnode*temp=q->front;
		while(temp!=NULL) {
			printf("%d ", temp->data);
			temp=temp->next;
		}
	}
}

int main () {
	queue*q=queue_create();
	enqueue(q,10);
	enqueue(q,20);
	dequeue(q);
	enqueue(q,40);
	queue_display(q);
	return 0;
}