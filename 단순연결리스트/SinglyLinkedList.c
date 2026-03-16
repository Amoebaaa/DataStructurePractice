#include <stdio.h>	//NULL 사용을 위함
#include <stdlib.h>	//동적할당을 위함
#include "SinglyLinkedList.h"

#ifndef True
#define True 1
#endif

#ifndef False
#define False 0
#endif

/*
* 매개변수로 받은 SinglyLinkedList 초기화
*/
void SinglyLinkedList_Init(SinglyLinkedList* list) {
	list->head = NULL;
	list->tail = NULL;
	list->cur = NULL;
	list->before = NULL;
	list->length = 0;
	list->cmp = NULL;
}

/*
* head에 node를 추가하는 함수 (left add)
* 반환값: 실패 시 0, 성공 시 1 
*/
int SinglyLinkedList_Ladd(SinglyLinkedList* list, SLL_Data data) {
	
	
	//새로운 노드 생성 및 값 대입
	SinglyLinkedList_Node* newNode = (SinglyLinkedList_Node*)malloc(sizeof(SinglyLinkedList_Node));
	if (newNode == NULL) {
		return False;
	}
	newNode->value = data;

	//비어있었다면
	if (list->length == 0) {
		list->tail = newNode;
		list->cur = newNode;
	}


	newNode->next = list->head; //새로운 노드는 기존 머리 노드를 가르킨다.
	list->head = newNode; //머리가 새로운 노드를 가르키게
	list->length++;	//길이 증가
	
}

/*
* tail에 node를 추가하는 함수 (left add)
*/
void SinglyLinkedList_Radd(SinglyLinkedList* list, SLL_Data data) {
	//구현 필요		
}

/*
* 비교함수에 따라 노드를 위치에 삽입하는 함수
*/
void SinglyLinkedList_CmpInsert(SinglyLinkedList* list, SLL_Data data) {
	//구현 필요		
}

/*
* 현재 가르키는 노드를 삭제하는 함수
* 반환값: 삭제한 노드의 값
* 실패요인: 가르키는 노드가 없는 경우
*/
SLL_Data SinglyLinkedList_delete(SinglyLinkedList* list) {
	//구현 필요		
	//free해줄 것
}

/*
* n번째 index에 node를 삽입하는 함수 (0 포함)
* 반환값: 0(실패) , 1(성공)
*/
int SinglyLinkedList_insert(SinglyLinkedList* list, SLL_Data data, unsigned int n) {
	//구현 필요		
}

/*
* cur의 값을 두번째 매개변수에 담아서 전달
* 반환값: 0(실패) , 1(성공)
*/
int SinglyLinkedList_get(SinglyLinkedList* list, SLL_Data* result) {
	
	if (list->cur == NULL) { //가르키는게 없다면 False 반환
		return False;
	}

	*result = list->cur->value;
	return True;
}

/*
* cur의 다음 값을 두번째 매개변수에 담아서 전달
* 반환값: 0(실패) , 1(성공)
*/
int SinglyLinkedList_getnext(SinglyLinkedList* list, SLL_Data* result) {
	//구현 필요

	if (list->cur->next == NULL) {	//다음 노드가 없다면
		return False;
	}

	list->before = list->cur;
	list->cur = list->cur->next;

	*result = list->cur->value;
	return True;
}


/*
* index의 값을 두번째 매개변수에 담아서 전달
* 반환값: 0(실패) , 1(성공)
*/
int SinglyLinkedList_getIndex(SinglyLinkedList* list, SLL_Data* result, unsigned int index) {
	//구현 필요
}

/*
* index 노드의 값을 설정
* 반환값: 0(실패) , 1(성공)
*/
int SinglyLinkedList_setIndex(SinglyLinkedList* list, SLL_Data* result) {
	//구현 필요
}

/*
* cur를 첫 노드로 설정
* 반환값: 0(실패) , 1(성공)
*/
int SinglyLinkedList_curFirst(SinglyLinkedList* list) {
	if (list->length == 0) { //노드가 없다면 False 반환 
		return False;
	}
	
	list->cur = list->head;
	list->before = NULL;
	return True;
}

int main() {
	
	SinglyLinkedList s;
	SLL_Data value;
	SinglyLinkedList_Init(&s);
	SinglyLinkedList_Ladd(&s, 3);
	SinglyLinkedList_Ladd(&s, 4);
	SinglyLinkedList_Ladd(&s, 5);
	SinglyLinkedList_curFirst(&s);

	SinglyLinkedList_get(&s, &value);
	printf("%d\n", value);
	SinglyLinkedList_getnext(&s, &value);
	printf("%d\n", value);

	SinglyLinkedList_getnext(&s, &value);
	printf("%d\n", value);

	
}