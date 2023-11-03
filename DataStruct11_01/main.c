#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 50
#define NUM_VERTEX 10
int visited[NUM_VERTEX];
int visited_bfs[NUM_VERTEX];

int stack[NUM_VERTEX];

int top = -1;
void push(int v) {
	if (top == NUM_VERTEX - 1) return;
	top++;
	stack[top] = v;
}
int pop() {
	if (top == -1) {
		printf("stack이 비었습니다.");
	}
	top--;
	return stack[top + 1];
}
void init_stack() {
	top = -1;
}
void init_visited() {
	for (int i = 0; i <= NUM_VERTEX; i++) {
		visited[i] = 0;
		visited_bfs[i] = 0;
	}
}

typedef struct GraphType {
	int n;
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
}GraphType;

void init(GraphType* g) {
	int r = 0;
	int c=0;
	g->n = 0;
	for (r = 0; c < MAX_VERTICES; r++) {
		for (c = 0; c < MAX_VERTICES; c++)
			g->adj_mat[r][c] = 0;
	}
}


void insert_vertex(GraphType* g, int v) {
	if ((g->n) + 1 > MAX_VERTICES) {
		fprintf(stderr, "그래프: 정점의 개수 초과");
		return;
	}
	g->n++;
}

void insert_edge(GraphType* g,int start,int end)
{
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}

	g->adj_mat[start][end] = 1;
	g->adj_mat[end][start] = 1;

}


void DFS(GraphType* g,int start,int end) {
	int i;
	int cur = start;
	int temp = 0;
	int temp1;
	visited[start] = 1;    // 현재 노드 방문 체크 
	printf("\n");
	push(cur);

	while (1) {//도착하면 push하는 방법으로 해보기 
		temp = 0;
		printf(" %d->", cur);
		for (i = 0; i <= g->n; i++) {    // 모든 인접한 노드 체크 g->n
			if (g->adj_mat[cur][i] == 1 && visited[i] == 0) {    // 인접하고 방문하지 않은 노드라면 
				if (end == i) {//찾기로 한 정점과 이어진 간선을 찾으면 
				printf(" %d", end);
					return;
				}
				visited[i] = 1;
			
				cur = i;
				temp = 1;
				temp1 = i;
				break;

			}
			
		}

		if (temp  ==0) {    // 갈수 없는 정점일때		
			int temp2 = pop();
			if (cur != temp2) {//길이없어서 스택에있는것을 빼올때 한번더 출력되는것과 방문횟수가 늘어나는것을 방지
				cur = temp2;
				
			}
		
			
		

		}
		else {
			push(temp1);
		}



		
	}

}


//필요함??
void insert_adj(GraphType* g) {


	for (int i = 0; i < g ->n;i++) {
		for (int r = 0; r < g->n; r++) {
			if (g->adj_mat[i][r] == 1) {
				push(r);//i에 인접한 정점을 모두 스택에 
			}

		}
	}

}


void print_adj(GraphType* g) {
	int r = 0;
	int c = 0;

	for (r = 0; r < g->n; r++) {//g->n 은 11까지 
	
			printf(" [%d] 인접:", r);

		
	
		for (c = 0; c < g->n; c++) {
			if (g->adj_mat[r][c] == 1) {
	
				printf(" %d", c);
			
			}
		}
		printf("\n");
			

	}
}

int DFS_1(GraphType *g,int cur) {
	int i;
	visited[cur] = 1;    // 현재 노드 방문 체크 
	printf(" %d ->",cur);
	for (i = 0; i <= g->n; i++) {    // 모든 인접한 노드 체크 
		if (g->adj_mat[cur][i] == 1 && visited[i] == 0) {    // 인접하고 방문하지 않은 노드라면 
			
			DFS_1(g,i);
		
		}
	}
}

//queue --------------------------------------
typedef int element;
int  front, rear;
element  queue[MAX_VERTICES + 2];

void init_queue()
{
	front = rear = 0;
}

int is_empty()
{
	return (front == rear);
}

void enqueue(element item)
{
	rear++;
	queue[rear] = item;
}

element dequeue()
{
	front++;
	return queue[front];
}

// BFS 이해가 쉽게 인접 행렬로 구현
void bfs_list(GraphType *g,int v,int end)
{
	int w;
	init_queue();
	visited_bfs[v] = 1;
	printf("%d ->", v);
	enqueue(v);

	while (!is_empty()) {

		v = dequeue();
		for (w = 0; w < g->n; w++) {
		
			if (g->adj_mat[v][w] == 1 && !visited_bfs[w]) {
			
				visited_bfs[w] = 1;
				
				if (end ==w) {//마지막 노드를 찾으면 반환함 
					printf(" %d", w);
					return;
				}
				else {
					printf(" %d ->", w);
				}
				enqueue(w);
			}
		}
	}
}


//---------------------------------------------
void start(GraphType* g) {
	int sel,start,end;
	printf("\n");
	printf("메뉴 입력:");
	scanf_s("%d", &sel);





	switch (sel) {
	case 1:
		printf("시작값과 탐색할 값입력:");
		scanf_s("%d %d", &start, &end);
		DFS(g,start,end);
		break;
	case 2:
		printf("시작값과 탐색할 값입력:");
		scanf_s("%d %d", &start, &end);
		bfs_list(g, start, end);
		break;
	case 3:
		exit(1);
		break;
	}
}


void main() {
	GraphType* g;
	int sel=0;
	g = (GraphType*)malloc(sizeof(GraphType));
	init(g);

	for (int i = 0; i <= 10; i++) {
		insert_vertex(g, i);
	}


	insert_edge(g, 0, 6);
	insert_edge(g, 0, 2);
	insert_edge(g, 0, 5);
	insert_edge(g, 0, 9);
	insert_edge(g, 0, 4);


	insert_edge(g, 1, 5);
	insert_edge(g, 1, 4);
	insert_edge(g, 1, 7);
	insert_edge(g, 1, 10);

	insert_edge(g, 2, 0);
	insert_edge(g, 2, 3);
	insert_edge(g, 2, 4);

	insert_edge(g, 3, 5);
	insert_edge(g, 3, 2);
	insert_edge(g, 3, 4);

	insert_edge(g, 4, 0);
	insert_edge(g, 4, 2);
	insert_edge(g, 4, 3);
	insert_edge(g, 4, 5);
	insert_edge(g, 4, 1);
	insert_edge(g, 4, 7);
	insert_edge(g, 4, 6);

	insert_edge(g, 5, 0);
	insert_edge(g, 5, 3);
	insert_edge(g, 5, 4);
	insert_edge(g, 5, 1);

	insert_edge(g, 6, 0);
	insert_edge(g, 6, 4);
	insert_edge(g, 6, 7);
	insert_edge(g, 6, 8);

	insert_edge(g, 7, 4);
	insert_edge(g, 7, 6);
	insert_edge(g, 7, 1);
	insert_edge(g, 7, 10);

	insert_edge(g, 8, 9);
	insert_edge(g, 8, 6);
	insert_edge(g, 8, 10);

	insert_edge(g, 9, 8);
	insert_edge(g, 9, 0);

	insert_edge(g, 9, 8);
	insert_edge(g, 9, 0);


	insert_edge(g, 10, 7);
	insert_edge(g, 10, 1);
	insert_edge(g, 10, 8);



	//print_adj(g);




	printf("------------------------------------\n");
	printf("1	:깊이 우선 탐색		    |\n");
	printf("2	:너비 우선 탐색		    |\n");
	printf("3	:종료		            |\n");
	printf("------------------------------------\n");



	printf("\n");
	while (1) {
		init_stack();
		init_visited();
		start(g);
	}
	




}

