#ifndef BIGNUM_H // preprocessor guard
#define BIGNUM_H // declare header file

/*----------------------------------------------------------
Name : Deepika
Date : 30/07/25
Description : Arbitrary Precision Calculator (without sign) - public engine API
----------------------------------------------------------*/

// library inclusion
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// declaring macros
#define SUCCESS 0
#define FAILURE -1

/*
 * Each digit of a number lives in its own node. The list is held in
 * "human reading order": the most significant digit sits at the head and
 * the least significant digit sits at the tail. This is the unsigned engine,
 * so the operands are always non-negative; only subtraction can produce a
 * negative result, which it reports through a separate flag.
 */
typedef struct node
{
	// struct members
	struct node *prev;
	int data;
	struct node *next;
} Dlist; // struct variable declaration

/* ---- list construction / teardown ---------------------------------- */

/* parse argv[1] and argv[3] into two digit lists */
int digit_to_list(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, char *argv[]);

/* insert a single digit at the head (most significant end) */
int insert_at_first(Dlist **head, Dlist **tail, int value);

/* insert a single digit at the tail (least significant end) */
int insert_at_last(Dlist **head, Dlist **tail, int value);

/* duplicate a whole list (deep copy) into destination head/tail */
int copy_list(Dlist *src_head, Dlist **dst_head, Dlist **dst_tail);

/* strip every redundant leading zero, always leaving at least one digit */
void delete_zero(Dlist **head, Dlist **tail);

/* free the entire list and reset head/tail to NULL */
int delete_list(Dlist **head, Dlist **tail);

/* free just the head node */
int delete_first(Dlist **head, Dlist **tail);

/* print the result (digits only; the caller decides about a leading '-') */
int print_list(Dlist *head);

/* ---- magnitude primitives ------------------------------------------ */

/* compare |list1| and |list2|: returns 1 if first is bigger, -1 if smaller, 0 if equal */
int compare_magnitude(Dlist *head1, Dlist *head2);

/* result = |list1| + |list2| */
int add_magnitude(Dlist *tail1, Dlist *tail2, Dlist **headR, Dlist **tailR);

/* result = |list1| - |list2|, assuming |list1| >= |list2| */
int sub_magnitude(Dlist *tail1, Dlist *tail2, Dlist **headR, Dlist **tailR);

/* one borrow-aware column of a subtraction, pushed onto the result list */
int update(int num1, int num2, Dlist **headR, Dlist **tailR, int *borrow);

/* swap two complete lists (both head and tail) */
void swap_list(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2);

/* ---- top-level operations ------------------------------------------ */

/* Addition */
int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2,
			 Dlist **headR, Dlist **tailR, char *argv[]);

/* Subtraction. *negative is set to 1 when the true result is below zero. */
int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2,
				Dlist **headR, Dlist **tailR, int *negative, char *argv[]);

/* Multiplication */
int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2,
				   Dlist **headR, Dlist **tailR, char *argv[]);

/* Division */
int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2,
			 Dlist **headR, Dlist **tailR, char *argv[]);

#endif // end of the conditional compilation block
