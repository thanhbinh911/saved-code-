#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

// node structure for a term in the polynomial
typedef struct node{
	int coeff;
	int expo;
	struct node* next;
}node;

//polynomial structure
typedef struct poly {
	int id;
	node* head;
}poly;

poly polynomials[1000]={0};
//function to create a new term in the polynomial

node*create_node(int coeff, int expo) {
	node*newnode=(node*)malloc(sizeof(node));
	//if statement to check if we allocate memory successfully or not
	if(newnode) {
		newnode->coeff=coeff;
		newnode->expo=expo;
		newnode->next=NULL;
	}
	return newnode;
}

poly* Create(int poly_id) {
	if(polynomials[poly_id].id==0) {
		polynomials[poly_id].id=poly_id;
		polynomials[poly_id].head=NULL;
	}
	return &polynomials[poly_id];
}
//utility functiont to add a term to the polynomial
void AddTerm(poly*po, int coeff, int expo) {
	node*newnode=create_node(coeff, expo);
	if(po->head==NULL)
		po->head=newnode;
	else {
		node*current=po->head;
		node*prev=NULL;
		while(current!=NULL &&current->expo>expo) {
			prev=current;
			current=current->next;
		}
		if(current!=NULL && current->expo==expo) {
			current->coeff+=coeff;
			free(newnode);	
		}
		else {
			if(prev!=NULL) 
				prev->next=newnode;
			else
				po->head=newnode;
			newnode->next=current;
		}
	}
}

//function to evaluate the  polynomial 

int EvaluatePoly(poly*po, int variable_value) {
	int result=0;
	node*current=po->head;
	while(current!=NULL) {
		result+=current->coeff*(int)pow(variable_value,current->expo);
		current=current->next;
	}
	return result;
}

void printPolyToBuffer(poly po, char* buffer) {
    node*current = po.head;
    while (current != NULL) {
        sprintf(buffer + strlen(buffer), "%d %d ", current->coeff, current->expo);
        current = current->next;
        }
	sprintf(buffer + strlen(buffer), "\n");
    }

void Destroy(poly*po) {
	node*current=po->head;
	while(current!=NULL) {
		node*temp=current;
		current=current->next;
		free(temp);
	}
	po->head=NULL;
}

poly*AddPoly(poly po1, poly po2,int poly_id) {
	Create(poly_id);
	node*ptr1=po1.head;
	node*ptr2=po2.head; 
	while(ptr1 !=NULL || ptr2 != NULL ) {
		int coeff=0, expo=0;
// this part is to check if both ptr1 and ptr2 still point to valid term in the polynomial 
// then we have 3 cases in which we compare the exponent of term;
		if(ptr1!=NULL && ptr2!=NULL) {
		if(ptr1->expo>ptr2->expo) {
			expo=ptr1->expo;
			coeff=ptr1->coeff;
			ptr1=ptr1->next;
		}
		else if (ptr1->expo<ptr2->expo) {
			expo=ptr2->expo;
			coeff=ptr2->coeff;
			ptr2=ptr2->next;
		}
		else {
			expo=ptr1->expo;
			coeff=ptr1->coeff+ptr2->coeff;
			ptr1=ptr1->next;
			ptr2=ptr2->next;
			}
		}
		else if(ptr1!=NULL) {
			coeff=ptr1->coeff;
			expo=ptr1->expo;
			ptr1=ptr1->next;
		}
		else if(ptr2!=NULL) {
			coeff=ptr2->coeff;
			expo=ptr2->expo;
			ptr2=ptr2->next;
		}
		AddTerm(&polynomials[poly_id],coeff,expo);
	}
	return &polynomials[poly_id];
}

int main () {
	char command[15];
	int id,coeff,expo;
	char outputBuffer[1000];
	outputBuffer[0]='\0';
	while(1) 	{
		scanf("%s", command);
		if(strcmp(command, "*")==0)
			break;
		else if(strcmp(command,"Create")==0) {
			scanf("%d", &id);
			Create(id);
		}
		else if(strcmp(command,"AddTerm")==0) {
			scanf("%d %d %d", &id, &coeff, &expo );
			poly*po=Create(id);
			AddTerm(po,coeff,expo);
		}
		else if(strcmp(command, "PrintPoly")==0) {
			scanf("%d", &id);
			if(id!=0) {
				printPolyToBuffer(polynomials[id], outputBuffer);
			}
		}
		else if(strcmp(command, "EvaluatePoly")==0) {
			int variable_value;
			scanf("%d %d",&id, &variable_value);
			int result=EvaluatePoly(&polynomials[id],variable_value);
			char str[20];
			sprintf(str,"%d", result);
			sprintf(outputBuffer + strlen(outputBuffer), "%s", str);
			sprintf(outputBuffer + strlen(outputBuffer), "\n");
			}	
		else if(strcmp(command, "AddPoly")==0) {
			int id1;
			int id2;
			int id_result;
			scanf("%d %d %d", &id1, &id2, &id_result);
			AddPoly(polynomials[id1], polynomials[id2], id_result);
		}
		else if(strcmp(command, "Destroy")==0) {
			scanf("%d", &id);
			Destroy(&polynomials[id]);
		}
	}
	printf("%s", outputBuffer);
}