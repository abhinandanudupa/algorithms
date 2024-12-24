#define MAX_N (1000000000)


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "random.h"


struct Node {
	int data;
	struct Node *left, *right, *parent;
};


void in_order(struct Node *root)
{
	if (root == NULL) {
		return;
	} else {
		if (root->left != NULL) {
			in_order(root->left);
		}
		printf("%4d\t", root->data);
		if (root->right != NULL) {
			in_order(root->right);
		}
	}
}

void print_tree(struct Node *root, int depth)
{
	if (root == NULL) {
		return;
	} else {
		if (root->left != NULL) {
			print_tree(root->left, depth + 1);
		}
		for (int i = 1; i <= depth; i++) {
			if (i != depth)
				printf("   |  ");
			else
				printf("   |--->");
		}
		printf("%2d\n", root->data);
		if (root->right != NULL) {
			print_tree(root->right, depth + 1);
		}
	}
}

int add_node(struct Node **root, int data)
{
	if (*root == NULL) {
		struct Node *r = malloc(sizeof(struct Node));
		r->parent = r->left = r->right = NULL;
		r->data = data;
		*root = r;
		return 0;
	}

	if (data < (*root)->data) {
		if ((*root)->left == NULL) {
			struct Node *r = malloc(sizeof(struct Node));
			r->left = r->right = NULL;
			r->data = data;
			r->parent = *root;
			(*root)->left = r;
			return 1;
		} else {
			return add_node(&((*root)->left), data);
		}
	} else {
		if ((*root)->right == NULL) {
			struct Node *r = malloc(sizeof(struct Node));
			r->left = r->right = NULL;
			r->data = data;
			r->parent = *root;
			(*root)->right = r;
			return 2;
		} else {
			return add_node(&((*root)->right), data);
		}
	}
}

struct Node *minimum(struct Node *root)
{
	if (root == NULL) {
		return NULL;
	}
	if (root->left == NULL) {
		return root;
	} else {
		return minimum(root->left);
	}
}

struct Node *maximum(struct Node *root)
{
	if (root == NULL) {
		return NULL;
	}
	if (root->right == NULL) {
		return root;
	} else {
		return maximum(root->right);
	}
}

int remove_node(struct Node **root, int x)
{
	if (*root == NULL) {
		return -1;
	} else if ((*root)->data == x) {
		if ((*root)->left == NULL && (*root)->right == NULL) {
			printf("Both NULL\n");
			struct Node *parent = (*root)->parent;
			struct Node *t = (*root);
			*root = NULL;
			free(t);

			return 1;
		} else if ((*root)->right != NULL && (*root)->left != NULL) {
			struct Node *min = minimum((*root)->right);
			int replacement = min->data;
			min->parent->left = NULL;
			free(min);
			(*root)->data = replacement;

			return 3;
		} else {
			struct Node *parent = (*root)->parent;
			if (parent != NULL) {
				struct Node *t = *root;
				*root = ((*root)->right != NULL) ? (*root)->right : (*root)->left;
				(*root)->parent = parent;
				free(t);

				return 2;
			}
		}
	} else if (x < (*root)->data) {
		remove_node(&((*root)->left), x);
	} else {
		remove_node(&((*root)->right), x);
	}
}

struct Node *search(struct Node *root, int x)
{
	if (root == NULL) {
		return NULL;
	}
	if (root->data == x) {
		return root;
	}
	if (root->left != NULL && root->data > x) {
		return search(root->left, x);
	}
	if (root->right != NULL && root->data < x) {
		return search(root->right, x);
	}

	return NULL;
}

int main() {
	struct Node *p = NULL;
	srand(time(NULL));
	int ret = 0, n = 20, to_delete = 0;
	for (int i = 0; i < n; i++) {
		int k = get_random_int(1, 100);
		if (i == 7) {
			to_delete = k;
			printf("To delete: %d\n", to_delete);
		}
		// int k = -(i + 1);
		add_node(&p, k);
	}
	in_order(p);
	printf("\n");
	print_tree(p, 0);
	remove_node(&p, to_delete);
	printf("After removal:\n");
	in_order(p);
	printf("\n");
	print_tree(p, 0);
	printf("\n");
}

