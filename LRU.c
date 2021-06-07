#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;

struct Node
{
	int page;
	Node *next;
};

Node *head = NULL;
Node *last = NULL;

int hits = 0;
int faluts = 0;
int size;
int read = 0;
int write = 0;
int access = 0;

void hit(int page)
{

	int isExist = 0;

	Node *cur = head;
	Node *bfr = head;

	int i = 0;

	while (cur != NULL)
	{
		if (i == size)
			break;
		if (cur->page == page)
		{
			isExist = 1;
			break;
		}

		bfr = cur;
		cur = cur->next;
		i++;
	}

	if (isExist)
	{
		bfr->next = cur->next;
		hits += 1;
		free(cur);
	}
	else
	{
		faluts += 1;
	}

	Node *node = (Node *)malloc(sizeof(Node));

	node->page = page;
	node->next = head;
	head = node;
}

int main()
{

	scanf("%d", &size);

	FILE *fp = fopen("access.list", "r");

	while (1)
	{
		int page;
		char str[100];
		int state = fscanf(fp, "%d %s", &page, str);
		if (state == EOF)
			break;
		if (str[0] == 'r')
			read++;
		if (str[0] == 'w')
			write++;
		access++;

		hit(page);
	}

	faluts = access - hits;

	double rate = ((double)faluts / access) * 100;

	printf("Total number of access: %d\n", access);
	printf("Total number of read: %d\n", read);
	printf("Total number of write: %d\n", write);
	printf("Number of page hits: %d\n", hits);
	printf("Number of page faults: %d\n", faluts);
	printf("Page fault rate: %d/%d = %.3lf %%", faluts, access, rate);

	return 0;
}