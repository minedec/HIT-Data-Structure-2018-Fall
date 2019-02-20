/*
/*姓名：
/*学号：1163450201
/*实验名称：图型结构的建立与搜索
*/
#include <stdio.h>
#include <limits.h>

#define INFINITY INT_MAX
#define MAX_NUM 20
#define old 1
#define new 0
#define true 1
#define false 0

int visited[MAX_NUM];
int dfn[MAX_NUM];
int bfn[MAX_NUM];
int cnt;    /*遍历编号*/

typedef struct Queue
{
    int queue[MAX_NUM];
    int front;
    int rear;
}Queue;

typedef enum{DG,AG} GraphKind;  /*定义图种类*/

typedef struct ArcCell
{
    int adj;   /*标记两点是否有边*/
    int info;  /*权值*/

}ArcCell , AdjMatrix[MAX_NUM][MAX_NUM];

typedef struct Mgraph
{
    char element[MAX_NUM];  /*保存顶点信息*/
    AdjMatrix arcs;     /*邻接关系*/
    int vexnum, arcnum;
    GraphKind kind;
}MGraph;

typedef struct ArcNode
{
    int adjvex;  /*标记该点的下标*/
    struct ArcNode * next;
    int info;  /*权值*/
}ArcNode;

typedef struct Vnode  /*定义头节点*/
{
    char element;
    ArcNode * firstnode;
}Vnode, AdjList[MAX_NUM];

typedef struct ALGraph
{
    AdjList vertices;  /*定义头结点列表*/
    int vexnum,arcnum;
    GraphKind kind;
}ALGraph;

void init()
{
    int i;
    for(i = 0 ; i < MAX_NUM; i++)
    {
        visited[i] = new;
        dfn[i] = -1;
        bfn[i] = -1;
    }
    cnt = 1;
}

void build_Mgraph(FILE * fp, MGraph * mgraph)
{
    int i, j, x, y;
    fscanf(fp, " %d %d", &mgraph->vexnum, &mgraph->arcnum);
    for(i = 0; i < mgraph->vexnum; i++)
    {
        fscanf(fp, " %c", &mgraph->element[i]);
    }
    for(i = 0; i < mgraph->vexnum; i++)
    {
        for(j = 0; j < mgraph->vexnum; j++)
        {
            mgraph->arcs[i][j].adj = 0;  /*邻接矩阵初始化*/
        }
    }
    for(i = 0; i < mgraph->arcnum; i++)
    {
        fscanf(fp, " %d %d", &x, &y);   /*无向图输入边*/
        mgraph->arcs[x][y].adj = 1;
        mgraph->arcs[y][x].adj = 1;
    }
}

void show_Mgraph(MGraph * mgraph)
{
    int i, j;
    for(i = 0; i < mgraph->vexnum; i++)
    {
        for(j = 0; j < mgraph->vexnum; j++)
        {
            printf("%d ", mgraph->arcs[i][j].adj);
        }
        printf("\n");
    }
}

/*邻接矩阵的递归DFS*/
void Mgraph_DFS_cur(MGraph * mgraph, int i)
{
    int j;
    printf("%c", mgraph->element[i]);
    dfn[i] = cnt++;
    printf("(%d) ", dfn[i]);
    visited[i] = old;
    for(j = 0; j < mgraph->vexnum; j++)
    {
        if(mgraph->arcs[i][j].adj == 1 && visited[j] == new)
        {
            Mgraph_DFS_cur(mgraph, j);
        }
    }
}

/*邻接矩阵的非递归DFS*/
void Mgraph_DFS_nocur(MGraph * mgraph,int i)
{
    int stack[MAX_NUM];
    int top = 0;
    int v = i;
    int j;
    stack[++top] = v;
    while(top != 0)
    {
        v = stack[top--];
        if(!visited[v])
        {
            dfn[v] = cnt++;
            printf("%c(%d) ", mgraph->element[v], dfn[v]);
            visited[v] = old;
        }
        for(j = mgraph->vexnum - 1; j >= 0; j--)
        {
            if(mgraph->arcs[v][j].adj == 1 && visited[j] == new)
            {
                stack[++top] = j;
            }
        }
    }
}

/*邻接矩阵的BFS*/
void Mgraph_BFS(MGraph * mgraph, int i)
{
    Queue Q;
    int v, j;
    Q.front = 0;
    Q.rear = 0;
    Q.queue[Q.rear++] = i;
    visited[i] = old;
    while(Q.front < Q.rear)
    {
        v = Q.queue[Q.front++];
        bfn[v] = cnt++;
        printf("%c(%d) ", mgraph->element[v], bfn[v]);
        for(j = 0; j < mgraph->vexnum; j++)
        {
            if(mgraph->arcs[v][j].adj && visited[j] == new)
            {
                Q.queue[Q.rear++] = j;
                visited[j] = old;
            }
        }
    }
}

/*邻接矩阵转化邻接表*/
void Mgraph_convertto_ALgraph(MGraph * mgraph, ALGraph * algraph)
{
    int i, j, k, x, y;
    ArcNode * p;
    ArcNode * t;
    algraph->vexnum = mgraph->vexnum;
    algraph->arcnum = mgraph->arcnum;
    for(i = 0; i < algraph->vexnum; i++)
    {
        algraph->vertices[i].element = mgraph->element[i];
        algraph->vertices[i].firstnode = NULL;
    }
    for(x = 0; x < algraph->vexnum; x++)
    {
        for(y = x ; y < algraph->vexnum; y++)
        {
            if(mgraph->arcs[x][y].adj == 1)  /*如果x y 有边*/
            {
                p = algraph->vertices[x].firstnode;
                while(p != NULL)
                {
                    t = p;
                    p = p->next;
                }
                p = (ArcNode *)malloc(sizeof(ArcNode));  /*申请结点*/
                p->adjvex = y;
                p->next = NULL;
                if(algraph->vertices[x].firstnode == NULL)  /*判断是否头指针为空*/
                {
                    algraph->vertices[x].firstnode = p;  /*插入到头指针处*/
                }
                else
                {
                    t->next = p;  /*否则插入到结点next指针处*/
                }

                p = algraph->vertices[y].firstnode;
                while(p != NULL)
                {
                    t = p;
                    p = p->next;
                }
                p = (ArcNode *)malloc(sizeof(ArcNode));
                p->adjvex = x;
                p->next = NULL;
                if(algraph->vertices[y].firstnode == NULL)
                {
                    algraph->vertices[y].firstnode = p;
                }
                else
                {
                    t->next = p;
                }
            }

        }

    }
}

void build_ALgraph(FILE * fp, ALGraph * algraph)
{
    int i, j, x, y;
    ArcNode * p;
    ArcNode * t;
    fscanf(fp, " %d %d", &algraph->vexnum, &algraph->arcnum);
    for(i = 0; i < algraph->vexnum; i++)
    {
        fscanf(fp, " %c", &algraph->vertices[i].element);
        algraph->vertices[i].firstnode = NULL;
    }
    for(i = 0; i < algraph->arcnum; i++)
    {
        fscanf(fp, " %d %d", &x , &y);
        p = algraph->vertices[x].firstnode;
        while(p != NULL)
        {
            t = p;
            p = p->next;
        }
        p = (ArcNode *)malloc(sizeof(ArcNode));
        p->adjvex = y;
        p->next = NULL;
        if(algraph->vertices[x].firstnode == NULL)
        {
            algraph->vertices[x].firstnode = p;
        }
        else
        {
            t->next = p;
        }
        
        p = algraph->vertices[y].firstnode;
        while(p != NULL)
        {
            t = p;
            p = p->next;
        }
        p = (ArcNode *)malloc(sizeof(ArcNode));
        p->adjvex = x;
        p->next = NULL;
        if(algraph->vertices[y].firstnode == NULL)
        {
            algraph->vertices[y].firstnode = p;
        }
        else
        {
            t->next = p;
        }
    }
}

void show_ALgraph(ALGraph * algraph)
{
    int i;
    ArcNode * p;
    for(i = 0; i < algraph->vexnum; i++)
    {
        printf("%c", algraph->vertices[i].element);
        p = algraph->vertices[i].firstnode;
        while(p != NULL)
        {
            printf("->%c", algraph->vertices[p->adjvex].element);
            p = p->next;
        }
        printf("\n");
    }
}

/*邻接表的递归DFS*/
void ALgraph_DFS_cur(ALGraph * algraph, int i)
{
    ArcNode * p;
    dfn[i] = cnt++;
    printf("%c(%d) ", algraph->vertices[i].element, dfn[i]);
    visited[i] = old;
    p = algraph->vertices[i].firstnode;
    while(p != NULL)
    {
        if(visited[p->adjvex] == new)
        {
            ALgraph_DFS_cur(algraph, p->adjvex);
        }
        p = p->next;
    }
}

/*邻接表的非递归DFS*/
void ALgraph_DFS_nocur(ALGraph * algraph, int i)
{
    int stack[MAX_NUM];
    int top = 0;
    ArcNode * p;
    int v, j;
    stack[++top] = i;
    while(top != 0)
    {
        v = stack[top--];
        if(!visited[v])
        {
            dfn[v] = cnt++;
            printf("%c(%d) ", algraph->vertices[v].element, dfn[v]);
            visited[v] = old;
        }
        for(p = algraph->vertices[v].firstnode; p != NULL; p = p->next)
        {
            if(visited[p->adjvex] == new)
            {
                stack[++top] = p->adjvex;

            }
        }
    }
}

/*邻接表的BFS*/
void ALgraph_BFS(ALGraph * algraph, int i)
{
    Queue Q;
    ArcNode * p;
    int v, j;
    Q.front = 0;
    Q.rear = 0;
    Q.queue[Q.rear++] = i;
    visited[i] = old;
    while(Q.rear > Q.front)
    {
        v = Q.queue[Q.front++];
        bfn[v] = cnt++;
        printf("%c(%d) ", algraph->vertices[v].element, bfn[v]);
        p = algraph->vertices[v].firstnode;
        while(p != NULL)
        {
            if(visited[p->adjvex] == new)
            {
                Q.queue[Q.rear++] = p->adjvex;
                visited[p->adjvex] = old;
            }
            p = p->next;
        }
    }

}

/*邻接表转为邻接矩阵*/
void ALgraph_convertto_Mgraph(MGraph * mgraph , ALGraph * algraph)
{
    int i, j, x, y;
    ArcNode * p;
    mgraph->vexnum = algraph->vexnum; mgraph->arcnum = algraph->vexnum;
    for(i = 0; i < mgraph->vexnum; i++)
    {
        mgraph->element[i] = algraph->vertices[i].element;
    }
    for(i = 0; i < mgraph->vexnum; i++)
    {
        for(j = 0; j < mgraph->vexnum; j++)
        {
            mgraph->arcs[i][j].adj = 0;  /*邻接矩阵初始化*/
        }
    }

        for(x = 0 ; x < mgraph->vexnum; x ++)   /*无向图输入边*/
        {
            p = algraph->vertices[x].firstnode;
            while(p != NULL)
            {
                y = p->adjvex;
                mgraph->arcs[x][y].adj = 1;
                mgraph->arcs[y][x].adj = 1;
                p = p->next;
            }
        }

}

void menu()
{
    FILE * fp;
    char op;
    int i,t = 1;
    MGraph mgraph;
    ALGraph algraph;
    mgraph.kind = DG;
    algraph.kind = DG;
    while(t)
    {
        t = 0;
        printf("\n===================================="
           "\n1.file input build adjacency matrix"
           "\n  ->show the matrix"
           "\n  ->show DFS and BFS path and number"
           "\n  ->show the list come from matrix\n"
           "\n2.file input build adjacency list"
           "\n  ->show the list"
           "\n  ->show DFS and BFS path and number"
           "\n  ->show the matrix come from list"
           "\n====================================\n");
        fflush(stdin);
        op = getchar();
        switch(op)
        {
            case '1':
            {
                if((fp = fopen("graph.txt","rt")) == NULL)
                {
                    printf("File not exist\n");
                    getchar();
                    break;
                }
                build_Mgraph(fp, &mgraph);
                printf("THE MATRIX\n");
                show_Mgraph(&mgraph);
                init();
                printf("\nND matrix DFS(recursion):");
                for(i = 0; i < mgraph.vexnum; i++)
                {
                    if(visited[i] == new)
                    {
                        Mgraph_DFS_cur(&mgraph, i);
                    }
                }
                printf("\nND matrix DFS(non-recursion):");
                init();
                for(i = 0; i < mgraph.vexnum; i++)
                {
                    if(visited[i] == new)
                    {
                        Mgraph_DFS_nocur(&mgraph, i);
                    }
                }
                printf("\nND matrix BFS:");
                init();
                for(i = 0; i < mgraph.vexnum; i++)
                {
                    if(visited[i] == new)
                    {
                        Mgraph_BFS(&mgraph, i);
                    }
                }
                //algraph = malloc(sizeof(ALGraph));
                //algraph.kind = DG;
                Mgraph_convertto_ALgraph(&mgraph, &algraph);
                printf("\n\nTHE LIST:\n");
                show_ALgraph(&algraph);
                fclose(fp);
                break;
            }
            case '2':
            {
                if((fp = fopen("graph.txt","rt")) == NULL)
                {
                    printf("File not exist\n");
                    getchar();
                    break;
                }
                build_ALgraph(fp, &algraph);
                printf("THE LIST:\n");
                show_ALgraph(&algraph);
                init();
                printf("\nND list DFS(recursion):");
                for(i = 0; i < algraph.vexnum; i++)
                {
                    if(visited[i] == new)
                    {
                        ALgraph_DFS_cur(&algraph, i);
                    }
                }
                init();
                printf("\nND list DFS(non-recursion):");
                for(i = 0; i < algraph.vexnum; i++)
                {
                    if(visited[i] == new)
                    {
                        ALgraph_DFS_nocur(&algraph, i);
                    }
                }
                init();
                printf("\nND list BFS:");
                for(i = 0; i < algraph.vexnum; i++)
                {
                    if(visited[i] == new)
                    {
                        ALgraph_BFS(&algraph, i);
                    }
                }
                printf("\n\nTHE MATRIX:\n");
                ALgraph_convertto_Mgraph(&mgraph, &algraph);
                show_Mgraph(&mgraph);
                break;
            }
            default:
            {

            }
        }
    }
}
int main()
{
    menu();
    return 0 ;
}
