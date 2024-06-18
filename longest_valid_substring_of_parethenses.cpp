#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int longestValidParentheses(char*s) {
	int size=strlen(s);
	int max=0;
	int*stack=(int*)malloc(sizeof(int)*(size+1));
	// point to the idx of top element in stack,
	// initialize =-1 as stack is empty
	// initialize the top element=-1 help deal with cases that the the valid substring of
	//parentheses start right from the beginning of the string
	int top=0;
	stack[top]=-1;
	for(int i=0; i<size; i++) {
		if(s[i]=='(')
			stack[++top]=i;
		else {
			top--;
			//there is no corresponding unmatched open bracket for cur closed bracket <=> the stack is empty
			// then we set the cur idx to the top of stack to set the base idx for upcoming valid substring of parentheses.
			if(top==-1)
				stack[++top]=i;
			else {
				int length=i-stack[top];
				if(length>max)
					max=length;	
			}
		}
	}
	free(stack);
	return max;
}


int main () {
	char str[30001];
	scanf("%s", str);
	int max_length=longestValidParentheses(str);
	printf("%d", max_length);
}