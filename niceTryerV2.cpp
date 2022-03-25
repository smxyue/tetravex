#include <stdio.h>
#include <list>

#define GAMESCALE 5
#define GAMEBLOCKS GAMESCALE *GAMESCALE

struct BackPoint
{
    char room; //位置
    char dir;
    char neighbor; //适配块
};
char matrix[GAMEBLOCKS * 4] = {1, 6, 8, 7, 2, 8, 7, 5, 4, 7, 5, 3, 3, 5, 4, 7, 4, 4, 1, 4, 7, 0, 0, 3, 5, 0, 3, 0, 3, 3, 4, 5, 7, 4, 8, 7, 4, 8, 1, 2, 3, 4, 8, 2, 0, 8, 2, 6, 5, 2, 2, 7, 7, 2, 8, 7, 2, 8, 6, 0, 2, 2, 3, 3, 6, 3, 9, 6, 7, 9, 0, 6, 7, 0, 8, 3, 0, 8, 6, 6, 1, 1, 5, 4, 7, 5, 8, 7, 6, 8, 7, 1, 7, 7, 4, 1, 3, 4, 1, 2};
char p[GAMEBLOCKS];
char tryIndex = 0;
char tryOrder[GAMEBLOCKS]; //用过的块号
std::list<BackPoint> backList;
int ap[25] = {23, 24, 20, 3, 4, 0, 1, 2, 21, 9, 5, 6, 7, 8, 14, 10, 11, 12, 13, 19, 15, 16, 17, 18, 22};
int firstRoom = 0;
void initTryOrder()
{
    for (int i = 0; i < GAMEBLOCKS; i++)
    {
        tryOrder[i] = -1;
        p[i] = -1;
    }
    backList.clear();
    tryIndex = 0;
}
void ascMatrix()
{
    for (int i = 0; i < GAMEBLOCKS * 4; i++)
        matrix[i] += '0';
}
void printMatrix()
{
    for (int i = 0; i < GAMEBLOCKS; i++)
    {
        printf("%d{%c,%c,%c,%c} ", i, matrix[i * 4], matrix[i * 4 + 1], matrix[i * 4 + 2], matrix[i * 4 + 3]);
    }
}
void printP(bool block = false)
{
    printf("\n\rPosition:[");
    for (int i = 0; i < GAMEBLOCKS; i++)
    {
        if (p[i] != -1)
        {
            printf("%d ", p[i]);
            if (block)
            {
                printf(":{%c %c %c %c} ",matrix[i*4],matrix[i*4+1],matrix[i*4+2],matrix[i*4+3]);
            }
        }
    }
    printf("]\n\r");
}
void printBackList()
{
    printf("backList:\n\r[");
    for (std::list<BackPoint>::iterator it = backList.begin(); it != backList.end(); ++it) 
    {
        printf("%d:%d ",it->room,it->neighbor);
    }
    printf("]\n\r");
}
bool isUsed(char block) //块index是否已经使用
{
    for (int i = 0; i <= tryIndex; i++)
    {
        if (tryOrder[i] == block)
        {
            return true;
        }
    }
    // std::list<BackPoint>::iterator it;
    // {
    //     for (it = backList.begin(); it != backList.end(); it++)
    //     {
    //         if (it->neighbor == block)
    //         {
    //             return true;
    //         }
    //     }
    // }
    return false;
}
void printTryOrder()
{
    printf("TryOder:[");
    for (int i = 0; i <= tryIndex; i++)
    {
        printf("%d ", tryOrder[i]);
    }
    printf("]\n\r");
}

bool tryBlock(char room, char block) //block块放在room位置是否合适
{
    char mark = 0;
    char row = room / GAMESCALE;
    char col = room % GAMESCALE;
    char neighborRoom, neighborBlock;   //room邻居的序号，实际块号
    //顺序查看四周,此时，block是被看成是在当前room位置位置的
    if (row > 0)
    {
        neighborRoom = room - GAMESCALE;    
        neighborBlock = p[neighborRoom];    //块号-1表示这个位置还没有数
        if (neighborBlock != -1)
        {
            if (matrix[neighborBlock * 4 + 3] == matrix[block * 4]) //检查上邻
            {
                mark ++;
            }
            else
            {
                return false;
            }
        }
    }
    if (col > 0)
    {
        neighborRoom = room - 1;
        neighborBlock = p[neighborRoom];
        if (neighborBlock != -1)
        {
            if (matrix[neighborBlock * 4 + 2] == matrix[block * 4 + 1]) //检查左邻
            {
               mark++; 
            }
            else
            {
                return false;
            }
        }
    }
    if (col < (GAMESCALE - 1))
    {
        neighborRoom = room + 1;
        neighborBlock = p[neighborRoom];
        if (neighborBlock != -1)
        {
            if (matrix[neighborBlock * 4 + 1] == matrix[block * 4 + 2]) //检查右邻
            {
                mark++;
            }
            else
            {
                return false;
            }
        }
    }
    if (row < GAMESCALE - 1)
    {
        neighborRoom = room + GAMESCALE;
        neighborBlock = p[neighborRoom];
        if (neighborBlock != -1)
        {
            if (matrix[neighborBlock * 4] == matrix[block * 4 + 3]) //检查下邻
            {
                mark++;
            }
            else
            {
                return false;
            }
        }
    }
    if (mark>0)
    {
        return true;
    }
    return false;
}
char tryEmpty() //获取一个空位，试图填充，把候选项压栈
{
    char emptyRoom = -1;
    for (char i = 0; i < GAMEBLOCKS; i++)   //查找空位
    {
        if (p[i] == -1)
        {
            emptyRoom = i;
            break;
        }
    }
   if (emptyRoom ==0) //第一个空位自动填入
    {
        initTryOrder();
        p[0] = firstRoom;
        firstRoom ++;
        if (firstRoom>=GAMEBLOCKS)
        {
            return 255; //无解
        }
        emptyRoom = 1;
    }
    if (emptyRoom == -1)    //如果全部非空
    {
        bool isfull = true;
        for (char i = 0; i < GAMEBLOCKS; i++)
        {
            if (p[i] == -1)
            {
                isfull = false;
            }
        }
        if (isfull)
        {
            return 128;
        }
    }
    
    int count = 0;
    for (char i = 0; i < GAMEBLOCKS; i++)
    {
        if (!isUsed(i))
        {
            if (tryBlock(emptyRoom, i))
            {
                count++;
                if (count == 1)
                {
                    p[emptyRoom] = i;
                    tryIndex++;
                    tryOrder[tryIndex] = i;
                    printf("%d <- %d{%c,%c,%c,%c}\n\r",emptyRoom,i,matrix[i*4],matrix[i*4+1],matrix[i*4+2],matrix[i*4+3]);
                }
                else
                {
                    BackPoint backItem;
                    backItem.room = emptyRoom;
                    backItem.neighbor = i;
                    backList.push_back(backItem);
                    printf("%d => %d{%c,%c,%c,%c}\n\r",emptyRoom,i,matrix[i*4],matrix[i*4+1],matrix[i*4+2],matrix[i*4+3]);
                }
            }
        }
    }
    return count;
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
int main()
{
    inputMatrix();
    //ascMatrix();
    initTryOrder();
    char backCount = tryEmpty();
    while (backCount >= 0)
    {
        if (backCount == 0)
        {
            if (!backList.empty())
            {
                BackPoint lastBack = backList.back();
                printf("\n\rBack room %d...\n\r",lastBack.room);
                printTryOrder();
                printBackList();               
                while ((tryIndex > 0) && (tryOrder[tryIndex] != p[lastBack.room])) //p[lastBack.room]为最后一个有备选项的位置填入的块号
                {
                    for (char i = 1; i < GAMEBLOCKS; i++)   
                    {
                        if (p[i] == tryOrder[tryIndex]) //找到该块所填充的位置，并作废，同时从试探集中也作废该块。
                        {
                            printf("x%d ",tryOrder[tryIndex]);
                            p[i] = -1;
                            tryOrder[tryIndex] = -1;
                            tryIndex--;
                            break;
                        }
                    }
                }
                p[lastBack.room] = lastBack.neighbor;//填入新试探块
                char lastRoom = lastBack.room;
                char lastNeighbor = lastBack.neighbor;
                printf("%d <= %d\n\r",lastBack.room,lastBack.neighbor);
                backList.pop_back();    //弹出 作废该试探块
                lastBack = backList.back();
                if (lastBack.room == lastRoom) //本位还有备选，本位在试探列表还要保留，否则，删掉
                {
                   // tryIndex ++;
                }
                tryOrder[tryIndex] =lastNeighbor;//新试探必须也填入
                
            }
            else//无备选无邻居,重新开始
            {
                initTryOrder();
                backCount = tryEmpty();
            }
        }
        else if (backCount == 128)
        {
            printf("\n\rGot you:\n\r");
            printP(true);
        }
        else if (backCount == 255)
        {
            printf("\n\rNo anwser!");
        }
        backCount = tryEmpty();
    } 
    printf("Done!\n\r");
    printP(true);
}