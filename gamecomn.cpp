#include <stdio.h>
#include <time.h>
#define GAMESCALE 4
#define testSize  7
void qpl(int *chs,int *p,int size);
void CloneP(int *p,int *newp);
void CloneChs(int *old, int *newp,int index, int size);
int matrix[4*GAMESCALE*GAMESCALE] = {'9','3','6','7','2','4','8','0','4','6','2','0','3','2','4','4','7','6','7','8','3','7','1','2','4','6','0','6','0','8','1','7','4','0','3','2','7','9','8','4','0','5','0','7','5','0','2','3','8','2','5','1','1','1','9','0','6','8','7','3','0','3','6','0'};
int p[GAMESCALE*GAMESCALE] = {-1};
int chs[GAMESCALE*GAMESCALE]={0};
int count =0;
void printTime();
void printMatrix();
bool checkp(int *pp);
bool checkItem(int *pp,int row, int col);
bool preCheck(int *pp,int len);
void printP(int *pp);
void inputMatrix();
int maxTry = 5;
int ap[25] = {23, 24,20, 3, 4, 0, 1, 2, 21, 9, 5, 6, 7, 8, 14, 10, 11, 12, 13, 19, 15, 16, 17, 18, 22};
void qplTest();

int main()
{
    
    for (int i=0;i<GAMESCALE*GAMESCALE;i++)
    {
        chs[i] = i;
        p[i] = -1;
    }
    
    inputMatrix();
    count =0;
    printTime();
    qpl(chs,p,GAMESCALE*GAMESCALE);
    //qplTest();
    printTime();
    printf("%d tryed!\n\r",count);
    //printMatrix();
}
void printMatrix()
{
    for(int row =0;row <GAMESCALE;row++)
    {
        for(int col = 0;col <GAMESCALE;col ++)
        {
            int start = (row * GAMESCALE + col) * 4;
            printf("[%c %c %c %c] ",matrix[start],matrix[start +1],matrix[start+2],matrix[start +3]);
        }
        printf("\n\r");
    }
}
void CloneChs(int *old, int *clone,int index, int size) //旧序列  新序列  要移除的元素索引  要克隆的序列长度。
{
    //去除某个特定的元素后形成新序列，空白填充-1
    for (int i=0;i<index;i++)
    {
        clone[i] = old[i];
    }
    for(int i=index;i<size-1;i++)
    {
        clone[i] = old[i+1];
    }
    for(int i=size;i<GAMESCALE*GAMESCALE;i++)
        clone[i] = -1;
}
void CloneP(int *oldp,int *newp)
{
    //复制已经排列好的位置的值，并把
    for(int i=0;i<GAMESCALE*GAMESCALE;i++)
    {
        newp[i] = oldp[i];
    }
}
void qpl(int * chs,int *pp,int size) //待选数组， 排序数组，排列长度
{
    //从最低位开始，依次填入待选数组里的所有元素，然后把这个顺序号去掉，用剩下的可选位排其他的
    if (size ==1)
    {
        pp[GAMESCALE*GAMESCALE-1] = chs[0];
        if (checkp(pp))
        {
            printf("try:%d\n\r",count);
            for(int l=0;l<GAMESCALE*GAMESCALE;l++)
            {
                int r = pp[l];
                printf("%d  {%c %c %c %c}  ",r,matrix[r*4],matrix[r*4+1],matrix[r*4+2],matrix[r*4+3]);
            }
         }
        count++;
    }
    else
    {
        for(int i=0;i<size;i++)
        {
            int newP[GAMESCALE*GAMESCALE] = {-1};
            for(int j=0;j<GAMESCALE*GAMESCALE;j++)
            {
                newP[j] = pp[j];
            }
            newP[GAMESCALE*GAMESCALE - size] = chs[i];
            int newChs[GAMESCALE*GAMESCALE];
            for (int j=0;j<i;j++)
            {
                newChs[j] = chs[j];
            }
            for(int j=i;j<size-1;j++)
            {
                newChs[j] = chs[j+1];
            }
            for(int j=size;j<GAMESCALE*GAMESCALE;j++)
                newChs[j] = -1;
            int newSize = size -1;
            if (preCheck(newP,GAMESCALE*GAMESCALE -size))//如果前置序列已经不对，后续的所有序列都不需要试探了
            {
                qpl(newChs,newP,newSize);
            }
        }
    }
}
void qplv1(int * chs,int *pp,int size) //待选数组， 排序数组，排列长度
{
    //从最低位开始，依次填入待选数组里的所有元素，然后把这个顺序号去掉，用剩下的可选位排其他的
    if (size ==1)
    {
        pp[testSize-1] = chs[0];
        printf("\n\r[");
        for (int i=0;i<testSize;i++)
       {
            if (pp[i] != -1)
                printf("%d ",pp[i]);
        }
        printf("]\n\r");
        count++;
    }
    else
    {
        for(int i=0;i<size;i++)
        {
            int newP[testSize] = {-1};
            for(int j=0;j<testSize;j++)
            {
                newP[j] = pp[j];
            }
            newP[testSize - size] = chs[i];
            int newChs[testSize];
            for (int j=0;j<i;j++)
            {
                newChs[j] = chs[j];
            }
            for(int j=i;j<size-1;j++)
            {
                newChs[j] = chs[j+1];
            }
            for(int j=size;j<testSize;j++)
                newChs[j] = -1;

            int newSize = size -1;
            if (newSize ==10000)
            {
                printf("**chs[");
                for(int j=0;j<testSize;j++)
                {
                    printf("%d ",newChs[j]);
                }
                printf("]\n\r");
            }
            qplv1(newChs,newP,newSize);
        }
    }
}
bool preCheck(int *pp,int len) //排列数组   长度
{
    for(int i=0;i<len;i++)
    {
        if (!checkItem(pp,i,pp[i]))
        {
             return false; 
        }
    }
    return true;
}
bool checkItem(int *pp,int grid,int index) //格位  值位
{
    if (index == -1)
        return true;
    int tindex;
    int row = grid / GAMESCALE;
    int col = grid % GAMESCALE;
     //上
     if (row > 0)
     {
        tindex = (row-1)*GAMESCALE+col; //行少列同
        tindex = pp[tindex];//该位实际的块是第几个。
        if (tindex != -1) //没有填
        {
            if (matrix[index*4] != matrix[tindex*4+3])
            {
                 return false;
            }    
        }
     }
     //右
     if (col < (GAMESCALE-1))
     {
        tindex = row*GAMESCALE+col+1;
        tindex = pp[tindex];
        if(tindex != -1)
        {
            if (matrix[index *4+2]  != matrix[tindex*4+1])
            {
                return false;
            }
        }
     }
     //下
     if (row < (GAMESCALE-1))
     {
        tindex = (row+1)*GAMESCALE+col;
        tindex = pp[tindex];
        if (tindex != -1)
        {
            if (matrix[index*4+3] != matrix[tindex*4])
            {
                return false;
            }    
        }
    }
    //左
    if (col >0)
    {
        tindex = row*GAMESCALE+col-1;
        tindex = pp[tindex];
        if (tindex != -1)
        {
            if (matrix[index*4+1] != matrix[tindex*4+2])
            {
                return false;
           }
        }
    }
    return true;
}
bool checkp(int *pp)
{
    int tindex;//相邻位
    for (int i=0;i<GAMESCALE * GAMESCALE;i++)//检查所有9个位置是否都正确
    {
        int index = pp[i]; //当排位为i的实际是matrix里的哪个
        if (!checkItem(pp,i,index))
            return false;
    }
    return true;
}

void printP(int *pp)
{
    printf("\n\r[");
    for (int i=0;i<GAMESCALE*GAMESCALE;i++)
    {
        if (pp[i] != -1)
            printf("%d ",pp[i]);
    }
    printf("]\n\r");
}

void inputMatrix()
{
    printf("Input block number(%d total) one by one(up-left-right-down order:\n\r",GAMESCALE*GAMESCALE * 4);
    int count = 0;
    while (count <GAMESCALE*GAMESCALE *4)
    {
        char ch = getchar();
        if (ch >='0' && ch <='9')
        {
            matrix[count] = ch;
            printf("%2d:%c\n\r",count,ch);
            count ++;
        }
    }
    printMatrix();
}

void printTime()
{
    time_t timep;
    time(&timep);
    struct tm *p;
    p=gmtime(&timep);
    printf("\n%d-%d-%d %d:%d:%d\n",1900+p->tm_year, 1+p->tm_mon,p->tm_mday,8+p->tm_hour,p->tm_min,p->tm_sec);
}

void qplTest()
{
    printf("\n\rTest....\n\r");
    qplv1(chs,p,testSize);
}