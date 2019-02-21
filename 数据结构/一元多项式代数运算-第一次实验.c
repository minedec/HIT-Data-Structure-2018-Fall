#include <stdio.h>
#include <stdlib.h>
#include <math.h>

///学号：1163450201
///姓名：
///实验一：一元多项式的代数运算
///设计线性表的动态链式存储，实现运算
///文件输入输出建立多项式
///计算x0的值，float型
///实现四则运算

/*定义多项式中的项*/
typedef struct polynode
{
    double coef;    /*系数*/
    int exp;        /*指数*/
    struct polynode * link; /*下一项指针*/
}poly,*polypointer;

/*为多项式的项申请内存*/
polypointer newPoly()
{
    polypointer x;
    x = (polypointer)malloc(sizeof(poly));
    if(x == NULL)
    {
        printf("内存不足，无法申请\n");
        exit(1);
    }
    x->coef = 0;
    x->exp = 0;
    x->link = NULL;
    return x;
}

/*建立一个新结点，系数c，指数e，链接到x后*/
polypointer polyAttach(double c, int e, polypointer arg)
{
    polypointer x;
    x = newPoly();
    x->coef = c;
    x->exp = e;
    arg->link = x;
    return x;
}

/*从头至尾打印多项式*/
void polyPrint(polypointer arg)
{
    if(arg->exp == 0)
    {
        printf("%.2lf", arg->coef);
    }
    else
    {
        printf("%.2lfX^%d", arg->coef, arg->exp);    
    }
    polypointer x = arg->link;
    while(x != NULL)
    {
        if(x->exp == 0)
        {
            if(x->coef > 0)
            {
                printf(" + %.2lf", x->coef);
            }
            else
            {
                printf(" - %.2lf", -x->coef);
            }
            x = x->link;
            continue;
        }
        if(x->coef > 0)
        {
            printf(" + %.2lfX^%d", x->coef, x->exp);
        }
        else
        {
            printf(" - %.2lfX^%d", -x->coef, x->exp);
        }
        x = x->link;
    }
    printf("\n");
}

/*多项式合并同类项*/
void polyCombine(polypointer * arg)
{
    polypointer p, q, c, d, tmp;
    double x = 0;
    p = (*arg);
    q = (*arg)->link;
    c = p;          /*c指向q的前一项*/
    d = newPoly();
    d->link = p;          /*d指向p的前一项*/
    if(q == NULL)   /*只有一项*/
    {
        if(p->coef == 0)     /*特殊：只有一个节点并且系数为0*/
        {
            *arg = newPoly();   /*返回空节点*/
            return;
        }
        return;     /*原样返回*/
    }
    while(p != NULL)
    {
        while(q != NULL)
        {
        if(q->exp == p->exp)        /*同类项*/
        {
            x = p->coef + q->coef;
            if(x != 0)              /*系数和不等于0*/
            {
                p->coef = x;
                c->link = q->link;  /*合并后删除q结点*/
                tmp = q;
                q = q->link;
                free(tmp);
            }
            else                    /*系数和为0,同时删除两个节点*/
            {
                if(p == *arg && (p->link != q))       /*如果第一个节点是头节点并且没有相邻*/
                {
                    tmp = (*arg);
                    *arg = (*arg)->link;    /*修改头节点*/
                    d->link = *arg;
                    free(tmp);              /*删除头节点*/
                    c->link = q->link;      /*删除q结点*/
                    tmp = q;
                    q = q->link;
                    free(tmp);
                }
                else if(p == *arg && (p->link == q))     /*如果第一个节点是头节点并且相邻*/
                {
                    tmp = (*arg);
                    *arg = ((*arg)->link)->link;    /*修改头节点*/
                    p = *arg;
                    d->link = *arg;
                    free(tmp);              /*删除头节点*/
                    c = *arg;
                    tmp = q;
                    q = (q->link)->link;
                    free(tmp);
                }
                else if(p != *arg && (p->link != q))              /*第一个节点不是头节点并且不相邻*/
                {
                    d->link = p->link;      /*删除p节点*/
                    tmp = p;
                    p = p->link;
                    free(tmp);
                    c->link = q->link;      /*删除q结点*/
                    tmp = q;
                    q = q->link;
                    free(tmp);
                }
                else if(p != *arg && (p->link == q))        /*第一个节点不是头节点并且相邻*/
                {
                    d->link = (p->link)->link;      /*删除p节点*/
                    tmp = p;
                    p = (p->link)->link;
                    free(tmp);
                    c = p;      /*删除q结点*/
                    tmp = q;
                    q = (q->link)->link;
                    free(tmp);
                }
                else
                {

                }
            }
        }
        else            /*不是同类项*/
        {
            q = q->link;
            c = c->link;
        }
        }
        d = d->link;
        p = p->link;
        if(p != NULL)
        {
            q = p->link;
            c = p;
        }
    }
    p = *arg;
    d = newPoly();
    d->link = p;

    /*消去系数为0项*/
    if(p->coef == 0)  /*如果头节点系数为0*/
    {
        tmp = p;
        *arg = p->link;
        p = p->link;
        d->link = p;
        free(tmp);
    }
    while(p != NULL)        /*消去系数为0项*/
    {
        if(p->coef == 0)
        {
            tmp = p;
            p = p->link;
            d->link = p;
            free(tmp);
            continue;
        }
        p = p->link;
        d = d->link;
    }
}

/*多项式按指数从大到小排序并且合并同类项*/
void polyRank(polypointer * arg)
{
    polyCombine(arg);       /*合并同类项*/
    polypointer p, q, k;
    double c;
    int e;
    p = (*arg);
    q = (*arg)->link;
    k = (*arg);
    while(p->link != NULL)
    {
        while(q!= NULL)
        {
            if(q->exp > k->exp)
                k = q;  /*标记指数比p大的位置*/
            q = q->link;
        }
        if(k != p)      /*若不等，交换k p值*/
        {
            c = p->coef;
            e = p->exp;
            p->coef = k->coef;
            p->exp = k->exp;
            k->coef = c;
            k->exp = e;
        }
        p = p->link;
        q = p->link;
        k = p;
    }
}

/*手动输入多项式*/
void HandInput(polypointer * arg)
{
    double c = 0;
    int e = 0;
    char s;
    polypointer x;
    while(scanf(" %lf", &c) != EOF && scanf(" %d%c", &e, &s) != EOF)
    {
        if((*arg)->link == NULL)
            x = *arg;
        x = polyAttach(c, e, x);
        if(s == '\n')
            break;
    }
    x = *arg;
    *arg = (*arg)->link;
    free(x);
}

/*文件输入多项式*/
int FileInput(polypointer * a, polypointer * b)
{
    polypointer x;
    double c = 0;
    int e = 0;
    char s;
    FILE *fp;
    if((fp = fopen("demo.txt","rt")) == NULL)
    {
        printf("文件不存在\n");
        getchar();
        return 0;
    }
    while(fscanf(fp," %lf", &c) != EOF && fscanf(fp," %d%c", &e, &s) != EOF)
    {
        if((*a)->link == NULL)
            x = *a;
        x = polyAttach(c, e, x);
        if(s == '\n')
            break;
    }
    x = *a;
    *a = (*a)->link;
    while(fscanf(fp," %lf", &c) != EOF && fscanf(fp," %d%c", &e, &s) != EOF)
    {
        if((*b)->link == NULL)
            x = *b;
        x = polyAttach(c, e, x);
        if(s == '\n')
            break;
    }
    x = *b;
    *b = (*b)->link;
    free(x);
    fclose(fp);
    return 1;
}

/*文件写回*/
int FileOutput(polypointer a, polypointer b)
{
    FILE *fp;
    polypointer x ;
    fp = fopen("demo.txt", "w");
    if(fp == NULL)
    {
        printf("文件不存在\n");
        getchar();
        return 0;
    }
    x = a;
    while(x != NULL)
    {
        fprintf(fp, " %lf %d", x->coef, x->exp);
        x = x->link;
    }
    fprintf(fp, "\n");
    x = b;
    while(x != NULL)
    {
        fprintf(fp, " %lf %d", x->coef, x->exp);
        x = x->link;
    }
    fprintf(fp, "\n");
    fclose(fp);
    return 1;
}

/*比较两个指数的大小*/
char polyCompare(int a, int b)
{
    int sum = a-b;
    if(sum == 0)
        return '=';
    else if(sum > 0)
        return '>';
    else
        return '<';
}

polypointer polyAdd(polypointer a, polypointer b)
{
    polypointer p,q,c,d;
    double x;
    c = newPoly();
    p = a;q = b;
    d = c;          /*初始化*/
    if(p->coef == 0 && p->link == NULL && q->coef == 0 && q->link == NULL)  /*特殊：pq只有一个节点并且系数都为0*/
    {
        return c;
    }
    while((p!=NULL) && (q != NULL))
    {
        switch(polyCompare(p->exp , q->exp))
        {
            case '=' :
            {
                x = p->coef + q->coef;      /*系数相加*/
                if(x != 0)
                    d = polyAttach(x, p->exp, d);   /*等于0，消去这一项*/
                p = p->link;
                q = q->link;
                break;
            }
            case '>':
            {
                d = polyAttach(p->coef , p->exp, d);    /*直接将p结点并入d中*/
                p = p->link;
                break;
            }
            case '<':
            {
                d = polyAttach(q->coef, q->exp, d);     /*直接将q结点并入d中*/
                q = q->link;
                break;
            }
        }
    }
    while(p != NULL)
    {
        d = polyAttach(p->coef, p->exp, d);
        p = p->link;
    }
    while(q != NULL)
    {
        d = polyAttach(q->coef, q->exp, d);
        q = q->link;
    }
    d->link = NULL;
    p = c;
    c = c->link;
    free(p);
    polyRank(&c);
    return c;
}

polypointer polySub(polypointer a, polypointer b)
{
    polypointer p,q,c,d;
    double x;
    c = newPoly();
    p = a;q = b;
    d = c;          /*初始化*/
    if(p->coef == 0 && p->link == NULL && q->coef == 0 && q->link == NULL)  /*特殊：pq只有一个节点并且系数都为0*/
    {
        return c;
    }
    while((p!=NULL) && (q != NULL))
    {
        switch(polyCompare(p->exp , q->exp))
        {
            case '=' :
            {
                x = p->coef - q->coef;      /*系数相减*/
                if(x != 0)
                    d = polyAttach(x, p->exp, d);   /*等于0，消去这一项*/
                p = p->link;
                q = q->link;
                break;
            }
            case '>':
            {
                d = polyAttach(p->coef , p->exp, d);    /*直接将p结点并入d中*/
                p = p->link;
                break;
            }
            case '<':
            {
                d = polyAttach((-q->coef), q->exp, d);     /*直接将q结点并入d中,并且将q系数变为相反数*/
                q = q->link;
                break;
            }
        }
    }
    while(p != NULL)
    {
        d = polyAttach(p->coef, p->exp, d);
        p = p->link;
    }
    while(q != NULL)
    {
        d = polyAttach((-q->coef), q->exp, d);
        q = q->link;
    }
    d->link = NULL;
    p = c;
    c = c->link;
    free(p);
    polyRank(&c);
    return c;
}

polypointer polyMul(polypointer a, polypointer b)
{
    polypointer p, q, c, h, t;
    c = newPoly();
    p = a;
    q = b;
    h = c;      /*保存结果头节点*/
    c->link = h;/*建立环形链表*/
    t = c;      /*保存尾节点*/
    double co = 0;
    int e = 0;
    while(p != NULL)
    {
        while(q != NULL)
        {
            co = p->coef * q->coef;
            e = p->exp + q->exp;
            while(c != NULL)      /*寻找匹配项*/
            {
                if(e == c->exp)
                {
                    c->coef = co + c->coef;
                    break;
                }
                c = c->link;
                if(c->link == h)
                {
                    c = polyAttach(co, e, c);
                    c->link = h;    /*尾指针指向头节点，循环链表*/
                    t = c;
                    break;
                }
            }
            q = q->link;
        }
        p = p->link;
        q = b;  /*复位*/
    }
    t->link = NULL;     /*修改尾节点*/
    if(h->link != NULL && h->coef == 0) /*是否就一个节点*/
    {
        p = h;
        h = h->link;
        free(p);
    }
    polyRank(&h);   /*多项式整理*/
    return h;
}

polypointer polyDiv(polypointer a, polypointer b)
{
    polypointer p, q, c, d, e, h;  /*c 结果，d 结果*除式，e 差式（新的被除式）*/
    double co = 0;
    int ex = 0;
    p = a;
    q = b;
    e = p;
    c = newPoly();
    h = c;
    if(p->exp < q->exp)     /*被除式最高项指数小于除式指数，余数项为被除式*/
    {
        c = p;
        return c;
    }
    while(e->exp >= q->exp)
    {
        co = e->coef / q->coef;
        ex = e->exp - q->exp;
        c = polyAttach(co, ex, c);
        d = polyMul(c, q);
        e = polySub(e, d);      /*新的被除式*/
    }
    printf("两式之余数为： ");
    polyPrint(e);
    c = h->link;
    free(h);
    polyRank(&c);
    return c;
}

/*计算x=x0多项式的和*/
float polyCalc(polypointer arg, float x)
{
    double sum = 0;
    double result = 0;
    while(arg != NULL)
    {
        result = pow((double)x, (double)arg->exp);
        sum = sum + (arg->coef) * result ;
        arg = arg->link;
    }
    return sum;
}

void polyState(polypointer a, polypointer b)
{
    printf( "========================\n"
            "数据结构与算法第一次实验\n"
            "A:");
    polyPrint(a);
    printf("B:");
    polyPrint(b);
    printf("========================\n");

}

/*菜单*/
void Menu()
{
    polypointer a,b,c;  /*建立3个多项式指针*/
    a = newPoly();
    b = newPoly();
    c = newPoly();         /*初始化*/
    float x = 0;
    while(1)
    {
        fflush(stdin);
        char op;
        system("cls");
        polyState(a, b);
        printf("1.建立指数降幂排列多项式\n"
               "2.计算x=x0的值\n"
               "3.多项式的四则运算\n"
               "4.打印当前多项式\n");
        op = getchar();
        switch(op)
        {
        case '1':
            {
                fflush(stdin);
                system("cls");
                polyState(a, b);
                printf("1.手动输入\n2.文件输入\n3.文件输出\n");
                op = getchar();
                if(op == '1')
                {
                    a = newPoly();
                    b = newPoly();
                    printf("请输入第一个多项式，系数与指数，中间空格分开,回车确认\n");
                    HandInput(&a);
                    polyRank(&a);
                    polyPrint(a);
                    printf("请输入第二个多项式，系数与指数，中间空格分开,回车确认\n");
                    HandInput(&b);
                    polyRank(&b);
                    polyPrint(b);
                    printf("输入任意键继续\n");
                    fflush(stdin);
                    getchar();
                }
                else if(op == '2')
                {
                    a = newPoly();
                    b = newPoly();
                    FileInput(&a, &b);
                    polyRank(&a);
                    polyRank(&b);
                    polyPrint(a);
                    polyPrint(b);
                    printf("输入任意键继续\n");
                    fflush(stdin);
                    getchar();
                }
                else if(op == '3')
                {
                    if(!FileOutput(a, b))
                    {
                        printf("输出错误\n");
                    }
                    printf("输入任意键继续\n");
                    fflush(stdin);
                    getchar();
                }
                else
                    printf("选项不存在\n");
                break;
            }
        case '2':
            {
                printf("请输入x0的值\n");
                scanf("%f", &x);
                printf("x=%f的计算结果为： \nA: %f\nB: %f\n", x,polyCalc(a, x), polyCalc(b,x));
                printf("输入任意键继续\n");
                fflush(stdin);
                getchar();
                break;
            }
        case '3':
            {
                fflush(stdin);
                system("cls");
                polyState(a, b);
                printf("1.多项式加法\n2.多项式减法\n3.多项式乘法\n4.多项式除法\n");
                op = getchar();
                if(op == '1')
                {
                    polyPrint(a);
                    polyPrint(b);
                    c = polyAdd(a, b);
                    printf("两式之和为： ");
                    polyPrint(c);
                    printf("输入任意键继续\n");
                    fflush(stdin);
                    getchar();
                }
                else if(op == '2')
                {
                    polyPrint(a);
                    polyPrint(b);
                    c = polySub(a, b);
                    printf("两式之差为： ");
                    polyPrint(c);
                    printf("输入任意键继续\n");
                    fflush(stdin);
                    getchar();
                }
                else if(op == '3')
                {
                    polyPrint(a);
                    polyPrint(b);
                    c = polyMul(a, b);
                    printf("两式之积为： ");
                    polyPrint(c);
                    printf("输入任意键继续\n");
                    fflush(stdin);
                    getchar();
                }
                else if(op == '4')
                {
                    polyPrint(a);
                    polyPrint(b);
                    c = polyDiv(a, b);
                    printf("两式之商为： ");
                    polyPrint(c);
                    printf("输入任意键继续\n");
                    fflush(stdin);
                    getchar();
                }
                else
                {
                    printf("选项不存在");
                    printf("输入任意键继续\n");
                    fflush(stdin);
                    getchar();
                }

                break;
            }
            case '4':
            {
                polyPrint(a);
                polyPrint(b);
                printf("输入任意键继续\n");
                fflush(stdin);
                getchar();
                break;
            }
            default :
                {

                }

        }
    }

}

int main()
{
    Menu();
    return 0;
}
