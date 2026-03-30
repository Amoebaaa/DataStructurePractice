#include <stdlib.h>
#include <limits.h>
#include "heap.h"


/*
* heap의 내부 사이즈가 최대치에 도달했다면 정해진 만큼 메모리를 늘린다.
* 이 때 할당 실패 혹은 size_t의 최대에 도달했다면 이 결과를 반환한다.
*
* heap의 여유공간 > 메모리 증가량 * 2이라면 메모리 증가량만큼 메모리를 반환한다.
*	ㄴ capacity - length > 메모리증가량  * 2
*/



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

typedef struct heap_t {
	void** value_array; //각 값을 void* 형태로 담기 위한 배열을 가리키는 포인터
	size_t* value_size; //각 값의 크기를 탐는다.
	size_t length; //값의 개수를 담는다.
	size_t capacity; //최대 값을 담는다.
	cmp cmp_func;
} heap_t;

int heap_default_cmp_func(void* value_a, size_t value_a_size, void* value_b, size_t value_b_size) {
	int a = *(int*)value_a;
	int b = *(int*)value_b;

	if (a < b) {
		return 1;
	}
	if (a == b) {
		return 0;
	}
	return -1;
}


/* 
* 매개변수로 전달받은 인덱스 값을 좌측 자식 노드의 인덱스로 변환 후 세번째 매개변수 포인터에 값을 저장한다.
* 
* 반환값
* 0: 오버플로우, 자식이 없는 경우
* 1: 계산식 반환 완료
*/
static int heap_get_left_child_index(heap_t * heap, size_t index, size_t* left_child_index) {
	size_t new_index = index * 2 + 1;
	if (new_index < index) { // 오버플로우
		return FALSE;
	}
	if (new_index > heap->length - 1) { //길이에서 벗어나는 경우
		return FALSE;
	}

	*left_child_index = new_index;
	return TRUE;
}
/*
* 매개변수로 전달받은 인덱스 값을 우측 자식 노드의 인덱스로 변환 후 세번째 매개변수 포인터에 값을 저장한다.
*
* 반환값
* 0: 오버플로우, 자식이 없는 경우
* 1: 계산식 반환 완료
*/
static int heap_get_right_child_index(heap_t* heap, size_t index, size_t* right_child_index) {
	size_t new_index = index * 2 + 2;
	if (new_index < index) { // 오버플로우
		return FALSE;
	}
	if (new_index > heap->length - 1) { //길이에서 벗어나는 경우
		return FALSE;
	}

	*right_child_index = new_index;
	return TRUE;
}

/*
* 매개변수로 전달받은 인덱스 값을 부모 노드의 인덱스로 변환 후 세번째 매개변수 포인터에 값을 저장한다.
*
* 반환값
* 0: 부모가 없는 경우
* 1: 계산식 반환 완료
*/
static int heap_get_parent_index(size_t index, size_t* parent_index) {
	if (index == 0) {
		return FALSE;
	}
	*parent_index = (index - 1) / 2;
	return TRUE;
}


/*
* free를 통해 메모리 반환이 필요한가 검사하는 함수
* 
* 반환값
* 1: heap의 여유공간 > 메모리 증가량 * 2 일 때 ( capacity - length > 메모리증가량  * 2 )
* 0: 그렇지 않을 때
*/
static int heap_need_free(heap_t* heap) {
	if (heap->capacity - heap->length > HEAP_CAPACITY_INCREAMENT_SIZE * 2) {
		return TRUE;
	}
	return FALSE;
}

/*
* 힙의 뒤에서부터 메모리 증가량만큼 free한다.
* 
* 반환값
* 0: 실패
* 1: 성공
*/
static int heap_free(heap_t* heap) {
	void* temp1;
	void* temp2;
	temp1 = realloc(heap->value_array, sizeof(void*) * (heap->capacity - HEAP_CAPACITY_INCREAMENT_SIZE));
	temp2 = realloc(heap->value_size, sizeof(size_t) * (heap->capacity - HEAP_CAPACITY_INCREAMENT_SIZE));
	if (temp1 == NULL || temp2 == NULL) {
		return FALSE;
	}

	heap->value_array = temp1;
	heap->value_size = temp2;

	heap->capacity -= HEAP_CAPACITY_INCREAMENT_SIZE;

	return TRUE;

}

/*
* realloc을 통한 메모리 추가 할당이 필요한가 검사하는 함수
* 
* 반환값
* 1: heap의 내부 사이즈가 최대치에 도달했다면
* 0: heap의 내부 사이즈가 최대치에 도달하지 않았다면
* 
*/
static int heap_need_realloc(heap_t* heap) {
	if (heap->length == heap->capacity) {
		return TRUE;
	}
	return FALSE;
}

/*
* 메모리를 정해진 만큼 추가할당한다.
* 
* 반환값
* 0: 메모리 할당 실패
* 0: 특정 메모리만큼 더해질 때 capacity가 표현할 수 없는 범위라면
* 1: 메모리 할당 성공
*/
static int heap_realloc(heap_t* heap) {
	if (SIZE_MAX - HEAP_CAPACITY_INCREAMENT_SIZE < heap->capacity) {
		return FALSE;
	}

	void* temp1;
	void* temp2;
	temp1 = realloc(heap->value_array, sizeof(void*) * (heap->capacity + HEAP_CAPACITY_INCREAMENT_SIZE));
	temp2 = realloc(heap->value_size, sizeof(size_t) * (heap->capacity + HEAP_CAPACITY_INCREAMENT_SIZE));
	if (temp1 == NULL || temp2 == NULL) {
		return FALSE;
	}

	heap->value_array = temp1;
	heap->value_size = temp2;

	heap->capacity += HEAP_CAPACITY_INCREAMENT_SIZE;

	return TRUE;

}

/*
* 자식의 개수를 반환해주는 함수
* 두번째 매개변수로 자신의 index를 전달받는다.
* 
* 반환값: 자식의 개수
*/
static int heap_get_child_num(heap_t* heap, size_t index) {
	size_t child_index; //함수 호출을 위해서만 존재
	if (heap_get_left_child_index(heap, index, &child_index) == 0) {	//자식이 없는 경우
		return 0;
	}
	if (heap_get_right_child_index(heap, index, &child_index) == 0) {	//자식 1개만 있는 경우
		return 1;
	}
	return 2;	//자식이 둘 모두 있는 경우
}

/*
* 나, 자식노드 2개 중 어떤 것이 가장 우선순위가 높은지 검사 후 반환하는 함수
* 
* 반환값
* -1: 입력노드가 length 이상일 때
* 0: 내가 우선순위가 가장 높거나 자식이 없을 경우
* 1: 좌측 자식이 우선순위가 높을 경우
* 2: 우측 자식이 우선순위가 높을 경우
* 
*/
static int heap_get_highest_priority_target_with_child(heap_t* heap, size_t index) {
	if (index >= heap->length) {
		return -1;
	}


	size_t left_child_index;
	size_t right_child_index;

	if (heap_get_left_child_index(heap, index, &left_child_index) == 0) {
		//자식이 없는 경우
		return 0;
	}

	if (heap_get_right_child_index(heap, index, &right_child_index) == 0) {
		//자식이 1개일 경우
		if (heap->cmp_func(heap->value_array[index], heap->value_size[index], heap->value_array[left_child_index], heap->value_size[left_child_index]) != -1) {
			//내가 우선순위가 높거나 같을 때
			return 0;
		}

		//내 우선순위가 낮을 때
		return 1;
	}

	//자식이 둘 다 있을 경우

	int child_priority;

	if (heap->cmp_func(heap->value_array[right_child_index], heap->value_size[right_child_index], heap->value_array[left_child_index], heap->value_size[left_child_index]) != -1) {
		//우측 자식의 우선순위가 높거나 같을 때
		child_priority = 2;
	}
	else {
		child_priority = 1;
	}
	
	if (child_priority == 2) {
		//우측 자식과 나를 비교
		if (heap->cmp_func(heap->value_array[index], heap->value_size[index], heap->value_array[right_child_index], heap->value_size[right_child_index]) != -1) {
			//내가 우선순위가 높거나 같을 때
			return 0;
		}
		//우측 자식이 더 높을 때
		return 2;
	}

	else {
		//좌측 자식과 나를 비교
		if (heap->cmp_func(heap->value_array[index], heap->value_size[index], heap->value_array[left_child_index], heap->value_size[left_child_index]) != -1) {
			//내가 우선순위가 높거나 같을 때
			return 0;
		}

		//좌측 자식이 더 높을 때
		return 1;
	}
}


/*
* 나와 부모노드 간 어떤 것이 우선순위가 더 높은지 검사 후 반환하는 함수
* 
* 반환값
* -2: 입력노드가 length 이상일 때
* -1: 내 우선순위가 부모보다 높을 경우
* 0: 우선순위가 같거나 부모 노드가 없을 경우 
* 1: 부모노드의 우선순위가 더 높은경우
*/
static int heap_get_highest_priority_target_with_parent(heap_t* heap, size_t index) {

	if (index >= heap->length) { //입력받은 index가 불량할 경우
		return -2;
	}


	size_t parent_index;
	//부모노드의 인덱스 계산
	if (heap_get_parent_index(index, &parent_index) == 0) {
		//부모노드가 없는 경우
		return 0;
	}

	int priority = heap->cmp_func(heap->value_array[index], heap->value_size[index], heap->value_array[parent_index], heap->value_size[parent_index]);

	if (priority == 1) {
		//나의 우선순위가 더 높을때
		return -1;
	}
	if (priority == 0) {
		//우선순위가 같을 때
		return 0;
	}

	//부모 노드의 우선순위가 더 높은 경우
	return 1;
}

/*
* 입력된 두 인덱스에 해당하는 노드간 값을 서로 바꾸는 함수
* 
* 반환값
* 0: 정상적이지 않은 인덱스 전달 (인덱스가 length를 벗어났을 때)
* 1: 교환 성공
*/
static int heap_node_exchange(heap_t* heap, size_t index_A, size_t index_B) {

	//length에서 벗어난 인덱스가 있다면 FALSE를 반환
	if (index_A >= heap->length || index_B >= heap->length) {
		return FALSE;
	}

	void* temp_value;
	size_t temp_size;

	//두 노드간 교환
	temp_value = heap->value_array[index_A];
	temp_size = heap->value_size[index_A];
	heap->value_array[index_A] = heap->value_array[index_B];
	heap->value_size[index_A] = heap->value_size[index_B];
	heap->value_array[index_B] = temp_value;
	heap->value_size[index_B] = temp_size;

	return TRUE;
}

heap_t* heap_create() {
	heap_t* result = (heap_t*)malloc(sizeof(heap_t));
	if (result == NULL) {
		return NULL;
	}
	return result;
}

int heap_init(heap_t* heap,cmp func) {
	heap->length = 0;
	heap->cmp_func = func;
	heap->value_array = (void**)malloc(sizeof(void*) * HEAP_CAPACITY_INCREAMENT_SIZE);
	if (heap->value_array == NULL) {
		return FALSE;
	}
	heap->value_size = (size_t*)malloc(sizeof(size_t) * HEAP_CAPACITY_INCREAMENT_SIZE);
	if (heap->value_size == NULL) {
		free(heap->value_array);
		return FALSE;
	}
	heap->capacity = HEAP_CAPACITY_INCREAMENT_SIZE;
	return TRUE;
}


int heap_delete(heap_t* heap, void** r_value, size_t* r_value_size) {
	/*
	* root node를 두번째 매개변수로 반환 후
	* 기존의 맨 마지막 노드를 root위치로 옮긴 후 heapify한다.
	* 
	* 좌 우 자식 노드 중 가장 우선순위가 높은 것과 위치를 교환한다.
	*  ㄴ 자기 자신이 우선순위가 가장 높거나 자식노드가 없을 때까지 반복한다.
	*/
	if (heap_isEmpty(heap)) {
		return FALSE;
	}

	//매개변수에 삭제될 값 담기
	*r_value = heap->value_array[0];
	*r_value_size = heap->value_size[0];


	//root에 마지막 노드를 올려놓기
	heap->value_array[0] = heap->value_array[heap->length - 1];
	heap->value_size[0] = heap->value_size[heap->length - 1];

	//마지막 노드 삭제
	heap->length -= 1;

	
	if (heap_need_free(heap)) {	//공간이 불필요하게 많이 남았다면 일부를 free한다.
		heap_free(heap);
	}

	size_t checking_index = 0; //루트에 올려진 마지막 노드를 따라가는 인덱스
	size_t next_index;		//마지막 노드가 다음에 가게 될 곳의 인덱스
	int check_priority;
	
	while (1) {
		check_priority = heap_get_highest_priority_target_with_child(heap, checking_index);
		if (check_priority <= 0) {	//내가 우선순위가 가장 높거나 자식이 없을 경우
			break; //탈출
		}
		else if (check_priority == 1) {	//좌측 자식의 우선순위가 가장 높을 경우
			heap_get_left_child_index(heap, checking_index, &next_index);
			heap_node_exchange(heap, checking_index, next_index);
			checking_index = next_index;
		}
		else {	//우측 자식의 우선순위가 가장 높을 경우
			heap_get_right_child_index(heap, checking_index, &next_index);
			heap_node_exchange(heap, checking_index, next_index);
			checking_index = next_index;
		}
	}
	return TRUE;
}

int heap_insert(heap_t* heap, void* input_value, size_t input_value_size) {
	/*
	* 마지막 노드에 값을 추가한다.
	* 이후 부모노드와 우선순위를 비교하면서 부모의 우선순위가 더 높거나 같을 때 까지 반복한다.
	* 함수를 끝내기 전 메모리를 더 할당해야하는지 검사한다.
	*/

	if (heap->length == heap->capacity) { //최대 크기에 도달했다면
		return FALSE;
	}

	//추가할당
	heap->length += 1;

	size_t my_index = heap->length - 1;	//제자리에 맞출 마지막 노드의 인덱스
	size_t next_index;
	int priority;	//우선순위 판단결과를 저장할 변수
	//마지막 노드에 매개변수로 받은 값 적용
	heap->value_array[my_index] = input_value;
	heap->value_size[my_index] = input_value_size;

	while (1) {
		priority = heap_get_highest_priority_target_with_parent(heap, my_index);
		if (priority == 1 || priority == 0) { //부모노드의 우선순위가 더 높거나 같거나 부모 노드가 없을 경우
			break;
		}
		heap_get_parent_index(my_index, &next_index);	//부모노드랑 바꾸기 위한 인덱스 계산
		heap_node_exchange(heap, my_index, next_index);

		my_index = next_index;
	}



	if (heap_need_realloc(heap)) {
		heap_realloc(heap);
	}

	return TRUE;


	//마지막에 추가 공간 할당 가능성 확인
}

size_t heap_get_length(heap_t* heap) {
	return heap->length;
}

int heap_isEmpty(heap_t* heap) {
	if (heap->length == 0) {
		return TRUE;
	}
	return FALSE;
}

int heap_peek(heap_t*heap, void**root_node_value, size_t * root_node_size) {
	if (heap_isEmpty(heap)) {
		return FALSE;
	}
	*root_node_value = heap->value_array[0];
	*root_node_size = heap->value_size[0];
	return TRUE;
}


void heap_reset(heap_t* heap) {
	free(heap->value_array);
	free(heap->value_size);
	heap_init(heap,heap->cmp_func);
}