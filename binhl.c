/* gcc binhl.c -DBINHL_STANDALONE -DMAX_BINH_LIST=1024 */
//#define BINHL_STANDALONE

#include "binhl.h"

int binhl_pop(binh_list *list) {

	int pos = 0;
	int id = list->ids[0].id;

	list->ids[0] = list->ids[--list->len];

	while (1) {
		int next_pos, next_id, val;
		int kid2_val, kid2_pos = (pos+1)*2;	
		int kid1_val, kid1_pos = kid2_pos - 1;

		if (kid1_pos > list->len || kid2_pos > list->len) break;

		next_id = list->ids[pos].id;
		val = list->values[list->ids[pos].id];
		kid1_val = list->values[list->ids[kid1_pos].id];
		kid2_val = list->values[list->ids[kid2_pos].id];

		if (val < kid1_val && val < kid2_val) break;

		next_pos = (kid1_val < kid2_val ? kid1_pos : kid2_pos);

		list->ids[pos] = list->ids[next_pos];
		list->ids[next_pos].id = next_id;
		
		pos = next_pos;
	}
	list->values[id] = 0;
	return id;
}
#define binhl_del(L,K) binhl_pop(L)

int binhl_push(binh_list *list, int id, int val) {

	int pos = list->len;
	int pre_pos = pos / 2;

	list->ids[pos].id = id;

	while (pre_pos != pos)
	{
		int n_id = list->ids[pre_pos].id;
		if (val < list->values[n_id]) {
			list->ids[pre_pos].id = id;
			list->ids[pos].id = n_id;
			pos = pre_pos;
			pre_pos = pos / 2;
		} else break;
	}

	list->values[id] = val;
	list->len++;

	return pos;
}
#define binhl_add binhl_push

#ifdef BINHL_STANDALONE
#include <stdio.h>

#define CARDS 5
char names[CARDS][80] = {
	{ " Troll " },//0
	{ " Goblin " },//1
	{ " Ogre " },//2
	{ " Orc " },//3
	{ " Giant " },//4
};
int costs[CARDS] = {
	1000,//0
	100,//1
	500,//2
	250,//3
	600,//4
};
void print_cards(binh_list* list) {
	int i;
	for (i = 0; i < list->len; i++) {
		printf(" % 6d ", list->ids[i].id);
	}
	printf("\n");
	for (i = 0; i < list->len; i++) {
		printf("%8s", names[list->ids[i].id]);
	}
	printf("\n");
	for (i = 0; i < list->len; i++) {
		printf("% 8d", list->values[list->ids[i].id]);
	}
	printf("\n");
}
int main(void) {
	binh_list deck = { 0 };
	int i;
	for (i = 0; i < CARDS; i++) {
		binhl_add(&deck, i, costs[i]);
	}
	print_cards(&deck);
	while (deck.len > 2) { 	
		printf("Popping next - %s!\n", names[binhl_pop(&deck)]);
	}
	print_cards(&deck);
	return 0;
}
#endif
