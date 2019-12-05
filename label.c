#include "parser.h"
#include "label.h"
//HASH TABLE
int hashLabel(char *s){
	int hash = 7;

	for (int i = 0; s[i] != '\0'; i++) {
	    hash = hash*31 + s[i];
	}

	return hash % HASH_SIZE;
}

Labellist lookupLabel(char *s){
	int index ;
	index = hash(s);
  Labellist p = tableLabel[index];
	while(p){
		if(hash(p->key)==index){

			return p;
		}
		p = p->next;
	}
return NULL;
}

void insertLabel(char *s , int value){
	int index;
	index = hash(s);
	//printf("%d\n",index);
	Labellist p;
	p=(Labellist)malloc(sizeof(struct listlabel));
	p->key = s;
	p->value = value;
	p->next = tableLabel[index];
	tableLabel[index]=p;
}

void init_tableLabel(){
	int size = HASH_SIZE;
	for(int i=0;i<size;i++){
		tableLabel[i]=NULL;
	}
}
