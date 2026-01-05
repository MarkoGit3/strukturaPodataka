#ifndef TEST_H
#define TEST_H

struct _Tree;
typedef struct _Tree* treePos;
typedef struct _Tree {
	int value;
	treePos left;
	treePos right;
}Tree;

treePos insertEl(treePos, int); //a) dio zadatka
int replaceMulti(treePos); //b) dio zadatka
int printInorder(treePos); //ispis u inorder
int saveTree(treePos); //upis stabla u datoteku
treePos freeTree(treePos); //oslobada cijelo stablo

#endif