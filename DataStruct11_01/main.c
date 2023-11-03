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
		printf("stack�� ������ϴ�.");
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
		fprintf(stderr, "�׷���: ������ ���� �ʰ�");
		return;
	}
	g->n++;
}

void insert_edge(GraphType* g,int start,int end)
{
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "�׷���: ���� ��ȣ ����");
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
	visited[start] = 1;    // ���� ��� �湮 üũ 
	printf("\n");
	push(cur);

	while (1) {//�����ϸ� push�ϴ� ������� �غ��� 
		temp = 0;
		printf(" %d->", cur);
		for (i = 0; i <= g->n; i++) {    // ��� ������ ��� üũ g->n
			if (g->adj_mat[cur][i] == 1 && visited[i] == 0) {    // �����ϰ� �湮���� ���� ����� 
				if (end == i) {//ã��� �� ������ �̾��� ������ ã���� 
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

		if (temp  ==0) {    // ���� ���� �����϶�		
			int temp2 = pop();
			if (cur != temp2) {//���̾�� ���ÿ��ִ°��� ���ö� �ѹ��� ��µǴ°Ͱ� �湮Ƚ���� �þ�°��� ����
				cur = temp2;
				
			}
		
			
		

		}
		else {
			push(temp1);
		}



		
	}

}


//�ʿ���??
void insert_adj(GraphType* g) {


	for (int i = 0; i < g ->n;i++) {
		for (int r = 0; r < g->n; r++) {
			if (g->adj_mat[i][r] == 1) {
				push(r);//i�� ������ ������ ��� ���ÿ� 
			}

		}
	}

}


void print_adj(GraphType* g) {
	int r = 0;
	int c = 0;

	for (r = 0; r < g->n; r++) {//g->n �� 11���� 
	
			printf(" [%d] ����:", r);

		
	
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
	visited[cur] = 1;    // ���� ��� �湮 üũ 
	printf(" %d ->",cur);
	for (i = 0; i <= g->n; i++) {    // ��� ������ ��� üũ 
		if (g->adj_mat[cur][i] == 1 && visited[i] == 0) {    // �����ϰ� �湮���� ���� ����� 
			
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

// BFS ���ذ� ���� ���� ��ķ� ����
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
				
				if (end ==w) {//������ ��带 ã���� ��ȯ�� 
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
	printf("�޴� �Է�:");
	scanf_s("%d", &sel);





	switch (sel) {
	case 1:
		printf("���۰��� Ž���� ���Է�:");
		scanf_s("%d %d", &start, &end);
		DFS(g,start,end);
		break;
	case 2:
		printf("���۰��� Ž���� ���Է�:");
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
	printf("1	:���� �켱 Ž��		    |\n");
	printf("2	:�ʺ� �켱 Ž��		    |\n");
	printf("3	:����		            |\n");
	printf("------------------------------------\n");



	printf("\n");
	while (1) {
		init_stack();
		init_visited();
		start(g);
	}
	




}

