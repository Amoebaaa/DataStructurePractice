#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H


#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif


enum { CIRCULAR_QUEUE_MAX = 5}; //반드시 1 이상의 정수로 작성할 것

typedef int circular_queue_type_t;

typedef struct circular_queue_t {
	circular_queue_type_t values[CIRCULAR_QUEUE_MAX+1]; //가득참, 비어있음을 구별하기 위해 + 1 
	circular_queue_type_t* front;
	circular_queue_type_t* rear;
}circular_queue_t;





//////////////////////////////함수 정의/////////////////////////////

/*
* 큐 초기화 함수
*/
void circular_queue_init(circular_queue_t* queue);

/*
* 큐가 비어있는지 확인하는 함수
* 
* 반환값
* 1: 비어있음
* 0: 비어있지 않음
*/
int circular_queue_isEmpty(circular_queue_t* queue);

/*
* 큐가 꽉 찼는지
*
* 반환값
* 1: 꽉 찼음
* 0: 꽉 차있지 않음
*/
int circular_queue_isFull(circular_queue_t* queue);

/*
* 큐에 값을 삽입하는 함수
* 
* 반환값
* 1: 삽입 성공
* 0: 삽입 실패
*/
int circular_queue_enqueue(circular_queue_t* queue, circular_queue_type_t data);

/*
* 큐에서 값을 추출해 두번째 매개변수에 전달하는 함수
*
* 반환값
* 1: 추출 성공
* 0: 추출 실패
*/
int circular_queue_dequeue(circular_queue_t* queue, circular_queue_type_t *data);


#endif