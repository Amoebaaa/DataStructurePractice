#include <stdlib.h>
#include "binary_tree.h"

//이진트리 노드 구조체
typedef struct binary_tree_node_t {
	binary_tree_data_t value;
	struct binary_tree_node_t* left;
	struct binary_tree_node_t* right;
} binary_tree_node_t;


binary_tree_node_t* Btree_get_new_node() {
	binary_tree_node_t* new_node = (binary_tree_node_t*)malloc(sizeof(binary_tree_node_t));
	if (new_node == NULL) {
		return NULL;
	}
	new_node->left = NULL;
	new_node->right = NULL;
	return new_node;
}


binary_tree_data_t Btree_getvalue(binary_tree_node_t* node) {
	return node->value;
}

void Btree_setvalue(binary_tree_node_t* node, binary_tree_data_t data) {
	node->value = data;
}

binary_tree_node_t* Btree_getrightnode(binary_tree_node_t* node) {
	return node->right;
}

binary_tree_node_t* Btree_getleftnode(binary_tree_node_t* node) {
	return node->left;
}




//전위 순회
void Btree_preorder_traversal(binary_tree_node_t* node, action func) {
	if (node == NULL)
		return;
	func(node);
	if(node->left != NULL)
		Btree_preorder_traversal(node->left,func);
	if(node->right != NULL)
		Btree_preorder_traversal(node->right, func);
	
}

//중위 순회
void Btree_inorder_traversal(binary_tree_node_t* node, action func) {
	if (node == NULL)
		return;
	if (node->left != NULL)
		Btree_inorder_traversal(node->left, func);
	func(node);
	if (node->right != NULL)
		Btree_inorder_traversal(node->right, func);
}

//후위 순회
void Btree_postorder_traversal(binary_tree_node_t* node, action func) {
	if (node == NULL)
		return;
	if (node->left != NULL)
		Btree_postorder_traversal(node->left, func);
	if (node->right != NULL)
		Btree_postorder_traversal(node->right, func);
	func(node);
}


/*
* 해당 노드를 free하는 함수
*/
static void Btree_delete_action(binary_tree_node_t* node){
	free(node);
}

void Btree_delete(binary_tree_node_t* node) {
	Btree_postorder_traversal(node, Btree_delete_action);
}



void Btree_setrightnode(binary_tree_node_t* node, binary_tree_node_t* new_node) {
	if (node == NULL) {
		return;
	}

	if (node->right != NULL) {
		//우측 sub-tree 삭제 
		Btree_delete(node->right);
	}

	node->right = new_node;
}

void Btree_setleftnode(binary_tree_node_t* node, binary_tree_node_t* new_node) {
	if (node == NULL) {
		return;
	}

	if (node->left != NULL) {
		Btree_delete(node->left);
	}

	node->left = new_node;
}
