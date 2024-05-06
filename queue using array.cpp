#include<stdio.h>
#include<stdlib.h>


typedef struct queue {
	int front,rear,capa;
	int*ptr;
}queue;

queue*queue_create(int cap) {
	queue*p=(queue*)malloc(sizeof(queue));
	p->front=0;
	p->rear=-1;
	p->capa=cap;
	p->ptr=(int*)malloc(sizeof(int)*cap);
	return p;
}

void queueEnqueue(queue* p, int data) {
	if(p->rear==(p->capa)-1) {
		printf("\nqueue is full\n");
	}
	else {
	p->ptr[++p->rear]=data;
	printf("\n%d is enqueued to queue\n", data );
	}
}


void queueDequeue (queue*p) {
	if(p->rear==-1) {
		printf("\n Queue is already Empty\n");
	}
	else {
	int value=p->ptr[0];
	printf("\n%d is dequeued from the queue\n", value);
	for(int i=p->front; i<=p->rear-1; i++) 
		p->ptr[i]=p->ptr[i+1]; 
	p->rear--;
	}
}

void queueFront(queue*p) {
	if(p->rear==-1) {
		printf("\nQueue is empty");
		return;
	}
	printf("\nFront element is: %d", p->ptr[0]);
	return ;
}

void queueDisplay(queue*p) {
	if(p->rear==-1) {
		printf("\nQueue is empty");
		return;
	}
	
	for(int i=0; i<=p->rear; i++)
		printf(" %d <--",p->ptr[i]);
	return;
}
int main () {
	int cap;
	scanf("%d", &cap);
	queue*p=queue_create(cap);
	queueDisplay(p);
	queueEnqueue(p,12);
	queueEnqueue(p,30);
	queueEnqueue(p,40);
	queueDequeue(p);
	queueDequeue(p);
	queueDisplay(p);
}