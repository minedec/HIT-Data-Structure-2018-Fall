/*
 * 姓名：
 * 学号：1163450201
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define RANDOM 0
#define FEWUNIQUE 1
#define REVERSE 2
#define SORTED 3
#define SIZE1 1e+1
#define SIZE2 1e+2
#define SIZE3 1e+3
#define SIZE4 1e+4
#define SIZE5 1e+5
#define SIZE_BIG 2e+4
#define SIZE_HUGE 1e+7

void list(int n, int arr[]);                // 打印数组元素
void BubbleSort(int n, int arr[]);          //冒泡排序
void swap(int * x, int * y);                //交换元素
void QuickSort(int i, int j, int A[]);    //快速排序
int * random(int size);                     //生成size大小乱序数据
int * fewunique(size);                      //生成size大小两点分布
int * reverse(int size);                    //生成size大小的倒序
int * sorted(int size);                     //生成size大小的顺序
double test(int size, int sort, int choice);//测试用函数
void menu();                                //菜单

void list(int n, int arr[])
{
    int i;
    for(i = 0; i < n; i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
}

void BubbleSort(int n, int arr[])
{
    int i,j;
    for(i = 0; i < n-1; i++)
    {
        for(j = n-1; j >= i+1; j--)
        {
            if(arr[j] < arr[j-1])
            {
                swap(&arr[j], &arr[j-1]);
            }
        }
    }
}

void swap(int * x, int * y)
{
    int tmp;
    tmp = *x;
    *x = *y;
    *y = tmp;
}

void QuickSort(int i, int j, int arr[]) 
{
  int L, R, pivot, temp;

  if(i == j) return;
  L=i;
  R=j;
  pivot= arr[(i+j)/2];  //寻找中间值

  // 从两端开始交换
  do {
    while (arr[L] < pivot) L++;
    while (arr[R] > pivot) R--;
    if (L <=R) {
      temp= arr[L];
      arr[L]= arr[R];
      arr[R]=temp;
      L++;
      R--;
    }
  } while (L<=R);
  //递归
  if (i < R) QuickSort(i, R, arr);
  if (L < j) QuickSort(L, j, arr);
}

int * random(int size)
{
    int i,j,k,tmp;
    int * arr;
    arr = malloc(sizeof(int)*size);
    for(i = 0; i < size; i++)
    {
        arr[i] = i;
    }
    srand((unsigned)(time(NULL)));
	for(k = 0; k < size; k++)
	{
		i = rand() % size;
		j = rand() % size;
		tmp = arr[i];
		arr[i] = arr[j];
		arr[j] = tmp;
	}
	//printf("random data set down...\n");
	return arr;
}

int * fewunique(size)
{
    int i,j, k,tmp;
    int * arr;
    arr = malloc(sizeof(int)*size);
    for(i = 0; i < size/2; i++)
    {
        arr[i] = 5;
    }
    for(j=i; j < size; j++)
    {
        arr[j] = 10;
    }
    for(k = 0; k < size; k++)
	{
		i = rand() % size;
		j = rand() % size;
		tmp = arr[i];
		arr[i] = arr[j];
		arr[j] = tmp;
	}
	//printf("fewunique data set down...\n");
	return arr;
}

int * reverse(int size)
{
    int i,j,k,tmp;
    int * arr = malloc(sizeof(int)*size);
    for(i = 0; i < size; i++)
    {
        arr[size - 1 - i] = i;
    }
    //printf("reverse data set down...\n");
    //list(size, arr);
    return arr;
}

int * sorted(int size)
{
    int i,j,k,tmp;
    int * arr = malloc(sizeof(int)*size);
    for(i = 0; i < size; i++)
        arr[i] = i;
    srand((unsigned)(time(NULL)));
	for(k = 0; k < size/8; k++)
	{
		i = rand() % size;
		j = rand() % size;
		tmp = arr[i];
		arr[i] = arr[j];
		arr[j] = tmp;
	}
	//printf("sorted data set down...\n");
	return arr;
}

double test(int size, int sort, int choice)
{
    int * arr = NULL;
    long start, finish;
    double dua;
    if(sort == RANDOM)
    {
        arr = random(size);
    }
    else if(sort == FEWUNIQUE)
    {
        arr = fewunique(size);
    }
    else if(sort == REVERSE)
    {
        arr = reverse(size);
    }
    else if(sort == SORTED)
    {
        arr = sorted(size);
    }

    if(choice == 0)
    {
       start = clock();
       BubbleSort(size, arr);
       finish = clock();
       //list(size, arr);

       free(arr);
       //return (double)((finish - start));
       return ((double)(finish - start)/CLOCKS_PER_SEC);
    }
    else if(choice == 1)
    {
        start = clock();
        QuickSort(0, size-1, arr);
        finish = clock();
        //list(size, arr);
        free(arr);
        //return (double)(finish - start);
        dua = (double)(finish - start)/CLOCKS_PER_SEC;
        return dua;
    }

}

void menu()
{
    char op = 0;
    double duration;
    int size, sort;
    while(1)
    {
        fflush(stdin);
        printf("===================\n"
               "LAB5\n"
               "===================\n"
               "1. Auto Test Bubble Sort and Quick Sort\n"
               "2. Manual Test\n");
        op = getchar();
        switch(op)
        {
        case '1':
            {
                printf("+------------+-------------+-----------------+------------------+---------------+--------------+\n"
                       "|    SIZE    |     TYPE    |      RANDOM     |     FEWUNIQUE    |     REVERSE   |     SORTED   |\n");
                printf("+------------+-------------+-----------------+------------------+---------------+--------------+\n");
                for(size = 1000; size < 10000; size +=1000)
                {
                printf("|%12d| Bubble Sort |%16.5lfs|%17.5lfs|%14.5lfs|%13.5lfs|\n"
                       "|            | Quick  Sort |%16.5lfs|%17.5lfs|%14.5lfs|%13.5lfs|\n"
                       "+------------+-------------+-----------------+------------------+---------------+--------------+\n",size,
                       test(size, RANDOM, 0),test(size, FEWUNIQUE, 0),test(size, REVERSE, 0),test(size, SORTED, 0),
                       test(size, RANDOM, 1),test(size, FEWUNIQUE, 1),test(size, REVERSE, 1),test(size, SORTED, 1));
                }
                printf(
                       "|    SIZE    |     TYPE    |      RANDOM     |     FEWUNIQUE    |     REVERSE   |     SORTED   |\n");
                printf("+------------+-------------+-----------------+------------------+---------------+--------------+\n");
                for(size = 10000; size< 100000; size+= 10000)
                {
                    printf("|%12d| Bubble Sort |%16.5lfs|%17.5lfs|%14.5lfs|%13.5lfs|\n"
                       "|            | Quick  Sort |%16.5lfs|%17.5lfs|%14.5lfs|%13.5lfs|\n"
                       "+------------+-------------+-----------------+------------------+---------------+--------------+\n",size,
                       test(size, RANDOM, 0),test(size, FEWUNIQUE, 0),test(size, REVERSE, 0),test(size, SORTED, 0),
                       test(size, RANDOM, 1),test(size, FEWUNIQUE, 1),test(size, REVERSE, 1),test(size, SORTED, 1));
                }
                printf(
                       "|    SIZE    |     TYPE    |      RANDOM     |     FEWUNIQUE    |     REVERSE   |     SORTED   |\n");
                printf("+------------+-------------+-----------------+------------------+---------------+--------------+\n");
                for(size = 100000; size<= 300000; size+= 10000)
                {
                    printf("|%12d| Bubble Sort |%16.5lfs|%17.5lfs|%14.5lfs|%13.5lfs|\n"
                       "|            | Quick  Sort |%16.5lfs|%17.5lfs|%14.5lfs|%13.5lfs|\n"
                       "+------------+-------------+-----------------+------------------+---------------+--------------+\n",size,
                       test(size, RANDOM, 0),test(size, FEWUNIQUE, 0),test(size, REVERSE, 0),test(size, SORTED, 0),
                       test(size, RANDOM, 1),test(size, FEWUNIQUE, 1),test(size, REVERSE, 1),test(size, SORTED, 1));
                }

                break;
            }
        case '2':
            {
                printf("size \n");
                scanf("%d", &size);
                printf("\nBubble Sort:\n");
                duration = test(size, RANDOM, 0);
                printf("RANDOM time is    %.5lfs\n", duration);
                duration = test(size, FEWUNIQUE, 0);
                printf("FEWUNIQUE time is %.5lfs\n", duration);
                duration = test(size, REVERSE, 0);
                printf("REVERSE time is   %.5lfs\n", duration);
                duration = test(size, SORTED, 0);
                printf("SORTED time is    %.5lfs\n", duration);
                printf("\n");
                printf("Quick Sort:\n");
                duration = test(size, RANDOM, 1);
                printf("RANDOM time is    %.5lfs\n", duration);
                duration = test(size, FEWUNIQUE, 1);
                printf("FEWUNIQUE time is %.5lfs\n", duration);
                duration = test(size, REVERSE, 1);
                printf("REVERSE time is   %.5lfs\n", duration);
                duration = test(size, SORTED, 1);
                printf("SORTED time is    %.5lfs\n", duration);
                printf("\n");
                break;
            }
        }
    }
}
int main()
{
    menu();
    printf("Hello world!\n");
    return 0;
}
