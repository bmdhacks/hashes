#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "binarytree.h"
#include "hash.h"

void linked_list_insert(linked_list **ll, const char *key, int value) 
{
	assert(ll != NULL); // we need at least a pointer to assign to
	
	if (*ll == NULL) { // initialize the first entry
		*ll = malloc(sizeof(linked_list));
		assert(*ll != NULL);
		memset(*ll, 0, sizeof(linked_list));
		strncpy((*ll)->key, key, MAX_WORDSIZE);
		(*ll)->value = value;
	}
	else if ((*ll)->key[0] == 0) { // crazy initialized but empty ?
		assert("this is weird");
		strncpy((*ll)->key, key, MAX_WORDSIZE);
		(*ll)->value = value;
	}
	else { // chaining!
		linked_list_insert(&((*ll)->next), key, value);
	}
}

// returns -1 on miss
int linked_list_get(linked_list *ll, const char *key) 
{
	if (ll == NULL) {
		return -1;
	}
	else if (0 == strncmp(ll->key, key, MAX_WORDSIZE)) {
		return ll->value;
	}
	else {
		return linked_list_get(ll->next, key);
	}
}

hashtable* hashtable_create() 
{
	hashtable *ht = malloc(sizeof(hashtable)*HASH_SIZE);
	assert(ht != NULL);
	memset(ht, 0, sizeof(hashtable));
	return ht;
}

// djb2 hash 
unsigned int djb2_hash(const char *str)
{
	unsigned long hash = 5381;
	int c;

	while ((c = (unsigned char)*str++))
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

	return hash % HASH_SIZE;
}

void hashtable_insert(hashtable* ht, const char *key, int value) 
{
	unsigned int hash = djb2_hash(key);
	linked_list *ll = ht[hash];
	linked_list_insert(&ll, key, value);
	ht[hash] = ll;
}

int hashtable_get(hashtable* ht, const char *key)
{
	unsigned int hash = djb2_hash(key);
	linked_list *ll = ht[hash];
	return linked_list_get(ll, key);
}
