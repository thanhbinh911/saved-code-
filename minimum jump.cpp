#include<stdio.h>
#include<climits>
int n;
int min (int a, int b) {
	return a<b?a:b;
}

int minimum_jumps(int arr[]) {
	int dp[n+1];
	dp[n]=0;	
	for(int i=n-1; i>=0; i--) {
		dp[i]=INT_MAX;
		for(int j=i+1; j<=i+arr[i]; j++) {	
			if(j<=n && dp[j]!=INT_MAX)		
				dp[i]=min(dp[i], dp[j]+1);
		}
	}
	return dp[0];
}

int main () {
	int arr[]={4,0,1,2,0,2,1}; 
	int length=sizeof(arr)/sizeof(arr[0]);
	n=length-1;
	int minimal=minimum_jumps(arr);
	if(minimal==INT_MAX)
		printf("0");
	else
	printf("%d", minimal);
}