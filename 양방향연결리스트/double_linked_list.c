#include <stdlib.h>
#include <limits.h>
#include "double_linked_list.h"

/*
typedef int DLL_data;

typedef struct double_linked_list_node_t {
	DLL_data value;
	struct double_linked_list_node_t* next;
	struct double_linked_list_node_t* prev;
}double_linked_list_node_t;

typedef struct {
	double_linked_list_node_t* head;
	double_linked_list_node_t* tail;
	double_linked_list_node_t* cur;
	unsigned int length;
}double_linked_list;
*/


int double_linked_list_init(double_linked_list* list) {

	//더미노드 2개 동적 할당
	double_linked_list_node_t* dummy_head_node = (double_linked_list_node_t*)malloc(sizeof(double_linked_list_node_t));
	if (dummy_head_node == NULL) {
		return FALSE;
	}
	double_linked_list_node_t* dummy_tail_node = (double_linked_list_node_t*)malloc(sizeof(double_linked_list_node_t));
	if (dummy_tail_node == NULL) {
		return FALSE;
	}

	//더미노드 초기화
	dummy_head_node->next = dummy_tail_node;
	dummy_head_node->prev = NULL;

	dummy_tail_node->next = NULL;
	dummy_tail_node->prev = dummy_head_node;

	//더미노드 연결
	list->head = dummy_head_node;
	list->tail = dummy_tail_node;

	//그 외 변수 초기화
	//double_linked_list_add_cur로 삽입하기 용이하도록
	//cur는 tail의 dummy node를 가리키게한다.
	list->cur = dummy_tail_node;
	list->length = 0;

	return TRUE;
}

int double_linked_list_add_head(double_linked_list* list, DLL_data data) {

	//새로운 노드 동적 할당
	double_linked_list_node_t* new_node = (double_linked_list_node_t*)malloc(sizeof(double_linked_list_node_t));
	if (new_node == NULL || list->length == UINT_MAX) {
		return FALSE;
	}
	new_node->value = data;

	new_node->next = list->head->next; 
	new_node->prev = list->head; //이전 노드는 더미노드

	//삽입된 위치의 전, 후 노드 초기화
	list->head->next->prev = new_node;
	list->head->next = new_node;

	//첫 노드라면 cur가 가리키게한다.
	if (list->length == 0) {
		list->cur = new_node;
	}

	list->length++;
	return TRUE;
}

int double_linked_list_add_tail(double_linked_list* list, DLL_data data) {
	
	//새로운 노드 동적 할당
	double_linked_list_node_t* new_node = (double_linked_list_node_t*)malloc(sizeof(double_linked_list_node_t));
	if (new_node == NULL || list->length == UINT_MAX) {
		return FALSE;
	}
	new_node->value = data;

	new_node->prev = list->tail->prev; 
	new_node->next = list->tail; //이후 노드는 더미노드

	//삽입된 위치의 전, 후 노드 초기화
	list->tail->prev->next = new_node;
	list->tail->prev = new_node;

	//첫 노드라면 cur가 가리키게한다.
	if (list->length == 0) {
		list->cur = new_node;
	}

	list->length++;
	return TRUE;
}

int double_linked_list_add_cur(double_linked_list* list, DLL_data data) {
	//새로운 노드 동적 할당
	double_linked_list_node_t* new_node = (double_linked_list_node_t*)malloc(sizeof(double_linked_list_node_t));
	if (new_node == NULL || list->length == UINT_MAX) {
		return FALSE;
	}
	
	//새로운 노드 초기화
	new_node->value = data;
	new_node->next = list->cur;
	new_node->prev = list->cur->prev;

	list->cur = new_node;

	//삽입된 위치의 전, 후 노드 초기화
	list->cur->prev->next = list->cur;
	list->cur->next->prev = list->cur;

	list->length++;
	return TRUE;

	//cur가 tail의 dummy node를 가리킬때도 (length ==0) 새 노드를 추가하며 정상동작한다.

}

int double_linked_list_first(double_linked_list* list, DLL_data* data) {
	if (list->length == 0) {	//노드가 없을 경우
		return FALSE;
	}
	list->cur = list->head->next;
	*data = list->cur->value;
	return TRUE;
}

int double_linked_list_last(double_linked_list* list, DLL_data* data) {
	if (list->length == 0) {	//노드가 없을 경우
		return FALSE;
	}
	list->cur = list->tail->prev;
	*data = list->cur->value;
	return TRUE;
}

int double_linked_list_next(double_linked_list* list, DLL_data* data) {
	if (list->cur == list->tail->prev || list->cur == list->tail) {	//마지막 노드거나 노드가 없을 경우
		return FALSE;
	}
	list->cur = list->cur->next;
	*data = list->cur->value;
	return TRUE;
}

int double_linked_list_prev(double_linked_list* list, DLL_data* data) {
	if (list->cur == list->head->next) {	//첫 노드일 경우
		return FALSE;
	}
	list->cur = list->cur->prev;
	*data = list->cur->value;
	return TRUE;
}

int double_linked_list_get(double_linked_list* list, DLL_data* data) {
	if (list->cur == list->tail->prev || list->cur == list->tail) {
		return FALSE;
	}
	*data = list->cur->value;
	return TRUE;
}

int double_linked_list_delete(double_linked_list* list, DLL_data* data) {
	if (list->length == 0 || list->cur == list->tail) { //가르키는 노드가 없을 경우
		return FALSE;
	}

	double_linked_list_node_t* next_cur = list->cur->next; //cur의 다음 노드 주소 저장
	
	//cur의 전, 후 노드 값 조정
	list->cur->prev->next = list->cur->next;
	list->cur->next->prev = list->cur->prev;

	//삭제, 값 전달
	*data = list->cur->value;
	free(list->cur);

	//cur는 다음 노드를 가르키기
	//마지막 노드를 삭제했다면 tail의 dummy node를 가리키게 된다.(init과 동일상태)
	list->cur = next_cur;

	list->length--;
	return TRUE;
}