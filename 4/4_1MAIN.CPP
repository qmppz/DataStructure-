#include "Queue.h"
 
#define MAXVEX  1000     //��󶥵���
typedef int Boolean;            //Boolean �ǲ������ͣ���ֵ��TRUE ��FALSE
bool visited[MAXVEX];        //���ʱ�־����
#define TRUE 1
#define FALSE 0

#define DEBUG
#define MAXVEX 1000         //��󶥵���
typedef char VertexType;        //��������Ӧ���û�����
typedef int EdgeType;           //���ϵ�Ȩֵ����Ӧ���û�����
 
//�ڽӱ� ����ṹ
typedef struct EdgeNode         //�߱����
{
    int adjvex;         //�ڽӵ��򣬴洢�ö����Ӧ���±�
   // EdgeType weigth;        //���ڴ洢Ȩֵ�����ڷ���ͼ���Բ���Ҫ
    struct EdgeNode *next;      //����ָ����һ���ڽӵ�
}EdgeNode;
 
typedef struct VertexNode       //������ṹ
{
    VertexType data;        //�����򣬴洢������Ϣ
    EdgeNode *firstedge;        //�߱�ͷָ��
}VertexNode, AdjList[MAXVEX];
 
typedef struct
{
    AdjList adjList;
    int numVertexes, numEdges;  //ͼ�е�ǰ�������ͱ���
}GraphList;
 
 
//����λ�� ���㼯g->adjList[]�������±�
int Locate(GraphList *g, char ch)
{
    int i;
    for(i = 0; i < MAXVEX; i++)
    {
        if(ch == g->adjList[i].data)
        {
            break;
        }
    }
    if(i >= MAXVEX)
    {
        fprintf(stderr,"there is no vertex.\n");
        return -1;
    }
    return i;
}
 
//����ͼ�� �ڽӱ��ṹ
void CreateGraph(GraphList *g)
{
    int i, k;
    EdgeNode *e;
    EdgeNode *f;
    printf("���붥�����ͱ���:\n");
    scanf("%d %d", &g->numVertexes, &g->numEdges);
     
    #ifdef DEBUG
    printf("%d,%d\n", g->numVertexes, g->numEdges);
    #endif
     
    for(i = 0; i < g->numVertexes; i++)
    {
        printf("�����붥��%d:\n", i);
        g->adjList[i].data = getchar();          //���붥����Ϣ
        g->adjList[i].firstedge = NULL;          //���߱���Ϊ�ձ�
        while(g->adjList[i].data == '\n')
        {
            g->adjList[i].data = getchar();
        }
    }
	//add
	g->adjList[i].firstedge = NULL;

    //�����߱�
    for(k = 0; k < g->numEdges; k++)
    {
        printf("�����(vi,vj)�ϵĶ������:\n");
        char p, q;
        p = getchar();
        while(p == '\n')
        {
            p = getchar();
        }
        q = getchar();
        while(q == '\n')
        {
            q = getchar();
        }
        int m, n;
        m = Locate(g, p);
        n = Locate(g, q);
        if(m == -1 || n == -1)
        {
            return;
        }
        #ifdef DEBUG
        printf("p = %c\n", p);
        printf("q = %c\n", q);
        printf("m = %d\n", m);
        printf("n = %d\n", n);
        #endif
     
        //���ڴ�����ռ䣬���ɱ߱����
        e = (EdgeNode *)malloc(sizeof(EdgeNode));
        if(e == NULL)
        {
            fprintf(stderr, "malloc() error.\n");
            return;
        }
        //�ڽ����Ϊj
        e->adjvex = n;
        //��eָ��ָ��ǰ����ָ��Ľṹ
        e->next = g->adjList[m].firstedge;
        //����ǰ�����ָ��ָ��e
        g->adjList[m].firstedge = e;
         
        f = (EdgeNode *)malloc(sizeof(EdgeNode));
        if(f == NULL)
        {
            fprintf(stderr, "malloc() error.\n");
            return;
        }
        f->adjvex = m;
        f->next = g->adjList[n].firstedge;
        g->adjList[n].firstedge = f;
    }
}
 

//ͼ �ļ����
void printGraph(GraphList *g)
{
    int i = 0;
    #ifdef DEBUG
    printf("printGraph() start.\n");
    #endif
     
    while(g->adjList[i].firstedge != NULL && i < MAXVEX)
    {
        printf("����:%c  ", g->adjList[i].data);
        EdgeNode *e = NULL;
        e = g->adjList[i].firstedge;
        while(e != NULL)
        {
            printf("%d  ", e->adjvex);
            e = e->next;
        }
        i++;
        printf("\n");
    }
}
 
// ������ȱ��� DFS
//�ڽӱ�����ȵݹ��㷨
void DFS(GraphList *g, int i)
{
    EdgeNode *p;
 
    visited[i] = TRUE;
    printf("%c ", g->adjList[i].data);   //��ӡ���㣬Ҳ������������
    p = g->adjList[i].firstedge;
    while(p)
    {
        if(!visited[p->adjvex])
        {
            DFS(g, p->adjvex);           //�Է��ʵ��ڽӶ���ݹ����
        }
        p = p->next;
    }
}
 
//�ڽӱ�����ȱ�������
void DFSTraverse(GraphList g)
{
    int i;
    for(i = 0; i < g.numVertexes; i++)
    {
        visited[i] = FALSE;
    }
    for(i = 0; i < g.numVertexes; i++)
    {
        if(!visited[i])
        {
            DFS(&g, i);
        }
    }
	printf("/*DFS��������*/\n");
}
//DFS end


//
//
void BFSTraverse(GraphList g)
{
    int i;
    EdgeNode *p;
    Queue q;
    for(i = 0; i < g.numVertexes; i++)
    {
        visited[i] = FALSE;
    }
    
	InitQueue(&q);
    for(i = 0; i < g.numVertexes; i++)
    {
        if(!visited[i])
        {
            visited[i] = TRUE;
            printf("%c ", g.adjList[i].data);   //��ӡ���㣬Ҳ������������
            EnQueue(&q, i);
            while(!QueueEmpty(q))
            {
                int m;
                DeQueue(&q, &m);
                p = g.adjList[m].firstedge;     //�ҵ���ǰ����߱�����ͷָ��
                while(p)
                {
                    if(!visited[p->adjvex])
                    {
                        visited[p->adjvex] = TRUE;
                        printf("%c ", g.adjList[p->adjvex].data);
                        EnQueue(&q, p->adjvex);
                    }
                    p = p->next;
                }
            }
        }
    }
}
//BFS end


 

int main(int argc, char **argv)
{
    GraphList g;
    CreateGraph(&g);
    printGraph(&g);
	
	//DFS
	printf("/*DFS���Դ�����:*/\n");
	DFSTraverse(g);
	
	//BFS
	printf("/*BFS���Դ�����:*/\n");
	BFSTraverse(g);

    return 0;
}