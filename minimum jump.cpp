#include<stdio.h>

int max(int a, int b) {
	return a>b?a:b;
}

int minimum_jumps(int arr[], int n) {
	if(n<=1)
		return 0;
	if(arr[0]==0)
		return -1;
	if(arr[0]>=n-1)
		return 1;
	int max_reach=arr[0];
	int jumps=1;
	int step=arr[0];
	for(int i=1; i<n; i++) {
		if(i==n-1)
			return jumps;
		if(arr[i]>=n-i)
			return jumps+1;
		max_reach=max(max_reach, i+arr[i]);
		step--;
		if(step==0) {
			jumps++;
		if(i>=max_reach)
			return -1;
		step=max_reach-i;		
		}
	}
	return -1;
}

int main () {
	int arr[]={3,4,1,3,1,0,1,1};
	int size=sizeof(arr)/sizeof(arr[0]);
	printf("%d", minimum_jumps(arr,size));
}