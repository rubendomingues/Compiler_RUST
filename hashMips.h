#ifndef __hashMips_h__
#define __hashMips_h__
#include <stdlib.h>
#include <stdio.h>
#define HASH_SIZE 1024

typedef struct listHash{
	char *key;
	char *type;
	struct listHash *next;
}*LIST;


LIST lookup(char *s); // pesquisar key numa hashTable
void insert(char *s, char *type);//inserir um valor com uma key
void init_table();//por tudo a null;
unsigned int hash(char *s);
void printList(LIST p);

LIST table[HASH_SIZE];

#endif
