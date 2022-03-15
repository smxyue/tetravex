#include <stdio.h>

//char matrix[36]={'2','8','5','9','6','3','8','2','2','8','1','1','4','4','8','6','4','9','8','4','1','8','8','9','1','1','8','2','9','9','3','4','0','8','7','1'};;
//char matrix[36]=  {'3','4','2','1','3','2','4','1','5','4','6','7','1','2','2','3','1','2','3','4','7','3','8','6','3','1','4','0','4','4','5','9','6','5','8','8'};
char matrix[36]=  {'3','4','2','1','5','4','6','7','1','2','2','3','1','2','3','4','7','3','8','6','3','1','4','0','4','4','5','9','3','2','4','1','6','5','8','8'};
char p[9];
unsigned long count = 0;

void inputMatrix();
void printMatrix();
void printp();
void initMatrix();
void makeTry();
int getBlockIndex(int block);
bool checkp();
void test();

int main()
{
    initMatrix();
    makeTry();
    //test();
    printf("%ld tryed, Done!\n\r",count);
}

void inputMatrix()
{
    printf("Input block number one by one(up-left-right-down order:\n\r");
    int count = 0;
    while (count <36)
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
void printMatrix()
{
    for(int row =0;row <3;row++)
    {
        for(int col = 0;col <3;col ++)
        {
            int start = (row * 3 + col) * 4;
            printf("[%c %c %c %c] ",matrix[start],matrix[start +1],matrix[start+2],matrix[start +3]);
        }
        printf("\n\r");
    }
}

void initMatrix()
{
    //matrix = {'2','8','5','9','6','3','8','2','2','8','1','1','4','4','8','6','4','9','8','4','1','8','8','9','1','1','8','2','9','9','3','4','0','8','7','1'};
}
void makeTry()
{
    count = 0;
    for(int a=0;a<9;a++)
        for(int b=0;b<9;b++)
            for(int c =0;c<9;c++)
                for(int d=0;d<9;d++)
                    for(int e=0;e<9;e++)
                        for(int f=0;f<9;f++)
                            for(int g=0;g<9;g++)
                                for(int h=0;h<9;h++)
                                    for(int i=0;i<9;i++)
                                    {
                                        if ( a!=b && b!=c && c!=d && d!=e && e !=f && f !=g && g!=h && h!=i && a !=c && a !=d && a!=e && a!=f && a!=g && a!=h && a!=i && b!=d && b!=e && b!=f && b!=g && b!=h && b!=i && c !=e && c !=f && c!=g && c!=h && c!=i && d !=f && d !=g && d !=h && d !=i && e !=g && e !=h && e !=i && f !=h && f!=i && g !=i )
                                        {
                                            p[0] =a;
                                            p[1] =b;
                                            p[2] =c;
                                            p[3] =d;
                                            p[4] =e;
                                            p[5] =f;
                                            p[6] =g;
                                            p[7] =h;
                                            p[8] =i;
                                            count ++;
                                            
                                            if (checkp())
                                            {
                                                printf("try:%d\n\r",count);
                                                printp();
                                                for(int j=0;j<9;j++)
                                                {
                                                    int tindex = getBlockIndex(j);
                                                    printf("{%c,%c,%c,%c}",matrix[tindex*4],matrix[tindex*4+1],matrix[tindex*4+2],matrix[tindex*4+3]);
                                                }
                                                printf("\n\r");
                                            }
                                        }
                                        
                                    }
}

bool checkp()
{
    int tindex;//相邻位
    for (int i=0;i<9;i++)//检查所有9个位置是否都正确
    {
        int index = p[i]; //当前位排列在哪
        int row = i / 3;
        int col = i % 3;
        //printf("\n\r%d index %d row %d col %d",i,p[i],row,col);
         //上
        if (row > 0)
        {
            tindex = (row -1) * 3 + col; //行少列同
            tindex = getBlockIndex(tindex);//该位实际的块是第几个。
            //printf("u:");
            if (matrix[index*4] != matrix[tindex*4+3])
                {
                    if (p[0]==0 && p[1] == 2 && p[2]==3 && p[3] == 4 && p[4] ==5 && p[5] ==6 && p[6] == 7 && p[7]==1)
                                            printf("UF");
                                            
                    return false;
                }    
            
        }
        //右
        if (col <2)
        {
            tindex = row *3 + col +1;
            tindex = getBlockIndex(tindex);
            //printf("r:");
             if (matrix[index * 4 +2]  != matrix[tindex*4 +1])
             {
                if (p[0]==0 && p[1] == 2 && p[2]==3 && p[3] == 4 && p[4] ==5 && p[5] ==6 && p[6] == 7 && p[7]==1)
                                            printf("%d  DF%d:%C  %d:%C\n\r",i,index, matrix[index*4 +2],tindex,matrix[tindex * 1]);
                return false;
             }
            
        }
        //下
        if (row <2)
        {
            tindex = (row + 1) * 3 + col;
            tindex = getBlockIndex(tindex);
            //printf("d:");
            if (matrix[index*4 +3] != matrix[tindex * 4])
            {
                 if (p[0]==0 && p[1] == 2 && p[2]==3 && p[3] == 4 && p[4] ==5 && p[5] ==6 && p[6] == 7 && p[7]==1)
                                            printf("%d  DF%d:%C  %d:%C\n\r",i,index, matrix[index*4 +3],tindex,matrix[tindex * 4]);
                 return false;
            }    
           
        }
        //左
        if (col >0)
        {
            tindex = row * 3 + col -1;
            tindex = getBlockIndex(tindex);
            //printf("l:");
             if (matrix[index *4 + 1] != matrix[tindex *4 +2])
            {
                if (p[0]==0 && p[1] == 2 && p[2]==3 && p[3] == 4 && p[4] ==5 && p[5] ==6 && p[6] == 7 && p[7]==1)
                                            printf("LF");
                return false;
            }
            
        }
    }
    return true;
}
int getBlockIndex(int block) //获取相邻位
{
    for (int j=0;j<9;j++)
    {
        if (p[j] == block)
        {
            return j;
        }
    }
    return -1;
}
void printp()
{
    for(int i=0;i<9;i++)
    {
        printf("%5d",p[i]);
    }
    printf("\n\r");
}


void test()
{
    p[0] = 0;
    p[1] = 2;
    p[2] = 3;
    p[3] = 4;
    p[4] = 5;
    p[5] = 6;
    p[6] = 7;
    p[7] = 1;
    p[8] = 8;
    for (int i=0;i<9;i++)
    {
        int index = p[i];
        int tindex = getBlockIndex(index);
        printf("%d  %d:%d  ",i,index,tindex);
    }
}
