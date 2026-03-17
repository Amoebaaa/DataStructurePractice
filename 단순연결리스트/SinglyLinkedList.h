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


/*
* 매개변수로 받은 SinglyLinkedList 초기화
*/
void SinglyLinkedList_Init(SinglyLinkedList* list);


/*
* head에 node를 추가하는 함수 (left add)
* 반환값: 실패 시 0, 성공 시 1
*/
int SinglyLinkedList_Ladd(SinglyLinkedList* list, SLL_Data data);

/*
* tail에 node를 추가하는 함수 (left add)
*/
void SinglyLinkedList_Radd(SinglyLinkedList* list, SLL_Data data);


/*
* 현재 가르키는 노드를 삭제하는 함수
* 반환값: 삭제한 노드의 값
* 실패요인: 가르키는 노드가 없는 경우
*/
SLL_Data SinglyLinkedList_delete(SinglyLinkedList* list);



/*
* cur의 값을 두번째 매개변수에 담아서 전달
* 반환값: 0(실패) , 1(성공)
*/
int SinglyLinkedList_get(SinglyLinkedList* list, SLL_Data* result);


/*
* cur의 현재 값을 두번째 매개변수에 전달 후 cur를 다음 노드로 옮긴다.
* 다음 값이 없다면 cur를 옮기지 않는다.
* 반환값: 0(실패) , 1(성공)
*/
int SinglyLinkedList_getAndNext(SinglyLinkedList* list, SLL_Data* result);


/*
* cur를 첫 노드로 설정
* 반환값: 0(실패) , 1(성공)
*/
int SinglyLinkedList_curFirst(SinglyLinkedList* list);


/*
* 연결리스트의 모든 노트를 출력한다.
* 반환값: 0(실패) , 1(성공)
*/
void SinglyLinkedList_prt(SinglyLinkedList* list);

#endif