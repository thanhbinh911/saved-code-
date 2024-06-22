#include<stdio.h>
#include<stdlib.h>



void backtrack(int*result, int n, int length, int num, int k, int*returnSize) {
	if(length==n) {
		result[(*returnSize)++]=num;
		return ;
	}
	int last_digit=num%10;
	if(last_digit+k<10)
		backtrack(result,n, length+1, num*10+(last_digit+k), k, returnSize);
	if(k!=0 && last_digit-k>=0)
		backtrack(result,n, length+1, num*10+(last_digit-k), k , returnSize);
}




int*numsSameConsecDiff(int n, int k , int*returnSize) {
	int*result=(int*)malloc(sizeof(int)*10000);
	*returnSize=0;
	// the range of value the first digit can get
	// when we fix the first digit, then we can find other digit by add or subtract k
	for(int i=1; i<=9; i++)
		backtrack(result, n, 1, i, k, returnSize);
	return result;
}

int main () {
	int n,k;
	scanf("%d%d", &n,&k);
	int returnSize;
	int*result=numsSameConsecDiff(n,k ,&returnSize);
	for(int i=0; i<returnSize; i++)
		printf("%d ", result[i]);
	free(result);
	return 0;
}