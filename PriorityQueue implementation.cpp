#include<stdio.h>
#include<stdlib.h>
// implementation of ascending order priority queue using a min-heap


//define the element structure(hold priority and data for each element)
typedef enum{
	INT,
	STRING,
	POINTER,
}DataType;


typedef struct{
	int priority;
	void*data;
	DataType type;
}HeapElement;

typedef struct{
	HeapElement* elements;
	int size;
	int capacity;
}PriorityQueue;


//function to swap 2 heap elements
void*swap(HeapElement*a, HeapElement*b) {
	HeapElement temp=*a;
	*a=*b;
	*b=temp;
}

void heapifyup(PriorityQueue*pq, int index) {
	int parent=(index-1)/2;
	if(index>0 && pq->elements[index].priority<pq->elements[parent].priority) {
		swap(&pq->elements[index], &pq->elements[parent]);
		heapifyup(pq, parent);
	}	
}

void heapifydown(PriorityQueue*pq,int index) {
	int left=2*index+1;
	int right=2*index+2;
	int smallest=index;
	if(left<pq->size && pq->elements[smallest].priority>pq->elements[left].priority)
		smallest=left;
	if(right<pq->size && pq->elements[smallest].priority>pq->elements[right].priority)
		smallest=right;
	if(index!=smallest){
		swap(&pq->elements[index], &pq->elements[smallest]);
		heapifydown(pq, smallest);
	}
}

void push(PriorityQueue*pq, void*data, int priority, DataType type) {
	if(pq->size==pq->capacity) {
		printf("Priority Queue is full\n");
		return;
	}
	pq->elements[pq->size].data=data;
	pq->elements[pq->size].priority=priority;
	pq->elements[pq->size].type=type;
	pq->size++;
	heapifyup(pq,pq->size-1);
}

void*pop(PriorityQueue*pq) {
	if(pq->size==0) {
		printf("Priority Queue is empty\n");
		return NULL;
	}
	void*data=pq->elements[0].data;
	pq->elements[0]=pq->elements[pq->size-1];
	pq->size--;
	heapifydown(pq,0);
	return data;
}

void*peek(PriorityQueue*pq, DataType*type) {
	if(pq->size==0) {
		printf("Priority Queue is empty\n");
		return NULL;
	}
	*type=pq->elements[0].type;
	return pq->elements[0].data;
}

int isEmpty(PriorityQueue*pq) {
	return pq->size==0;
}

void freePriorityQueue(PriorityQueue*pq) {
	free(pq->elements);
	free(pq);
}


PriorityQueue* createPriorityQueue(int capacity) {
	PriorityQueue*pq=(PriorityQueue*)malloc(sizeof(PriorityQueue));
	pq->elements=(HeapElement*)malloc(sizeof(HeapElement)*capacity);
	pq->size=0;
	pq->capacity=capacity;
	return pq;
}


int main () {
	PriorityQueue*pq=createPriorityQueue(10);
	//TEST WITH INTEGER DATA
	int data1=100;
	push(pq,&data1,3, INT);
	//TEST WITH STRING DATA
	char data2[]="task2";
	push(pq,data2,1,STRING);
	//EXAMPLE WITH DYNAMICALLY ALLOCATED DATA
	int*data3=malloc(sizeof(int));
	*data3=9;
	push(pq,data3,2,INT);
	
	//Peek and print top element with type casting 
	DataType type;
	void*topData=peek(pq,&type);
		if(topData!=NULL) { 
			if(type==INT) 
				printf("Top element: %d\n", *(int*)topData);
			else if(type==STRING) 
				printf("Top element: %s\n", (char*)topData);
			else {
				printf("Top element is a pointer\n");
			} 
		}
	free(data3);
	freePriorityQueue(pq);
	return 0;
}