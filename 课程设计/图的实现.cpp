/* Linear Table On Sequence Structure */
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

/*---------page 10 on textbook ---------*/
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2

typedef int status; 
typedef int ElemType; //����Ԫ�����Ͷ���

/*-------page 22 on textbook -------*/
#define MAX_VERTEX_NUM   20
typedef struct ArcNode{  
	ElemType         adjvex;//�û���ָ��Ķ����λ�� 
	struct ArcNode   *nextarc;//ָ����һ����ָ�� 
}ArcNode;
typedef struct VNode{
	ElemType     data;// ͼ�Ķ�����Ϣ 
	ArcNode        *firstarc;// ָ���һ�������ö���Ļ���ָ�� 
}VNode,AdjList[MAX_VERTEX_NUM];//AdjList[MAX_VERTEX_NUM]Ϊ���㼯��
typedef struct{
	AdjList       vertices;//ͼ�Ķ��� 
	ElemType      vexnum,arcnum;//ͼ�ĵ�ǰ�������ͻ��� 
}ALGraph,*Graph;
/*-----page 19 on textbook ---------*/
status CreateCraph(Graph &G);
status DestroyCraph (Graph G);
status LocateVex(Graph G,ElemType u);
//int GetVex (Graph G,v);
//status PutVex (Graph G,v,value);
//status FirstAdjVex(Graph &G, v); //�򻯹�
//status NextAdjVex(Graph &G, v, w);
//status InsertVex(Graph &G,v);
//status DeleteVex(Graph &G,v);
//status InsertArc(Graph &G,v,w);
//status DeleteArc(Graph &G,v,w);  //�򻯹�//
//status DFSTraverse(Graph G,visit());
//status BFSTraverse(Graph G,visit());
// status
/*--------------------------------------------*/
int  main(void){
   Graph G=(Graph)malloc(sizeof(ALGraph)); 
   int op=1;
   ElemType u; 
  while(op){
	system("cls");	printf("\n\n");
	printf("      Menu for graph On Sequence Structure \n");
	printf("-------------------------------------------------\n");
	printf("    	  1. CreateCraph         7. NextAdjVex\n");
	printf("    	  2. DestroyCraph        8. InsertVex\n");
	printf("    	  3. LocateVex           9. DeleteVex \n");
	printf("    	  4. GetVex             10. InsertArc\n");
	printf("    	  5. PutVex             11. DeleteArc\n");
	printf("    	  6. FirstAdjVex        12. DFSTraverse\n");
	printf("    	 13.BFSTraverse          0. Exit\n");
	printf("-------------------------------------------------\n");
	printf("    ��ѡ����Ĳ���[0~13]:");
	scanf("%d",&op);
    switch(op){
    	case 1:
    		if(CreateCraph(G)==OK);
    		printf("�����ɹ�");
			else printf("����ʧ��");
			getchar(); getchar();
			break;
		case 2:{
			
			break;
		}
			
		 

	}//end of switch
  }//end of while
  printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
}//end of main()
//--------page 23 on textbook -------------------

status CreateCraph(Graph &G){
	int i,j,k;
	ArcNode *s;
	printf("���붥�����ͱ�����\n");
	scanf("%d %d",&G->vexnum,&G->arcnum);
	//���������
	for(i=1;i<=G->vexnum;i++){
		G->vertices[i].data=i;
		G->vertices[i].firstarc=NULL;
		
	} 
	//�����߱� 
	for(k=1;k<=G->arcnum;k++){
		printf("������㣺\n");
		scanf("%d %d",&i,&j);
		s = (ArcNode*)malloc(sizeof(ArcNode));
		s->adjvex=j;
		s->nextarc=NULL;
		G->vertices[i].firstarc = s;
		s = (ArcNode*)malloc(sizeof(ArcNode));
		s->adjvex=i;
		s->nextarc=G->vertices[j].firstarc;
		G->vertices[j].firstarc = s;
	} 	
}
status DestroyCraph (Graph G){
	G->arcnum=0;
	G->vexnum=0;
	ArcNode *p,*q;
	int i;
	for(i=1;i<=G->vexnum;i++){
		//�Զ�����б���
		p=G->vertices[i].firstarc;
		G->vertices[i].firstarc=NULL;
		while(p!=NULL){
			q=p->nextarc;
			free(p);
			p=q;
		}
	}
	return OK;
}

status LocateVex(Graph G,ElemType u){
	int i;
	for(i=1;i<=G->vexnum;i++){
		if(G->vertices[i].data == u)return i;
	}
	return ERROR;
}

