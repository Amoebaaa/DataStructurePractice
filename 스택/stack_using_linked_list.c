#include "stack_using_linked_list.h"

void stack_init(stack_t* s) {
	trcll_init(&(s->list));	//원형 연결리스트 초기화
}

int stack_pop(stack_t* s, stack_data_t* data) {
	if (stack_isEmpty(s)) {
		return FALSE;
	}

	//언제나 cur는 head, before는 tail 가리키기에 delete함수 활용 가능
	
	//삭제 및 삭제된 값 전달
	trcll_data_t removed_data;
	trcll_delete(&(s->list), &removed_data);
	*data = (stack_data_t)removed_data;

	//delete 함수 이후에도 cur은 head를 가리킨다.

	return TRUE;
}

int stack_push(stack_t* s, stack_data_t data) {
	
	if (trcll_insert_head(&(s->list), (trcll_data_t)data) == FALSE) {	//공간할당 실패
		return FALSE;
	}
	

	//delete의 함수 활용을 위해 언제나 cur는 head, before는 tail을 가리키도록 설정
	s->list.cur = s->list.tail->next;
	s->list.before = s->list.tail;

	return TRUE;
}


int stack_peek(stack_t* s, stack_data_t* data) {
	if (stack_isEmpty(s)) {
		return FALSE;
	}

	//cur는 언제나 head를 가리킨다.
	*data = s->list.cur->value;
	return TRUE;
}

int stack_isEmpty(stack_t* s) {
	if (s->list.length == 0) { //원형 연결 리스트 구조체의 length 활용
		return TRUE;
	}
	return FALSE;
}
