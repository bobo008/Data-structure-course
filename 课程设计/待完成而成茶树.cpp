/* Linear Table On Sequence Structure */
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

/*---------page 10 on textbook ---------*/
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define LH +1 //���
#define EH 0 //�ȸ�
#define RH -1 //�Ҹ�
typedef int status;
typedef int ElemType; //����Ԫ�����Ͷ���
/*-------page 22 on textbook -------*/
#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef struct {
	ElemType id;
	char name[10];
	struct BSTNode *friends;
	struct BSTNode *fans;
	struct BSTNode *attention;
	struct BSTNode *hobby;
}DataNode;

typedef struct BSTNode {
	DataNode data;
	int bf; //����ƽ������
	struct BSTNode *lchild;//����ָ��
	struct BSTNode *rchild;//�Һ���ָ��
}BSTNode, *BSTree;

int quanju = 0, quanju1 = 1;
 
/*-----page 19 on textbook ---------*/
status set_init(BSTree &T);//��ʼ��AVL��
status set_destroy(BSTree &T);//����AVL��

status R_Rotate(BSTree &T);//��������������������
status L_Rotate(BSTree &T);//��������������������
status LeftBalance(BSTree &T); //����������ƽ����ת����
status RightBalance(BSTree &T);//����������ƽ����ת����
bool set_insert(BSTree &T, DataNode &e, bool &taller);//������e
bool set_remove(BSTree &T, int id, bool &shorter);//ɾ��ƽ���������ָ�����

status set_difference(BSTree &T, BSTree T1);//����ƽ�����������T������
status set_intersection(BSTree &T, BSTree T1);//����ƽ��������󽻣���T������
status set_union(BSTree &T, BSTree T1);//����ƽ��������󲢣���T������
status set_size(BSTree T);//��ƽ��������ĳ�Ա����
status set_equal(BSTree T, BSTree T1);//�ж�����ƽ��������Ƿ����
BSTree set_member(BSTree T, int id);//�ж�Ԫ���Ƿ�Ϊ���ϳ�Ա�Ĳ��ң�����ָ��
status InOrderTraverse(BSTree T);//ǰ�����ƽ�������
status PreOrderTraverse(BSTree T);
status PosOrderTraverse(BSTree T);
status Visit(BSTree T);//���������Ľ�����
status Visit1(BSTree T);//���������Ľ�����
status set_subset(BSTree T, BSTree T1) ;//�ж�����ƽ��������Ƿ�Ϊ�Ӽ� 
status set(BSTree &G,int i);
status set1(BSTree &G,int i); 

status SaveBSTree1(FILE *fp, BSTree T, char *filename);//�ļ��洢���������ڴ洢�ڶ��׵�ƽ�������
status SaveBSTree(FILE *fp, BSTree T);//�ļ��洢���������ڴ洢��һ�׵�ƽ�������
status LoadBStree(BSTree &T, char *filename);//�ļ���ȡ���������ڶ�ȡ��һ�׵�ƽ�������
status Load(BSTree &T, char *filename, int i);//�ļ���ȡ���������ڶ�ȡ�ڶ��׵�ƽ�������
status Save(FILE *fp, char *filename);//�ı��洢���������ڴ洢�ڶ��׵�ƽ���������ʱ��������
status clear(char *filename);//�ı��������
status LoadBStree1(BSTree &T, char *filename);//�ļ���ȡ���������ڶ�ȡ��һ�׵�ƽ�������
void level(BSTree T, int h);
status LevelOrderTraverse(BSTree T);
status BiTreeDepth(BSTree T);
int  main() {
	BSTree T = NULL, T1 = NULL;//ƽ�������T 
	int op = 1; 
	bool taller = false;//����ֵtaller�������ʼֵΪfalse 
	bool shorter = false;//����ֵshorter�������ʼֵΪfalse 
	int i;
	int e;
	FILE  *fp;//�ļ�ָ�� 
	while (op) {
		system("cls");	printf("\n\n");
		printf("      Menu for Linear Table On Sequence Structure \n");
		printf("-------------------------------------------------\n");
		printf("    	  1. set_init          2. set_destroy \n");
		printf("    	  3. set_insert        4. set_remove\n");
		printf("    	  5. set_intersection  6. set_union\n");
		printf("    	  7. set_difference    8. set_size\n");
		printf("    	  9. set_member       10. set_subset\n");
		printf("    	 11. set_equal        12. InOrderTraverse\n");
		printf("    	 13. com_att          14. com_hob\n");
		printf("    	 15. com_fri          16. SaveBSTree\n");
		printf("    	 17. LoadBStree       18. PreOrderTraverse\n");
		printf("    	 19. PosOrderTraverse 20. LevelOrderTraverse\n");
		printf("-------------------------------------------------\n");
		printf("    ��ѡ����Ĳ���[0~20]:");
		scanf("%d", &op);
		switch (op) {
		case 1:
			if (set_init(T) == OK)printf("��ʼ���ɹ�\n");//�����������ɹ�
			else printf("��ʼ��ʧ��");//����������ʧ��
			getchar(); getchar();
			break;
		case 2:
			if (set_destroy(T) == ERROR)printf("�����ڶ�����");//��������������� 
			else printf("���ٳɹ�");//���ٳɹ� 
			getchar(); getchar();
			break;
		case 3:
		{
			DataNode q;
			q.attention = NULL;
			q.fans = NULL;
			q.friends = NULL;
			q.hobby = NULL;
			int i;
			printf("��������Ҫ�����id��");//������Ҫ�����id 
			scanf("%d", &q.id);
			printf("��������Ҫ�����������");//������Ҫ�����id 
			scanf("%s", q.name);
			
			printf("����������Ҫ����ĳ�Ա�Ĺ�ע����") ;
			scanf("%d",&i);
			getchar();
			set(q.attention,i); 
			rewind(stdin);
			
			printf("����������Ҫ����ĳ�Ա�ķ�˿����") ;
			scanf("%d",&i);
			getchar();
			set(q.fans,i);
			rewind(stdin);
			
			printf("����������Ҫ����ĳ�Ա����������") ;
			scanf("%d",&i);
			getchar();
			set(q.friends,i);
			rewind(stdin);
			
			printf("����������Ҫ����ĳ�Ա�İ�������") ;
			scanf("%d",&i);
			set1(q.hobby,i);
			rewind(stdin);
			
			//q.attention = NULL;
			//q.fans = NULL;
            //q.friends = NULL;
			//q.hobby = NULL;
			if (set_insert(T, q, taller)) {
				printf("����ɹ�");//����ɹ� 
			}
			else printf("����ʧ��");//����ʧ�� 
			getchar(); getchar();
			break;

		}
		case 4:
		{
			printf("��������Ҫɾ����id��");//������Ҫɾ����id
			scanf("%d", &i);
			if (set_remove(T, i, shorter)) {
				printf("ɾ���ɹ�");//ɾ���ɹ� 
			}
			else printf("ɾ��ʧ��");//ɾ��ʧ�� 
			getchar(); getchar();
			break;
		}
		case 5: 
		{
			set_destroy(T1);
			char filename[10];
			printf("�������ȡ���ı�����");
			scanf("%s",filename);
			LoadBStree1(T1, filename); 
			set_intersection(T1, T);//�����ߵĽ��� 
			printf("�����󽻱������£�\n");
			quanju1 = 1;
			InOrderTraverse(T1);//�����֮��ı������� 
			getchar(); getchar();
			break;
		}
		case 6: 
		{
			set_destroy(T1);
			char filename[10];
			printf("�������ȡ���ı�����");
			scanf("%s",filename);
			LoadBStree1(T1, filename);
			set_union(T1, T);//�����ߵĲ��� 
			printf("�����󲢱������£�\n");
			quanju1 = 1;
			InOrderTraverse(T1);//�����֮��ı������� 
			getchar(); getchar();
			break;
		}
		case 7: 
		{
			set_destroy(T1);
			char filename[10];
			printf("�������ȡ���ı�����");
			scanf("%s",filename);
			LoadBStree1(T1, filename);
			set_difference(T1, T);//�����ߵĲ 
			printf("�������������£�\n");
			quanju1 = 1;
			InOrderTraverse(T1);//������֮��ı������� 
			getchar(); getchar();
			break;
		}
		case 8:
		{
			quanju = 0;
			set_size(T);
			printf("�ö��������� %d ��Ԫ��", quanju);//��������ں��ж��ٸ�Ԫ�صĺ��� 
			getchar();getchar();
			break;
		}
		case 9:
		{
			int k;
			BSTree H;
			printf("����������Ҫ���ҵ�id��");//������Ҫ���ҵ�id 
			scanf("%d", &k);
			H=set_member(T, k);
			if (H == NULL)printf("�����ڸó�Ա");//������Ҳ�����Ա 
			else { 
				printf("�ó�Ա������Ϊ��%s\n", H->data.name);
				printf("�ó�Ա�Ĺ�עΪ��\n");
				quanju1 = 1;
				InOrderTraverse(H->data.attention);//������ù�ͬ��ע 
				printf("\n�ó�Ա�İ���Ϊ��\n");
				quanju1 = 1;
				InOrderTraverse(H->data.hobby);//������ù�ͬ���� 
				printf("\n�ó�Ա�ĺ���Ϊ��\n");
				quanju1 = 1;
				InOrderTraverse(H->data.friends);//������ù�ͬ���� 
				printf("\n�ó�Ա�ķ�˿Ϊ��\n");
				quanju1 = 1;
				InOrderTraverse(H->data.fans);//������ù�ͬ��˿ 
			}
			getchar(); getchar();
			break;
		}
		
		case 10:
		{
			set_destroy(T1);
			char filename[10];
			printf("�������ȡ���ı�����");
			scanf("%s",filename);
			LoadBStree1(T1, filename);
			if(set_subset(T, T1)==TRUE)//�ж������Ƿ�Ϊ�Ӽ� 
			printf("T1��T���Ӽ�\n");
			else printf("T1����T���Ӽ�\n");
			getchar(); getchar();
			break;
		}
		case 11: 
		{
			set_destroy(T1);
			char filename[10];
			printf("�������ȡ���ı�����");
			scanf("%s",filename);
			LoadBStree1(T1, filename);
			if (set_equal(T, T1) == TRUE)//�ж������Ƿ���� 
				printf("T1��T�����\n");
			else printf("T1����T�����\n");
			getchar(); getchar();
			break;
		}
		case 12:
		{
			quanju1=1; 
			printf("����������������£�\n"); 
			InOrderTraverse(T);//����һ�����ȫ����Ա����Ϣ 
			getchar(); getchar();
			break;
		}
		case 13:
		{
			int e, t;
			BSTree Q, J, K=NULL;
			rewind(stdin);
			printf("����������Ҫ���ҵ�һλ��Ա��id��");//������Ҫ���ҵ�id 
			scanf("%d", &e);
			getchar();
			Q = set_member(T, e);
			printf("����������Ҫ���ҵڶ�λ��Ա��id��");//������Ҫ���ҵ�id 
			scanf("%d", &t);
			J = set_member(T, t);
			if (Q == NULL || J == NULL)printf("�Ҳ�����Ա");//������Ҳ�����Ա 
			else {
				set_union(K,Q->data.attention);
				set_intersection(Q->data.attention, J->data.attention);
				quanju1 = 1;
				printf("��ͬ��עΪ��\n");//�����ͬ��ע 
				InOrderTraverse(Q->data.attention);
				set_union(Q->data.attention,K);
			}
			getchar(); getchar();
			break;
		}
		case 14:
		{
			int e, t;
			BSTree Q, J, K=NULL;
			rewind(stdin);
			printf("����������Ҫ���ҵ�һλ��Ա��id��");//������Ҫ���ҵ�id 
			scanf("%d", &e);
			getchar();
			Q = set_member(T, e);
			printf("����������Ҫ���ҵڶ�λ��Ա��id��");//������Ҫ���ҵ�id 
			scanf("%d", &t);
			J = set_member(T, t);
			if (Q == NULL || J == NULL)printf("�Ҳ�����Ա");//����Ҳ�����Ա 
			else {
				set_union(K,Q->data.hobby);
				set_intersection(Q->data.hobby, J->data.hobby);//������ù�ͬ���� 
				quanju1 = 1;
				printf("��ͬ����Ϊ��\n");//���������ͬ���� 
				InOrderTraverse(Q->data.hobby);
				set_union(Q->data.hobby,K);
			}
			getchar(); getchar();
			break;
		}
		case 15:
		{
			int e, t;
			BSTree Q, J, K=NULL;
			rewind(stdin);
			printf("����������Ҫ���ҵ�һλ��Ա��id��");//������Ҫ���ҵ�id 
			scanf("%d", &e);
			getchar();
			Q = set_member(T, e);
			printf("����������Ҫ���ҵڶ�λ��Ա��id��");//������Ҫ���ҵ�id 
			scanf("%d", &t);
			getchar();
			J = set_member(T, t);
			if (Q == NULL || J == NULL)printf("�Ҳ�����Ա");//����Ҳ�����Ա 
			else {
				set_union(K,Q->data.friends);
				set_intersection(K, J->data.friends);
				if(set_member(Q->data.friends,t)!=NULL){
					printf("����Ϊ����"); //������Ϊ���ѣ��㲻�Ƕ��Ⱥ����� 
					getchar();getchar();
				    break;	
				}
				if(K==NULL)printf("���߲��Ƕ��Ⱥ���");//���ߴ��ڹ�ͬ����ԥ����Ϊ���Ⱥ��� 
				else printf("�����Ƕ��Ⱥ���"); 
			}
			getchar(); getchar();
			break;
		}	
		case 16:
		{
			clear("list.txt");//��պ��������ı��ڵ�������� 
			clear("att.txt");//��պ��������ı��ڵ�������� 
			clear("fan.txt");//��պ��������ı��ڵ�������� 
			clear("fri.txt");//��պ��������ı��ڵ�������� 
			clear("hob.txt");//��պ��������ı��ڵ�������� 
			SaveBSTree(fp, T);//�洢�����������ݴ����ı�֮�� 
			printf("�洢�ɹ�");
			getchar(); getchar();
			break;
		}
		case 17:
		{
			LoadBStree(T, "list.txt");//��ȡ��������ȡ�ı��ڵ����ݴ��������֮�� 
			printf("��ȡ�ɹ�");
			getchar(); getchar();
			break;
		}
		case 18:
		{
			quanju1=1; 
			printf("ǰ��������������£�\n"); 
			PreOrderTraverse(T);//����һ�����ȫ����Ա����Ϣ 
			getchar(); getchar();
			break;
		}
		case 19:
		{
			quanju1=1; 
			printf("����������������£�\n"); 
			PosOrderTraverse(T);//����һ�����ȫ����Ա����Ϣ 
			getchar(); getchar();
			break;
		}
		case 20:
		{
			quanju1=1; 
			printf("��α������������£�\n"); 
			LevelOrderTraverse(T);//����һ�����ȫ����Ա����Ϣ 
			getchar(); getchar();
			break;
		}
        case 0:break; 

		}//end of switch
	}//end of while
	printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
}//end of main()
 /*--------page 23 on textbook --------------------*/
status set_init(BSTree &T) {
	T = NULL;
	return OK;
}
status set_destroy(BSTree &T) {
	//���ٶ����� ���� 
	if (T == NULL) return OK;// T==NULl,����ERROR 
	if (T != NULL) {
		if (T->lchild != NULL) {
			set_destroy(T->lchild);//T=T->lchild���õݹ麯�� 
			T->lchild = NULL;
		}
		if (T->rchild != NULL) {
			set_destroy(T->rchild);//T=T->rchild���õݹ麯�� 
			T->rchild = NULL;
		}
		if (T != NULL) {
			free(T);//free��� 
			T = NULL;
		}
	}
	return OK;//����OK 
}
status R_Rotate(BSTree &T) {
	//����TΪ���Ķ�������������������,LL��ƽ����ת��
	BSTree lc;
	lc = T->lchild;//lcָ���*p�����������
	T->lchild = lc->rchild;//lc���������ҽ�ΪT��������
	lc->rchild = T;//T�ҽ�Ϊlc�������� 
	T = lc; //pָ���µĽ��
}
status L_Rotate(BSTree &T) {
	//����TΪ���Ķ�������������������RR��ƽ����ת��
	BSTree rc;
	rc = T->rchild;//rcָ���*p�����������
	T->rchild = rc->lchild;//rc���������ҽ�ΪT��������
	rc->lchild = T;
	T = rc;//Tָ���µĽ��
}
status LeftBalance(BSTree &T) {
	//����ָ��T��ָ���Ϊ���Ķ���������ƽ����ת����LR��ƽ����ת��
	BSTree lc, rd;
	lc = T->lchild;//lcָ��T�������������
	switch (lc->bf)//���T����������ƽ��ȣ�������Ӧƽ�⴦��
	{
		case EH:T->bf=LH;lc->bf=RH; R_Rotate(T);break;
	case LH://�½�������T�����ӵ��������ϣ�Ҫ������������
		T->bf = lc->bf = EH;
		R_Rotate(T);
		break;
	case RH://�½�������T�����ӵ��������ϣ�Ҫ��˫������
		rd = lc->rchild;//rdָ��T�����ӵ���������
		switch (rd->bf)//�޸�T�������ӵ�ƽ������
		{
		case LH:T->bf = RH; lc->bf = EH; break;
		case EH:T->bf = lc->bf = EH; break;
		case RH:T->bf = EH; lc->bf = LH; break;
		}
		rd->bf = EH;
		L_Rotate(T->lchild); //��T��������������ƽ�⴦��
		R_Rotate(T); //��T������ƽ�⴦��
	}

}
status RightBalance(BSTree &T) {
	//����ָ��T��ָ���Ϊ���Ķ���������ƽ����ת����RL��ƽ����ת��
	BSTree rc, ld;
	rc = T->rchild; //rcָ��T�������������
	switch (rc->bf) //���T����������ƽ��ȣ�������Ӧƽ�⴦��
	{
		case EH:T->bf=RH;rc->bf=LH;L_Rotate(T); break;
	case RH: //�½�������T���Һ��ӵ��������ϣ�Ҫ������������
		T->bf = rc->bf = EH;
		L_Rotate(T); break;
	case LH: //�½�������T���Һ��ӵ��������ϣ�Ҫ��˫������
		ld = rc->lchild; //ldָ��T���Һ��ӵ���������
		switch (ld->bf) //�޸�T�����Һ��ӵ�ƽ������
		{
		case LH: T->bf = EH; rc->bf = RH; break;
		case EH: T->bf = rc->bf = EH; break;
		case RH: T->bf = LH; rc->bf = EH; break;
		}
		ld->bf = EH;
		R_Rotate(T->rchild);//��T��������������ƽ�⴦��
		L_Rotate(T); //��T������ƽ�⴦��
	}

}
bool set_insert(BSTree &T, DataNode &e, bool &taller) {
	//������e,��T�в����ں�e��ͬ�ؼ��ֵĽ�㣬�����һ������Ԫ��Ϊe���½�㣬������1�����򷵻�0
	if (!T) {//�����½��ʱ����tallerΪtrue��TΪ�գ�ֱ�Ӳ����� 
		T = (BSTree)malloc(sizeof(BSTNode));
		T->data = e;
		T->lchild = T->rchild = NULL;
		T->bf = EH;
		taller = true;

	}
	else {
		if (e.id == T->data.id) { //�����Ѵ��ں�����ͬ�ؼ��ֵĽ�����ٲ���
			taller = false;
			return false;
		}
		if (e.id<T->data.id) {//Ӧ������T���������н�������
			if (!set_insert(T->lchild, e, taller))
				return false;//δ����ɹ� 
			if (taller)//�Ѳ��뵽T��������������������bf��Ҫ�任 
				switch (T->bf) {//���T��ƽ���
				case LH://ԭ�����������������ߣ���Ҫ����ƽ�⴦��
					LeftBalance(T);
					taller = false;
					break;
				case EH: //ԭ�������������ӵȸߣ��������������߶�ʹ������
					T->bf = LH;
					taller = true;
					break;
				case RH: //ԭ�����������������ߣ������������ȸ�
					T->bf = EH;
					taller = false; break;
				}

		}
		else { //Ӧ������T���������н�������
			if (!set_insert(T->rchild, e, taller))
				return false;//δ����ɹ� 
			if (taller) {//�Ѳ��뵽T��������������������bf��Ҫ�任 
				switch (T->bf) { //���T��ƽ���
				case LH://ԭ�����������������ߣ������������ȸ�
					T->bf = EH;
					taller = false;
					break;
				case EH://ԭ�������������ӵȸߣ��������������߶�ʹ������
					T->bf = RH;
					taller = true;
					break;
				case RH://ԭ�����������������ߣ���Ҫ����ƽ�⴦��
					RightBalance(T);
					taller = false;
					break;
				}
			}
		}
	}
	return true;
}
bool set_remove(BSTree &T, int id,bool &shorter) {
    BSTree p, q = NULL; // ɾ�����~ 	
	int targ = 0; // ��־λ����ɾ��������ҽ��~ 	
	bool return_flag = false; 	
	if(!T) 	
	{// ���ܳ���ɾ��Ҷ��Ϊ�յ�������� 		
	return 0; 	} 	
	if(id==T->data.id) 	
	{// ���ΪҪɾ����㣬~ 		
	shorter = true; // ���ҵ���Ҫɾ����㣬�±�ʶΪTRUE~ 		
	if(NULL==T->rchild) 		
	{ // ���û���ҽڵ� 			
	p = T; 			
	T = T->lchild; 			
	free(p); 			
	return 1; // ԭtree������ƽ�⣬�������~ 	
	} 		
	else 		
	{ 			
	p = T->rchild; 			
	while(p->lchild!= NULL) 			
	{ // �ҵ�tree����������������~ 			
		p = p->lchild; 			
		} 			
	T->data.id = p->data.id; 			
	return_flag = set_remove(T->rchild, p->data.id, shorter); 			
	targ = RH; 		}	 
		} 	
	else if(id<T->data.id)	
	{ 	
		return_flag = set_remove(T->lchild, id, shorter); 		
		targ = LH; 	} 	
	else 
	{ 		
	return_flag = set_remove(T->rchild, id, shorter); 		
	targ = RH; 	} 	 	// ��֤���ڹ�Ϊkey�Ľ��~ 	
	if(true == shorter) 	
	{ 		
	if(targ==LH) 		
	{// ɾ������������ 			
	switch(T->bf) 				
	{					 					
	    case LH: // ����ԭ�����Ҹ߶ȷֱ�Ϊh��h-1,����������ɾ������ 					
		T->bf = EH; shorter = true; break; 					
		case EH: 						
		T->bf = RH; shorter = false;break; 				
		case RH: // ���ԭ�������ѱ���������1~��������ɾ�������������²�ƽ��~ 					
		RightBalance(T); shorter=true; break; 			
		} // switch(tree->bf) 		
	} 		
	else 		
	{// ɾ������������ 		
		switch(T->bf) 				
		{					 				
			case LH: 	LeftBalance(T); shorter = true; break; 				
			case EH: 	T->bf = LH; shorter = false; break; 				
			case RH:	T->bf = EH; shorter = true; break; 		
		} // switch(tree->bf) 	
	}		 
	}// if(TRUE == lower) 	 
	return return_flag; 
}
/*
bool set_remove(BSTree &T, int id, bool &shorter)
{
	//ɾ��ƽ���������ָ�����
	if (T == NULL)return false;//���TΪ�գ�����FALSE 
	else if (id == T->data.id) {//idΪT��ͷԪ�� 
		BSTree p;
		if (T->lchild == NULL) {//���T��������Ϊ�� 
			p = T;
			T = T->rchild;
			free(p);
			shorter = true;
		}
		else if (T->rchild == NULL) {//���T��������Ϊ�գ� 
			p = T;
			T = T->lchild;
			free(p);
			shorter = true;
		}
		else {//���T������������Ϊ�� 
			p = T->lchild;
			while (p->rchild)p = p->rchild;
			T->data = p->data;
			set_remove(T->lchild, p->data.id, shorter);//���õݹ������һ�� 
		}
	}
	else if (id<T->data.id) {//���idС�� T->data.id
		if (!set_remove(T->lchild, id, shorter))//���õݹ������һ�� 
			return false;
		if (shorter) {//ɾ���Ժ���Ҫ����ƽ�� 
			switch (T->bf) {
			case LH: //ԭ�����������������ߣ������������ȸ�
				T->bf = EH;
				shorter = true;
				break;
			case EH://ԭ�������������ӵȸߣ��������������߶�ʹ������
				T->bf = RH;
				shorter = false;
				break;
			case RH://ԭ�����������������ߣ���Ҫ����ƽ�⴦��
				if (T->rchild->bf == EH)
					shorter = false;
				else
					shorter = true;
				RightBalance(T);
				break;
			}
		}
	}
	else {//���id���� T->data.id
		if (!set_remove(T->rchild, id, shorter))return false;//���õݹ������һ�� 
		if (shorter) {//ɾ���Ժ���Ҫ����ƽ�� 
			switch (T->bf) {
			case LH: //ԭ�����������������ߣ������������ȸ�
				if (T->lchild->bf == EH)
					shorter = false;
				else
					shorter = true;
				LeftBalance(T);
				break;
			case EH: //ԭ�������������ӵȸߣ��������������߶�ʹ������
				T->bf = LH;
				shorter = false;
				break;
			case RH://ԭ�����������������ߣ���Ҫ����ƽ�⴦��
				T->bf = EH;
				shorter = true;
				break;
			}
		}
	}
	return true;
}/*

bool set_remove(BSTree &T, int id, bool &shorter)
{
	//ɾ��ƽ���������ָ�����
	if (T == NULL)return false;//���TΪ�գ�����FALSE 
	else if (id == T->data.id) {//idΪT��ͷԪ�� 
		BSTree p;
		if (T->lchild == NULL) {//���T��������Ϊ�� 
			p = T;
			T = T->rchild;
			free(p);
			shorter = true;
		}
		else if (T->rchild == NULL) {//���T��������Ϊ�գ� 
			p = T;
			T = T->lchild;
			free(p);
			shorter = true;
		}
		else {//���T������������Ϊ�� 
			p = T->lchild;
			while (p->rchild)p = p->rchild;
			T->data = p->data;
			set_remove(T->lchild, p->data.id, shorter);//���õݹ������һ�� 
		}
	}
	else if (id<T->data.id) {//���idС�� T->data.id
		if (!set_remove(T->lchild, id, shorter))//���õݹ������һ�� 
			return false;
		if (shorter) {//ɾ���Ժ���Ҫ����ƽ�� 
			switch (T->bf) {
			case LH: //ԭ�����������������ߣ������������ȸ�
				T->bf = EH;
				shorter = true;
				break;
			case EH://ԭ�������������ӵȸߣ��������������߶�ʹ������
				T->bf = RH;
				shorter = false;
				break;
			case RH://ԭ�����������������ߣ���Ҫ����ƽ�⴦��
				if (T->rchild->bf == EH)
					shorter = false;
				else
					shorter = true;
				RightBalance(T);
				break;
			}
		}
	}
	else {//���id���� T->data.id
		if (!set_remove(T->rchild, id, shorter))return false;//���õݹ������һ�� 
		if (shorter) {//ɾ���Ժ���Ҫ����ƽ�� 
			switch (T->bf) {
			case LH: //ԭ�����������������ߣ������������ȸ�
				if (T->lchild->bf == EH)
					shorter = false;
				else
					shorter = true;
				LeftBalance(T);
				break;
			case EH: //ԭ�������������ӵȸߣ��������������߶�ʹ������
				T->bf = LH;
				shorter = false;
				break;
			case RH://ԭ�����������������ߣ���Ҫ����ƽ�⴦��
				T->bf = EH;
				shorter = true;
				break;
			}
		}
	}
	return true;
}/*
status set(BSTree &T,int i){
	int j;
	bool taller;
	DataNode t;
	t.attention=NULL;
	t.fans=NULL;
	t.friends=NULL;
	t.hobby=NULL;
	rewind(stdin);
	for(j=1;j<=i;j++){
		printf("��������Ҫ�����id��");//������Ҫ�����id 
		scanf("%d", &t.id);
		printf("��������Ҫ�����������");//������Ҫ�����id 
		scanf("%s", t.name);
		set_insert(T, t, taller);//����ȡ�����ݴ���T֮�� 
	} 
	return 0;
}*/
BSTree set_member(BSTree T, int id)
{
	//�ж�Ԫ���Ƿ�Ϊ���ϳ�Ա�Ĳ��ң�����ָ��
	if (T == NULL)return NULL;
	if (T->data.id < id) {
		return set_member(T->rchild, id);//���õݹ������Ҽ��ϳ�Ա 
	}
	else if (T->data.id > id) {
		return set_member(T->lchild, id);//���õݹ������Ҽ��ϳ�Ա 
	}
	else return T;

}

status set_subset(BSTree T, BSTree T1) {
	//�ж�T1�Ƿ�ΪT���Ӽ��ĺ���������TRUE��FALSE 
	if (T1 == NULL) {
		return TRUE;//����TRUE 
	}
	if (set_member(T, T1->data.id)) {//�ж�T1�ڵ�Ԫ���Ƿ�ΪT�ڵ�Ԫ�أ�������һ���������򷵻�FALSE 
		if (!set_subset(T, T1->lchild))return FALSE;//�ݹ��ж�T1->lchild�Ƿ�ΪT�ڵ�Ԫ�� 
		if (!set_subset(T, T1->rchild))return FALSE;//�ݹ��ж�T1->rchild�Ƿ�ΪT�ڵ�Ԫ�� 
		return TRUE;//����TRUE 

	}
	else {
		return FALSE;//����FALSE
	}
}
status set_equal(BSTree T, BSTree T1)
{
	//�ж�����ƽ��������Ƿ����
	if (set_subset(T, T1) && set_subset(T1, T))return TRUE;//���T��T1���Ӽ���T1��T���Ӽ������������ 
	else return FALSE;//����FALSE
}
status set_intersection(BSTree &T, BSTree T1)
{
	//����ƽ��������󽻣���T������
	bool shorter = false;//����ֵshorter�������ʼֵΪfalse 
	if (T == NULL)return 0;
	if (set_member(T1, T->data.id) == NULL) {//�ж�T->data�Ƿ�ΪT1�ڵ�Ԫ�أ��ǵĻ���Ҫɾ�� 
		set_remove(T, T->data.id, shorter);// 
		set_intersection(T, T1);//���õݹ�
	}
	else {
		set_intersection(T->lchild, T1);//���õݹ�
		set_intersection(T->rchild, T1);//���õݹ�

	}
}
status set_union(BSTree &T, BSTree T1) {
	//����ƽ��������󲢣���T������
	bool taller = false;//����ֵshorter�������ʼֵΪfalse 
	if (!T1)return 0;
	set_insert(T, T1->data, taller);
	set_union(T, T1->lchild);//���õݹ�
	set_union(T, T1->rchild);//���õݹ�

}
status set_difference(BSTree &T, BSTree T1) {
	//����ƽ�����������T������
	bool shorter = false;//����ֵshorter�������ʼֵΪfalse 
	if (!T || !T1)return 0;
	set_remove(T, T1->data.id, shorter);//�� T1->data��T֮��ɾ��
	set_difference(T, T1->lchild);//���õݹ�
	set_difference(T, T1->rchild);//���õݹ�

}
status set_size(BSTree T) {
	//��ƽ��������ĳ�Ա����
	if (T == NULL)return TRUE;//����TRUE
	else {
		quanju++;
	}
	set_size(T->lchild);//���õݹ�
	set_size(T->rchild);//���õݹ�
}

status InOrderTraverse(BSTree T) {
	//���ö�������洢�ṹ��Visit�Ƕ�����Ԫ�ز�����Ӧ�ú���
	//����������T�ĵݹ��㷨����ÿ������Ԫ�ص���Visit����
	if (T) {
		if (InOrderTraverse(T->lchild))//���õݹ�
			if (Visit(T))//����T->data��������� 
				if (InOrderTraverse(T->rchild)) return OK;//����OK 
		return ERROR;//����ERROR
	}
	else return OK;//����OK 
}
status PreOrderTraverse(BSTree T) {
	//���ö�������洢�ṹ��Visit�Ƕ�����Ԫ�ز�����Ӧ�ú���
	//����������T�ĵݹ��㷨����ÿ������Ԫ�ص���Visit����
	if (T) {
		if (Visit(T))//���õݹ�
			if (PreOrderTraverse(T->lchild))//����T->data��������� 
				if (PreOrderTraverse(T->rchild)) return OK;//����OK 
		return ERROR;//����ERROR
	}
	else return OK;//����OK 
}
status PosOrderTraverse(BSTree T) {
	//���ö�������洢�ṹ��Visit�Ƕ�����Ԫ�ز�����Ӧ�ú���
	//����������T�ĵݹ��㷨����ÿ������Ԫ�ص���Visit����
	if (T) {
		if (PosOrderTraverse(T->lchild))//���õݹ�
			if (PosOrderTraverse(T->rchild))//����T->data��������� 
				if (Visit(T)) return OK;//����OK 
		return ERROR;//����ERROR
	}
	else return OK;//����OK 
}
status Visit(BSTree T) {
	//���������Ľ�����
	printf("%-4d %-8s ", T->data.id, T->data.name);//��������Ϣ 
	quanju1++;
	if (quanju1 == 8) {
		quanju1 = 1;
		printf("\n");
	}
	return OK;//����OK 
}
status clear(char *filename) {
	//�ı��������
	fopen(filename, "w");//���ı���������� 
}
status SaveBSTree(FILE *fp, BSTree T) {
	//�ļ��洢���������ڴ洢��һ�׵�ƽ�������
	FILE *fp1 = NULL;
	if ((fp = fopen("list.txt", "a+")) == NULL)//���ı��������ʧ�ܷ��ش��� 
	{
		printf("File open erroe\n ");
		return ERROR;//����ERROR
	}
	if (T) {
		fprintf(fp, "%d %s ", T->data.id, T->data.name);
		SaveBSTree1(fp1, T->data.attention, "att.txt");//���ı�֮�д������� 
		Save(fp1, "att.txt");//���ı�֮�д��뻻�з� 
		SaveBSTree1(fp1, T->data.friends, "fri.txt");//���ı�֮�д������� 
		Save(fp1, "fri.txt");//���ı�֮�д��뻻�з� 
		SaveBSTree1(fp1, T->data.fans, "fan.txt");//���ı�֮�д������� 
		Save(fp1, "fan.txt");//���ı�֮�д��뻻�з� 
		SaveBSTree1(fp1, T->data.hobby, "hob.txt");//���ı�֮�д������� 
		Save(fp1, "hob.txt");//���ı�֮�д��뻻�з� 
	}
	else return ERROR;
	if (T->lchild)SaveBSTree(fp, T->lchild);//���õݹ麯������ T->lchild�����ı� 
	if (T->rchild)SaveBSTree(fp, T->rchild);//���õݹ麯������ T->rchild�����ı� 
	fclose(fp);//�ر��ı�ָ�� 
	return OK;//����OK
}
status Save(FILE *fp, char *filename) {
	//�ı��洢���������ڴ洢�ڶ��׵�ƽ���������ʱ��������
	if ((fp = fopen(filename, "a+")) == NULL)//���ı��������ʧ�ܷ��ش��� 
	{
		printf("File open erroe\n ");
		return ERROR;//����ERROR
	}
	else fprintf(fp, "\n");//���ı�֮�д��뻻�з� 
	fclose(fp);//�ر��ı�ָ�� 
	return OK;//����OK 
}
status SaveBSTree1(FILE *fp, BSTree T, char *filename) {
	//�ļ��洢���������ڴ洢�ڶ��׵�ƽ�������
	if ((fp = fopen(filename, "a+")) == NULL)//���ı��������ʧ�ܷ��ش��� 
	{
		printf("File open erroe\n ");
		return ERROR;//����ERROR
	}
	if (T)
		fprintf(fp, "%d %s  ", T->data.id,T->data.name);//���ı�֮�д������� 
	else return ERROR;
	if (T->lchild)SaveBSTree1(fp, T->lchild, filename);//���õݹ麯������ T->lchild�����ı� 
	if (T->rchild)SaveBSTree1(fp, T->rchild, filename);//���õݹ麯������ T->rchild�����ı� 
	fclose(fp);//�ر��ı�ָ�� 
	return OK;//����OK 
}
status LoadBStree1(BSTree &T, char *filename) {
	//�ļ���ȡ���������ڶ�ȡ��һ�׵�ƽ�������
	BSTree p = (BSTree)malloc(sizeof(BSTNode));
	p->data.attention = NULL;//�� p->data.attention ָ��� 
	p->data.fans = NULL;//�� p->data.fans ָ��� 
	p->data.friends = NULL;//�� p->data.friends ָ��� 
	p->data.hobby = NULL;//�� p->data.hobby ָ��� 
	FILE *fp;//�ı�ָ�� 
	bool taller;
	if ((fp = fopen(filename, "r")) == NULL)//���ı��������ʧ�ܷ��ش��� 
	{
		printf("File open error\n"); return ERROR;//����ERROR
	}
	while (fscanf(fp, "%d %s", &p->data.id, p->data.name) != EOF) {
		set_insert(T, p->data, taller);//����ȡ�����ݴ���T֮�� 
	}
	fclose(fp);//�ر��ı�ָ�� 
	return TRUE;//����TRUE
}
status LoadBStree(BSTree &T, char *filename) {
	//�ļ���ȡ���������ڶ�ȡ��һ�׵�ƽ�������
	BSTree p = (BSTree)malloc(sizeof(BSTNode));
	p->data.attention = NULL;//�� p->data.attention ָ��� 
	p->data.fans = NULL;//�� p->data.fans ָ��� 
	p->data.friends = NULL;//�� p->data.friends ָ��� 
	p->data.hobby = NULL;//�� p->data.hobby ָ��� 
	FILE *fp;//�ı�ָ�� 
	int i = 0;
	bool taller;
	if ((fp = fopen(filename, "r")) == NULL)//���ı��������ʧ�ܷ��ش��� 
	{
		printf("File open error\n"); return ERROR;//����ERROR
	}
	while (fscanf(fp, "%d %s", &p->data.id, p->data.name) != EOF) {
		Load(p->data.attention, "att.txt", i);//�ļ���ȡ���������ڶ�ȡ�ڶ��׵�ƽ�������
		Load(p->data.fans, "fan.txt", i);//�ļ���ȡ���������ڶ�ȡ�ڶ��׵�ƽ�������
		Load(p->data.friends, "fri.txt", i);//�ļ���ȡ���������ڶ�ȡ�ڶ��׵�ƽ�������
		Load(p->data.hobby, "hob.txt", i);//�ļ���ȡ���������ڶ�ȡ�ڶ��׵�ƽ�������
		set_insert(T, p->data, taller);//����ȡ�����ݴ���T֮�� 
		p->data.attention = NULL;//�� p->data.attention ָ��� 
		p->data.fans = NULL;//�� p->data.fans ָ��� 
		p->data.friends = NULL;//�� p->data.friends ָ��� 
		p->data.hobby = NULL;//�� p->data.hobby ָ��� 
		i++;
	}
	fclose(fp);//�ر��ı�ָ�� 
	return TRUE;//����TRUE
}
status Load(BSTree &T, char *filename, int i) {
	//�ļ���ȡ���������ڶ�ȡ�ڶ��׵�ƽ�������
	BSTree p = (BSTree)malloc(sizeof(BSTNode));
	p->data.attention = NULL;//�� p->data.attention ָ��� 
	p->data.fans = NULL;//�� p->data.fans ָ��� 
	p->data.friends = NULL;//�� p->data.friends ָ��� 
	p->data.hobby = NULL;//�� p->data.hobby ָ��� 
	bool taller;//����ֵtaller
	int j, l, n;
	FILE *fp;//�ı�ָ�� 
	char c;
	char k[100000];//k��Ҫ�㹻�����������ܴ����һ�е����� 
	if ((fp = fopen(filename, "r")) == NULL)//���ı��������ʧ�ܷ��ش��� 
	{
		printf("File open error\n"); return ERROR;//����ERROR
	}
	for (j = 0; j<i; j++) {
		fgets(k, 100000, fp);//��ǰ��n-1�и��������ȡ��n�е����� 
	}
	while (fscanf(fp, "%d %s", &p->data.id, p->data.name) != EOF) {
		set_insert(T, p->data, taller);//����ȡ�����ݴ���T֮�� 
		c = fgetc(fp);
		if (c != ' ')//���û�ж����ո�˵����һ�ж�ȡ����������
			break;
	}
	fclose(fp);//�ر��ı�ָ��
	return TRUE;//����TRUE
}
status set(BSTree &G,int i){
	int j,k;
	BSTree p = (BSTree)malloc(sizeof(BSTNode));
	p->data.attention = NULL;//�� p->data.attention ָ��� 
	p->data.fans = NULL;//�� p->data.fans ָ��� 
	p->data.friends = NULL;//�� p->data.friends ָ��� 
	p->data.hobby = NULL;//�� p->data.hobby ָ��� 
	bool taller = false;
	for(j=1;j<=i;j++){
		rewind(stdin);
		printf("������� %d ����Ա����Ϣ��",j);
		scanf("%d %s",&p->data.id,p->data.name);
		//getchar();
		//printf("������� %d ����Ա����Ϣ��",j);
		//gets();
		set_insert(G, p->data, taller);
	}
}
status set1(BSTree &G,int i){
	int j,k;
	BSTree p = (BSTree)malloc(sizeof(BSTNode));
	p->data.attention = NULL;//�� p->data.attention ָ��� 
	p->data.fans = NULL;//�� p->data.fans ָ��� 
	p->data.friends = NULL;//�� p->data.friends ָ��� 
	p->data.hobby = NULL;//�� p->data.hobby ָ��� 
	bool taller = false;
	for(j=1;j<=i;j++){
		rewind(stdin);
		printf("������� %d �����õ���Ϣ��",j);
		scanf("%d %s",&p->data.id,p->data.name);
		//getchar();
		//printf("������� %d ����Ա����Ϣ��",j);
		//gets();
		set_insert(G, p->data, taller);
	}
}

void level(BSTree T, int h) {
	//��α�����غ��� 
	if (T) {
		if (h == 1)
			Visit1(T);//����T->data��������� 
		else {
			level(T->lchild, h - 1);//���õݹ�
			level(T->rchild, h - 1);//���õݹ�
		}
	}
}
status LevelOrderTraverse(BSTree T) {
	//��α�����غ��� 
	if (T) {
		int h = BiTreeDepth(T);//����� 
		int i,j;
		for (i = 1;i <= h;i++){
			printf("��%d�������¼�������",i); 

			level(T, i);//���ò�κ��� 
			printf("\n"); 
		}
		return OK;//����ERROR
	}
	else return OK;//����ERROR
}

status BiTreeDepth(BSTree T){
	//���ض���������� ���� 
	int i,j; 
	if(T==NULL)return 0;
	i=BiTreeDepth(T->lchild);//���õݹ�
	j=BiTreeDepth(T->rchild);//���õݹ�
	if(i>j)return (i+1);//�Ż� (i+1)
	return (j+1);// �Ż� (j+1)
}
status Visit1(BSTree T) {
	//���������Ľ�����
	printf("%d ", T->data.id);//��������Ϣ 
	return OK;//����OK 
}
