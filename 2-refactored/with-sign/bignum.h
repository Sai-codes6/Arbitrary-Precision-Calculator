#ifndef BIGNUM_H // preprocessor guard
#define BIGNUM_H // declare header file

/*----------------------------------------------------------
Name : Deepika
Date : 30/07/25
Description : Arbitrary Precision Calculator - public engine API
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
 * the least significant digit sits at the tail. The doubly linked layout
 * lets me walk tail -> head when I propagate carries and borrows, and
 * head -> tail when I print or run long division.
 */
typedef struct node
{
	// struct members
	struct node *prev;
	int data;
	struct node *next;
} Dlist; // struct variable declaration

/* ---- list construction / teardown ---------------------------------- */

/* parse argv[1] and argv[3] into two digit lists and report their signs */
int digit_to_list(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2,
				   char *sign1, char *sign2, char *argv[]);

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

/* print a number: its sign (only when negative) followed by every digit */
int print_list(Dlist *head, char signR);

/* ---- magnitude primitives (sign is handled one layer up) ----------- */

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

/* ---- signed top-level operations ----------------------------------- */

/* Addition */
int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2,
			 Dlist **headR, Dlist **tailR,
			 char *sign1, char *sign2, char *signR, char *argv[]);

/* Subtraction */
int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2,
				Dlist **headR, Dlist **tailR,
				char *sign1, char *sign2, char *signR, char *argv[]);

/* Multiplication */
int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2,
				   Dlist **headR, Dlist **tailR,
				   char *sign1, char *sign2, char *signR, char *argv[]);

/* Division */
int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2,
			 Dlist **headR, Dlist **tailR,
			 char *sign1, char *sign2, char *signR, char *argv[]);

#endif // end of the conditional compilation block
