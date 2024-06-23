#include<stdio.h>
#include<stdlib.h>

int cmp(const void *a, const void*b ) {
	return *((int*)a)-*((int*)b);
}


int* deckRevealedIncreasing(int*deck, int deckSize, int*returnSize) {
	qsort(deck, deckSize, sizeof(deck[0]), cmp);
	int*res=(int*)malloc(sizeof(int)*deckSize);
	int*queueIndex=(int*)malloc(sizeof(int)*deckSize*2);
	*returnSize=deckSize;
	int front=0;
	int rear=0;
	for(int i=0; i<deckSize; i++) 
		queueIndex[rear++]=i;
	for(int i=0; i<deckSize; i++) {
		res[queueIndex[front]]=deck[i];
		front++;
		if(front<rear) {
			queueIndex[rear++]=queueIndex[front++];
		}
	}
	free(queueIndex);
	return res;
}


void print_deck(int*res, int returnSize) {
	for(int i=0; i<returnSize; i++)
		printf("%d ", res[i]);
}

int main () {
	int n;
	scanf("%d", &n);
	int deck[n];
	for(int i=0; i<n; i++)
		scanf("%d", &deck[i]);
	int returnSize=0;
	int*res=deckRevealedIncreasing(deck, n, &returnSize);
	print_deck(res,returnSize);
	free(res);
	return 0;
}