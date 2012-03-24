/**
*  Calculator Program that adds and subtracts two really large numbers.
*/ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {	
    struct node *next;
    struct node *prev;
    int data;
};

/**
* Checks if the user's input is numerical. 
* Returns 1 if user's input is numerical, 0 otherwise. 
**/
int check_input(char *input)
{
    int i;
    for(i = 0; i < strlen(input); i++){
        if (input[i] < '0'||input[i] > '9')
            return 0;
    }

    return 1;
}


/**
* Returns the list size of a list. 
*/
int listSize(struct node *ptr) {
    int size = 0;

    while(ptr != NULL) {
        size++;
        ptr = ptr->prev;
    } 

    return size;
}

/**
* Compares all the elements in the two lists to see which one is larger. 
* Returns 1 is *f is larger, returns 2 if *s is larger, returns 0 if they are the same. 
*/ 
int compare(struct node *f,struct node *s) {
    while(f->prev!=NULL){
        f = f->prev;
        s = s->prev;
    }
    while(f!=NULL)
    {
        if(f->data > s->data){
            return 1;
        }
        else if(f->data < s->data){
            return 2;
        }
        else{
            f = f->next;
            s = s->next;
        }
    }

    return 0;
}

/**
* Prints the resulting list after calculation. 
*/
void printList(struct node *ptr) {
    while(ptr!=NULL) {
        printf("%d", ptr->data);
        ptr = ptr->prev;
    }

    printf("\n");
}

/**
* Creates a linked list. 
**/
void create_list(struct node **ptr,char *input) {
    int i;
    struct node *temp;

    for(i = 0; i < strlen(input); i++){
        if(i == 0) {
            (*ptr) = malloc(sizeof(struct node));
            (*ptr)->data = input[i]-'0';
            (*ptr)->next = NULL;
            (*ptr)->prev = NULL;
        }
        else {
            temp = malloc(sizeof(struct node));
            temp->data = input[i]-'0';
            temp->next = NULL;
            temp->prev = *ptr;
            (*ptr)->next = temp;
            *ptr = temp;
        }
    }
}

/**
* Adds two long numbers. 
**/ 
void add(struct node *first, struct node *second) {

    int sum = 0;	
    struct node *addition;
    int firstN;
    int secondN;
    int carry = 0;
    char s3[50] = "";
    char temp[2];

    while ((first != NULL && second != NULL)) {

        firstN = first->data;
        secondN = second->data;

        if ((firstN+secondN+carry) > 9) {
            sum = (firstN+secondN+carry)%10;
            carry = 1;
        }

        else {
            sum = firstN + secondN+carry;
            carry = 0;
        }	

        sprintf(temp, "%d", sum);		
        strcat(s3,temp);


        first = first->prev;
        second = second->prev;
        sum = 0; 
    }

    while(first!=NULL) {

        firstN = first->data;
        if ((firstN+carry) > 9) {
            sum = (firstN+carry)%10;
            carry = 1;
        }

        else {
            sum = firstN +carry;
            carry = 0;
        }	

        sprintf(temp, "%d", sum);		
        strcat(s3,temp);
        first = first->prev;

    }

    while(second!= NULL) {

        secondN = second->data;
        if ((secondN+carry) > 9) {
            sum = (secondN+carry)%10;
            carry = 1;
        }

        else {
            sum = secondN +carry;
            carry = 0;
        }	

        sprintf(temp, "%d", sum);		
        strcat(s3,temp);

        second = second->prev;
    }	

    if(carry == 1) {
        sprintf(temp, "%d", 1);		
        strcat(s3,temp);
    }
    create_list(&addition, s3);
    printList(addition);

}

/**
* Subtracts two large numbers. 
*/ 
char* doSubtract(struct node *first, struct node *second) {

    int borrow;
    int difference;
    char temp[2];
    char s3[50] = "";
    char s4[50] ="";
    int firstN;
    int secondN;
    unsigned long i;

    borrow = 0;
    while (second != NULL) {
        firstN = first->data;
        secondN = second->data;

        if(firstN==0){
            difference = 10 - borrow - secondN;
            borrow = 1;
        }
        else if(firstN-borrow < secondN) {
            difference = firstN - borrow + 10 - secondN;
            borrow = 1;
        }
        else {
            difference = firstN - borrow - secondN;
            borrow = 0;
        }

        sprintf(temp, "%d", difference);
        strcat(s3, temp);

        first = first->prev;
        second = second->prev;
    }


    while(first!=NULL) {
        firstN = first->data;
        if(firstN==0){
            difference = 10 - borrow;
            borrow = 1;
        }
        else{
            difference = firstN - borrow;
            borrow = 0;
        }
        sprintf(temp, "%d", difference);		
        strcat(s4,temp);
        first = first->prev;

    }

    for(i = strlen(s4) -1; i >= 0; i--) {
        if(s4[i] != '0'){
            break;
        }

    }

    if(i != 0){
        strncat(s3,s4,i+1);
    }
    else if(s4[0]!='0'){
        strncat(s3,s4,1);
    }
    return s3;
}

/**
* Evaluates and processes the first and second lists.  
**/ 
void subtract(struct node *first, struct node *second) {

    char *s3;
    int flag =0;
    struct node *subtract;

    /* If the first list is larger than the second */ 
    if(listSize(first) > listSize(second)){
        s3 = doSubtract(first,second);
    }

    else if(listSize(first) < listSize(second)){
        s3 = doSubtract(second,first);
        flag = 1;
    }

    else{
        /* If each element in both lists are the same */ 
        if(compare(first, second) == 0) {
            strcat(s3, "0");
        }     

        else if(compare(first,second) == 1) {
            s3 = doSubtract(first,second);
        }
        else{
            s3 = doSubtract(second,first);
            flag = 1;
        }
    }
    printf("%lu",strlen(s3));
    create_list(&subtract, s3);

    if(flag == 1)
    {
        printf("-");
    }

    printList(subtract);
}  

/**
* Creates a main method to handle user input. 
*/
int main (void) {	
    char command[300];
    char command2[300];	
    char command3[100];

    struct node *first = NULL;	
    struct node *second = NULL;

    printf("Welcome to the two function calculator program!\n");

    while (1) {				
        printf("Enter a command or a number: ");
        fgets(command, sizeof(command), stdin);
        command[strlen(command) - 1] = '\0';

        if (check_input(command) == 1) {		
            printf("Enter a second number or a command: ");
            fgets(command2, sizeof(command2), stdin);
            command2[strlen(command2) -1] = '\0';
            create_list(&first,command);

            if (check_input(command2) == 1) {
                printf("Enter a command: ");
                fgets(command3, sizeof(command3), stdin);
                command3[strlen(command3) - 1] = '\0';
                create_list(&second, command2);	

                /* List of commands for command #3 */ 
                if (strcmp(command3, "+") == 0) {
                    printf("The sum is: ");
                    add(first, second);
                }

                else if(strcmp(command3, "-") == 0) {
                    printf("The difference is: ");
                    subtract(first, second);
                }
                else {
                    printf("Error: Please enter an operator after entering two numbers.\n");
                    printf("Refer to the help documentation by entering 'help'. \n");
                }
            }			
             /* List of commands for command #2 */ 
            else if (strcasecmp(command2, "help") == 0) {
                printf("\n");
                printf("This is a calculator that can add, subtract, divide and multiply very large numbers.\n");
                printf("You can enter the following things: \n");
                printf("number: By entering a number, you can enter another number and then specify an operator.\n");
                printf("The list of operators are: +, -, x, //\n");
                printf("Separators: Enables the comma spacing in numbers.\n");
                printf("quit: Quits the program.\n");
                printf("\n");
            }

            else if (strcasecmp(command2, "quit") == 0) {
                break;
            }

            else {
                printf("Command not recognized.\n");
            }					 
        }	 					 

        else {
            /* List of commands for command #1 */ 
            if (strcasecmp(command, "help") == 0) {
                printf("\n");
                printf("This is a calculator that can add, subtract, divide and multiply very large numbers.\n");
                printf("You can enter the following things: \n");
                printf("number: By entering a number, you can enter another number and then specify an operator.\n");
                printf("The list of operators are: +, -, x, //\n");
                printf("Separators: Enables the comma spacing in numbers.\n");
                printf("quit: Quits the program.\n");
                printf("\n");
            }

            else if (strcasecmp(command, "quit") == 0) {
                break;
            }

            else {
                printf("Command not recognized.\n");
            }
        }

    }
    return 0;		
} /* End main */ 