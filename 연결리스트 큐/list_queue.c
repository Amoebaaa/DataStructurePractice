#include <stdlib.h>
#include "list_queue.h"


//////////////////////////구조체//////////////////////////

//연결 리스트의 노드
struct queue_linked_list_node_t {
	list_queue_data_type_t value;
	struct queue_linked_list_node_t* next;
};

//연결 리스트
struct queue_linked_list_t {
	queue_linked_list_node_t* head;
	queue_linked_list_node_t* tail;
};

//큐
struct list_queue_t{
	queue_linked_list_t list;
};



////////////////////////////연결리스트 구현////////////////////////////////////
/*
* 연결리스트 초기화
* 
* 반환값
* 0: 메모리할당 실패
* 1: 성공
*/
static int list_init(queue_linked_list_t* list) {

	//더미노드 생성 
	queue_linked_list_node_t* dummy_head;
	dummy_head = (queue_linked_list_node_t*)malloc(sizeof(queue_linked_list_node_t));
	if (dummy_head == NULL) {	//메모리 할당 실패
		return FALSE;
	}

	dummy_head->next = NULL;
	dummy_head->value = -404;

	list->head = dummy_head;
	list->tail = dummy_head;

	return TRUE;
}

/*
* 연결리스트가 비어있는지 검사한다.
* 
* 반환값
* 1: 비어있을 때
* 0: 비어있지 않을 때
*/
static int list_isEmpty(queue_linked_list_t* list) {
	if (list->head == list->tail) {
		return TRUE;
	}
	return FALSE;
}

/*
* 연결리스트의 tail에 노드를 추가한다.
* enqueue시 사용된다.
* 
* 반환값
* 1: 성공
* 0: 메모리할당 실패
*/
static int list_insert_tail(queue_linked_list_t* list, list_queue_data_type_t data) {
	queue_linked_list_node_t* new_node;
	new_node= (queue_linked_list_node_t*)malloc(sizeof(queue_linked_list_node_t));
	if (new_node == NULL) { //메모리할당 실패
		return FALSE;
	}
	
	//값 삽입
	new_node->value = data;
	new_node->next = NULL;

	list->tail->next = new_node;
	list->tail = new_node;


	return TRUE;
}

/*
* 연결리스트의 head에서 노드를 삭제한다.  
* 삭제된 값은 두번째 매개변수로 전달된다.
* dequeue시 사용한다.
* 
* 반환값
* 1: 성공
* 0: 실패(노드가 없을 경우)
*/
static int list_delete_head(queue_linked_list_t* list, list_queue_data_type_t* data) {
	if (list_isEmpty(list)) {
		return FALSE;
	}
	*data = list->head->next->value;
	
	queue_linked_list_node_t* tmp = list->head->next->next;
	if (list->head->next == list->tail) {	//tail이 가르키는 노드를 삭제한다면 더미노드를 가리키게 할 것
		list->tail = list->head;
	}
	free(list->head->next);
	list->head->next = tmp;
	
	return TRUE;
}

/*
* 연결리스트의 head부분의 값을 두번째 매개변수로 전달한다.
* 값은 삭제되지 않는다.
* 
* 반환값
* 1: 성공
* 0: 실패(노드가 없을 경우)
*/
static int list_peek_head(queue_linked_list_t* list, list_queue_data_type_t* data) {
	if (list_isEmpty(list)) {
		return FALSE;
	}

	*data = list->head->next->value;
	return TRUE;
}

////////////////////////////큐 구현////////////////////////////////////

list_queue_t* list_queue_create(void) {
	list_queue_t* new_queue = (list_queue_t*)malloc(sizeof(list_queue_t));
	if (new_queue == NULL) {  //메모리할당 실패
		return NULL;
	}
	if (list_queue_init(new_queue) == 0) { //초기화 실패
		free(new_queue);
		return NULL;
	}
	return new_queue;
}

int list_queue_init(list_queue_t* queue) {
	return list_init(&(queue->list));
}

int list_queue_isEmpty(list_queue_t* queue) {
	return list_isEmpty(&(queue->list));
}

int list_queue_enqueue(list_queue_t* queue, list_queue_data_type_t data) {
	return list_insert_tail(&(queue->list), data);
}

int list_queue_dequeue(list_queue_t* queue, list_queue_data_type_t* data) {
	return list_delete_head(&(queue->list), data);
}

int list_queue_peek(list_queue_t* queue, list_queue_data_type_t* data) {
	return list_peek_head(&(queue->list), data);
}