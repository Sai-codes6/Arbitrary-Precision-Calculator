#include "apc.h"  // header file inclusion

/* function to multiply the two operands */
int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR, char *argv[])
{
	// Definition goes here 
	char *str1 = argv[1], *str2 = argv[3];    // initialize local variables
	if (*str1 == '0' || *str2 == '0')     // if either one of the list is 0 
	{
		insert_at_first(headR, tailR, 0);     // insert 0 at the head node of the result list
		return SUCCESS;
	}

	Dlist *temp1 = *tail1;    // store tail1 and tail2 in two temporary variables
	Dlist *temp2 = *tail2;

	// initialize heads and tails with null
	Dlist *headR1 = NULL;
    Dlist *tailR1 = NULL;
	Dlist *headR2 = NULL;
    Dlist *tailR2 = NULL;

	int carry, mul = 0, count = 0;   // declare carry and initialize mul and count with 0

	while (temp2 != NULL)   // traverse till temp2 reaches null
	{
		carry = 0;     // reset carry
		for (int i = 0; i < count; i++)   // lopp from 1 till count
		{
			insert_at_first(&headR1, &tailR1, 0);  // insert 0 at the head node of the result list
		}

		while (temp1 != NULL)		// traverse till temp1 reaches null
		{
			mul = (temp1->data) * (temp2->data) + carry;    // calculate mul by multiplying both temp's data and adding carry to it
			if (mul > 9)     // if mul is greater than 9
			{
				int num = mul % 10;		// store the remainder of mul % 10 in num
				carry = mul / 10;       // store the quoetient of mul / 10 in carry

				// insert num at the head node of the result list
				insert_at_first(&headR1, &tailR1, num);
			}
			else
			{
				// insert mul at the head node of the result list
				insert_at_first(&headR1, &tailR1, mul);
				carry = 0;   // reset carry
			}
			temp1 = temp1->prev;  // update the temp1 with temp's prev so as to move towards head
		}

		if (carry != 0)   // if carry is not equal to 0
		{
			insert_at_first(&headR1, &tailR1, carry);    // insert carry at the head node of the result list
		}

		// function call to add list1 and list2 and store in listR
		addition(&headR1, &tailR1, &headR2, &tailR2, headR, tailR, argv);    

		// update temp1 with tail1 and temp2 with temp2's prev
		temp1 = *tail1;      
		temp2 = temp2->prev;
		// update headR2 with headR and tailR2 with tailR
		headR2 = *headR;
		tailR2 = *tailR;
		// update headR and tailR with null
		*headR = NULL;
		*tailR = NULL;

		delete_list(&headR1, &tailR1);    // function call to delete listR1
        // update headR1 and tailR1 with null
		headR1 = NULL;
        tailR1 = NULL;
        count++;   // increment count
		delete_zero(&headR2, &tailR2);
	}

	// update headR and tailR with headR2 and tailR2 
	*headR = headR2;
	*tailR = tailR2;

	return SUCCESS;
}
