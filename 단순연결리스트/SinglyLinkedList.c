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
	//새로운 노드 생성 및 값 대입
	SinglyLinkedList_Node* newNode = (SinglyLinkedList_Node*)malloc(sizeof(SinglyLinkedList_Node));
	if (newNode == NULL) {
		return False;
	}
	newNode->value = data;
	newNode->next = NULL;
	//비어있다면
	//cur, tail, head 초기화
	if (list->length == 0) {
		list->cur = newNode;
		list->head = newNode;
	}


	//비어있지않았다면
	//기존의 끝 노드가 새로운 노드 가르키기
	else {
		list->tail->next = newNode;
	}

	list->tail = newNode;
	list->length++;
	return True;
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
	
	SLL_Data deletedData = 0;

	//가르키는게 없었다면
	if (list->cur == NULL) {
		return deletedData;
	}

	//노드가 하나밖에 없는 경우
	if (list->length == 1) {
		list->head = NULL;
		list->before = NULL;

		deletedData = list->cur->value;
		free(list->cur);
		list->cur = NULL;
		list->length--;
		return deletedData;
	}


	//노드가 2개 이상이지만 cur가 맨 처음일 경우
	if (list->head == list->cur) {
		
		list->head = list->cur->next;

		deletedData = list->cur->value;
		free(list->cur);
		list->cur = list->head;
		list->length--;
		return deletedData;
	}

	//그외의 경우	

	list->before->next = list->cur->next;

	deletedData = list->cur->value;
	free(list->cur);
	
	list->cur = list->before->next;
	list->length--;
	return deletedData;

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
* cur의 현재 값을 두번째 매개변수에 전달 후 cur를 다음 노드로 옮긴다.
* 다음 값이 없다면 cur를 옮기지 않는다.
* 반환값: 0(실패) , 1(성공)
* 다음 노드가 없거나 현재 노드가 없다면 실패
*/
int SinglyLinkedList_getAndNext(SinglyLinkedList* list, SLL_Data* result) {

	if (!SinglyLinkedList_get(list, result)) { //실패 시
		return False;
	}
	

	//cur를 다음 노드로 옮기기



	if (list->cur->next == NULL) {	//다음 노드가 없다면
		return False;
	}

	//다음 노드가 있다면

	list->before = list->cur;
	list->cur = list->cur->next;

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

/*
* 연결리스트의 모든 노트를 출력한다.
* 반환값: 0(실패) , 1(성공)
*/
void SinglyLinkedList_prt(SinglyLinkedList* list) {

	SinglyLinkedList_curFirst(list);
	SLL_Data value;
	while (SinglyLinkedList_getAndNext(list, &value)) {
		printf("%d ", value);
	}
	printf("%d ", value);
	printf("\nlength: %d\n", list->length);
}