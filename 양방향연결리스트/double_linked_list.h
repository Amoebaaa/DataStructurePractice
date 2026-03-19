#pragma once

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

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


/*
* 초기화 함수
* 
* 더미노드도 만들어서 head와 tail에 연결한다.
* 
* 반환값
* 0: 실패
* 1: 성공
*/
int double_linked_list_init(double_linked_list* list);


/*
* 머리에 새로운 노드를 추가한다.
* 
* cur가 가르키는 노드는 변하지 않는다. (첫 노드라면 cur가 가르키게한다.)
* 
* 반환값
* 0: 메모리 할당 실패
* 0: length가 최대치
* 1: 메모리 할당 성공
*/
int double_linked_list_add_head(double_linked_list* list, DLL_data data);


/*
* 꼬리에 새로운 노드를 추가한다.
*
* cur가 가르키는 노드는 변하지 않는다. (첫 노드라면 cur가 가르키게한다.)
* 
* 반환값
* 0: 메모리 할당 실패
* 0: length가 최대치
* 1: 메모리 할당 성공
*/
int double_linked_list_add_tail(double_linked_list* list, DLL_data data);

/*
* cur가 가르키는 위치에 새로운 노드를 추가한다.
* 리스트가 비어있다면 새로 추가한다.
* cur는 추가한 노드를 가르킨다.
* 
* 반환값
* 0: 메모리 할당 실패
* 0: length가 최대치
* 1: 메모리 할당 성공
*/
int double_linked_list_add_cur(double_linked_list* list, DLL_data data);

/*
* cur를 첫 노드로 옮기고 두번째 매개변수에 해당 값을 담는다.
* 
* 반환값
* 0: 첫 노드가 없을 시
* 1: 성공
*/
int double_linked_list_first(double_linked_list* list, DLL_data* data);


/*
* cur를 마지막 노드로 옮기고 두번째 매개변수에 해당 값을 담는다.
*
* 반환값
* 0: 노드가 없을 시
* 1: 성공
*/
int double_linked_list_last(double_linked_list* list, DLL_data* data);

/*
* cur를 다음 노드로 옮기고 두번째 매개변수에 해당 값을 담는다.
*
* 반환값
* 0: 다음 노드가 없을 시
* 1: 성공
*/
int double_linked_list_next(double_linked_list* list, DLL_data* data);


/*
* cur를 이전 노드로 옮기고 두번째 매개변수에 해당 값을 담는다.
*
* 반환값
* 0: 이전 노드가 없을 시
* 1: 성공
*/
int double_linked_list_prev(double_linked_list* list, DLL_data* data);

/*
* cur가 가르키는 노드의 값을 두번째 매개변수에 담는다.
*
* 반환값
* 0: 노드가 없을 시
* 1: 성공
*/
int double_linked_list_get(double_linked_list* list, DLL_data* data);


/*
* cur가 가르키는 노드를 삭제한다.
* 삭제하는 노드의 값은 두번째 매개변수에 담는다.
* cur는 삭제한 다음 노드를 가르킨다.
* 
* 반환값
* 0: 노드가 없을 시
* 1: 성공
*/
int double_linked_list_delete(double_linked_list* list, DLL_data* data);

