#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

//function to return precedence of operator;

int prec(char c) {
	if(c=='^')
		return 3;
	if(c=='*' || c=='/' )
		return 2;
	if(c=='+' || c=='-')
		return 1;
	return -1;
}

// function to return the associativity of operators;

char asso(char c) {
	if(c=='^') 
		return 'R';
	return 'L';
	//default to left-associative
}


//the main function to convert infix expression to postfix expression
void infixtopostfix(char exp[]) {
	char result[102];
	int length=strlen(exp);
	char stack[102];
	int topidx=-1;
	int resultidx=0;
	for(int i=0; i<length; i++) {
		char c=exp[i];
		if(isalpha(c) || isdigit(c))
			result[resultidx++]=c;
		else if(c=='(')
			stack[++topidx]=c;
		else if(c==')') {
			while(topidx>=0 && stack[topidx]!='(') {
				result[resultidx++]=stack[topidx--];
			}
			topidx--;
			// pop the'('	
		}
		else {
			while(topidx >=0 && (prec(c)<prec(stack[topidx]) || (prec(c)==prec(stack[topidx]) && asso(c)=='L')))
				result[resultidx++]=stack[topidx--];
			stack[++topidx]=c;
		}
	}	
		while(topidx>=0) 
				result[resultidx++]=stack[topidx--];
		result[resultidx]='\0';
		printf("%s", result);
}                      
	


int main () {
	char exp[101];
	fgets(exp, 102, stdin);
	exp[strlen(exp)-1]='\0';
	infixtopostfix(exp);
	return 0;
}

