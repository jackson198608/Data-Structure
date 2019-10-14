#ifndef STATIC_LIST_H   //静态链表
#define STATIC_LIST_H
#include"Node.h"
#include<iostream>
using std::cout;
#define DEFAULT_SIZE 30

template<typename ElemType>
class StaticList
{
protected:
	int head; //头部标记
	int avail; //当前可用位置标记
	int length; //当前存入数据长度标记
	Node<ElemType> *sll;  //数据存储区域，数组

public:
	StaticList(int size=DEFAULT_SIZE);
	~StaticList();
	int InsertElem(const ElemType &e);
	int InsertElem(int i,const ElemType &e);
	void Traverse();
	int DeleteElem(int i);//差删除元素待补充
};

template<typename ElemType>
StaticList<ElemType>::StaticList(int size=DEFAULT_SIZE)
{
	sll=new Node<ElemType>[size];
	
	//无论节点是否存入了数据，都先将指针域初始化了一下。其实不代表真的关系
	//方便的是，插入数据的时候，自动建立关系，所以初始化一下。要好好理解
	for(int i=1;i<size-1;i++)
		sll[i].next=i+1;   
	
	//头结点，尾节点目前都没有下一步的数据，所以next为 -1
	sll[0].next=-1;   
	sll[size-1].next=-1;
	
	head=0;
	avail=1; //avail 直接从1开始说明 head不保存数据
	length=0;
}

template<typename ElemType>
StaticList<ElemType>::~StaticList()
{
	if(sll!=NULL)
	    delete[] sll;
}

template<typename ElemType>
int StaticList<ElemType>::InsertElem(const ElemType &e)  //在表头插入元素
{
	if(avail==-1)
		return 0;    //空间已满，返回失败
	int i=avail;
	
	 //avail要自动走到下一步。这也是初始化list的时候，要for 初始化next区域的原因。方便自动找到下一个空节点。
	avail=sll[avail].next;
	sll[i].data=e;
	sll[i].next=sll[head].next;
	sll[head].next=i;
	length++;
	return 1;
}


//在指定位置插入元素
//第i个结点不代表 数组的i序号，而是链表意义顺序上的第i个结点
template<typename ElemType>
int  StaticList<ElemType>::InsertElem(int i,const ElemType &e)  
{
	if(i<1||i>length+1)
		 return 0;   //返回失败
	 if(avail==-1)
		 return 0;    //空间已满，返回失败
	 int p=head,k=avail;
	
	 //循环找到插入位置的前一个元素
	 for(int j=0;j<i-1;j++)
		  p=sll[p].next;
	
         avail=sll[avail].next;
	 sll[k].data=e;
	 sll[k].next=sll[p].next;
	 sll[p].next=k;
	 length++;
	 return 1;   //返回成功
}

template<typename ElemType>
void StaticList<ElemType>::Traverse()
{
	int p=head;
	while(sll[p].next!=-1)
	{
		cout<<sll[sll[p].next].data;
		p=sll[p].next;
	}
}

template<typename ElemType>
int StaticList<ElemType>::DeleteElem(int i)
{
	if(i<1||i>length)
		return 0;  //返回失败
	int p=head,k=avail;
    for(int j=0;j<i-1;j++)
		  p=sll[p].next;
	avail=sll[p].next;
    sll[p].next=sll[avail].next;
	sll[avail].next=k;
	
}
#endif
