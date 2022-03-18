#include <stdio.h>
#include <list>

#define GAMESCALE 5
#define GAMEBLOCKS GAMESCALE * GAMESCALE

struct BackPoint
{
    char room;  //位置
    char dir;
    char neighbor;  //适配块
};
char matrix[GAMEBLOCKS*4] = {1,6,8,7,2,8,7,5,4,7,5,3,3,5,4,7,4,4,1,4,7,0,0,3,5,0,3,0,3,3,4,5,7,4,8,7,4,8,1,2,3,4,8,2,0,8,2,6,5,2,2,7,7,2,8,7,2,8,6,0,2,2,3,3,6,3,9,6,7,9,0,6,7,0,8,3,0,8,6,6,1,1,5,4,7,5,8,7,6,8,7,1,7,7,4,1,3,4,1,2};
char p[GAMEBLOCKS];
char tryIndex = 0;
char tryOrder[GAMEBLOCKS]; //用过的块号
std::list<BackPoint> backList;
int ap[25] = {23, 24,20, 3, 4, 0, 1, 2, 21, 9, 5, 6, 7, 8, 14, 10, 11, 12, 13, 19, 15, 16, 17, 18, 22};
void initTryOrder()
{
    for(int i=0;i<GAMEBLOCKS;i++)
    {
        tryOrder[i] = -1;
        p[i] = -1;
    }
    backList.clear();
    tryIndex = 0;
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
    printf("\n\rPosition:[");
    for(int i=0;i<GAMEBLOCKS;i++)
    {
        if (p[i]!=-1)
        {
            printf(" %d:%d",i,p[i]);
            if (block)
            {
                printf(":{%c %c %c %c} ");
            }
        }
    }
    printf("]\n\r");
}

bool isUsed(char block) //块index是否已经使用
{
    for (int i=0;i<=tryIndex;i++)
    {
        if (tryOrder[i] == block)
        {
            return true; 
        }
    }
    std::list<BackPoint>::iterator it;
    {
        for(it=backList.begin();it!=backList.end();it++)
        {
            if (it->neighbor == block)
            {
                return true;
            }
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
    for (int i =0;i<=tryIndex;i++)
    {
        printf("%d ",tryOrder[i]);
    }
    printf("]\n\r");
}
void addTry(char row, char col,char block, char found)//将block作为row,col居民 
{
    
    char newIndex = row*GAMESCALE + col;
    if (found ==1)
    {
        p[newIndex] = block;
        tryIndex ++;
        tryOrder[tryIndex] = block;//TryOrder记录块号
        //printf("Add Block %d to %d(%d:%d) as neighbor %d\n\r",i,newIndex,row,col,dir);
    }
    else if ( found >1)
    {
        BackPoint point;
        point.room = newIndex;  //位置
        point.neighbor = block;
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
            if (dir ==0 && row >0)  //查上邻
            {
                if (matrix[p[room]*4] == matrix[i*4+3])
                {
                    if (isNeigborFit(row-1,col,i))//作为上临是否合适
                    {
                        found ++;
                        addTry(row-1,col,i,found);                        
                    }
                }
            }
            else if (dir ==1 && col >0)
            {
                if (matrix[p[room]*4+1] == matrix[i*4+2])
                {
                     if(isNeigborFit(row,col-1,i)) //作为左邻是否合适
                    {
                        found ++;
                        addTry(row,col-1,i,found); 
                    }
                }
            }
            else if (dir ==2 && col < (GAMESCALE -1))
            {
                if (matrix[p[room] *4+2] == matrix[i*4+1])
                {
                    if (isNeigborFit(row,col+1,i)) //作为右邻是否合适
                    {
                        found ++;
                        addTry(row,col+1,i,found); 
                    }
                }
            }
            else if (dir ==3 && row < GAMESCALE -1) 
            {
                if (matrix[p[room]*4+3] == matrix[i*4]) 
                {
                    if (isNeigborFit(row+1,col,i))//作为下邻是否合适
                    {
                        found ++;
                        addTry(row+1,col,i,found); 
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
int getNeighBorRoom(char room, char dir) //根据序号和方向找到邻居序号
{
    char row, col;
    if (dir ==0)
        return room - GAMESCALE;
    if (dir == 1)
        return room -1;
    if (dir ==2)
        return room +1;
    if (dir ==3)
        return room + GAMESCALE;
    return -1;
}

int main()
{
    ascMatrix();
    printMatrix();
    for(int i=23;i<GAMEBLOCKS;i++)
    {
        printf("\n\rtry:%d......\n\r",i);
        initTryOrder();
        tryOrder[0] = i;
        p[0] = i;
        char empty = getEmpty();
        while (empty !=-1)
        {
            char room = getEmptyNeigborRoom(&empty);    //获取空白位附近的邻居，作为填充依据
            char neighborCount = findNeigborBlocks(room,empty);
            if (neighborCount==0)   //如果没找到合适邻居块，需要回退
            {
                if (backList.empty())
                {
                    //无后备可用，失败返回
                    printP();
                    printf("\n\rfailed!");
                    break;
                }
                else
                {
                    BackPoint last = backList.back();//获取最后一个后备位置
                    printP();
                    printTryOrder();
                    printf("back room %d...\n\r",last.room);
                    char rindex = p[last.room] *4;
                    char nindex = last.neighbor;
                    while (tryOrder[tryIndex] != last.room && (tryIndex >0))
                    {
                        for(int i=0;i<GAMEBLOCKS;i++)//从排列表中抹去回退位
                        {
                            if (p[i] == tryOrder[tryIndex])
                            {
                                p[i] = -1; //抹去排除
                                break;
                            }
                        }
                        tryOrder[tryIndex] = -1; //抹去试探记录
                        tryIndex --;
                    }
                    //重新换一个试探块
                    p[last.room] = last.neighbor;   //备选项直接填进适配位置
                    backList.pop_back();            //该备选失效
                   
                    printf("room %d {%c,%c,%c,%c} backed with block %d{%c,%c,%c,%c}\n\r",last.room,matrix[rindex],matrix[rindex+1],matrix[rindex+2],matrix[rindex+3],nindex,matrix[nindex*4],matrix[nindex*4+1],matrix[nindex*4+2],matrix[nindex*4+3]);
                }
            }
            else
            {
                //printf("%dfound %d neighbors\n\r",room,neighborCount);
            }
            empty = getEmpty();
        }
    }
    printf("\n\rDone...\n\r");
}

int main1()
{
    char empty ,found;
    empty= 6;
    initTryOrder();
    p[1]=1;
    found = getEmptyNeigborRoom(&empty);
    printf("%dfound->empty%d",found,empty);
    empty= 6;
    initTryOrder();
    p[5]=2;
    found = getEmptyNeigborRoom(&empty);
    printf("%dfound->empty%d",found,empty);
    empty= 6;
    initTryOrder();
    p[7]=3;
    found = getEmptyNeigborRoom(&empty);
    printf("%dfound->empty%d",found,empty);
    empty= 6;
    initTryOrder();
    p[11]=4;
    found = getEmptyNeigborRoom(&empty);
    printf("%df->empty%d",found,empty);
}
int main2()
{
    initTryOrder();
    for(char i=GAMEBLOCKS-1;i>0;i--)
    {
        p[i] = ap[i];
        char empty = i-1;
        char found = getEmptyNeigborRoom(&empty);
        printf("%d:neighbor:%d->%d\n\r",i,found,empty);
    }
}
int main3()
{
    ascMatrix();
    for(int i=0;i<GAMEBLOCKS;i++)
    {
        p[i] = ap[i];
    }

    for(char i =0;i< GAMEBLOCKS;i++)
    {
        
        for(int dir=0;dir<=3;dir++)
        {
            char tindex;
            initTryOrder();
            tryOrder[tryIndex] = i;
            int count = findNeigborBlocks(i,dir);
            printf("%d{%c,%c,%c,%c}->%d: found %d neighbors[",i,matrix[i*4],matrix[i*4+1],matrix[i*4+2],matrix[i*4+3],dir,count);
            if (tryOrder[1] !=-1)
            {
                tindex = tryOrder[1];
                char nb = getNeighBorRoom(i,dir);
                printf("(%d{%c,%c,%c,%c} %d{%c,%c,%c,%c})\n\r",tindex,matrix[tindex*4],matrix[tindex*4+1],matrix[tindex*4+2],matrix[tindex*4+3],nb,matrix[nb*4],matrix[nb*4+1],matrix[nb*4+2],matrix[nb*4+3]);
            }
            printTryOrder();
            printf("backList:");
            while(!backList.empty())
            {
                tindex =backList.back().neighbor;
                printf("{%c,%c,%c,%c}",matrix[tindex*4],matrix[tindex*4+1],matrix[tindex*4+2],matrix[tindex*4+3]);
                backList.pop_back();
            }
            printf("\n\r");
        }
    }
}
int main4()
{
    initTryOrder();
    for(int i=0;i<GAMEBLOCKS;i++)
    {
        p[i] = ap[i];
        printf("\n\r");
        for(int j=0;j<=i;j++)
        {
            char row = j / GAMESCALE;
            char col = j % GAMESCALE;
            printf("%d:%d\t",j,isNeigborFit(row,col,j));
        }
    }
}
int main5()
{
    ascMatrix();
    initTryOrder();
    p[0] = 23;
    char pi = p[0];
    printf("room 0!{%c,%c,%c,%c}\n\r",matrix[pi*4],matrix[pi*4+1],matrix[pi*4+2],matrix[pi*4+3]);
    char found = findNeigborBlocks(0,2);
    char index = p[1];
    printf("%d found!{%c,%c,%c,%c}\n\r",found,matrix[index*4],matrix[index*4+1],matrix[index*4+2],matrix[index*4+3]);
    //popBL();
}