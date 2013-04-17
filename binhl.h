#ifndef _BINHL_H_
#define _BINHL_H_

#define MAX_BINH_LIST 4096

#include <stdint.h>

typedef union {
	intptr_t 	id;
	void*   	ptr;
} intvoid;

typedef struct binh_list {
	int len;
	intvoid ids[MAX_BINH_LIST];
	int values[MAX_BINH_LIST];
} binh_list;

int binhl_pop(binh_list *list);
int binhl_push(binh_list *list, int id, int val);

#endif
