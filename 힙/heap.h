#pragma once

#ifndef HEAP_CAPACITY_INCREAMENT_SIZE
#define HEAP_CAPACITY_INCREAMENT_SIZE 10	//힙이 최대크기에 도달했을때 늘어나는 사이즈
#endif

#ifndef TRUE
#define TRUE 1
#endif


#ifndef FALSE
#define FALSE 0
#endif

/*
* 우선순위 판단함수
* 
* 매개변수로는 비교할 값 2개와 각각이 몇 바이트를 차지하는지 입력받는다.
* 
* 반환값
* -1: 좌측 피연산자의 우선순위가 낮다.
* 0 : 동일하다.
* 1 : 좌측 피연산자의 우선순위가 높다.
*/
typedef int (*cmp)(void* value_a, size_t value_a_size, void* value_b, size_t value_b_size);

//힙 구조체
typedef struct heap_t heap_t;



/*
* heap_t을 생성 후 주소를 반환하는 함수
* 
* 반환값
* heap_t의 주소값
* NULL: 메모리 할당 실패
*/
heap_t* heap_create();


/*
* heap 구조체 초기화
* 
* 두번째 매개변수로는 우선순위 판단 함수를 전달받는다.
* 
* 반환값
* 0: 초기 메모리할당 실패
* 1: 초기 메모리할당 성공
*/
int heap_init(heap_t* heap, cmp func);

/*
* 힙의 노드를 비교하는데의 기본 cmp함수 이다.
* 노드에 저장되는 값이 int, 값이 낮을 수록 우선순위가 높다.
*/
int heap_default_cmp_func(void* value_a, size_t value_a_size, void* value_b, size_t value_b_size);


/*
* 힙에 값을 삽입한다.
* 
* 우선순위가 높은 값이 root node로 간다.
* 
* 반환값
* 0: 최대 길이에 도달했을 경우
* 1: 성공
*/
int heap_insert(heap_t* heap,void* input_value,size_t input_value_size);


/*
* 우선순위가 가장 높은 노드를 돌려준다.
* 두번째 매개변수로 해당 노드 값의 주소, 세번째 매개변수로 해당 노드 값의 크기를 돌려준다.
*
* 반환값
* 0: 노드가 없을 경우
* 1: 성공
*/
int heap_delete(heap_t* heap, void** r_value, size_t* r_value_size);


/*
* 힙의 메모리를 free를 이용해 기본 값으로 초기화 시킨다.
* 
* 각 노드의 값이 메모리 주소를 담고있을 경우 메모리 누수가 발생할 수 있다.
*/
void heap_reset(heap_t* heap);


/*
* 힙이 비었는지 검사한다.
* 
* 반환값
* 1: 비어있다.
* 0: 비어있지 않다.
*/
int heap_isEmpty(heap_t* heap);


/*
* 힙에서 root node 값을 돌려준다.
* 두번째 매개변수에 root node 값의 주소, 세번째 매개변수에 해당 값의 크기를 전달한다.
*/
int heap_peek(heap_t* heap, void** root_node_value, size_t* root_node_size);

/*
* 힙의 현재 크기를 반환한다.
*/
size_t heap_get_length(heap_t* heap);
