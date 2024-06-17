//#include<stdio.h>
//#include<string.h>
//#include<ctype.h>
//
//
//
//int decode_ways(char* str,int length, int dp[]) {
//	if(length==0 || str[0]=='0')
//		return 0;
//	else 
//		dp[0]=1;
//	for(int i=1; i<length; i++) {
//		if(str[i]=='0' && str[i-1]=='0')
//			return 0;
//		else {
//			if(str[i-1]=='0')
//			dp[i]=dp[i-1];
//			else if (str[i]=='0') {
//				if(str[i-1]>'2')
//					return 0;
//				else {
//					if(i==1)
//						dp[1]=1;
//					else 
//					dp[i]=dp[i-2];
//			}
//		}
//			else {
//				if((str[i-1] =='2' && str[i]<='6')|| str[i-1]=='1') {
//					if(i==1)
//						dp[1]=2;
//					else
//						dp[i]=dp[i-1]+dp[i-2];
//					}
//				else
//					dp[i]=dp[i-1];
//			}
//		}
//	}
//	return dp[length-1];
//}

//int main () {
//	char str[101];
//	scanf("%s", str);
//	int length=strlen(str);
//	int dp[length];
//	int nums=decode_ways(str, length, dp);
//	printf("%d", nums);
//}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int numDecodings(char* s) {
    int n = strlen(s);
    if (n == 0 || s[0] == '0') {
        return 0;
    }

    int *dp = (int *)malloc((n + 1) * sizeof(int));
    // there is only one way to decode an empty string
    dp[0] = 1;
    // base case: string with 1 digit
    // we already handle in advance the case in which the first digit =0
    // -> so there is only one way to decode a single character if it's not '0'
    dp[1] = 1;

    for (int i = 2; i <= n; i++) {
    	//at the beginning, initialize at each i dp[i]=0 to handle the case that if str[i]='0'
        dp[i] = 0;
        // Check if single digit decode is possible
        //note: with single digit decode(at cur idx): the nums of way that we can decodes at cur idx depends on the nums of way at the idx before
	  
        if (s[i - 1] >= '1' && s[i - 1] <= '9') {
            dp[i] += dp[i - 1];
        }
        // Check if two digit decode is possible
        if (s[i - 2] == '1' || (s[i - 2] == '2' && s[i - 1] <= '6')) {
            dp[i] += dp[i - 2];
        }
    }
    int result = dp[n];
    free(dp);
    return result;
}

int main() {
    char s[101];
    scanf("%s", s);
    printf("Number of ways to decode: %d\n", numDecodings(s));
    return 0;
}