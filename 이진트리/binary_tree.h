#pragma once

//이진트리에서 사용할 값 
//int외 다른 자료형, 구조체 등으로 변경 가능하나 포인터로 사용 시 메모리 누수 가능성이 있습니다.
typedef int binary_tree_data_t;


//이진트리 노드 구조체 (불투명 구조체)
typedef struct binary_tree_node_t binary_tree_node_t;

/*
* 노드를 생성, 초기화 후 반환하는 함수
* 
* 반환값
* NULL: 메모리 할당 실패
*/
binary_tree_node_t* Btree_get_new_node();


/*
* 해당 노드가 담고있는 값을 반환하는 함수
*/
binary_tree_data_t Btree_getvalue(binary_tree_node_t* node);

/*
* 해당 노드의 값을 바꾸는 함수
*/
void Btree_setvalue(binary_tree_node_t* node, binary_tree_data_t data);


/*
* 좌측의 자식 노드 주소를 반환하는 함수
*/
binary_tree_node_t* Btree_getrightnode(binary_tree_node_t* node);

/*
* 우측의 자식 노드 주소를 반환하는 함수
*/
binary_tree_node_t* Btree_getleftnode(binary_tree_node_t* node);


/*
* 우측의 자식 노드로 2번째 매개변수의 노드를 추가하는 함수
* 만약 이미 존재한다면 삭제 후 추가한다.
*/
void Btree_setrightnode(binary_tree_node_t* node, binary_tree_node_t* new_node);

/*
* 좌측의 자식 노드로 2번째 매개변수의 노드를 추가하는 함수
* 만약 이미 존재한다면 삭제 후 추가한다.
*/
void Btree_setleftnode(binary_tree_node_t* node, binary_tree_node_t* new_node);


/*
* 해당 노드와 모든 자식 노드를 포함해서 free한다.
*/
void Btree_delete(binary_tree_node_t* node);


/*
* 각 노드를 순회하며 해당 노드에서 할 동작을 정의하는 함수 포인터
* 
* 첫번째 매개변수: 해당 노드의 주소값
*/
typedef void (*action)(binary_tree_node_t* node);

//전위 순회
void Btree_preorder_traversal(binary_tree_node_t* node, action func);

//중위 순회
void Btree_inorder_traversal(binary_tree_node_t* node, action func);

//후위 순회
void Btree_postorder_traversal(binary_tree_node_t* node, action func);

