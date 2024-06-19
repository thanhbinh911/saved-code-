#include<stdio.h>
#include<climits>
#define MAX 100


int max(int a, int b) {
	return a>b?a:b;
}


int max_sum(int val[], int wt[], int w, int n) {
	int prev[w+1];
	for(int i=0; i<=w; i++)
		prev[i]= ((int)(i/wt[0]))*val[0];	   
	for(int i=1; i<n; i++) {
		for(int j=0; j<=w; j++) {
			int not_take= prev[j];
			int take=INT_MIN;
			if(wt[i]<=j)
			take=val[i]+prev[j-wt[i]];
			prev[j]=max(not_take,take);			
		}
	}	       
	return prev[w];
}

int main () {
	int W=100;
	int val[]={1,30};
	int wt[]={1,50};
	int n=sizeof(val)/sizeof(val[0]);
	int max=max_sum(val,wt,W,n);
	printf("%d", max);
}