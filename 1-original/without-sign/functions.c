#include "apc.h" // header file inclusion

/* function to add the digits to the list */
int digit_to_list(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, char *argv[])
{
    if (argv == NULL)
    {
        return FAILURE;
    }

    int i, digit1, digit2;                 // variable declaration
    char *str1 = argv[1], *str2 = argv[3]; // store the two operands in str1 and 2 pointers

    i = 0;                  // init i with 0
    while (str1[i] != '\0') // traverse through the first operand
    {
        if (str1[i] < '0' || str1[i] > '9')
        {
            printf("Invalid number\n"); // if the digit is less than or greater than 9 it's invalid
            return FAILURE;
        }
        else
        {
            digit1 = str1[i] - 48;                // convert to int and store in digit1
            insert_at_last(head1, tail1, digit1); // function call to insert the digit at the end of the list
        }
        i++; // increment i
    }

    i = 0;                  // update i with 0
    while (str2[i] != '\0') // traverse through the second operand
    {
        if (str2[i] < '0' || str2[i] > '9')
        {
            printf("Invalid number\n"); // if the digit is less than or greater than 9 it's invalid
            return FAILURE;
        }
        else
        {
            digit2 = str2[i] - 48;                // convert to int and store in digit2
            insert_at_last(head2, tail2, digit2); // function call to insert the digit at the end of the list
        }
        i++; // increment i
    }
    return SUCCESS;
}

/* function to insert the value at last end of the list */
int insert_at_last(Dlist **head, Dlist **tail, int value)
{
    // allocate memory for the new node
    Dlist *new = malloc(sizeof(Dlist));
	if (new == NULL)
	{
		return FAILURE; // malloc failed
	}
    // update new nodes data prev and next
	new->data = value;
	new->prev = NULL;
	new->next = NULL;

    // if list is empty, new node becomes the head and tail
	if (*head == NULL)
	{	
        // update both head and tail with new
		*head = new;
        *tail = new;
		return SUCCESS;
	}

	new->prev = *tail;   // update the new node's prev ptr
	(*tail)->next = new;   // update tail's next with new node
	*tail = new;    // update tail with new node
    return SUCCESS;
} 

/* function to insert the value at first end of the list */
int insert_at_first(Dlist **head, Dlist **tail, int value)
{
    Dlist *new = malloc(sizeof(Dlist));     // allocate memory for the new node
    if (new == NULL)
    {
        return FAILURE;    // malloc failed
    }
    // update new nodes data prev and next
    new->data = value;
    new->prev = NULL;
    new->next = NULL;

    // if list is empty, new node becomes the head and tail
    if (*head == NULL)
    {
        // update both head and tail with new
        *head = new;
        *tail = new;
        return SUCCESS;
    }

    new->next = *head;   // new node points to the old head node
    (*head)->prev = new;  // old head node's prev points to the new node
    *head = new;    // update the head to new node
    return SUCCESS;
}

/* function to delete the list */
int delete_list(Dlist **head, Dlist **tail)
{
    Dlist *temp = *head;     // store head in a temporary variable
    // loop till temp reaches null
    while (temp != NULL)
    {
        Dlist *temp2 = temp->next;     // store temp's next in another temporary variable
        free(temp);     // free the temp node
        temp = temp2;   // update temp with temp2
    }
    // update nead and tail with null
    *head=NULL;
    *tail=NULL;

    return SUCCESS;
}

/* function to delete first node */
int delete_first(Dlist **head, Dlist **tail)
{
    if (*head == NULL)
    {
        return FAILURE;    // failure if list is empty
    }

    if(*head == *tail)    // only one node in the list
    {
        free(*head);   // free the head node
        // update nead and tail with null
        *head = NULL;
        *tail = NULL;
        return SUCCESS;
    }
    else
    {
        Dlist *temp;
        temp = *head;   // store head in a temporary variable
        *head = (*head)->next;    //point head to next node
        free(temp);     // free the temp node
        (*head)->prev = NULL;     // update head's prev with null
        return SUCCESS;
    }
}

/* function to delete any zero digit stored in left hand side of a number */
void delete_zero(Dlist **head, Dlist **tail)
{
    if ((*head) != NULL && (*head)->data == 0)   // if head is not null and head's data is zero
    {
        delete_first(head, tail);  // function call to delete the first node i.e 0
    }
}

/* function to print the list */
int print_list(Dlist *head)
{
    // Cheking the list is empty or not
    if (head == NULL)  
    {
        printf("INFO:List is empty");
    }
    else
    {
        while (head)   // traverse through the list
        {
            // Printing the list
            printf("%d", head->data);
            
            //Travering in forward direction
            head = head->next;
        }
    }
}