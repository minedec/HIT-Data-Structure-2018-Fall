#include <stdio.h>
#include <stdlib.h>
#define MAX 50

///树形结构建立与遍历
///学号：1163450201
///姓名：
///班级：

/*定义二叉树结构，左右链表表示*/
typedef struct Node
{
    struct Node * lchild;
    struct Node * rchild;
    char data;
}* BTREE, Node;

/*定义队列*/
struct QUEUE
{
    BTREE data[MAX];
    int front;
    int rear;
};

/*新建树节点*/
void BNew(BTREE * bt)
{
    BTREE x;
    x = (BTREE)malloc(sizeof(Node));
    if(x == NULL)
    {
        printf("Lack of Memory,please retry\n");
        exit(1);
    }
    x->lchild = NULL;
    x->rchild = NULL;
    x->data = '\0';
    *bt = x;
}

/*以先序遍历建立二叉树*/
BTREE BBuild()
{
    char ch;
    BTREE bt;
    //fflush(stdin);
    scanf("%c",&ch);
    if(ch == '#')	/*若为#，则置为空节点*/
        bt = NULL;
    else
    {
        BNew(&bt);
        if(!bt)
            exit(0);
        bt->data = ch;
        bt->lchild = BBuild();
        bt->rchild = BBuild();
    }
    return bt;
}

/*以文件形式输入二叉树*/
BTREE BBuild_F(FILE *fp)
{
    char ch;
    BTREE bt;
    fscanf(fp, "%c",&ch);
    if(ch == '#')
        bt = NULL;
    else
    {
        BNew(&bt);
        if(!bt)
            exit(0);
        bt->data = ch;
        bt->lchild = BBuild_F(fp);
        bt->rchild = BBuild_F(fp);
    }
    return bt;
}

/*以广义表形式显示二叉树*/
void BShow(BTREE bt)
{
    if(bt != NULL)
    {
        printf("%c", bt->data);
        if(bt->lchild != NULL || bt->rchild != NULL)	/*有子节点存在*/
        {
            printf("(");
            BShow(bt->lchild);
            if(bt->rchild != NULL)	/*右子树不为空*/
            {
                printf(",");
                BShow(bt->rchild);
                printf(")");
            }
        }
    }
}

/*文件形式保存二叉树*/
void BSave(BTREE bt, FILE * fp)
{
    if(bt)
    {
        fprintf(fp, "%c", bt->data);
        BSave(bt->lchild, fp);
        BSave(bt->rchild, fp);
    }
    else
    {
        fprintf(fp, "#");
    }
}

/*将先序遍历结果写入文件*/
void BSave_Pre(BTREE bt, FILE * fp)
{
    if(bt)
    {
        fprintf(fp, "%c", bt->data);
        BSave_Pre(bt->lchild, fp);
        BSave_Pre(bt->rchild, fp);
    }
}

/*将中序遍历结果写入文件*/
void BSave_In(BTREE bt, FILE * fp)
{
    if(bt)
    {
        BSave_In(bt->lchild, fp);
        fprintf(fp, "%c", bt->data);
        BSave_In(bt->rchild, fp);
    }
}

/*将后序遍历结果写入文件*/
void BSave_Post(BTREE bt, FILE * fp)
{
    if(bt)
    {
        BSave_Post(bt->lchild, fp);
        BSave_Post(bt->rchild, fp);
        fprintf(fp, "%c", bt->data);
    }
}

/*将层序遍历结果写入文件*/
void BSave_L(BTREE bt, FILE * fp)
{
    struct QUEUE Q;
    BTREE p = bt;
    Q.front = 0;
    Q.rear = 0;
    Q.data[0] = NULL;
    if(bt)
    {
        Q.data[Q.rear] = p;
        while(!(Q.front > Q.rear))	/*判断队列是否为空*/
        {
            p = Q.data[Q.front];
            Q.front++;
            fprintf(fp, "%c", p->data);
            if(p->lchild)
            {
                Q.rear++;
                Q.data[Q.rear] = p->lchild;
            }
            if(p->rchild)
            {
                Q.rear++;
                Q.data[Q.rear] = p->rchild;
            }
        }
    }
}

/*先序遍历二叉树递归*/
void PreOrderRE(BTREE bt)
{
    if(bt)
    {
        printf("%c", bt->data);
        PreOrderRE(bt->lchild);
        PreOrderRE(bt->rchild);
    }
}

/*先序非递归遍历二叉树*/
void PreOrderURE(BTREE bt)
{
    BTREE stack[MAX];
    int top = 0;
    do
    {
        while(bt != NULL)	/*将左路子树入栈*/
        {
            printf("%c", bt->data);
            top++;
            if(top > MAX)
                printf("Stack is full\n");
            else
                stack[top] = bt;
            bt = bt->lchild;
        }
        if(top != 0)
        {
            bt = stack[top];
            top--;
            bt = bt->rchild;	/*寻找右子树的左路子树*/
        }
    }
    while((top!= 0) || (bt != NULL));
}

/*递归中序遍历*/
void InOrderRE(BTREE bt)
{
    if(bt)
    {
        InOrderRE(bt->lchild);
        printf("%c", bt->data);
        InOrderRE(bt->rchild);
    }
}

/*非递归中序遍历*/
void InOrderURE(BTREE bt)
{
    BTREE stack[MAX];
    int top = 0;
    do
    {
        while(bt != NULL)	/*左路子树入栈*/
        {
            top++;
            if(top > MAX)
                printf("Stack is full\n");
            else
                stack[top] = bt;
            bt = bt->lchild;
        }
        if(top != 0)
        {
            bt = stack[top];
            top--;
            printf("%c", bt->data);
            bt = bt->rchild;	/*右子树左路子树入栈*/
        }
    }
    while((top != 0) || (bt != NULL));
}

/*递归后序遍历*/
void PostOrderRE(BTREE bt)
{
    if(bt)
    {
        PostOrderRE(bt->lchild);
        PostOrderRE(bt->rchild);
        printf("%c", bt->data);
    }
}

/*非递归后序遍历*/
void PostOrderURE(BTREE bt)
{
    BTREE stack[MAX], p;	/*保存右子树地址变量*/
    int top = 0;
    int b;	/*左路子树是否访问完毕变量*/
    do
    {
        while(bt != NULL)	/*左路子树入栈*/
        {
            top++;
            if(top > MAX)
                printf("Stack is full\n");
            else
                stack[top] = bt;
            bt = bt->lchild;
        }
        p = NULL;	/*默认右子树为空*/
        b = 1;		/*左路子树以全部访问*/
        while((top != 0) && b)
        {
            bt = stack[top];
            if(bt->rchild == p)
            {
                printf("%c", bt->data);
                top--;
                p = bt;
            }
            else
            {
                bt = bt->rchild;	/*有未访问的右子树*/
                b = 0;	/*标记左路子树未访问*/
            }
        }
    }
    while(top != 0);
}

/*层序遍历*/
void LeverList(BTREE bt)
{
    struct QUEUE Q;
    BTREE p = bt;
    Q.front = 0;
    Q.rear = 0;
    Q.data[0] = NULL;
    if(bt)
    {
        Q.data[Q.rear] = p;
        while(!(Q.front > Q.rear))	/*判断队列是否为空*/
        {
            p = Q.data[Q.front];
            Q.front++;
            printf("%c", p->data);
            /*每弹出一个节点，访问其左右子树，若有，则入队*/
            if(p->lchild)
            {
                Q.rear++;
                Q.data[Q.rear] = p->lchild;
            }
            if(p->rchild)
            {
                Q.rear++;
                Q.data[Q.rear] = p->rchild;
            }
        }
    }
}

/*判断是否为完全二叉树*/
int BJudge(BTREE bt)
{
    //char data[MAX];
    int i = 0;	/*统计第一次出现NULL的位置*/
    int count = 0;	/*统计队列中字符数量（不包括NULL）*/
    struct QUEUE Q;
    BTREE p = bt;
    Q.front = 0;
    Q.rear = 0;
    Q.data[0] = NULL;
    if(bt)
    {
        Q.data[Q.rear] = p;
        while(!(Q.front > Q.rear))	//判断是否为空
        {
            p = Q.data[Q.front];
            Q.front++;
            if(!p)
                continue;
            printf("%c", p->data);
            count++;
            if(p->lchild)
            {
                Q.rear++;
                Q.data[Q.rear] = p->lchild;
            }
            else
            {
                Q.rear++;
                Q.data[Q.rear] = NULL;
            }
            if(p->rchild)
            {
                Q.rear++;
                Q.data[Q.rear] = p->rchild;
            }
            else
            {
                Q.rear++;
                Q.data[Q.rear] = NULL;
            }
        }
    }
    while((Q.data[i]) != NULL)
    {
        i++;
    }
    if(count == i)	/*如果队列中第一次出现NULL的位置在所有字符之后，则表示为完全呃二叉树*/
        return 1;
    else
        return 0;

}

void menu()
{
    FILE * fp;
    char c;
    BTREE bt;
    //BNew(&bt);
    while(1)
    {
        //system("cls");
        fflush(stdin);
        printf("=========================\n"
               "1.Build BinaryTree(Input)\n2.Build BinaryTree(File)\n3.Show BinaryTree\n4.Save BinaryTree\n5.Visit BinaryTree\n6.Judge BinaryTree whether complete\n"
               "=========================\n");
        c = getchar();
        switch(c)
        {
        case '1':
        {
            printf("Use preorder to build binarytree,input # if there is no lchild and rchild\n");
            fflush(stdin);
            bt = NULL;
            bt = BBuild();
            break;
        }
        case '3':
        {
            BShow(bt);
            printf("\n");
            break;
        }
        case '4':
        {
            fp = fopen("BTREE.txt", "w");
            if(fp == NULL)
            {
                printf("File not exist!\n");
                getchar();
                break;
            }
            BSave(bt, fp);
            fclose(fp);
            break;
        }
        case '5':
        {
            fflush(stdin);
            printf("============\n"
                   "1.Preorder\n2.Inorder\n3.Postorder\n4.Level list\n"
                   "============\n");
            c = getchar();
            switch (c)
            {
            case '1':
            {
                printf("Recursion is: ");
                PreOrderRE(bt);
                printf("\n");
                printf("Nonrecursion is: ");
                PreOrderURE(bt);
                printf("\n");
                fp = fopen("BTREE_PRE.txt", "w");
                if(fp == NULL)
                {
                    printf("File not exist!\n");
                    getchar();
                    break;
                }
                BSave_Pre(bt, fp);
                printf("Save complete\n");
                fclose(fp);
                break;
            }
            case '2':
            {
                printf("Recursion is: ");
                InOrderRE(bt);
                printf("\n");
                printf("Nonrecursion is: ");
                InOrderURE(bt);
                printf("\n");
                fp = fopen("BTREE_IN.txt", "w");
                if(fp == NULL)
                {
                    printf("File not exist!\n");
                    getchar();
                    break;
                }
                BSave_In(bt, fp);
                printf("Save complete\n");
                fclose(fp);
                break;
            }
            case '3':
            {
                printf("Recursion is: ");
                PostOrderRE(bt);
                printf("\n");
                printf("Nonrecursion is: ");
                PostOrderURE(bt);
                printf("\n");
                fp = fopen("BTREE_POST.txt", "w");
                if(fp == NULL)
                {
                    printf("File not exist!\n");
                    getchar();
                    break;
                }
                BSave_Post(bt, fp);
                printf("Save complete\n");
                fclose(fp);
                break;
            }
            case '4':
            {
                LeverList(bt);
                printf("\n");
                fp = fopen("BTREE_L.txt", "w");
                if(fp == NULL)
                {
                    printf("File not exist!\n");
                    getchar();
                    break;
                }
                BSave_L(bt, fp);
                printf("Save complete\n");
                fclose(fp);
                break;
            }
            }
            break;
        }
        case '6':
        {
            if(BJudge(bt))
            {
                printf("\n");
                printf("Is a complete binarytree\n");
            }
            else
            {
                printf("\n");
                printf("Not a complete binarytree\n");
            }
            break;
        }
        case '2':
        {
            if((fp = fopen("BTREE.txt","rt")) == NULL)
            {
                printf("File not exist\n");
                getchar();
                break;
            }
            bt = BBuild_F(fp);
            fclose(fp);
            break;
        }
        }
    }
}

int main()
{
    menu();
    return 0;
}
