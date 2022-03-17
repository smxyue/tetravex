#include <stdio.h>
#include <list>

std::list<char> myList;
int main()
{
    for (char i =0;i<10;i++)
    {
        myList.push_back(i*i);
        printf("%d list size:%d   back:%d\n\r",i,myList.size(),myList.back());
    }
    printf("output。。。。\n\r");
    while (!myList.empty())
    {
        printf("list size:%d   back:%d\n\r",myList.size(),myList.back());
        myList.pop_back();
    }
}