/*
 * 姓名：
 * 学号：1163450201
 * 实验名称：lab4 BST
 * 实验内容：1.左右链存储结构、插入（建立）、删除、查找、排序
 *          2.折半查找
 *          3.计算ASL
 */

#include <stdio.h>
#include <stdlib.h>
#define left -1;
#define right 1;
#define MAX_LENTH 1024
typedef int records;

/*BST结构体*/
typedef struct CellType
{
	records data;
	struct CellType * lchild;
	struct CellType * rchild;
} * BST;


int arr1[MAX_LENTH] = {0}; /*顺序存储*/
int arr2[MAX_LENTH] = {0}; /*随机存贮*/
int arrt[MAX_LENTH] = {0};
int C = 0;
int cot = 0;  /*记录失败节点数*/

/*插入（建立）算法*/
void Insert(records R, BST * F)
{
    BST * p = F;
	if((*p) == NULL)
	{
		(*p) = malloc(sizeof(struct CellType));
		(*p)->data = R;
		(*p)->lchild = NULL;
		(*p)->rchild = NULL;
	}
	else if(R < (*p)->data)
	{
		Insert(R, &((*p)->lchild));
	}
	else if(R > (*p)->data)
	{
		Insert(R, &((*p)->rchild));
	}
}

/*删除算法*/
void Delete(records R, BST  F)
{
	BST parent;    /* 指针指向父节点 */
	int position, tmp;
	while(F != NULL)
	{
		if(R < F->data)
		{
			parent = F;
			F = F->lchild;
			position = left;
		}
		else if(R > F->data)
		{
			parent = F;
			F = F->rchild;
			position = right;
		}
		else
		{
			break;
		}
	}
	/* 如果结点为叶子结点 */
	if((F->lchild == NULL) && (F->rchild == NULL))
	{
		if(position == -1)   /* F为父结点左子树 */
		{
			parent->lchild = NULL;
			free(F);
		}
		else if(position == 1)    /* F为父结点右子树 */
		{
			parent->rchild = NULL;
			free(F);
		}
		else{}
	}
	/* 如果结点右子树为空 */
	else if(F->rchild == NULL)
	{
		if(position == -1)
		{
			parent->lchild = F->lchild;
			free(F);
		}
		else if(position == 1)
		{
			parent->rchild = F->lchild;
			free(F);
		}
	}
	/* 如果结点左子树为空 */
	else if(F->lchild == NULL)
	{
		if(position == -1)
		{
			parent->lchild = F->rchild;
			free(F);
		}
		else if(position == 1)
		{
			parent->rchild = F->rchild;
			free(F);
		}
	}
	/* 如果都有左右子树 */
	else
	{
		F->data = DeleteMin(F->rchild);
	}
}

/* 找出右子树最小结点的data */
records DeleteMin(BST F)
{
	records tmp;
	BST p;
	if(F->lchild == NULL)
	{
		p = F;
		tmp = F->data;
		F = F->rchild;
		free(F);
		return tmp;
	}
	else
		return(DeleteMin(F->lchild));
}

int asl = 0;  /*asl开关*/

/* 查找算法 */
BST search_S(records R, BST F)
{
	BST p = F;
	if(asl)
    {
        C++; /*路长加一*/
    }
	if(p == NULL)
	{
		return NULL;
	}
	else if(R == p->data)
	{
		return p;
	}
	else if(R < p->data)
	{
		return(search_S(R, p->lchild));
	}
	else
	{
		return(search_S(R, p->rchild));
	}
}

/*查找失败函数*/
void search_F(BST F,int path)
{
    path++;  /*路长加一*/
    if(F == NULL)
    {
        cot++;
        C += path;
        return;
    }
    else
    {
        search_F(F->lchild, path);
        search_F(F->rchild, path);
    }
}

/*先序遍历*/
void PreOrderRE(BST bt)
{
    if(bt)
    {
        printf("%d ", bt->data);
        PreOrderRE(bt->lchild);
        PreOrderRE(bt->rchild);
    }
}
/*中序遍历*/
void InOrderRE(BST bt)
{
    if(bt)
    {
        InOrderRE(bt->lchild);
        printf("%d ", bt->data);
        InOrderRE(bt->rchild);
    }
}
/*中序输入数组arr1*/
int cnt = 0;
void InOrderRE_Input(BST bt)
{
    if(bt)
    {
        InOrderRE_Input(bt->lchild);
        arr1[cnt++] = bt->data;
        InOrderRE_Input(bt->rchild);
    }
}
/*折半查找*/
int BinarySearch(records R, int arr[MAX_LENTH],int low, int up)
{
    int mid;
    while(low <= up)
    {
        C++;  /*路长加一*/
        mid = (low + up) / 2;
        if(arr[mid] == R)
            return mid;
        else if(arr[mid] > R)
        {
            up = mid-1;
        }
        else
        {
            low = mid+1;
        }

    }
    return -1;
}
/*折半查找判定树*/
void BinarySearch_T(int arr[MAX_LENTH], BST * F, int i, int j)
{
    int mid;
    if(i > j)
        return;
    else
    {
        mid = (i+j) /2;
        Insert(arr[mid], F);
        BinarySearch_T(arr, F, i, mid-1);
        BinarySearch_T(arr, F, mid+1, j);
    }
}

/*建立顺序BST*/
void MakeTestSet1(BST * F)
{
	int i = 0;
	for(i = 1; i < 2048; i += 2)
	{
		Insert(i, F);
	}
}

/*建立乱序BST*/
void MakeTestSet2(BST * F)
{
	int i, j;
	int tmp;
	int randnum;
	for(i = 0; i < MAX_LENTH; i++)
	{
		arr2[i] = arr1[i];
	}
    srand((unsigned)(time(NULL)));
	for(i = 0; i < MAX_LENTH; i++)
	{
		i = rand() % 1024;
		j = rand() % 1024;
		tmp = arr2[i];
		arr2[i] = arr2[j];
		arr2[j] = tmp;
	}
	for(i = 0; i < MAX_LENTH; i++)
	{
		Insert(arr2[i], F);
	}
}

/*测试函数1*/
void Test1_ASL(BST F)
{
	double ASL,P;
	/*成功次数*/
	P = (double)1/1024;
	ASL = 0;
	asl = 1;
	C = 0;
	int i = 1;
	for(i = 1; i < 2048; i += 2)
	{
		search_S(i, F);
		ASL += C * P;
		C = 0;
	}
	printf("In order Success ASL: %.3lf\n", ASL);
	/*失败次数*/
	ASL = 0;
	cot = 0;
	search_F(F, 0);
	ASL = (double)C / cot;
	printf("In order Failed ASL: %.3lf\n", ASL);
}

/*测试函数2*/
void Test2_ASL(BST * F)
{
	double ASL,P;
	/*成功次数*/
	P = (double)1/1024;
	ASL = 0;
	asl = 1;
	C = 0;
	int i = 1;
	for(i = 1; i < 2048; i += 2)
	{
		search_S(i, F);
		ASL += C * P;
		C = 0;
	}
	printf("Out of order Success ASL: %.3lf\n", ASL);
	/*失败次数*/
	ASL = 0;
	cot = 0;
	search_F(F, 0);
	ASL = (double)C / cot;
	printf("Out of order Failed ASL: %.3lf\n", ASL);
}

/*测试函数3*/
void Test3_ASL(BST * F)
{
    double ASL,P;
	P = (double)1/1024;
	/*成功次数*/
	ASL = 0;
	C = 0;
	asl = 1;
	int i = 1;
	for(i = 1; i < 2048; i += 2)
	{
		if(BinarySearch(i, arr1, 0, MAX_LENTH) < 0)
			printf("no found\n");
        //search_S(i, F);
		ASL += C * P;
		C = 0;
	}
	printf("Binary Search Success ASL: %.3lf\n", ASL);
	/*失败次数*/
	ASL = 0;
	cot = 0;
	search_F(F, 0);
	ASL = (double)C / cot;
	printf("Binary Search Failed ASL: %.3lf\n", ASL);
}

/*测试小BST函数1*/
void Test1_ASL_T(BST F, int num)
{
	double ASL,P;
	/*成功次数*/
	P = (double)1/num;
	ASL = 0;
	asl = 1;
	C = 0;
	int i = 1;
	for(i = 0; i < num ; i++)
	{
		search_S(arrt[i], F);
		ASL += C * P;
		C = 0;
	}
	printf("In order Success ASL: %.3lf\n", ASL);
	/*失败次数*/
	ASL = 0;
	cot = 0;
	search_F(F, 0);
	ASL = (double)C / cot;
	printf("In order Failed ASL: %.3lf\n", ASL);
}

/*测试小BST函数2*/
void Test3_ASL_T(BST * F, int num)
{
    double ASL,P;
	P = (double)1/num;
	ASL = 0;
	C = 0;
	asl = 1;
	int i = 1;
	for(i = 1; i < num; i ++)
	{
		if(BinarySearch(arrt[i], arrt, 0, num-1) < 0)
			printf("no found\n");
		ASL += C * P;
		C = 0;
	}
	printf("Binary Search Success ASL: %.3lf\n", ASL);
	/*失败次数*/
	ASL = 0;
	cot = 0;
	search_F(F, 0);
	ASL = (double)C / cot;
	printf("Binary Search Failed ASL: %.3lf\n", ASL);
}

void menu()
{
    printf("==================================================\n"
           "=              === LAB4:BST ===                 =\n"
           "==================================================\n"
           "=1.-> BST Build (1024 in order number 0-2048 odd)=\n"
           "=  -> BST Build (out of order)                   =\n"
           "=2.-> BST Delete                                 =\n"
           "=3.-> BST Search                                 =\n"
           "=4.-> BST in order ASL                           =\n"
           "=  -> BST out of order ASL                       =\n"
           "=  -> Binary Search ASL                          =\n"
           "==================================================\n");
}
int main()
{
    BST F1, F2,F3,Ft,Fl;
    BST tmp;
    BST head;
    int num;
    int tmpn;
    int count = 0;  /*标记元素个数*/
    int i = 0;
    char op;

    F1 = NULL;
    F2 = NULL;
    F3 = NULL;
    Ft = NULL;
    Fl = NULL;

    while(1)
    {
        menu();
        fflush(stdin);
        op = getchar();
        switch(op)
        {
        case '1':
            {
                MakeTestSet1(&F1); /*arr1顺序*/
                cnt = 0;
                InOrderRE_Input(F1);
                MakeTestSet2(&F2);  /*arr2乱序*/
                BinarySearch_T(arr1, &F3, 0, 1023);  /*建立折半查找树*/
                break;
            }
        case '2':
            {
                printf("Input num and No.BST(1 or 2):");
                scanf("%d %d", &tmpn, &num);
                if(num == 1)
                {
                    Delete(tmpn, F1);
                    //InOrderRE(F1);
                    printf("Delete %d\n", tmpn);
                    InOrderRE(F1);
                    printf("\n");
                }
                else if(num == 2)
                {
                    Delete(tmpn, F2);
                    printf("Delete %d\n", tmpn);
                    InOrderRE(F2);
                    printf("\n");
                }
                else
                    printf("Error\n");
                break;
            }
        case '3':
            {
                printf("Input num and No.BST(1 or 2):");
                scanf("%d %d", &tmpn, &num);
                if(num == 1)  /*在顺序BST中查找*/
                {
                    tmp = search_S(tmpn, F1);
                    printf("The address of node is:0x%0x\n", tmp);
                }
                else if(num == 2)  /*在乱序BST中查找*/
                {
                    tmp = search_S(tmpn, F2);
                    printf("The address of node is:0x%0x\n", tmp);
                }
                else
                    printf("Error\n");
                break;
            }
        case '4':
            {
                Test1_ASL(F1);
                Test2_ASL(F2);
                Test3_ASL(F3);
                //PreOrderRE(F3);
                break;
            }
        case '5':  /*测试功能，勿用*/
            {
                scanf("%d", &num);
                for(i = 1; i <= 2 * num -1 ; i += 2)
                {
                    arrt[count++] = i;
                }

                for(i = 0; i < num; i++)
                {
                    scanf("%d", &tmpn);
                    Insert(tmpn, &Ft);
                }
                Test1_ASL_T(Ft, num);
                InOrderRE(Ft);

                BinarySearch_T(arrt, &Fl, 0, count-1);
                Test3_ASL_T(Fl, num);
            }
        }
    }
    return 0;
}
