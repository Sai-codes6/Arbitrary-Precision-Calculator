#include "bignum.h" // engine header inclusion

/*============================================================
  LIST CONSTRUCTION / TEARDOWN
============================================================*/

/* function to insert the value at the last (least significant) end of the list */
int insert_at_last(Dlist **head, Dlist **tail, int value)
{
	// allocate memory for the new node
	Dlist *new = malloc(sizeof(Dlist));
	if (new == NULL)
	{
		return FAILURE; // malloc failed
	}
	// update new node's data, prev and next
	new->data = value;
	new->prev = NULL;
	new->next = NULL;

	// if list is empty, the new node becomes both head and tail
	if (*head == NULL)
	{
		*head = new;
		*tail = new;
		return SUCCESS;
	}

	new->prev = *tail;   // new node points back to the old tail
	(*tail)->next = new; // old tail points forward to the new node
	*tail = new;         // tail now refers to the new node
	return SUCCESS;
}

/* function to insert the value at the first (most significant) end of the list */
int insert_at_first(Dlist **head, Dlist **tail, int value)
{
	Dlist *new = malloc(sizeof(Dlist)); // allocate memory for the new node
	if (new == NULL)
	{
		return FAILURE; // malloc failed
	}
	// update new node's data, prev and next
	new->data = value;
	new->prev = NULL;
	new->next = NULL;

	// if list is empty, the new node becomes both head and tail
	if (*head == NULL)
	{
		*head = new;
		*tail = new;
		return SUCCESS;
	}

	new->next = *head;   // new node points forward to the old head
	(*head)->prev = new; // old head points back to the new node
	*head = new;         // head now refers to the new node
	return SUCCESS;
}

/* function to deep copy a list so the original can be consumed safely */
int copy_list(Dlist *src_head, Dlist **dst_head, Dlist **dst_tail)
{
	*dst_head = NULL;
	*dst_tail = NULL;

	Dlist *temp = src_head; // walk the source from head to tail
	while (temp != NULL)
	{
		// append each digit at the tail so order is preserved
		if (insert_at_last(dst_head, dst_tail, temp->data) == FAILURE)
		{
			delete_list(dst_head, dst_tail); // roll back on allocation failure
			return FAILURE;
		}
		temp = temp->next;
	}
	return SUCCESS;
}

/* function to delete the whole list */
int delete_list(Dlist **head, Dlist **tail)
{
	Dlist *temp = *head; // start at the head
	while (temp != NULL)
	{
		Dlist *temp2 = temp->next; // remember the next node first
		free(temp);                // free the current node
		temp = temp2;              // advance to the remembered node
	}
	// reset head and tail to NULL so the list is genuinely empty
	*head = NULL;
	*tail = NULL;

	return SUCCESS;
}

/* function to delete the first (head) node */
int delete_first(Dlist **head, Dlist **tail)
{
	if (*head == NULL)
	{
		return FAILURE; // nothing to delete
	}

	if (*head == *tail) // only one node in the list
	{
		free(*head);
		*head = NULL;
		*tail = NULL;
		return SUCCESS;
	}

	Dlist *temp = *head;   // remember the head
	*head = (*head)->next; // move head forward
	(*head)->prev = NULL;  // detach the new head's back pointer
	free(temp);            // free the old head
	return SUCCESS;
}

/* function to strip EVERY redundant leading zero, always leaving one digit */
void delete_zero(Dlist **head, Dlist **tail)
{
	// keep removing a leading zero as long as there is more than one node left
	while ((*head) != NULL && (*head)->data == 0 && (*head) != (*tail))
	{
		delete_first(head, tail);
	}
}

/* function to print the list: print a '-' only for a negative result, then every digit */
int print_list(Dlist *head, char signR)
{
	if (head == NULL)
	{
		printf("INFO:List is empty");
		return FAILURE;
	}

	if (signR == '-')
	{
		printf("-"); // sign is printed once, ahead of the digits
	}
	while (head != NULL) // traverse head -> tail (most significant first)
	{
		printf("%d", head->data);
		head = head->next;
	}
	return SUCCESS;
}

/*============================================================
  INPUT PARSING
============================================================*/

/* function to read a single optional leading sign from one operand string.
 * I advance the index past the sign so the digit loop never sees it, and I
 * default an absent sign to '+'. Each operand is parsed independently, which
 * is exactly the bug the earlier build had when it shared one index. */
static int parse_one(const char *str, char *sign, Dlist **head, Dlist **tail)
{
	int i = 0; // local index, private to this operand

	if (str[0] == '+' || str[0] == '-')
	{
		*sign = str[0]; // record the explicit sign
		i = 1;          // skip the sign character
	}
	else
	{
		*sign = '+'; // no sign means positive
	}

	// an operand that is only a sign with no digits is invalid
	if (str[i] == '\0')
	{
		printf("Invalid number\n");
		return FAILURE;
	}

	while (str[i] != '\0') // walk the remaining characters
	{
		if (str[i] < '0' || str[i] > '9')
		{
			printf("Invalid number\n"); // anything outside 0-9 is rejected
			return FAILURE;
		}
		insert_at_last(head, tail, str[i] - '0'); // append the digit at the tail
		i++;
	}
	return SUCCESS;
}

/* function to load both operands into their lists and capture both signs */
int digit_to_list(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2,
				   char *sign1, char *sign2, char *argv[])
{
	if (argv == NULL)
	{
		return FAILURE;
	}

	// parse each operand with its own index so neither corrupts the other
	if (parse_one(argv[1], sign1, head1, tail1) == FAILURE)
	{
		return FAILURE;
	}
	if (parse_one(argv[3], sign2, head2, tail2) == FAILURE)
	{
		return FAILURE;
	}

	// strip any leading zeros the user may have typed (e.g. 007 -> 7)
	delete_zero(head1, tail1);
	delete_zero(head2, tail2);
	return SUCCESS;
}

/*============================================================
  MAGNITUDE PRIMITIVES (sign-agnostic)
============================================================*/

/* function to count the digits in a list */
static int list_length(Dlist *head)
{
	int count = 0;
	while (head != NULL)
	{
		count++;
		head = head->next;
	}
	return count;
}

/* function to compare two magnitudes: 1 if |list1|>|list2|, -1 if smaller, 0 if equal */
int compare_magnitude(Dlist *head1, Dlist *head2)
{
	int len1 = list_length(head1);
	int len2 = list_length(head2);

	// the number with more digits is the larger magnitude
	if (len1 > len2)
	{
		return 1;
	}
	if (len1 < len2)
	{
		return -1;
	}

	// equal length: compare digit by digit from the most significant end
	while (head1 != NULL && head2 != NULL)
	{
		if (head1->data > head2->data)
		{
			return 1;
		}
		if (head1->data < head2->data)
		{
			return -1;
		}
		head1 = head1->next;
		head2 = head2->next;
	}
	return 0; // all digits matched
}

/* function to add two magnitudes, walking both tails toward the heads */
int add_magnitude(Dlist *tail1, Dlist *tail2, Dlist **headR, Dlist **tailR)
{
	int sum, carry = 0;

	while (tail1 != NULL || tail2 != NULL) // until both lists are exhausted
	{
		sum = carry; // start the column with whatever carried in
		if (tail1 != NULL)
		{
			sum += tail1->data;
			tail1 = tail1->prev;
		}
		if (tail2 != NULL)
		{
			sum += tail2->data;
			tail2 = tail2->prev;
		}

		carry = sum / 10;                          // carry out of this column
		insert_at_first(headR, tailR, sum % 10);   // keep only the units digit
	}

	if (carry != 0) // a final carry becomes a new most significant digit
	{
		insert_at_first(headR, tailR, carry);
	}
	return SUCCESS;
}

/* function to handle a single borrow-aware subtraction column */
int update(int num1, int num2, Dlist **headR, Dlist **tailR, int *borrow)
{
	int res;
	if (num1 < num2) // this column needs to borrow from the next
	{
		*borrow = 1;
		num1 += 10;
	}
	else
	{
		*borrow = 0;
	}
	res = num1 - num2;
	insert_at_first(headR, tailR, res); // push the column result onto the front
	return SUCCESS;
}

/* function to subtract magnitudes assuming |list1| >= |list2| */
int sub_magnitude(Dlist *tail1, Dlist *tail2, Dlist **headR, Dlist **tailR)
{
	int n1, n2, borrow = 0;

	while (tail1 != NULL) // the larger number drives the loop
	{
		n1 = tail1->data - borrow;          // apply any pending borrow
		n2 = (tail2 != NULL) ? tail2->data : 0; // shorter number contributes 0 once exhausted

		if (update(n1, n2, headR, tailR, &borrow) != SUCCESS)
		{
			return FAILURE;
		}

		tail1 = tail1->prev;
		if (tail2 != NULL)
		{
			tail2 = tail2->prev;
		}
	}

	delete_zero(headR, tailR); // a subtraction like 100-99 leaves leading zeros to trim
	return SUCCESS;
}

/* function to swap two complete lists (head and tail together) */
void swap_list(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2)
{
	Dlist *temp = *head1;
	*head1 = *head2;
	*head2 = temp;

	temp = *tail1;
	*tail1 = *tail2;
	*tail2 = temp;
}

/*============================================================
  SIGNED TOP-LEVEL OPERATIONS
============================================================*/

/* function to normalise a zero result so it is never printed as "-0" */
static void normalise_zero(Dlist *headR, char *signR)
{
	if (headR != NULL && headR->next == NULL && headR->data == 0)
	{
		*signR = '+';
	}
}

/* function to add two signed operands */
int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2,
			 Dlist **headR, Dlist **tailR,
			 char *sign1, char *sign2, char *signR, char *argv[])
{
	(void)argv; // signs already parsed, argv no longer needed here

	if (*sign1 == *sign2)
	{
		// same sign: magnitudes add and the shared sign carries through
		*signR = *sign1;
		add_magnitude(*tail1, *tail2, headR, tailR);
	}
	else
	{
		// opposite signs: the larger magnitude wins and we subtract
		int cmp = compare_magnitude(*head1, *head2);
		if (cmp == 0)
		{
			*signR = '+'; // equal and opposite cancel to zero
			insert_at_first(headR, tailR, 0);
		}
		else if (cmp > 0)
		{
			*signR = *sign1; // |a| > |b|, result keeps a's sign
			sub_magnitude(*tail1, *tail2, headR, tailR);
		}
		else
		{
			*signR = *sign2; // |b| > |a|, result keeps b's sign
			sub_magnitude(*tail2, *tail1, headR, tailR);
		}
	}

	normalise_zero(*headR, signR);
	return SUCCESS;
}

/* function to subtract two signed operands: a - b is just a + (-b) */
int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2,
				Dlist **headR, Dlist **tailR,
				char *sign1, char *sign2, char *signR, char *argv[])
{
	// flip the second operand's sign, then reuse the addition logic
	char flipped = (*sign2 == '+') ? '-' : '+';
	return addition(head1, tail1, head2, tail2, headR, tailR,
					sign1, &flipped, signR, argv);
}

/* function to multiply two signed operands */
int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2,
				   Dlist **headR, Dlist **tailR,
				   char *sign1, char *sign2, char *signR, char *argv[])
{
	(void)argv;

	// the product sign follows the classic rule: like signs -> '+', unlike -> '-'
	*signR = (*sign1 == *sign2) ? '+' : '-';

	// either operand being zero short-circuits to a single 0
	if ((*head1 != NULL && (*head1)->next == NULL && (*head1)->data == 0) ||
		(*head2 != NULL && (*head2)->next == NULL && (*head2)->data == 0))
	{
		*signR = '+';
		insert_at_first(headR, tailR, 0);
		return SUCCESS;
	}

	Dlist *temp2 = *tail2; // outer loop walks the multiplier from its tail

	// accumulator holds the running sum of partial products
	Dlist *accH = NULL, *accT = NULL;
	int shift = 0; // how many trailing zeros this partial product needs

	while (temp2 != NULL)
	{
		// build one partial product list for the current multiplier digit
		Dlist *partH = NULL, *partT = NULL;
		int i;
		for (i = 0; i < shift; i++)
		{
			insert_at_first(&partH, &partT, 0); // positional zero padding
		}

		int carry = 0;
		Dlist *temp1 = *tail1; // inner loop walks the multiplicand from its tail
		while (temp1 != NULL)
		{
			int mul = (temp1->data * temp2->data) + carry;
			carry = mul / 10;
			insert_at_first(&partH, &partT, mul % 10);
			temp1 = temp1->prev;
		}
		if (carry != 0)
		{
			insert_at_first(&partH, &partT, carry);
		}

		// fold the partial product into the accumulator
		Dlist *sumH = NULL, *sumT = NULL;
		add_magnitude(accT, partT, &sumH, &sumT);

		// retire the old accumulator and the partial product
		delete_list(&accH, &accT);
		delete_list(&partH, &partT);

		accH = sumH; // the freshly built sum becomes the accumulator
		accT = sumT;

		temp2 = temp2->prev;
		shift++;
	}

	delete_zero(&accH, &accT); // trim any leading zero the accumulation left
	*headR = accH;
	*tailR = accT;

	normalise_zero(*headR, signR);
	return SUCCESS;
}

/* function to divide two signed operands using long division.
 * I bring digits of the dividend down one at a time into a running
 * remainder, and find each quotient digit by repeated subtraction of the
 * divisor (at most nine subtractions per digit). The quotient is built as a
 * full digit list, so it stays arbitrary precision instead of an int. */
int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2,
			 Dlist **headR, Dlist **tailR,
			 char *sign1, char *sign2, char *signR, char *argv[])
{
	(void)argv;
	(void)tail1;

	// dividing zero by anything is zero
	if (*head1 != NULL && (*head1)->next == NULL && (*head1)->data == 0)
	{
		*signR = '+';
		insert_at_first(headR, tailR, 0);
		return SUCCESS;
	}
	// division by zero is undefined
	if (*head2 != NULL && (*head2)->next == NULL && (*head2)->data == 0)
	{
		printf("Error! Divisor can't be 0\n");
		return FAILURE;
	}

	// like signs give a positive quotient, unlike signs a negative one
	*signR = (*sign1 == *sign2) ? '+' : '-';

	Dlist *quoH = NULL, *quoT = NULL; // the quotient we are building
	Dlist *remH = NULL, *remT = NULL; // the running remainder

	Dlist *cur = *head1; // pull dividend digits most significant first
	while (cur != NULL)
	{
		// remainder = remainder * 10 + next dividend digit
		insert_at_last(&remH, &remT, cur->data);
		delete_zero(&remH, &remT); // keep the remainder normalised

		int q_digit = 0;
		// subtract the divisor while it still fits into the remainder
		while (compare_magnitude(remH, *head2) >= 0)
		{
			Dlist *diffH = NULL, *diffT = NULL;
			sub_magnitude(remT, *tail2, &diffH, &diffT);
			delete_list(&remH, &remT); // discard the old remainder
			remH = diffH;              // adopt the reduced remainder
			remT = diffT;
			q_digit++;
		}

		insert_at_last(&quoH, &quoT, q_digit); // record this quotient digit
		cur = cur->next;
	}

	delete_list(&remH, &remT); // remainder is not reported by this calculator
	delete_zero(&quoH, &quoT); // drop leading zeros from the quotient

	*headR = quoH;
	*tailR = quoT;

	normalise_zero(*headR, signR);
	return SUCCESS;
}
