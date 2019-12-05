#ifndef __label_h__
#define __label_h__
#define HASHLABLE_SIZE 1024
typedef struct listlabel{
	char *key;
	int value;
	struct listlabel *next;
}*Labellist;


Labellist lookupLabel(char *s); // pesquisar key numa hashTable
void insertLabel(char *s , int value);//inserir um valor com uma key
void init_tableLabel();//por tudo a null;
int hashLabel(char *s);
void printListLabel(Labellist p);

Labellist tableLabel[HASHLABLE_SIZE];
#endif
