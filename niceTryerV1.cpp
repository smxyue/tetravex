#include <stdio.h>
#include <list>

#define GAMESCALE 5
#define GAMEBLOCKS GAMESCALE * GAMESCALE

struct BackPoint
{
    char room;
    char dir;
    char neighbor;
};
char matrix[GAMEBLOCKS*4] = {1,6,8,7,2,8,7,5,4,7,5,3,3,5,4,7,4,4,1,4,7,0,0,3,5,0,3,0,3,3,4,5,7,4,8,7,4,8,1,2,3,4,8,2,0,8,2,6,5,2,2,7,7,2,8,7,2,8,6,0,2,2,3,3,6,3,9,6,7,9,0,6,7,0,8,3,0,8,6,6,1,1,5,4,7,5,8,7,6,8,7,1,7,7,4,1,3,4,1,2};
char p[GAMEBLOCKS];
char tryIndex = 0;
char tryOrder[GAMEBLOCKS];
std::list<BackPoint> backList;
void initTryOrder()
{
    for(int i=0;i<GAMEBLOCKS;i++)
    {
        tryOrder[i] = -1;
        p[i] = -1;
    }
}
void ascMatrix()
{
    for(int i=0;i<GAMEBLOCKS*4;i++)
        matrix[i] += '0';
}
void printMatrix()
{
    for(int i=0;i<GAMEBLOCKS;i++)
    {
        printf("%d{%c,%c,%c,%c} ",i,matrix[i*4],matrix[i*4+1],matrix[i*4+2],matrix[i*4+3]);
    }
}
void printP(bool block = false)
{
    printf("\n\r");
    for(int i=0;i<GAMEBLOCKS;i++)
    {
        printf(" %d",p[i]);
        if (block)
        {
            printf(":{%c %c %c %c} ");
        }
    }
}

int testLine[GAMEBLOCKS];
bool isUsed(char index) //块index是否已经使用
{
    for (int i=0;i<=tryIndex;i++)
    {
        if (tryOrder[i] == index)
        {
            return true; 
        }
    }
     return false;
}
bool isNeigborFit(char row,char col,char block)//index块如果放在row，col位置，是否四邻和谐？
{
    int tindex; 
     //上临
     if (row > 0)
     {
        tindex = (row-1)*GAMESCALE+col; //邻居房号
        tindex = p[tindex];//入住块
        if (tindex != -1) //没有填
        {
            if (matrix[block*4] != matrix[tindex*4+3])
            {
                 return false;
            }    
        }
     }
     //左
    if (col >0)
    {
        tindex = row*GAMESCALE+col-1;
        tindex = p[tindex];
        if (tindex != -1)
        {
            if (matrix[block*4+1] != matrix[tindex*4+2])
            {
                return false;
           }
        }
    }
     //右
     if (col < (GAMESCALE-1))
     {
        tindex = row*GAMESCALE+col+1;
        tindex = p[tindex];
        if(tindex != -1)
        {
            if (matrix[block *4+2]  != matrix[tindex*4+1])
            {
                return false;
            }
         }
     }
     //下
     if (row < (GAMESCALE-1))
     {
        tindex = (row+1)*GAMESCALE+col;
        tindex = p[tindex];
        if (tindex != -1)
        {
            if (matrix[block*4+3] != matrix[tindex*4])
            {
                return false;
            }    
        }
    }
    return true;
}
void printTryOrder()
{
    printf("TryOder:[");
    for (int i =0;i<tryIndex;i++)
    {
        printf("%d ",tryOrder[i]);
    }
    printf("]\n\r");
}
void addTry(char row, char col,char dir, char i, char *found)//将i作为row-1,col居民
{
    
    char newIndex = row*GAMESCALE + col;
    (*found) ++;
    if ((*found) ==1)
    {
        p[newIndex] == i;
        tryIndex ++;
        tryOrder[tryIndex] = i;
        printTryOrder();
    }
    else if ( (*found) >1)
    {
        BackPoint point;
        point.room = row * GAMESCALE + col;
        point.dir = dir;
        point.neighbor = i;
        backList.push_back(point);
    }

}
int findNeigborBlocks(char room,char dir)//查找所有合适的邻居块，如果有一个，填入，如果有多个，剩余的加入预备队。返回找到的邻居数。
{
    char found = 0;
    char row = room / GAMESCALE;
    char col = room % GAMESCALE;
    for(char i=0;i<GAMEBLOCKS;i++)  //查找所有未使用块
    {
        if (!isUsed(i))
        {
            if (dir ==0 && row >0)
            {
                if (matrix[room*4] == matrix[i*4+3])
                {
                    if (isNeigborFit(row-1,col,i))
                    {
                        addTry(row,col,dir,i,&found);                        
                    }
                }
            }
            else if (dir ==1 && col >0)
            {
                if (matrix[room*4+1] == matrix[i*4+2])
                {
                     if(isNeigborFit(row,col-1,i))
                    {
                        addTry(row,col-1,dir,i,&found); 
                    }
                }
            }
            else if (dir ==2 && col < GAMESCALE -1)
            {
                if (matrix[room *4+2] == matrix[i*4+1])
                {
                    if (isNeigborFit(row,col+1,i))
                    {
                        addTry(row,col+1,dir,i,&found); 
                    }
                }
            }
            else if (dir ==3 && row < GAMESCALE -1)
            {
                if (matrix[room*4+3] == matrix[i*4])
                {
                    printf("\n\rhas down neighbor\n\r");
                     if (isNeigborFit(row+1,col,i))
                    {
                        addTry(row+1,col,dir,i,&found); 
                    }
                }
            }
        }
    }
    return found;
}
char getEmpty()
{
    for(char i=0;i<GAMEBLOCKS;i++)
    {
        if (p[i]==-1)
            return i; 
    }
    return -1;
}
char getEmptyNeigborRoom(char *empty) //返回合适的块号，对比的方位在empty中
{
    char row = (*empty) / GAMESCALE;
    char col = (*empty) % GAMESCALE;
    //printf("empty gird%d:%d,%d\n\r",*empty,row,col);

    char index;
    if (row>0)
    {
        index = (row-1) * GAMESCALE + col;
        if (p[index] != -1)//邻居在上，空在下
        {
            *empty = 3;    
            return index;
        }
    }
    if (col>0)
    {
        index = row * GAMESCALE + col -1;
        if (p[index] != -1)//邻居在左，空在右
        {    
            *empty = 2;
            return index;
        }
    }
    if (col <GAMESCALE -1)
    {
        index = row * GAMESCALE + col +1;
        if (p[index] != -1)//邻居在右，空在左
        {
            *empty =1;
            return index;
        }
    }
    if (row < GAMESCALE -1)
    {
        index = (row +1) * GAMESCALE + col;
        if (p[index]!=-1) //邻居在下，空在上
        {
            *empty = 0;
            return index;
        }
    }
    return -1;  //this will gota never happen.
}
int getNeighBorRoom(char room, char dir)
{
    char row, col,index;
    row = room /GAMESCALE;
    col = room %GAMESCALE;
    if (dir ==0)
        return index - GAMESCALE;
    if (dir == 1)
        return index -1;
    if (dir ==2)
        return index +1;
    if (dir ==3)
        return index + GAMESCALE;
    return -1;
}
bool isTry=true;
int main()
{
    ascMatrix();
    printMatrix();
    for(int i=0;i<GAMEBLOCKS;i++)
    {
        printf("\n\rtry:%d......\n\r",i);
        initTryOrder();
        tryOrder[0] = i;
        p[0] = i;
        isTry= true;
        while (isTry)
        {
            char empty = getEmpty();    //获取空位置
            if (empty == -1)            //如果全部填完，打印,结束。
            {
                printP();
                isTry = false;
            }
            else
            {
                char room = getEmptyNeigborRoom(&empty);    //获取空白位附近的邻居，作为填充依据
                if (findNeigborBlocks(room,empty)==0)//如果没找到合适邻居块，需要回退
                {
                    if (backList.empty())
                    {
                        isTry = false; //无后备可用，失败返回
                    }
                    else
                    {
                        BackPoint last = backList.back();//获取最后一个后备位置
                        while (tryOrder[tryIndex] != last.neighbor)
                        {
                            for(int i=0;i<GAMEBLOCKS;i++)
                            {
                                if (p[i] == tryOrder[tryIndex])
                                {
                                    p[i] = -1; //抹去排除
                                }
                                tryOrder[tryIndex] = -1; //抹去试探记录
                                tryIndex --;
                            }
                        }
                        //抹去上一个试探位
                        char lastIndex = getNeighBorRoom(last.room,last.dir);
                        p[lastIndex] = last.neighbor;
                        backList.pop_back();
                    }
                }
            }
        }
    }
    printf("\n\rDone...\n\r");
}