#include <stdio.h>
#include <stdlib.h>
#include <limits.h> 
#include "tail_referenced_circular_linked_list.h"


/*
typedef int trcll_data_t;

typedef struct trcll_node_t {
	trcll_data_t value;
	trcll_node_t* next;
}trcll_node_t;

typedef struct {
	trcll_node_t* tail;
	trcll_node_t* cur;
	trcll_node_t* before;
	unsigned int length;
}trcll_t;
*/



void trcll_init(trcll_t* list) {
	list->tail = NULL;
	list->cur = NULL;
	list->before = NULL;
	list->length = 0;
}


int trcll_insert_head(trcll_t* list, trcll_data_t data) {

	trcll_node_t* new_node = (trcll_node_t*)malloc(sizeof(trcll_node_t));
	if (new_node == NULL || list->length == UINT_MAX) { //메모리할당 실패 혹은 최대 길이 도달
		return FALSE;
	}
	new_node->value = data;


	if (list->length == 0) { //노드가 없다면
		new_node->next = new_node;
		list->tail = new_node;
		list->cur = new_node;
		list->before = new_node;
	}
	else {	//노드가 있다면
		new_node->next = list->tail->next;
		list->tail->next = new_node;

		//before와 cur 사이에 새로운 노드가 위치한다면 (list->tail == list->before 일때)
		//before는 새로운 노드를 가르키게한다.
		if (list->tail == list->before) {
			list->before = new_node;
		}

	}

	list->length++;
	return TRUE;
}


int trcll_insert_tail(trcll_t* list, trcll_data_t data) {
	

	//head쪽에 노드를 추가한 이후 tail이 가르키는 노드를 바꿔주는 것으로 구현 가능하다

	if (trcll_insert_head(list, data) == FALSE) {	//메모리할당 실패 혹은 최대 길이 도달
		return FALSE;
	}
	list->tail = list->tail->next;

	return TRUE;
} 


int trcll_first(trcll_t* list, trcll_data_t* data) {
	if (list->length == 0) { //노드가 없을 때
		return FALSE;
	}
	list->cur = list->tail->next;
	list->before = list->tail;
	*data = list->cur->value;
	return TRUE;
}


int trcll_next(trcll_t* list, trcll_data_t* data) {
	if (list->length == 0) { //노드가 없을 때
		return FALSE;
	}
	list->before = list->cur;
	list->cur = list->cur->next;
	*data = list->cur->value;
	return TRUE;
}


int trcll_delete(trcll_t* list, trcll_data_t* data) {
	if (list->length == 0) { //노드가 없을 경우
		return FALSE;
	}

	if (list->length == 1) { //노드가 하나 뿐인 경우
		*data = list->cur->value;
		free(list->cur);

		trcll_init(list);
		return TRUE;
	}

	if (list->cur == list->tail) { //삭제하려는 노드를 tail이 가르키는 경우
		list->tail = list->before; //tail은 before를 가르키도록
	}

	
	//before는 건들필요 없다.

	list->cur = list->cur->next;

	*data = list->before->next->value;
	free(list->before->next);
	list->before->next = list->cur;
	list->length--;
	return TRUE;
}

