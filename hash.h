#ifndef _HASH_H
#define _HASH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "binarytree.h"

// fancy prime number pre-picked to scale
#define HASH_SIZE 2357207

// shitty linked list
typedef struct linked_list_s
{
	char key[MAX_WORDSIZE+1];
	int value;
	struct linked_list_s *next;
} linked_list;

void linked_list_insert(linked_list **ll, const char *key, int value);

// returns -1 on miss
int linked_list_get(linked_list *ll, const char *key);

typedef linked_list* hashtable;
hashtable* hashtable_create();
void hashtable_insert(hashtable* ht, const char *key, int value);
int hashtable_get(hashtable* ht, const char *key);

#endif // _HASH_H
