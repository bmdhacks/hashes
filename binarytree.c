#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "binarytree.h"

static void binarytree_set(binarytree* bt, void* ent, size_t ent_size) 
{
	assert(bt->ent == NULL);
	bt->ent = malloc(ent_size);
	assert(bt->ent != NULL);
	memcpy(bt->ent, ent, ent_size);
}

binarytree* binarytree_create()
{
	binarytree* newtree = malloc(sizeof(binarytree));
	memset(newtree, 0, sizeof(binarytree));
	assert(newtree != NULL);
	
	return newtree;
}

int binarytree_insert(binarytree** bt, cmp_func cmp, void *ent, size_t ent_size)
{
	if (*bt == NULL) {
			*bt = binarytree_create();
			binarytree_set(*bt, ent, ent_size);
	}
	else if ((*bt)->ent == NULL) {
		binarytree_set(*bt, ent, ent_size);
	}
	else if (0 < (*cmp)((*bt)->ent, ent)) {
		binarytree_insert(&(*bt)->left, cmp, ent, ent_size);
	}
	else {
		binarytree_insert(&(*bt)->right, cmp, ent, ent_size);
	}

	return 1; // always successful for now
}

void* binarytree_find(binarytree *bt, cmp_func cmp, void *ent)
{
	if (bt == NULL || bt->ent == NULL) {
		return NULL;
	}

	int res = (*cmp)(bt->ent, ent);

	if (res == 0) {
		return bt->ent;
	}
	else if (0 < res) {
		return binarytree_find(bt->left, cmp, ent);
	}
	else {
		return binarytree_find(bt->right, cmp, ent);
	}
}

dict_ent* dict_create(const char* key, int value) 
{
	dict_ent* dict = malloc(sizeof(dict_ent));
	assert(dict != NULL);
	memset(dict, 0, sizeof(dict_ent));
	dict->value = value;
	strncpy(dict->key, key, MAX_WORDSIZE);

	return dict;
}

int dict_cmp(void *d1, void *d2) 
{
	return strncmp(((dict_ent*)d1)->key, ((dict_ent*)d2)->key, MAX_WORDSIZE);
}

