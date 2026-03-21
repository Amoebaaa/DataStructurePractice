#pragma once

#include "tail_referenced_circular_linked_list.h" //원형 연결 리스트 사용

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

//tail이 stack의 밑바닥에 있도록 구현

typedef trcll_data_t stack_data_t; //스택에서 사용할 데이터 타입

typedef struct {	//스택 구조체
	trcll_t list;
} stack_t;

/*
* 스택 초기화
*/
void stack_init(stack_t* s);

/*
* stack의 윗부분을 두번째 매개변수로 전달하고 stack에서 제외한다.
* 
* 반환값
* 0: 담긴 내용이 없을 경우
* 1: 성공
*/
int stack_pop(stack_t* s, stack_data_t* data);


/*
* stack에 두번째 매개변수(data)를 쌓는다.
*
* 반환값
* 0: 메모리 할당 실패
* 1: 성공
*/
int stack_push(stack_t* s, stack_data_t data);


/*
* stack의 가장 윗부분을 두번째 매개변수로 전달하지만 stack에서 제외하지 않는다.
* 
* 반환값
* 0: 담긴 내용이 없을 경우
* 1: 성공
*/
int stack_peek(stack_t* s, stack_data_t* data);

/*
* stack이 비어있는지 확인한다.
* 
* 반환값
* 0: 비어있지 않을 경우
* 1: 비어있을 경우
*/
int stack_isEmpty(stack_t* s);