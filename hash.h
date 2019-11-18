#ifndef __hash_h__
#define __hash_h__
#define HASH_SIZE 1024
typedef struct listh{
	char *key;
	Expr* value;
	struct listh *next;
}*LIST;


LIST lookup(char *s); // pesquisar key numa hashTable
void insert(char *s , Expr* value);//inserir um valor com uma key
void init_table();//por tudo a null;
int hash(char *s);
void printList(LIST p);

LIST table[HASH_SIZE];
#endif
