#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <time.h>

#define RED   "\x1B[31m"
#define RESET "\x1B[0m"
#define DEBUG(...)  do { fprintf(stderr, RED); fprintf(stderr, __VA_ARGS__); } while(0);


struct ucs_result {
	int distance;
	int* path;
};

struct input_graph {
	int * graph;
	int graph_size;
	int path_size;
	int start;
	int end;
};

struct queue {
	size_t cap;
	size_t size;
	int front;
	int* vals;
} queue = { 100, 0, 0, NULL } ;

/**
* Enqueue value into queue
*
* Output:
*   0 if success, else -1
*/
int enqueue(struct queue *q, int val) {
	if (q->vals == NULL) {
		q->vals = malloc(q->cap * sizeof(*q->vals));
	} else if (q->size == q->cap) {
		if (q->cap * 2 < q->cap) {
			fprintf(stderr, "Max queue capacity %ld reahced %s:%d", q->cap, __FILE_NAME__, __LINE__);
			return -1;
		}
		int* t = malloc(q->cap * 2 * sizeof(*q->vals));
		if (t == NULL) {
			fprintf(stderr, "Out of memory %s:%d", __FILE_NAME__, __LINE__);
			return -1;
		}
		// copy to bigger chunk and unwrap
		memcpy(t, q->vals+q->front, (q->cap - q->front) * sizeof(*q->vals));
		memcpy(t + (q->cap - q->front), q->vals, q->front * sizeof(*q->vals));
		free(q->vals);
		q->front = 0;
		q->vals = t;
	}
	q->vals[(q->front + q->size) % q->cap] = val;
	q->size++;
	return 0;
}

int dequeue(struct queue *q) {
	int val = q->vals[q->front];
	q->front++;
	q->size--;
	return val;
}


struct input_graph input() {
	struct input_graph ip;
	scanf("%d", &ip.graph_size);
	scanf("%d %d", &ip.start, &ip.end);
	int a, b, c, mincost = 1;

	scanf("%d", &ip.path_size);
	ip.graph = calloc(ip.graph_size * ip.graph_size , sizeof(*ip.graph));
	for (int i = 0; i < ip.path_size; ++i) {
		scanf("%d %d %d", &a, &b, &c);
		ip.graph[a*ip.graph_size + b] = c;
		if (c < mincost) mincost=c;
	}
	if (mincost < 0) {
		DEBUG("Negative cost detected %d\n", mincost);
		for (int i = 0; i < ip.graph_size * ip.graph_size; ++i) {
			if (ip.graph[i]!=0) {
				ip.graph[i] -= (mincost - 1); // make cost positive number
			}
		}
	}
	return ip;
};


struct ucs_result ucs(struct input_graph *inp) {
	struct ucs_result result;
	int * queue = malloc(inp->graph_size * sizeof(*queue));

	// free
	free(queue);
	return result;
};

int main() {

	struct input_graph inp = input();
	for (int i = 0; i < inp.graph_size; ++i) {
		for (int j = 0; j < inp.graph_size; ++j) {
		DEBUG("%d ", inp.graph[i * inp.graph_size + j]);
		}
		DEBUG("\n");
	}

	struct ucs_result result = ucs(&inp);
	free(inp.graph);
	return 0;
}
