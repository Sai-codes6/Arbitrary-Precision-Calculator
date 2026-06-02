/*----------------------------------------------------------
Name : Deepika
Date : 30/07/25
Description : Arbitrary Precision Calculator
----------------------------------------------------------*/

#include "bignum.h" // engine header inclusion

int main(int argc, char *argv[])
{
	/* the calculator expects exactly: <num1> <operator> <num2> */
	if (argc != 4)
	{
		printf("Usage: %s <number1> <operator + - x /> <number2>\n", argv[0]);
		printf("Example: %s 12345678901234567890 x 98765 \n", argv[0]);
		return FAILURE;
	}

	/* Declare the pointers and signs */
	char sign1 = '+', sign2 = '+', signR = '+';
	// init 3 head and tail pointers to NULL
	Dlist *head1 = NULL, *tail1 = NULL;
	Dlist *head2 = NULL, *tail2 = NULL;
	Dlist *headR = NULL, *tailR = NULL;

	char opr = argv[2][0]; // store the operator

	/* load both operands into their digit lists and capture the signs */
	if (digit_to_list(&head1, &tail1, &head2, &tail2, &sign1, &sign2, argv) == FAILURE)
	{
		delete_list(&head1, &tail1);
		delete_list(&head2, &tail2);
		return FAILURE;
	}

	switch (opr)
	{
	case '+':
		/* perform the addition operation */
		if (addition(&head1, &tail1, &head2, &tail2, &headR, &tailR,
					 &sign1, &sign2, &signR, argv) == SUCCESS)
		{
			printf("Addition Result = ");
			print_list(headR, signR);
			printf("\n");
		}
		break;

	case '-':
		/* perform the subtraction operation */
		if (subtraction(&head1, &tail1, &head2, &tail2, &headR, &tailR,
						&sign1, &sign2, &signR, argv) == SUCCESS)
		{
			printf("Subtraction Result = ");
			print_list(headR, signR);
			printf("\n");
		}
		break;

	case 'x':
		/* perform the multiplication operation */
		if (multiplication(&head1, &tail1, &head2, &tail2, &headR, &tailR,
						   &sign1, &sign2, &signR, argv) == SUCCESS)
		{
			printf("Multiplication Result = ");
			print_list(headR, signR);
			printf("\n");
		}
		break;

	case '/':
		/* perform the division operation */
		if (division(&head1, &tail1, &head2, &tail2, &headR, &tailR,
					 &sign1, &sign2, &signR, argv) == SUCCESS)
		{
			printf("Division Result = ");
			print_list(headR, signR);
			printf("\n");
		}
		break;

	default:
		printf("Invalid Input :-( Try again...\n");
	}

	/* release every list before exiting so no memory is leaked */
	delete_list(&head1, &tail1);
	delete_list(&head2, &tail2);
	delete_list(&headR, &tailR);

	return SUCCESS;
}
