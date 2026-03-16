#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H

//노드에서 사용할 값
typedef int SLL_Data;		//필요하다면 다른 자료형이나 구조체로 변경 가능

//노드 정의
typedef struct SinglyLinkedList_Node{
	SLL_Data value;	//값 저장
	struct SinglyLinkedList_Node* next;	//다음 노드 가르키기
}SinglyLinkedList_Node;


//단순 연결 리스트 정의
typedef struct {
	SinglyLinkedList_Node* head;	//첫 노드
	SinglyLinkedList_Node* tail;	//끝 노드
	SinglyLinkedList_Node* cur;		//현재 가르키는 노드
	SinglyLinkedList_Node* before;	//cur의 직전 노드
	unsigned int length;	//노드의 개수
				//메모리 한계 때문에 int로 만들어도 충분하다.
	
	int (*cmp)(SLL_Data, SLL_Data);	//비교 기준 함수

} SinglyLinkedList;

#endif