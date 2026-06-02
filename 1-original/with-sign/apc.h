#ifndef APC_H // preprocessor directive
#define APC_H // declare header file

// library inclusion
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// declaring macros
#define SUCCESS 0
#define FAILURE -1

// structure declaration
typedef struct node
{
	// struct members
	char sign;
	struct node *prev;
	int data;
	struct node *next;
} Dlist; // struct variable declaration

/* Include the prototypes here */

/* store the operands into the list */
int digit_to_list(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, char *sign1, char *sign2, char *argv[]);

/* insert at first */
int insert_at_first(Dlist **head, Dlist **tail, int value);

/* insert at last */
int insert_at_last(Dlist **head, Dlist **tail, int value);

/* delete a node with data has zero left side */
void delete_zero(Dlist **headR, Dlist **tailR);

/* delete the list */
int delete_list(Dlist **head, Dlist **tail);

/* delete the first node */
int delete_first(Dlist **head, Dlist **tail);

/* print the result */
int print_list(Dlist *head, char signR);

/* func to update the result list */
int update(int num1, int num2, Dlist **headR, Dlist **tailR, int *borrow);

/* swap the list*/
void swap_list(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2);

/* Addition */
int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR, char *sign1, char *sign2, char *signR, char *argv[]);

/* subtraction */
int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR, char *sign1, char *sign2, char *signR, char *argv[]);

/* Multiplication */
int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR, char *sign1, char *sign2, char *signR, char *argv[]);

/* Division */
int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR, char *sign1, char *sign2, char *signR, char *argv[]);

#endif // end of the conditional compilation block