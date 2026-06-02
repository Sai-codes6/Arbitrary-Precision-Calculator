#include "apc.h"   // header file inclusion

/* function to divide the two operands */
int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR, char *argv[])
{
	/* Definition goes here */
	char *str1 = argv[1], *str2 = argv[3];  // initialize local variables
	if (*str1 == '0')    // if num1 is 0
	{
		insert_at_first(headR, tailR, 0);   // insert 0 at the head node of the result list
		return SUCCESS;
	}
	if (*str2 == '0')   // error if num2 is 0
	{
		printf("Error! Divisor can't be 0\n");
		return FAILURE;
	}

	// declare local variables
	Dlist *temp1;
	Dlist *temp2;
	int list1_count, list2_count, flag1;   
	int flag = 1;
	int count = 0;

	while (flag)   // loop until flag is set
	{
		// update temp1,2 with head1,2
		temp1 = *head1;
		temp2 = *head2;
		list1_count = 0, list2_count = 0;    // reset the list's count

		// count of list1
		while (temp1 != NULL)
		{
			list1_count++;   // increment count
			temp1 = temp1->next;   // update temp with temp's next
		}
		// count of list2
		while (temp2 != NULL)
		{
			list2_count++;   // increment count
			temp2 = temp2->next;    // update temp with temp's next
		}
		if (list1_count > list2_count)     // if list1 count is greater than list2 count
		{
			subtraction(head1, tail1, head2, tail2, headR, tailR, argv);   // function call to subtract two lists
			count++;    // increment the count every time subtract func is called
			
			// function call to delete list1
			delete_list(head1, tail1);   
			// update head1 and tail1 with headR and tailR
			*head1 = *headR;
			*tail1 = *tailR;
			// update headR and tailR with null
			*headR = NULL;
			*tailR = NULL;
		}
		else if (list1_count == list2_count)   // if list1 count is equal than list2 count
		{
			// update temp1,2 with head1,2
			temp1 = *head1;
			temp2 = *head2;
			flag1 = 0;    // initialize flag1 with 0
			while (temp1 != NULL && temp2 != NULL)   // traverse till temp1 and temp2 reaches null
			{
				if (temp1->data >= temp2->data)    // if temp1's data is greater than or equal to temp2's data
				{
					flag1 = 1;   // set the flag1
					break;   // exit the loop
				}
				else if (temp1->data < temp2->data)    // if temp1's data is less than to temp2's data
				{
					flag = 0;   // reset flag
				}
				else if (temp1->data == temp2->data)   // if temp1's data is equal to temp2's data
				{
					// update the temps with temp's next so as to move towards tail one node at a time
					temp1 = temp1->next;
					temp2 = temp2->next;
				}
			}

			if (flag1)   // if flag1 is set
			{
				subtraction(head1, tail1, head2, tail2, headR, tailR, argv);  // function call to subtract two lists
				count++;		// increment the count every time subtract func is called
				
				// function call to delete list1
				delete_list(head1, tail1);
				// update head1 and tail1 with headR and tailR
				*head1 = *headR;
				*tail1 = *tailR;
				// update headR and tailR with null
				*headR = NULL;
				*tailR = NULL;
			}
		}
		else
		{
			flag = 0;
			// return FAILURE;
		}
	}
	// function call to delete any zero digit stored at the head nodes of list1,2
	delete_zero(head1, tail1);
	delete_zero(head2, tail2);
	
	insert_at_first(headR, tailR, count);   // function call to insert the count at the head node of the result list
	return SUCCESS;
}