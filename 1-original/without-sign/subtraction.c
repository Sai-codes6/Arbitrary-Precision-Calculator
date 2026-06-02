#include "apc.h"  // header file inclusion

/* function to subtract the two operands */
int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR, char *argv[])
{
	/* Definition goes here */
	int flag = 0;
	// check for greater number
	if (strlen(argv[1]) == strlen(argv[3]))   // if both the operands lengths are equal
	{
		if (strcmp(argv[1], argv[3]) < 0)    // if 1st operand is less than 2nd
		{
			swap_list(head1, tail1, head2, tail2);    // swap the two list addresses
			flag = 1;
		}
	}
	else if (strlen(argv[1]) < strlen(argv[3]))    // if list1 is less than list2
	{
		swap_list(head1, tail1, head2, tail2);     // swap the two list addresses
		flag = 1;
	}
	
	// initialize strcture ptr's
	Dlist *temp1 = *tail1;   // store tail1 and tail2 in two temporary variables
	Dlist *temp2 = *tail2;
	int n1, n2, borrow = 0;  // initialize borrow with 0 and dec two local variables n1, n2

	while (temp1 != NULL)    // traverse till temp1 reaches null
	{
		if (temp2 != NULL)    // if temp2 is not null
		{
			if (borrow == 1)   // if borrow is set
			{
				n1 = (temp1->data) - 1;   // update n1 value with temp1's data - 1
 			}
			else
			{
				n1 = temp1->data;   // if borrow is reset update n1 value with temp1's data
			}
			// n1 = (borrow == 1) ? ((temp1->data) - 1) : (temp1->data);     // initialize n1 value depending on borrow
			n2 = temp2->data;     // init n2 value with temp2 data
			if (update(n1, n2, headR, tailR, &borrow) == SUCCESS)    // check whether updating the result list is a success
			{
				// update the temps with temp's prev so as to move towards head one node at a time
				temp1 = temp1->prev;   
				temp2 = temp2->prev;
			}
			else
			{
				return FAILURE;   // return failure if update function fails
			}
		}
		else   // if temp2 is null
		{
			if (borrow == 1)    // if borrow is set
			{
				n1 = (temp1->data) - 1;   // update n1 value with temp1's data - 1
 			}
			else
			{
				n1 = temp1->data;    // if borrow is reset update n1 value with temp1's data
			}
			// n1 = (borrow == 1) ? ((temp1->data) - 1) : (temp1->data);   // initialize n1 value depending on borrow
			n2 = 0;     // init n2 with 0

			if (update(n1, n2, headR, tailR, &borrow) == SUCCESS)   // check whether updating the result list is a success
			{
				// update the temp1 with temp's prev so as to move towards head 
				temp1 = temp1->prev;
			}
			else
			{
				return FAILURE;   // return failure if update function fails
			}
		}
	}

	// delete any zero digit stored in left hand side of a number  -> 05 to 5
	delete_zero(headR, tailR);  
	if (flag)   // if swap is performed then result will be -ve
	{
		printf("-");
	}
	return SUCCESS;
}

/* func to swap the lists */
void swap_list(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2)
{
	// swap the addresses of the two lists
    Dlist *temp = *head1;    // store head1 in a temp var
    *head1 = *head2;       	// update temp1 with temp2 address
    *head2 = temp;			// update temp2 with temp

    temp = *tail1;        // store tail1 in a temp var
    *tail1 = *tail2; 	  // update tail1 with tail2 addr
    *tail2 = temp;		  // update tail2 with temp
}

/* function to update the result list */
int update(int num1, int num2, Dlist **headR, Dlist **tailR, int *borrow)
{
    int res;   // declare local variable
    if (num1 < num2)     // if num1 is less than num2
    {
        *borrow = 1;    // set the borrow
        num1 += 10;    // add 10 to num1
        res = num1 - num2;   // update the res with num1 - num2

		// insert the res at the head node of result list
        insert_at_first(headR, tailR, res);
    }
    else   // if num1 is greater than or equal to num2
    {
        *borrow = 0;   // reset the borrow
        res = num1 - num2;   // update the res with num1 - num2

		// insert the res at the head node of result list
        insert_at_first(headR, tailR, res);
    }
    return SUCCESS;
}