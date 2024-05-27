#include<stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

typedef struct {
	int data[MAX_SIZE];
	int size;
}maxHeap;

void swap(int*x, int*y) {
	int temp=*x;
	*x=*y;
	*y=temp;
}

void heapifyUp (maxHeap*heap, int index) {
	int parent=(index-1)/2;
	while(index>0 && heap->data[index]>heap->data[parent]) {
		swap(&heap->data[index], &heap->data[parent]);
		heapifyUp(heap,parent);
	}
}
/* inserting a new element into a heap involves adding the element ar the end of the tree
(or array) to maintain the complete binary tree property and then performing a heapify-up
operation to restore the heap property
	step1: add the new element at the end of array
	step2: perform heapify-up to maintain the heap property
*/
void insert(maxHeap*heap, int value) {
	if(heap->size>=MAX_SIZE) {
		printf("heap overflow\n");
		return ;
	}
	heap->data[heap->size++]=value;
	heapifyUp(heap, heap->size-1);
}

/*REMOVE(extract) 
step1: replace the root with the last element in the array
step2: reducethe size of the heap
step3: perform heapify-down to maintain the heap property
*/

void heapifyDown(maxHeap*heap, int index) {
		int largest=index;
		int left=2*index+1;
		int right=2*index+2;
		if(left<heap->size && heap->data[left]>heap->data[largest])
			largest=left;
		if(right<heap->size && heap->data[right]>heap->data[largest])
			largest=right;
//(only swap the element at cur idx if the largest element among it, its left child and right child != cur_idx)
		if(largest!=index) {
			swap(&heap->data[index], &heap->data[largest]);
			heapifyDown(heap, largest);
		}
}


// function to remove the root element from the heap
int removeRoot(maxHeap*heap) {
	if(heap->size==0) {
		printf("Heap is empty\n");
		return -1;
	}
	int root=heap->data[0];
	//replace the root with the last element in the array
	heap->data[0]=heap->data[heap->size-1];
	// reduce the size of the heap
	heap->size--;
	heapifyDown(heap, 0);
	return root;
}

// Peek(Get Top) : accessing the root_element(maximum) without removing it(O(1)<- since we directly access the first ele of the array)
int peek(maxHeap*heap) {
	if(heap->size==0) {
		printf("Heap is empty\n");
		return -1;
	}
	return heap->data[0];
}

// Heapify : the process of converting a binary tree into a heap(can be done either by heapifyng up or down)
void buildHeap(maxHeap*heap) {
	for(int i=(heap->size)/2-1; i>=0; i--) {
		heapifyDown(heap, i);
	}
}

//Building a heap: involve converting an arbitrary array into a heap
// by performing heapy-fy down operation from the last non-leaf node(internal node) to the root

void buildHeapFromArray(maxHeap*heap, int*array, int size) {
	if(size>MAX_SIZE) {
		printf("Array size exceeds maximum heap size\n");
		return;
	}
	for(int i=0; i<size; i++) {
		heap->data[i]=array[i];
	}
	heap->size=size;
	buildHeap(heap);
}

void printHeap(maxHeap*heap) {
	for(int i=0; i<heap->size; i++) 
		printf("%d ", heap->data[i]);
	printf("\n");
}

int main () {
	maxHeap heap;
	heap.size=0;
	
	
	insert(&heap, 30);
    insert(&heap, 20);
    insert(&heap, 15);
    insert(&heap, 10);
	insert(&heap, 40);
    insert(&heap, 8);
    insert(&heap, 5);
    
	printf("Heap after insertion: \n");
    printHeap(&heap);
    
	int root=removeRoot(&heap);
    printf("%d Removed root: %d\n");
    
	printf("Heap after removal:\n");
    printHeap(&heap);
    
	int array[] = {10, 20, 15, 30, 40, 50, 60};
    buildHeapFromArray(&heap, array, 7);

    printf("Heap built from array:\n");
    printHeap(&heap); 
	
	return 0;   
}
 