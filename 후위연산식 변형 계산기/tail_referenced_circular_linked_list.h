#ifndef	TAIL_REFERENCE_CIRCULAR_LINKED_LIST_H
#define TAIL_REFERENCE_CIRCULAR_LINKED_LIST_H

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

/*
* 변형 원형 연결 리스트
*
* tail을 활용한 구현
* 
* 삽입, 조회, 삭제만 가능
*/

typedef char trcll_data_t;

typedef struct trcll_node_t {
	trcll_data_t value;
	struct trcll_node_t* next;
}trcll_node_t;

typedef struct {
	trcll_node_t* tail;		//head는 필요 없다.
	trcll_node_t* cur;
	trcll_node_t* before;
	unsigned int length;
}trcll_t;

/*
* 리스트 초기화 함수
*/
void trcll_init(trcll_t* list);


/*
* 머리에 새로운 노드를 추가하는 함수
* cur은 기존에 가르키던 위치를 유지한다.
* before는 cur의 직전 노드를 가르킨다. (바뀔 수 있다.)
*
* 반환값
* 0: 메모리 할당 실패 혹은 최대 길이 도달
* 1: 성공
*/
int trcll_insert_head(trcll_t* list, trcll_data_t data);


/*
* 꼬리에 새로운 노드를 추가하는 함수
* cur은 기존에 가르키던 위치를 유지한다.
* before는 cur의 직전 노드를 가르킨다.
*
* 반환값
* 0: 메모리 할당 실패 혹은 최대 길이 도달
* 1: 성공
*/
int trcll_insert_tail(trcll_t* list, trcll_data_t data);


/*
* cur을 head 노드로 옮기며 값을 두번째 매개변수에 전달하는 함수
* 
* 반환값
* 0: 노드가 없는 경우
* 1: 반환 성공
*/
int trcll_first(trcll_t* list, trcll_data_t* data);


/*
* cur을 한 칸 이동시키며 값을 두번째 매개변수에 전달하는 함수
*
* 반환값
* 0: 노드가 없는 경우
* 1: 반환 성공
*/
int trcll_next(trcll_t* list, trcll_data_t* data);


/*
* cur가 가르키는 노드를 삭제한다.
* cur은 삭제한 노드 다음 노드를 가르킨다.
* 두번째 매개변수에 삭제된 값을 저장한다.
* 
* 반환값
* 0: 노드가 없는 경우
* 1: 삭제 성공
*/
int trcll_delete(trcll_t* list, trcll_data_t* data);



#endif