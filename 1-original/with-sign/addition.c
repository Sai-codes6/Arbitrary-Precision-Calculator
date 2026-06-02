#include "apc.h" // header file inclusion

/* function to add the two operands */
int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR, char *sign1, char *sign2, char *signR, char *argv[])
{
	/* Definition goes here */
	// check for greater number
	if (strlen(argv[1]) == strlen(argv[3])) // if both the operands lengths are equal
	{
		if (strcmp(argv[1], argv[3]) < 0) // if 1st operand is less than 2nd
		{
			if (*sign1 == '+' && *sign2 == '-') // if num1 is +ve and num2 is -ve
			{
				*signR = '-'; // result sign will be -ve as (+num1) + (-num2) -> -ve  as num1 < num2
				*sign1 = '+'; // update the sign1 with +ve
				*sign2 = '+'; // update the sign2 with +ve
				// function call to subtract two lists
				subtraction(head1, tail1, head2, tail2, headR, tailR, sign1, sign2, signR, argv);
				return SUCCESS;
			}
			else if (*sign1 == '-' && *sign2 == '+') // if num2 is +ve and num1 is -ve
			{
				*signR = '+'; // result sign will be +ve as (-num1) + (+num2) -> +ve as num1 < num2
				*sign1 = '-'; // update the sign1 with -ve
				*sign2 = '-'; // update the sign2 with -ve
				// function call to subtract two lists
				subtraction(head1, tail1, head2, tail2, headR, tailR, sign1, sign2, signR, argv);
				return SUCCESS;
			}
		}
		// if num1 > num2
		else if (strcmp(argv[1], argv[3]) > 0)
		{
			if (*sign1 == '+' && *sign2 == '-') // if num1 is +ve and num2 is -ve
			{
				*signR = '+'; // result sign will be -ve as (+num1) + (-num2) -> +ve  as num1 > num2
				*sign1 = '+'; // update the sign1 with +ve
				*sign2 = '+'; // update the sign2 with +ve
				// function call to subtract two lists
				subtraction(head1, tail1, head2, tail2, headR, tailR, sign1, sign2, signR, argv);
				return SUCCESS;
			}
			else if (*sign1 == '-' && *sign2 == '+') // if num2 is +ve and num1 is -ve
			{
				*signR = '-'; // result sign will be +ve as (-num1) + (+num2) -> -ve as num1 > num2
				*sign1 = '-'; // update the sign1 with -ve
				*sign2 = '-'; // update the sign2 with -ve
				// function call to subtract two lists
				subtraction(head1, tail1, head2, tail2, headR, tailR, sign1, sign2, signR, argv);
				return SUCCESS;
			}
		}
		else // both numbers are same
		{
			if ((*sign1 == '+' && *sign2 == '-') || (*sign1 == '-' && *sign2 == '+')) // example : (+1234 + -1234)  ||  (-1234 + +1234)  will result in 0
			{
				insert_at_first(headR, tailR, 0); // when both operands are equal -> res is 0
				return SUCCESS;
			}
		}
	}
	else if (strlen(argv[1]) < strlen(argv[3])) // if length of list1 is less than length of list2
	{
		if (*sign1 == '+' && *sign2 == '-') // if num1 is +ve and num2 is -ve
			{
				*signR = '+'; // result sign will be -ve as (+num1) + (-num2) -> +ve  as num1 > num2
				*sign1 = '+'; // update the sign1 with +ve
				*sign2 = '+'; // update the sign2 with +ve
				// function call to subtract two lists
				subtraction(head1, tail1, head2, tail2, headR, tailR, sign1, sign2, signR, argv);
				return SUCCESS;
			}
			else if (*sign1 == '-' && *sign2 == '+') // if num2 is +ve and num1 is -ve
			{
				*signR = '-'; // result sign will be +ve as (-num1) + (+num2) -> -ve as num1 > num2
				*sign1 = '-'; // update the sign1 with -ve
				*sign2 = '-'; // update the sign2 with -ve
				// function call to subtract two lists
				subtraction(head1, tail1, head2, tail2, headR, tailR, sign1, sign2, signR, argv);
				return SUCCESS;
			}
	}
	else // if length of list1 is greater than length of list2
	{
		if (*sign1 == '+' && *sign2 == '-') // if num1 is +ve and num2 is -ve
			{
				*signR = '-'; // result sign will be -ve as (+num1) + (-num2) -> -ve  as num1 < num2
				*sign1 = '+'; // update the sign1 with +ve
				*sign2 = '+'; // update the sign2 with +ve
				// function call to subtract two lists
				subtraction(head1, tail1, head2, tail2, headR, tailR, sign1, sign2, signR, argv);
				return SUCCESS;
			}
			else if (*sign1 == '-' && *sign2 == '+') // if num2 is +ve and num1 is -ve
			{
				*signR = '+'; // result sign will be +ve as (-num1) + (+num2) -> +ve as num1 < num2
				*sign1 = '-'; // update the sign1 with -ve
				*sign2 = '-'; // update the sign2 with -ve
				// function call to subtract two lists
				subtraction(head1, tail1, head2, tail2, headR, tailR, sign1, sign2, signR, argv);
				return SUCCESS;
			}
	}
	if (*sign1 == '+' && *sign2 == '+') // if both the numbers are +ve
	{
		*signR = '+'; // result sign will be +ve
	}
	else if (*sign1 == '-' && *sign2 == '-') // if both the numbers are -ve
	{
		*signR = '-'; // result sign will be -ve
	}

	// variable declaration
	Dlist *temp1 = *tail1; // store tail1 and tail2 in two temporary variables
	Dlist *temp2 = *tail2;
	int sum = 0, carry = 0, rem = 0; // initialize sum, carry and rem with 0

	while (temp1 != NULL || temp2 != NULL) // traverse till temp1 or temp2 reaches null
	{
		if (temp1 != NULL && temp2 != NULL) // if both are not equal to null
		{
			sum = temp1->data + temp2->data + carry; // sum will be addition of both temps data + carry if any
			// update the temps with temp's prev so as to move towards head one node at a time
			temp1 = temp1->prev;
			temp2 = temp2->prev;
		}
		else if (temp1 != NULL && temp2 == NULL) // if list2 reaches null and list1 has nodes left
		{
			sum = temp1->data + carry; // sum will be list1's node data + carry
			temp1 = temp1->prev;	   // update the temp with temp's prev
		}
		else if (temp1 == NULL && temp2 != NULL) // if list1 reaches null and list2 has nodes left
		{
			sum = temp2->data + carry; // sum will be list2's node data + carry
			temp2 = temp2->prev;	   // update the temp with temp's prev
		}

		// when sum is greater than 9
		if (sum > 9)
		{
			rem = sum % 10;	  // calculate the remainder
			carry = 0;		  // first reset the carry
			carry = sum / 10; // calculate the carry

			// insert the remainder at head node of result list
			insert_at_first(headR, tailR, rem);
		}
		else // when sum is less than 9
		{
			// insert the sum at head node of result list
			insert_at_first(headR, tailR, sum);
			carry = 0; // reset the carry
		}
	}
	// if carray is not equal to zero
	if (carry != 0)
	{
		// insert the carry at head node of result list
		insert_at_first(headR, tailR, carry);
	}

	return SUCCESS;
}
