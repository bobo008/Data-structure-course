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
#define LH +1 //左高
#define EH 0 //等高
#define RH -1 //右高
typedef int status;
typedef int ElemType; //数据元素类型定义
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
	int bf; //结点的平衡因子
	struct BSTNode *lchild;//左孩子指针
	struct BSTNode *rchild;//右孩子指针
}BSTNode, *BSTree;

int quanju = 0, quanju1 = 1;
 
/*-----page 19 on textbook ---------*/
status set_init(BSTree &T);//初始化AVL树
status set_destroy(BSTree &T);//销毁AVL树

status R_Rotate(BSTree &T);//二叉排序树作右旋处理
status L_Rotate(BSTree &T);//二叉排序树作左旋处理
status LeftBalance(BSTree &T); //二叉树作左平衡旋转处理
status RightBalance(BSTree &T);//二叉树作右平衡旋转处理
bool set_insert(BSTree &T, DataNode &e, bool &taller);//插入结点e
bool set_remove(BSTree &T, int id, bool &shorter);//删除平衡二叉树的指定结点

status set_difference(BSTree &T, BSTree T1);//两个平衡二叉树求差，以T来返回
status set_intersection(BSTree &T, BSTree T1);//两个平衡二叉树求交，以T来返回
status set_union(BSTree &T, BSTree T1);//两个平衡二叉树求并，以T来返回
status set_size(BSTree T);//求平衡二叉树的成员个数
status set_equal(BSTree T, BSTree T1);//判断两个平衡二叉树是否相等
BSTree set_member(BSTree T, int id);//判断元素是否为集合成员的查找，返回指针
status InOrderTraverse(BSTree T);//前序遍历平衡二叉树
status PreOrderTraverse(BSTree T);
status PosOrderTraverse(BSTree T);
status Visit(BSTree T);//遍历函数的结点访问
status Visit1(BSTree T);//遍历函数的结点访问
status set_subset(BSTree T, BSTree T1) ;//判断两个平衡二叉树是否为子集 
status set(BSTree &G,int i);
status set1(BSTree &G,int i); 

status SaveBSTree1(FILE *fp, BSTree T, char *filename);//文件存储函数，用于存储第二阶的平衡二叉树
status SaveBSTree(FILE *fp, BSTree T);//文件存储函数，用于存储第一阶的平衡二叉树
status LoadBStree(BSTree &T, char *filename);//文件读取函数，用于读取第一阶的平衡二叉树
status Load(BSTree &T, char *filename, int i);//文件读取函数，用于读取第二阶的平衡二叉树
status Save(FILE *fp, char *filename);//文本存储函数，用于存储第二阶的平衡二叉树的时候以作用
status clear(char *filename);//文本清除函数
status LoadBStree1(BSTree &T, char *filename);//文件读取函数，用于读取第一阶的平衡二叉树
void level(BSTree T, int h);
status LevelOrderTraverse(BSTree T);
status BiTreeDepth(BSTree T);
int  main() {
	BSTree T = NULL, T1 = NULL;//平衡二叉树T 
	int op = 1; 
	bool taller = false;//布尔值taller，给其初始值为false 
	bool shorter = false;//布尔值shorter，给其初始值为false 
	int i;
	int e;
	FILE  *fp;//文件指针 
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
		printf("    请选择你的操作[0~20]:");
		scanf("%d", &op);
		switch (op) {
		case 1:
			if (set_init(T) == OK)printf("初始化成功\n");//创建二叉树成功
			else printf("初始化失败");//创建二叉树失败
			getchar(); getchar();
			break;
		case 2:
			if (set_destroy(T) == ERROR)printf("不存在二叉树");//输出二叉树不存在 
			else printf("销毁成功");//销毁成功 
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
			printf("请输入你要插入的id：");//输入需要插入的id 
			scanf("%d", &q.id);
			printf("请输入你要插入的姓名：");//输入需要插入的id 
			scanf("%s", q.name);
			
			printf("请输入你需要插入的成员的关注数：") ;
			scanf("%d",&i);
			getchar();
			set(q.attention,i); 
			rewind(stdin);
			
			printf("请输入你需要插入的成员的粉丝数：") ;
			scanf("%d",&i);
			getchar();
			set(q.fans,i);
			rewind(stdin);
			
			printf("请输入你需要插入的成员的朋友数：") ;
			scanf("%d",&i);
			getchar();
			set(q.friends,i);
			rewind(stdin);
			
			printf("请输入你需要插入的成员的爱好数：") ;
			scanf("%d",&i);
			set1(q.hobby,i);
			rewind(stdin);
			
			//q.attention = NULL;
			//q.fans = NULL;
            //q.friends = NULL;
			//q.hobby = NULL;
			if (set_insert(T, q, taller)) {
				printf("插入成功");//插入成功 
			}
			else printf("插入失败");//插入失败 
			getchar(); getchar();
			break;

		}
		case 4:
		{
			printf("请输入你要删除的id：");//输入需要删除的id
			scanf("%d", &i);
			if (set_remove(T, i, shorter)) {
				printf("删除成功");//删除成功 
			}
			else printf("删除失败");//删除失败 
			getchar(); getchar();
			break;
		}
		case 5: 
		{
			set_destroy(T1);
			char filename[10];
			printf("请输入读取的文本名：");
			scanf("%s",filename);
			LoadBStree1(T1, filename); 
			set_intersection(T1, T);//求两者的交集 
			printf("两者求交遍历如下：\n");
			quanju1 = 1;
			InOrderTraverse(T1);//输出求交之后的遍历序列 
			getchar(); getchar();
			break;
		}
		case 6: 
		{
			set_destroy(T1);
			char filename[10];
			printf("请输入读取的文本名：");
			scanf("%s",filename);
			LoadBStree1(T1, filename);
			set_union(T1, T);//求两者的并集 
			printf("两者求并遍历如下：\n");
			quanju1 = 1;
			InOrderTraverse(T1);//输出求并之后的遍历序列 
			getchar(); getchar();
			break;
		}
		case 7: 
		{
			set_destroy(T1);
			char filename[10];
			printf("请输入读取的文本名：");
			scanf("%s",filename);
			LoadBStree1(T1, filename);
			set_difference(T1, T);//求两者的差集 
			printf("两者求差遍历如下：\n");
			quanju1 = 1;
			InOrderTraverse(T1);//输出求差之后的遍历序列 
			getchar(); getchar();
			break;
		}
		case 8:
		{
			quanju = 0;
			set_size(T);
			printf("该二叉树含有 %d 个元素", quanju);//求二叉树内含有多少个元素的函数 
			getchar();getchar();
			break;
		}
		case 9:
		{
			int k;
			BSTree H;
			printf("请输入你需要查找的id：");//输入需要查找的id 
			scanf("%d", &k);
			H=set_member(T, k);
			if (H == NULL)printf("不存在该成员");//输出与找不到成员 
			else { 
				printf("该成员的姓名为：%s\n", H->data.name);
				printf("该成员的关注为：\n");
				quanju1 = 1;
				InOrderTraverse(H->data.attention);//遍历求得共同关注 
				printf("\n该成员的爱好为：\n");
				quanju1 = 1;
				InOrderTraverse(H->data.hobby);//遍历求得共同爱好 
				printf("\n该成员的好友为：\n");
				quanju1 = 1;
				InOrderTraverse(H->data.friends);//遍历求得共同好友 
				printf("\n该成员的粉丝为：\n");
				quanju1 = 1;
				InOrderTraverse(H->data.fans);//遍历求得共同粉丝 
			}
			getchar(); getchar();
			break;
		}
		
		case 10:
		{
			set_destroy(T1);
			char filename[10];
			printf("请输入读取的文本名：");
			scanf("%s",filename);
			LoadBStree1(T1, filename);
			if(set_subset(T, T1)==TRUE)//判断两者是否为子集 
			printf("T1是T的子集\n");
			else printf("T1不是T的子集\n");
			getchar(); getchar();
			break;
		}
		case 11: 
		{
			set_destroy(T1);
			char filename[10];
			printf("请输入读取的文本名：");
			scanf("%s",filename);
			LoadBStree1(T1, filename);
			if (set_equal(T, T1) == TRUE)//判断两者是否相等 
				printf("T1与T的相等\n");
			else printf("T1不与T的相等\n");
			getchar(); getchar();
			break;
		}
		case 12:
		{
			quanju1=1; 
			printf("中序遍历的数据如下：\n"); 
			InOrderTraverse(T);//遍历一遍输出全部成员的信息 
			getchar(); getchar();
			break;
		}
		case 13:
		{
			int e, t;
			BSTree Q, J, K=NULL;
			rewind(stdin);
			printf("请输入你需要查找第一位成员的id：");//输入需要查找的id 
			scanf("%d", &e);
			getchar();
			Q = set_member(T, e);
			printf("请输入你需要查找第二位成员的id：");//输入需要查找的id 
			scanf("%d", &t);
			J = set_member(T, t);
			if (Q == NULL || J == NULL)printf("找不到成员");//输出与找不到成员 
			else {
				set_union(K,Q->data.attention);
				set_intersection(Q->data.attention, J->data.attention);
				quanju1 = 1;
				printf("共同关注为：\n");//输出共同关注 
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
			printf("请输入你需要查找第一位成员的id：");//输入需要查找的id 
			scanf("%d", &e);
			getchar();
			Q = set_member(T, e);
			printf("请输入你需要查找第二位成员的id：");//输入需要查找的id 
			scanf("%d", &t);
			J = set_member(T, t);
			if (Q == NULL || J == NULL)printf("找不到成员");//输出找不到成员 
			else {
				set_union(K,Q->data.hobby);
				set_intersection(Q->data.hobby, J->data.hobby);//求交来求得共同爱好 
				quanju1 = 1;
				printf("共同爱好为：\n");//遍历输出共同爱好 
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
			printf("请输入你需要查找第一位成员的id：");//输入需要查找的id 
			scanf("%d", &e);
			getchar();
			Q = set_member(T, e);
			printf("请输入你需要查找第二位成员的id：");//输入需要查找的id 
			scanf("%d", &t);
			getchar();
			J = set_member(T, t);
			if (Q == NULL || J == NULL)printf("找不到成员");//输出找不到成员 
			else {
				set_union(K,Q->data.friends);
				set_intersection(K, J->data.friends);
				if(set_member(Q->data.friends,t)!=NULL){
					printf("两者为好友"); //若两者为好友，便不是二度好友了 
					getchar();getchar();
				    break;	
				}
				if(K==NULL)printf("两者不是二度好友");//两者存在共同好犹豫，则为二度好友 
				else printf("两者是二度好友"); 
			}
			getchar(); getchar();
			break;
		}	
		case 16:
		{
			clear("list.txt");//清空函数，将文本内的数据清空 
			clear("att.txt");//清空函数，将文本内的数据清空 
			clear("fan.txt");//清空函数，将文本内的数据清空 
			clear("fri.txt");//清空函数，将文本内的数据清空 
			clear("hob.txt");//清空函数，将文本内的数据清空 
			SaveBSTree(fp, T);//存储函数，将数据存入文本之中 
			printf("存储成功");
			getchar(); getchar();
			break;
		}
		case 17:
		{
			LoadBStree(T, "list.txt");//读取函数，读取文本内的数据存入二叉树之中 
			printf("读取成功");
			getchar(); getchar();
			break;
		}
		case 18:
		{
			quanju1=1; 
			printf("前序遍历的数据如下：\n"); 
			PreOrderTraverse(T);//遍历一遍输出全部成员的信息 
			getchar(); getchar();
			break;
		}
		case 19:
		{
			quanju1=1; 
			printf("后序遍历的数据如下：\n"); 
			PosOrderTraverse(T);//遍历一遍输出全部成员的信息 
			getchar(); getchar();
			break;
		}
		case 20:
		{
			quanju1=1; 
			printf("层次遍历的数据如下：\n"); 
			LevelOrderTraverse(T);//遍历一遍输出全部成员的信息 
			getchar(); getchar();
			break;
		}
        case 0:break; 

		}//end of switch
	}//end of while
	printf("欢迎下次再使用本系统！\n");
}//end of main()
 /*--------page 23 on textbook --------------------*/
status set_init(BSTree &T) {
	T = NULL;
	return OK;
}
status set_destroy(BSTree &T) {
	//销毁二叉树 函数 
	if (T == NULL) return OK;// T==NULl,返回ERROR 
	if (T != NULL) {
		if (T->lchild != NULL) {
			set_destroy(T->lchild);//T=T->lchild调用递归函数 
			T->lchild = NULL;
		}
		if (T->rchild != NULL) {
			set_destroy(T->rchild);//T=T->rchild调用递归函数 
			T->rchild = NULL;
		}
		if (T != NULL) {
			free(T);//free结点 
			T = NULL;
		}
	}
	return OK;//返回OK 
}
status R_Rotate(BSTree &T) {
	//对以T为根的二叉排序树作右旋处理,LL型平衡旋转法
	BSTree lc;
	lc = T->lchild;//lc指向的*p左子树根结点
	T->lchild = lc->rchild;//lc的右子树挂接为T的左子树
	lc->rchild = T;//T挂接为lc的右子树 
	T = lc; //p指向新的结点
}
status L_Rotate(BSTree &T) {
	//对以T为根的二叉排序树作左旋处理，RR型平衡旋转法
	BSTree rc;
	rc = T->rchild;//rc指向的*p右子树根结点
	T->rchild = rc->lchild;//rc的左子树挂接为T的右子树
	rc->lchild = T;
	T = rc;//T指向新的结点
}
status LeftBalance(BSTree &T) {
	//对以指针T所指结点为根的二叉树作左平衡旋转处理，LR型平衡旋转法
	BSTree lc, rd;
	lc = T->lchild;//lc指向T的左子树根结点
	switch (lc->bf)//检查T的左子树的平衡度，并作相应平衡处理
	{
		case EH:T->bf=LH;lc->bf=RH; R_Rotate(T);break;
	case LH://新结点插入在T的左孩子的左子树上，要作单右旋处理
		T->bf = lc->bf = EH;
		R_Rotate(T);
		break;
	case RH://新结点插入在T的左孩子的右子树上，要作双旋处理
		rd = lc->rchild;//rd指向T的左孩子的右子树根
		switch (rd->bf)//修改T及其左孩子的平衡因子
		{
		case LH:T->bf = RH; lc->bf = EH; break;
		case EH:T->bf = lc->bf = EH; break;
		case RH:T->bf = EH; lc->bf = LH; break;
		}
		rd->bf = EH;
		L_Rotate(T->lchild); //对T的左子树作左旋平衡处理
		R_Rotate(T); //对T作右旋平衡处理
	}

}
status RightBalance(BSTree &T) {
	//对以指针T所指结点为根的二叉树作右平衡旋转处理，RL型平衡旋转法
	BSTree rc, ld;
	rc = T->rchild; //rc指向T的右子树根结点
	switch (rc->bf) //检查T的右子树的平衡度，并作相应平衡处理
	{
		case EH:T->bf=RH;rc->bf=LH;L_Rotate(T); break;
	case RH: //新结点插入在T的右孩子的右子树上，要作单左旋处理
		T->bf = rc->bf = EH;
		L_Rotate(T); break;
	case LH: //新结点插入在T的右孩子的左子树上，要作双旋处理
		ld = rc->lchild; //ld指向T的右孩子的左子树根
		switch (ld->bf) //修改T及其右孩子的平衡因子
		{
		case LH: T->bf = EH; rc->bf = RH; break;
		case EH: T->bf = rc->bf = EH; break;
		case RH: T->bf = LH; rc->bf = EH; break;
		}
		ld->bf = EH;
		R_Rotate(T->rchild);//对T的右子树作左旋平衡处理
		L_Rotate(T); //对T作左旋平衡处理
	}

}
bool set_insert(BSTree &T, DataNode &e, bool &taller) {
	//插入结点e,若T中不存在和e相同关键字的结点，则插入一个数据元素为e的新结点，并返回1，否则返回0
	if (!T) {//插入新结点时将置taller为true，T为空，直接插入便可 
		T = (BSTree)malloc(sizeof(BSTNode));
		T->data = e;
		T->lchild = T->rchild = NULL;
		T->bf = EH;
		taller = true;

	}
	else {
		if (e.id == T->data.id) { //树中已存在和有相同关键字的结点则不再插入
			taller = false;
			return false;
		}
		if (e.id<T->data.id) {//应继续在T的左子树中进行搜索
			if (!set_insert(T->lchild, e, taller))
				return false;//未插入成功 
			if (taller)//已插入到T的左子树中则左子树的bf需要变换 
				switch (T->bf) {//检查T的平衡度
				case LH://原本左子树比右子树高，需要作左平衡处理
					LeftBalance(T);
					taller = false;
					break;
				case EH: //原本左子树、右子等高，现因左子树增高而使树增高
					T->bf = LH;
					taller = true;
					break;
				case RH: //原本右子树比左子树高，现左、右子树等高
					T->bf = EH;
					taller = false; break;
				}

		}
		else { //应继续在T的右子树中进行搜索
			if (!set_insert(T->rchild, e, taller))
				return false;//未插入成功 
			if (taller) {//已插入到T的右子树中则右子树的bf需要变换 
				switch (T->bf) { //检查T的平衡度
				case LH://原本左子树比右子树高，现左、右子树等高
					T->bf = EH;
					taller = false;
					break;
				case EH://原本左子树、右子等高，现因右子树增高而使树增高
					T->bf = RH;
					taller = true;
					break;
				case RH://原本右子树比左子树高，需要作右平衡处理
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
    BSTree p, q = NULL; // 删除结点~ 	
	int targ = 0; // 标志位，即删除左结点或右结点~ 	
	bool return_flag = false; 	
	if(!T) 	
	{// 可能出现删除叶子为空的情况不？ 		
	return 0; 	} 	
	if(id==T->data.id) 	
	{// 如果为要删除结点，~ 		
	shorter = true; // 即找到所要删除结点，致标识为TRUE~ 		
	if(NULL==T->rchild) 		
	{ // 如果没有右节点 			
	p = T; 			
	T = T->lchild; 			
	free(p); 			
	return 1; // 原tree左子树平衡，无需调整~ 	
	} 		
	else 		
	{ 			
	p = T->rchild; 			
	while(p->lchild!= NULL) 			
	{ // 找到tree的右子树的最左结点~ 			
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
	targ = RH; 	} 	 	// 保证存在过为key的结点~ 	
	if(true == shorter) 	
	{ 		
	if(targ==LH) 		
	{// 删除的是左子树 			
	switch(T->bf) 				
	{					 					
	    case LH: // 由于原来左右高度分别为h、h-1,现在左子树删除，则 					
		T->bf = EH; shorter = true; break; 					
		case EH: 						
		T->bf = RH; shorter = false;break; 				
		case RH: // 如果原右子树已比左子树高1~，现在又删左子树，将导致不平衡~ 					
		RightBalance(T); shorter=true; break; 			
		} // switch(tree->bf) 		
	} 		
	else 		
	{// 删除的是右子树 		
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
	//删除平衡二叉树的指定结点
	if (T == NULL)return false;//如果T为空，返回FALSE 
	else if (id == T->data.id) {//id为T的头元素 
		BSTree p;
		if (T->lchild == NULL) {//如果T的左子树为空 
			p = T;
			T = T->rchild;
			free(p);
			shorter = true;
		}
		else if (T->rchild == NULL) {//如果T的右子树为空， 
			p = T;
			T = T->lchild;
			free(p);
			shorter = true;
		}
		else {//如果T的左右子树不为空 
			p = T->lchild;
			while (p->rchild)p = p->rchild;
			T->data = p->data;
			set_remove(T->lchild, p->data.id, shorter);//调用递归查找下一级 
		}
	}
	else if (id<T->data.id) {//如果id小于 T->data.id
		if (!set_remove(T->lchild, id, shorter))//调用递归查找下一级 
			return false;
		if (shorter) {//删除以后需要调节平衡 
			switch (T->bf) {
			case LH: //原本左子树比右子树高，现左、右子树等高
				T->bf = EH;
				shorter = true;
				break;
			case EH://原本左子树、右子等高，现因右子树增高而使树增高
				T->bf = RH;
				shorter = false;
				break;
			case RH://原本右子树比左子树高，需要作右平衡处理
				if (T->rchild->bf == EH)
					shorter = false;
				else
					shorter = true;
				RightBalance(T);
				break;
			}
		}
	}
	else {//如果id大于 T->data.id
		if (!set_remove(T->rchild, id, shorter))return false;//调用递归查找下一级 
		if (shorter) {//删除以后需要调节平衡 
			switch (T->bf) {
			case LH: //原本左子树比右子树高，现左、右子树等高
				if (T->lchild->bf == EH)
					shorter = false;
				else
					shorter = true;
				LeftBalance(T);
				break;
			case EH: //原本左子树、右子等高，现因右子树增高而使树增高
				T->bf = LH;
				shorter = false;
				break;
			case RH://原本右子树比左子树高，需要作右平衡处理
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
	//删除平衡二叉树的指定结点
	if (T == NULL)return false;//如果T为空，返回FALSE 
	else if (id == T->data.id) {//id为T的头元素 
		BSTree p;
		if (T->lchild == NULL) {//如果T的左子树为空 
			p = T;
			T = T->rchild;
			free(p);
			shorter = true;
		}
		else if (T->rchild == NULL) {//如果T的右子树为空， 
			p = T;
			T = T->lchild;
			free(p);
			shorter = true;
		}
		else {//如果T的左右子树不为空 
			p = T->lchild;
			while (p->rchild)p = p->rchild;
			T->data = p->data;
			set_remove(T->lchild, p->data.id, shorter);//调用递归查找下一级 
		}
	}
	else if (id<T->data.id) {//如果id小于 T->data.id
		if (!set_remove(T->lchild, id, shorter))//调用递归查找下一级 
			return false;
		if (shorter) {//删除以后需要调节平衡 
			switch (T->bf) {
			case LH: //原本左子树比右子树高，现左、右子树等高
				T->bf = EH;
				shorter = true;
				break;
			case EH://原本左子树、右子等高，现因右子树增高而使树增高
				T->bf = RH;
				shorter = false;
				break;
			case RH://原本右子树比左子树高，需要作右平衡处理
				if (T->rchild->bf == EH)
					shorter = false;
				else
					shorter = true;
				RightBalance(T);
				break;
			}
		}
	}
	else {//如果id大于 T->data.id
		if (!set_remove(T->rchild, id, shorter))return false;//调用递归查找下一级 
		if (shorter) {//删除以后需要调节平衡 
			switch (T->bf) {
			case LH: //原本左子树比右子树高，现左、右子树等高
				if (T->lchild->bf == EH)
					shorter = false;
				else
					shorter = true;
				LeftBalance(T);
				break;
			case EH: //原本左子树、右子等高，现因右子树增高而使树增高
				T->bf = LH;
				shorter = false;
				break;
			case RH://原本右子树比左子树高，需要作右平衡处理
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
		printf("请输入你要插入的id：");//输入需要插入的id 
		scanf("%d", &t.id);
		printf("请输入你要插入的姓名：");//输入需要插入的id 
		scanf("%s", t.name);
		set_insert(T, t, taller);//将读取的数据存入T之中 
	} 
	return 0;
}*/
BSTree set_member(BSTree T, int id)
{
	//判断元素是否为集合成员的查找，返回指针
	if (T == NULL)return NULL;
	if (T->data.id < id) {
		return set_member(T->rchild, id);//调用递归来查找集合成员 
	}
	else if (T->data.id > id) {
		return set_member(T->lchild, id);//调用递归来查找集合成员 
	}
	else return T;

}

status set_subset(BSTree T, BSTree T1) {
	//判断T1是否为T的子集的函数，返回TRUE或FALSE 
	if (T1 == NULL) {
		return TRUE;//返回TRUE 
	}
	if (set_member(T, T1->data.id)) {//判断T1内的元素是否为T内的元素，是则下一步，不是则返回FALSE 
		if (!set_subset(T, T1->lchild))return FALSE;//递归判断T1->lchild是否为T内的元素 
		if (!set_subset(T, T1->rchild))return FALSE;//递归判断T1->rchild是否为T内的元素 
		return TRUE;//返回TRUE 

	}
	else {
		return FALSE;//返回FALSE
	}
}
status set_equal(BSTree T, BSTree T1)
{
	//判断两个平衡二叉树是否相等
	if (set_subset(T, T1) && set_subset(T1, T))return TRUE;//如果T是T1的子集，T1是T的子集，则两者相等 
	else return FALSE;//返回FALSE
}
status set_intersection(BSTree &T, BSTree T1)
{
	//两个平衡二叉树求交，以T来返回
	bool shorter = false;//布尔值shorter，给其初始值为false 
	if (T == NULL)return 0;
	if (set_member(T1, T->data.id) == NULL) {//判断T->data是否为T1内的元素，是的话需要删除 
		set_remove(T, T->data.id, shorter);// 
		set_intersection(T, T1);//调用递归
	}
	else {
		set_intersection(T->lchild, T1);//调用递归
		set_intersection(T->rchild, T1);//调用递归

	}
}
status set_union(BSTree &T, BSTree T1) {
	//两个平衡二叉树求并，以T来返回
	bool taller = false;//布尔值shorter，给其初始值为false 
	if (!T1)return 0;
	set_insert(T, T1->data, taller);
	set_union(T, T1->lchild);//调用递归
	set_union(T, T1->rchild);//调用递归

}
status set_difference(BSTree &T, BSTree T1) {
	//两个平衡二叉树求差，以T来返回
	bool shorter = false;//布尔值shorter，给其初始值为false 
	if (!T || !T1)return 0;
	set_remove(T, T1->data.id, shorter);//将 T1->data从T之中删除
	set_difference(T, T1->lchild);//调用递归
	set_difference(T, T1->rchild);//调用递归

}
status set_size(BSTree T) {
	//求平衡二叉树的成员个数
	if (T == NULL)return TRUE;//返回TRUE
	else {
		quanju++;
	}
	set_size(T->lchild);//调用递归
	set_size(T->rchild);//调用递归
}

status InOrderTraverse(BSTree T) {
	//采用二叉链表存储结构，Visit是对数据元素操作的应用函数
	//遍历二叉树T的递归算法，对每个数据元素调用Visit函数
	if (T) {
		if (InOrderTraverse(T->lchild))//调用递归
			if (Visit(T))//访问T->data，将其输出 
				if (InOrderTraverse(T->rchild)) return OK;//返回OK 
		return ERROR;//返回ERROR
	}
	else return OK;//返回OK 
}
status PreOrderTraverse(BSTree T) {
	//采用二叉链表存储结构，Visit是对数据元素操作的应用函数
	//遍历二叉树T的递归算法，对每个数据元素调用Visit函数
	if (T) {
		if (Visit(T))//调用递归
			if (PreOrderTraverse(T->lchild))//访问T->data，将其输出 
				if (PreOrderTraverse(T->rchild)) return OK;//返回OK 
		return ERROR;//返回ERROR
	}
	else return OK;//返回OK 
}
status PosOrderTraverse(BSTree T) {
	//采用二叉链表存储结构，Visit是对数据元素操作的应用函数
	//遍历二叉树T的递归算法，对每个数据元素调用Visit函数
	if (T) {
		if (PosOrderTraverse(T->lchild))//调用递归
			if (PosOrderTraverse(T->rchild))//访问T->data，将其输出 
				if (Visit(T)) return OK;//返回OK 
		return ERROR;//返回ERROR
	}
	else return OK;//返回OK 
}
status Visit(BSTree T) {
	//遍历函数的结点访问
	printf("%-4d %-8s ", T->data.id, T->data.name);//输出结点信息 
	quanju1++;
	if (quanju1 == 8) {
		quanju1 = 1;
		printf("\n");
	}
	return OK;//返回OK 
}
status clear(char *filename) {
	//文本清除函数
	fopen(filename, "w");//打开文本并清除内容 
}
status SaveBSTree(FILE *fp, BSTree T) {
	//文件存储函数，用于存储第一阶的平衡二叉树
	FILE *fp1 = NULL;
	if ((fp = fopen("list.txt", "a+")) == NULL)//打开文本，如果打开失败返回错误 
	{
		printf("File open erroe\n ");
		return ERROR;//返回ERROR
	}
	if (T) {
		fprintf(fp, "%d %s ", T->data.id, T->data.name);
		SaveBSTree1(fp1, T->data.attention, "att.txt");//在文本之中存入数据 
		Save(fp1, "att.txt");//在文本之中存入换行符 
		SaveBSTree1(fp1, T->data.friends, "fri.txt");//在文本之中存入数据 
		Save(fp1, "fri.txt");//在文本之中存入换行符 
		SaveBSTree1(fp1, T->data.fans, "fan.txt");//在文本之中存入数据 
		Save(fp1, "fan.txt");//在文本之中存入换行符 
		SaveBSTree1(fp1, T->data.hobby, "hob.txt");//在文本之中存入数据 
		Save(fp1, "hob.txt");//在文本之中存入换行符 
	}
	else return ERROR;
	if (T->lchild)SaveBSTree(fp, T->lchild);//调用递归函数，将 T->lchild存入文本 
	if (T->rchild)SaveBSTree(fp, T->rchild);//调用递归函数，将 T->rchild存入文本 
	fclose(fp);//关闭文本指针 
	return OK;//返回OK
}
status Save(FILE *fp, char *filename) {
	//文本存储函数，用于存储第二阶的平衡二叉树的时候以作用
	if ((fp = fopen(filename, "a+")) == NULL)//打开文本，如果打开失败返回错误 
	{
		printf("File open erroe\n ");
		return ERROR;//返回ERROR
	}
	else fprintf(fp, "\n");//在文本之中存入换行符 
	fclose(fp);//关闭文本指针 
	return OK;//返回OK 
}
status SaveBSTree1(FILE *fp, BSTree T, char *filename) {
	//文件存储函数，用于存储第二阶的平衡二叉树
	if ((fp = fopen(filename, "a+")) == NULL)//打开文本，如果打开失败返回错误 
	{
		printf("File open erroe\n ");
		return ERROR;//返回ERROR
	}
	if (T)
		fprintf(fp, "%d %s  ", T->data.id,T->data.name);//在文本之中存入数据 
	else return ERROR;
	if (T->lchild)SaveBSTree1(fp, T->lchild, filename);//调用递归函数，将 T->lchild存入文本 
	if (T->rchild)SaveBSTree1(fp, T->rchild, filename);//调用递归函数，将 T->rchild存入文本 
	fclose(fp);//关闭文本指针 
	return OK;//返回OK 
}
status LoadBStree1(BSTree &T, char *filename) {
	//文件读取函数，用于读取第一阶的平衡二叉树
	BSTree p = (BSTree)malloc(sizeof(BSTNode));
	p->data.attention = NULL;//将 p->data.attention 指向空 
	p->data.fans = NULL;//将 p->data.fans 指向空 
	p->data.friends = NULL;//将 p->data.friends 指向空 
	p->data.hobby = NULL;//将 p->data.hobby 指向空 
	FILE *fp;//文本指针 
	bool taller;
	if ((fp = fopen(filename, "r")) == NULL)//打开文本，如果打开失败返回错误 
	{
		printf("File open error\n"); return ERROR;//返回ERROR
	}
	while (fscanf(fp, "%d %s", &p->data.id, p->data.name) != EOF) {
		set_insert(T, p->data, taller);//将读取的数据存入T之中 
	}
	fclose(fp);//关闭文本指针 
	return TRUE;//返回TRUE
}
status LoadBStree(BSTree &T, char *filename) {
	//文件读取函数，用于读取第一阶的平衡二叉树
	BSTree p = (BSTree)malloc(sizeof(BSTNode));
	p->data.attention = NULL;//将 p->data.attention 指向空 
	p->data.fans = NULL;//将 p->data.fans 指向空 
	p->data.friends = NULL;//将 p->data.friends 指向空 
	p->data.hobby = NULL;//将 p->data.hobby 指向空 
	FILE *fp;//文本指针 
	int i = 0;
	bool taller;
	if ((fp = fopen(filename, "r")) == NULL)//打开文本，如果打开失败返回错误 
	{
		printf("File open error\n"); return ERROR;//返回ERROR
	}
	while (fscanf(fp, "%d %s", &p->data.id, p->data.name) != EOF) {
		Load(p->data.attention, "att.txt", i);//文件读取函数，用于读取第二阶的平衡二叉树
		Load(p->data.fans, "fan.txt", i);//文件读取函数，用于读取第二阶的平衡二叉树
		Load(p->data.friends, "fri.txt", i);//文件读取函数，用于读取第二阶的平衡二叉树
		Load(p->data.hobby, "hob.txt", i);//文件读取函数，用于读取第二阶的平衡二叉树
		set_insert(T, p->data, taller);//将读取的数据存入T之中 
		p->data.attention = NULL;//将 p->data.attention 指向空 
		p->data.fans = NULL;//将 p->data.fans 指向空 
		p->data.friends = NULL;//将 p->data.friends 指向空 
		p->data.hobby = NULL;//将 p->data.hobby 指向空 
		i++;
	}
	fclose(fp);//关闭文本指针 
	return TRUE;//返回TRUE
}
status Load(BSTree &T, char *filename, int i) {
	//文件读取函数，用于读取第二阶的平衡二叉树
	BSTree p = (BSTree)malloc(sizeof(BSTNode));
	p->data.attention = NULL;//将 p->data.attention 指向空 
	p->data.fans = NULL;//将 p->data.fans 指向空 
	p->data.friends = NULL;//将 p->data.friends 指向空 
	p->data.hobby = NULL;//将 p->data.hobby 指向空 
	bool taller;//布尔值taller
	int j, l, n;
	FILE *fp;//文本指针 
	char c;
	char k[100000];//k需要足够长，这样才能存得下一行的数据 
	if ((fp = fopen(filename, "r")) == NULL)//打开文本，如果打开失败返回错误 
	{
		printf("File open error\n"); return ERROR;//返回ERROR
	}
	for (j = 0; j<i; j++) {
		fgets(k, 100000, fp);//将前面n-1行给清除，读取第n行的数据 
	}
	while (fscanf(fp, "%d %s", &p->data.id, p->data.name) != EOF) {
		set_insert(T, p->data, taller);//将读取的数据存入T之中 
		c = fgetc(fp);
		if (c != ' ')//如果没有读到空格，说明这一行读取结束，返回
			break;
	}
	fclose(fp);//关闭文本指针
	return TRUE;//返回TRUE
}
status set(BSTree &G,int i){
	int j,k;
	BSTree p = (BSTree)malloc(sizeof(BSTNode));
	p->data.attention = NULL;//将 p->data.attention 指向空 
	p->data.fans = NULL;//将 p->data.fans 指向空 
	p->data.friends = NULL;//将 p->data.friends 指向空 
	p->data.hobby = NULL;//将 p->data.hobby 指向空 
	bool taller = false;
	for(j=1;j<=i;j++){
		rewind(stdin);
		printf("请输入第 %d 个成员的信息：",j);
		scanf("%d %s",&p->data.id,p->data.name);
		//getchar();
		//printf("请输入第 %d 个成员的信息：",j);
		//gets();
		set_insert(G, p->data, taller);
	}
}
status set1(BSTree &G,int i){
	int j,k;
	BSTree p = (BSTree)malloc(sizeof(BSTNode));
	p->data.attention = NULL;//将 p->data.attention 指向空 
	p->data.fans = NULL;//将 p->data.fans 指向空 
	p->data.friends = NULL;//将 p->data.friends 指向空 
	p->data.hobby = NULL;//将 p->data.hobby 指向空 
	bool taller = false;
	for(j=1;j<=i;j++){
		rewind(stdin);
		printf("请输入第 %d 个爱好的信息：",j);
		scanf("%d %s",&p->data.id,p->data.name);
		//getchar();
		//printf("请输入第 %d 个成员的信息：",j);
		//gets();
		set_insert(G, p->data, taller);
	}
}

void level(BSTree T, int h) {
	//层次遍历相关函数 
	if (T) {
		if (h == 1)
			Visit1(T);//访问T->data，将其输出 
		else {
			level(T->lchild, h - 1);//调用递归
			level(T->rchild, h - 1);//调用递归
		}
	}
}
status LevelOrderTraverse(BSTree T) {
	//层次遍历相关函数 
	if (T) {
		int h = BiTreeDepth(T);//求深度 
		int i,j;
		for (i = 1;i <= h;i++){
			printf("第%d层有以下几个数：",i); 

			level(T, i);//调用层次函数 
			printf("\n"); 
		}
		return OK;//返回ERROR
	}
	else return OK;//返回ERROR
}

status BiTreeDepth(BSTree T){
	//返回二叉树的深度 函数 
	int i,j; 
	if(T==NULL)return 0;
	i=BiTreeDepth(T->lchild);//调用递归
	j=BiTreeDepth(T->rchild);//调用递归
	if(i>j)return (i+1);//放回 (i+1)
	return (j+1);// 放回 (j+1)
}
status Visit1(BSTree T) {
	//遍历函数的结点访问
	printf("%d ", T->data.id);//输出结点信息 
	return OK;//返回OK 
}
