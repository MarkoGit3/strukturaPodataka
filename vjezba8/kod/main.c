#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "test.h"

struct _Tree;
typedef struct _Tree* treePos;
typedef struct _Tree {
	int value;
	treePos left;
	treePos right;
}Tree;

treePos insertTree(treePos, int); // unos elemenata u stablo
int printInorder(treePos); //ispis u inorder
int printPostorder(treePos); //ispis u postorder
int printPreorder(treePos); //ispis u preorder
int printLevelorder(treePos); //ispsi u levelorder
treePos removeEl(treePos, int); //oslobada odabrani cvor
treePos findEl(treePos); //pronalazenje nekog elementa
treePos freeTree(treePos); //oslobada cijelo stablo

int main() {
	treePos root = NULL;
	int value;

	puts("Za prekid unosa upisite slovo: ");
	while(1){
		if (scanf("%d", &value)==0) {
			int temp;
			while ((temp = getchar()) != '\n' && temp != EOF);
			break;
		}

		root = insertTree(root, value);
	}
	if (root == NULL) {
		puts("Greska pri unosu.");
		return EXIT_FAILURE;
	}

	puts("Inorder ispis:\n");
	printInorder(root);
	puts("Postorder ispis:\n");
	printPostorder(root);
	puts("Preorder ispis:\n");
	printPreorder(root);
	puts("Levelorder ispis:\n");
	//printLevelorder(root);

	puts("Odaberite element za ukinuti:");
	if (scanf("%d", &value) == 0) {
		return EXIT_FAILURE;
	}
	removeEl(root, value);
	puts("Preorder ispis:\n");
	printPreorder(root);

	puts("izasa");
	freeTree(root);
	return EXIT_SUCCESS;
}

treePos insertTree(treePos root, int value){
	if (root == NULL) {
		root = (treePos)malloc(sizeof(Tree));
		if (root == NULL) {
			puts("Neuspjesna alokacija memorije.");
			return NULL;
		}
		root->value = value;
		root->left = NULL;
		root->right = NULL;
	}
	else if (root->value > value) {
		root->left = insertTree(root->left, value);
		//puts("Livo");
	}
	else if (root->value < value) {
		root->right = insertTree(root->right, value);
		//puts("Desno");
	}
	return root;
}
int printInorder(treePos temp){
	treePos root = temp;
	if (root==NULL) {
		return EXIT_SUCCESS;
	}

	if (root->left != NULL) {
		printInorder(root->left);
	}
	printf("\t%d\n", temp->value);
	if (root->right != NULL) {
		printInorder(root->right);
	}

	return EXIT_SUCCESS;
}
int printPostorder(treePos temp){
	treePos root = temp;
	if (root == NULL) {
		return EXIT_SUCCESS;
	}

	if (root->left != NULL) {
		printInorder(root->left);
	}
	if (root->right != NULL) {
		printInorder(root->right);
	}
	printf("\t%d\n", temp->value);
	
	return EXIT_SUCCESS;
}
int printPreorder(treePos temp){
	treePos root = temp;
	if (root == NULL) {
		return EXIT_SUCCESS;
	}

	printf("\t%d\n", temp->value);
	if (root->left != NULL) {
		printInorder(root->left);
	}
	if (root->right != NULL) {
		printInorder(root->right);
	}

	return EXIT_SUCCESS;
}
int printLevelorder(treePos temp){

	return EXIT_SUCCESS;
}
treePos removeEl(treePos root, int value){
	if (root == NULL) {
		return NULL;
	}
	treePos temp;

	if (root->value > value) {
		root->left = removeEl(root->left, value);
	}
	else if (root->value < value) {
		root->right = removeEl(root->right, value);
	}
	else{
		if (root->left != NULL && root->right != NULL) {
			temp = findEl(root->right);
			root->value = temp->value;
			root->right = removeEl(root->right, root->value);
		}
		else {
			temp = root;
			if (root->left == NULL) {
				root = root->right;
			}
			else {
				root = root->left;
			}
			free(temp);
		}
	}
	return root;
}
treePos findEl(treePos root){
	if (root == NULL){
		return NULL;
	}

	while (root->left != NULL){
		root = root->left;
	}
	return root;
}
treePos freeTree(treePos root){
	if (root == NULL) {
		return NULL;
	}
		
	root->left = freeTree(root->left);
	root->right = freeTree(root->right);
	
	free(root);
	return NULL;
}