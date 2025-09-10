#ifndef DLIST_H
#define DLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SYSERR(x,option,y,message,z)	if((x) option (y))		\
											{						\
																							printf("%s %s %d : %s\n",__FILE__,__func__,__LINE__,message);\
																							return z;			\
																						}


#define ARRSIZE(arr) (sizeof(arr) / sizeof(arr[0]))

//链表节点;
typedef struct node
{
	struct node *before;	//指向前驱的指针;
	void *data;
	struct node *after;		//指向后继的指针;
}node_t;

//创建链表;
node_t *create_dlist();

//插入到链表头部; @data是要插入的数据 @size要插入的数据大小;
int insert_hdlist(node_t *head,const void *data,int size);

typedef void (*showfun_t)(const void *data);
void show_hdlist(node_t *head,showfun_t showfun);
void show_tdlist(node_t *head,showfun_t showfun);

//插入到链表尾部
int insert_tdlist(node_t *head,const void *data,int size);

//按值查找;
typedef int (*cmpfun_t)(const void *data1,const void *data2);
node_t *find_vdlist(node_t *head,const void *data,cmpfun_t cmpfun);

//删除第1个数据节点;
int delete_hdlist(node_t *head);
//删除尾部节点;
int delete_tdlist(node_t *head);
//按值删除;
node_t *delete_vdlist(node_t *head,const void *data,cmpfun_t
		cmpfun);

//销毁链表;
int destroy_dlist(node_t **head);

//使用冒泡排序实现对链表排序;
int blubSort_dlist(node_t *head,cmpfun_t cmpfun);
//使用选择排序实现对链表排序;
int selectSort_dlist(node_t *head,cmpfun_t cmpfun);
void free_dlist(node_t *list);


typedef void (*showfun_t)(const void *);
void show_hdlist(node_t *head, showfun_t showfun);
#endif	//end DLIST_H

