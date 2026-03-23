#pragma once

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif


/*
* enqueue 시 tail쪽에 노드 추가
* dequeue 시 head쪽에서 추출
*/

//사용할 데이터 타입
typedef int list_queue_data_type_t;
//노드
typedef struct queue_linked_list_node_t queue_linked_list_node_t;
//연결리스트
typedef struct queue_linked_list_t queue_linked_list_t;
//큐
typedef struct list_queue_t list_queue_t;


//큐 포인터를 반환하는 함수
list_queue_t* list_queue_create(void);


/*
*큐와 내부의 리스트 초기화
*
* 반환값
* 0: 메모리 할당 실패
* 1: 성공
*/
int list_queue_init(list_queue_t* queue);

/*
* 큐가 비어있는지 검사한다.
* 
* 반환값
* 0: 비어있지 않을 때
* 1: 비어있을 때
*/
int list_queue_isEmpty(list_queue_t* queue);

/*
* 큐에 값을 삽입한다.
* 
* 반환값
* 0: 메모리 할당 실패
* 1: 성공
* 
*/
int list_queue_enqueue(list_queue_t* queue, list_queue_data_type_t data);

/*
* 큐에서 값을 추출하여 두번째 매개변수로 전달한다.
* 
* 반환값
* 0: 비어있을 시
* 1: 성공
*/
int list_queue_dequeue(list_queue_t* queue, list_queue_data_type_t *data);

/*
* 큐에서 다음에 나올 값을 두번째 매개변수에 전달한다.
* 큐 내부에는 변동이 없다.
* 
* 반환값
* 0: 비어있을 시
* 1: 성공
*/
int list_queue_peek(list_queue_t* queue, list_queue_data_type_t* data);