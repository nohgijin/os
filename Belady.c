#include <stdio.h>



int hits = 0;
int faluts = 0;
int maxSize;
int read = 0;
int write = 0;
int access = 0;
int size = 0;
int pipe[1001] = { 0, };
int arr[50001];

int when(int page, int current) {
	int i;
	for (i = current + 1; i < access; i++) {
		if (page == arr[i]) return i;
	}
	return i;
}

void hit(int page, int current) {

	if (pipe[page]) {
		hits++;
	}
	else {
		if (size < maxSize) {
			pipe[page] = 1;
			size++;
		}
		else if (size == maxSize) {
			int old = 0;
			int oldPage;
			for (int i = 0; i < 1001; i++) {
				if (pipe[i] == 1) {
					int next = when(i, current);
					if (next > old) {
						old = next;
						oldPage = i;
					}
				}
				if (old == access)break;
			}

			pipe[oldPage] = 0;
			pipe[page] = 1;

		}

	}
}


int main() {


	scanf("%d", &maxSize);

	FILE* fp = fopen("access.list", "r");


	while (1) {
		int page;
		char str[100];
		int state = fscanf(fp, "%d %s", &page, str);
		if (state == EOF) break;
		if (str[0] == 'r') read++;
		if (str[0] == 'w') write++;
		arr[access] = page;
		access++;
	}

	for (int i = 0; i < access; i++) {
		hit(arr[i], i);
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