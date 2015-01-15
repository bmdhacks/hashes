#ifndef _BTREE_H
#define _BTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct binarytree_s
{
	struct binarytree_s *left, *right;
	void* ent; // payload
} binarytree;

/**
 * allocate a binarytree
 */
binarytree* binarytree_create();

/**
 * comparison function for binarytree payloads
 */
typedef int(*cmp_func)(void *a, void *b);

/**
 * insert an entry into the binarytree.  
 * @param bt binarytree to modify by adding
 *   the new entry.  If this points to NULL a new binarytree will be
 *   allocated.
 * @param cmp implementation of the payload comparison function
 * @param ent entry to add to the binarytree
 * @param ent_size size of the entry structure
 */
int binarytree_insert(binarytree** bt, cmp_func cmp, void *ent, size_t ent_size);
void* binarytree_find(binarytree *bt, cmp_func cmp, void *ent);

// maximum size of a word in the dictionary
#define MAX_WORDSIZE 64

/**
 * key/value entry for our binarytree containing a string key and an int value
 */
typedef struct 
{
	int value;
	char key[MAX_WORDSIZE];
} dict_ent;

/**
 * Create a dictionary entry
 */
dict_ent* dict_create(const char* key, int value);

/**
 * Implementation of the comparison function for our dictionary
 * key/value structure that compares the keys with strcmp
 */
int dict_cmp(void *d1, void *d2);

#endif //_BTREE_H
