
#include "circular_queue.h"

void circular_queue_init(circular_queue_t* queue) {
	//비어있는 상태 초기 세팅

	queue->front = &(queue->values[0]);
	queue->rear = &(queue->values[CIRCULAR_QUEUE_MAX]);

	return;
}

int circular_queue_isEmpty(circular_queue_t* queue) {
	/*
	* 1. front가 첫번째 요소, rear가 마지막 요소를 가리킬 경우
	* 2. front - 1 == rear일 경우
	*/
	//조건 2
	if (queue->front - 1 == queue->rear) {
		return TRUE;
	}

	//조건1
	if (queue->front == &(queue->values[0]) && queue->rear == &(queue->values[CIRCULAR_QUEUE_MAX])) {
		return TRUE;
	}

	return FALSE;
}

int circular_queue_isFull(circular_queue_t* queue) {
	/*
	* 1. front + CIRCULAR_QUEUE_MAX - 1 == rear일 때
	* 2. rear + 2 == front 일 때
	*/

	//조건2
	if (queue->rear + 2 == queue->front) {
		return TRUE;
	}

	//조건1

	if (queue->front + CIRCULAR_QUEUE_MAX - 1 == queue->rear) {
		return TRUE;
	}
	return FALSE;
}

int circular_queue_enqueue(circular_queue_t* queue, circular_queue_type_t data) {
	
	/*
	* rear를 한 칸 움직이고 해당 위치에 값을 추가한다. 
	*/

	if (circular_queue_isFull(queue)) {
		return FALSE;
	}
	
	if (queue->rear == &(queue->values[CIRCULAR_QUEUE_MAX])) { //배열의 마지막 부분이라면
		queue->rear = &(queue->values[0]);
	}
	else {		//배열의 마지막 부분이 아니라면
		queue->rear += 1;
	}

	//값 대입
	*(queue->rear) = data;

	return TRUE;
}


int circular_queue_dequeue(circular_queue_t* queue, circular_queue_type_t* data) {
	/*
	* front에서 값을 추출하고 front를 한 칸 움직인다.
	* 값을 삭제할 필요는 없다.
	*/
	if (circular_queue_isEmpty(queue)) {
		return FALSE;
	}

	*data = *(queue->front);
	

	if (queue->front == &(queue->values[CIRCULAR_QUEUE_MAX])) { //배열의 마지막 부분이라면
		queue->front = &(queue->values[0]);
	}
	else {		//배열의 마지막 부분이 아니라면
		queue->front += 1;
	}
	return TRUE;
}