#include <stdio.h>
#include <stdlib.h>
#include "test.h"

treePos insertEl(treePos root, int value) {
	if (root == NULL) {
		root = (treePos)malloc(sizeof(Tree));
		if (root == NULL) {
			puts("Greska pri alokaciji memorije.");
			return NULL;
		}
		root->value = value;
		root->left = NULL;
		root->right = NULL;
		return root;
	}
	else if (value >= root->value) {
		root->right = insertEl(root->right, value);
	}
	else if (value < root->value) {
		root->left = insertEl(root->left, value);
	}

	return root;
}
int replaceMulti(treePos root) {
	int oldValue = root->value;
	root->value = 0;

	if (root->left == NULL && root->right == NULL) {
		return oldValue;
	}

	if (root->left != NULL) {
		root->value += replaceMulti(root->left);
	}
	if (root->right != NULL) {
		root->value += replaceMulti(root->right);
	}

	return oldValue + root->value;
}
int printInorder(treePos temp) {
	treePos root = temp;
	if (root == NULL) {
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
int saveTree(treePos temp) {
	if (temp == NULL) {
		return EXIT_SUCCESS;
	}
	FILE* fajl = fopen("datoteka.txt", "a");


	if (temp->left != NULL) {
		saveTree(temp->left);
	}

	fprintf(fajl, "%d\n", temp->value);

	if (temp->right != NULL) {
		saveTree(temp->right);
	}

	fclose(fajl);
	return EXIT_SUCCESS;
}
treePos freeTree(treePos root) {
	if (root == NULL) {
		return NULL;
	}

	root->left = freeTree(root->left);
	root->right = freeTree(root->right);

	free(root);
	return NULL;
}