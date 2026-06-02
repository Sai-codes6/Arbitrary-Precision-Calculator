/*----------------------------------------------------------
Name : Deepika
Date : 30/07/25
Description : Arbitrary preecision calculator
----------------------------------------------------------*/

#include "apc.h"    // header file inclusion

int main(int argc, char *argv[])
{
	/* Declare the pointers */
	// init 3 head and tail pointers to null
	Dlist *head1 = NULL, *tail1 = NULL;
	Dlist *head2 = NULL, *tail2 = NULL;
	Dlist *headR = NULL, *tailR = NULL;

	char opr = argv[2][0];     // store the operator
	/* call the function to add the digits to the list */
	if (digit_to_list(&head1, &tail1, &head2, &tail2, argv) == FAILURE)
	{
		return FAILURE;
	}

	switch (opr)
	{
		case '+':
			/* call the function to perform the addition operation */
			if (addition(&head1, &tail1, &head2, &tail2, &headR, &tailR, argv) == SUCCESS)
			{
				printf("Addition Result = ");
				print_list(headR);     // function call to print the result
				printf("\n");
			}
			break;
		case '-':
			/* call the function to perform the subtraction operation */
			printf("Subtraction Result = ");
			if (subtraction(&head1, &tail1, &head2, &tail2, &headR, &tailR, argv) == SUCCESS)
			{
				print_list(headR);    // function call to print the result
				printf("\n");
			}
			break;
		case 'x':
		    /* call the function to perform the multiplication operation */
			if (multiplication(&head1, &tail1, &head2, &tail2, &headR, &tailR, argv) == SUCCESS)
			{
				printf("Multiplication Result = ");
				print_list(headR);    // function call to print the result
				printf("\n");
			}
			break;
		case '/':
			/* call the function to perform the division operation */
			if (division(&head1, &tail1, &head2, &tail2, &headR, &tailR, argv) == SUCCESS)
			{
				printf("Division Result = ");
				print_list(headR);      // function call to print the result
				printf("\n");
			}
			break;
		default:
			printf("Invalid Input :-( Try again...\n");
	}
	return SUCCESS;
}
