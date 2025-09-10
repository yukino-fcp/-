#include "dlist.h"


node_t *create_dlist()
{
	node_t *head = malloc(sizeof(node_t));
	SYSERR(NULL,==,head,"malloc error",NULL);
	head->data = NULL;
	head->before = head->after = head;
	return head;
}
int insert_hdlist(node_t *head,const void *data,int size)
{
	SYSERR(NULL,==,head,"head is null",-1);
	SYSERR(NULL,==,data,"data is null",-1);
	SYSERR(size,<,1,"size must >= 1",-1);
	node_t *newnode = malloc(sizeof(node_t));

	SYSERR(NULL,==,newnode,"malloc error",-1);
	newnode->data = malloc(size);
	SYSERR(NULL,==,newnode->data,"malloc errro",-1);
	memcpy(newnode->data,data,size);

	newnode->after = head->after;
	newnode->before = head;
	head->after->before = newnode;
	head->after = newnode;

	return 0;
}

void show_hdlist(node_t *head,showfun_t showfun)
{
	SYSERR(NULL,==,head,"head is null",);
	node_t *temp = head->after;
	while(temp != head)
	{
		showfun(temp->data);
		temp = temp->after;
	}
	printf("\n");
}

void show_tdlist(node_t *head,showfun_t showfun)
{
	SYSERR(NULL,==,head,"head is null",);
	node_t *temp = head->before;	//找尾
	while(temp != head)
	{
		showfun(temp->data);
		temp = temp->before;
	}
	printf("\n");
}

int insert_tdlist(node_t *head,const void *data,int size)
{
	SYSERR(NULL,==,head,"head is null",-1);
	SYSERR(NULL,==,data,"data is null",-1);
	SYSERR(size,<,1,"size must >= 1",-1);
	node_t *temp = head->before;

	node_t *newnode = malloc(sizeof(node_t));
	SYSERR(NULL,==,newnode,"malloc error",-1);
	newnode->data = malloc(size);
	SYSERR(NULL,==,newnode->data,"malloc error",-1);

	memcpy(newnode->data,data,size);
	newnode->after = head;
	newnode->before = temp;
	temp->after = newnode;

	head->before = newnode;
	return 0;
}


node_t *find_vdlist(node_t *head,const void *data,cmpfun_t cmpfun)
{
	SYSERR(NULL,==,head,"head is null",NULL);
	SYSERR(NULL,==,data,"data is null",NULL);
	SYSERR(head->after,==,head,"list is empty",NULL);
	node_t *temp = head->after;
	while(temp != head && temp->data != NULL)
	{
		if(!cmpfun(temp->data,data))
			return temp;
		temp = temp->after;
	}
	return NULL;
}

int delete_hdlist(node_t *head)
{
	SYSERR(NULL,==,head,"head is null",-1);
	SYSERR(head->after,==,head,"list is empty",-1);
	node_t *temp = head->after;

	temp->after->before = head;
	head->after = temp->after;
	free(temp->data);
	free(temp);
	return 0;
}


int delete_tdlist(node_t *head)
{
	SYSERR(NULL,==,head,"head is null",-1);
	SYSERR(head->after,==,head,"list is empty",-1);
	node_t *temp = head->before;

	temp->before->after = head;
	head->before = temp->before;
	free(temp->data);
	free(temp);
	return 0;
}

node_t *delete_vdlist(node_t *head,const void *data,cmpfun_t cmpfun)
{
	SYSERR(NULL,==,head,"head is null",NULL);
	SYSERR(head->after,==,head,"list is empty",NULL);
	node_t *temp = head->after,*before = head;;
	while(temp != head && temp->data != NULL)
	{
		if(!cmpfun(data,temp->data))	//找到
		{
			temp->before->after = temp->after;
			temp->after->before = temp->before;
			before = temp->before;
			free(temp->data);
			free(temp);
			return before;
		}
		temp = temp->after;
	}
	return NULL;
}


int destroy_dlist(node_t **head)
{
	SYSERR(NULL,==,*head,"head is null",-1);
	node_t *temp = (*head)->after, *after = (*head)->after;
	while(temp != (*head))
	{
		after = temp->after;
		free(temp->data);
		free(temp);
		temp = after;
	}
	free(*head);
	*head = NULL;
	return 0;
}

int blubSort_dlist(node_t *head,cmpfun_t cmpfun)
{
	SYSERR(NULL,==,head,"head is null",-1);
	node_t *inext,*jnext,*end;
	int flag;
	void *temp = NULL;

	for(inext = head->after,end = head->before; inext != head; inext = inext->after,end = end->before)
	{
		flag = 0;
		for(jnext = head->after; jnext != end; jnext = jnext->after)
		{
			if(cmpfun(jnext->data,jnext->after->data) > 0)
			{
				temp = jnext->data;
				jnext->data = jnext->after->data;
				jnext->after->data = temp;
				flag = 1;
			}
		}
		if(!flag)
			break;
	}
	return 0;	
}

int selectSort_dlist(node_t *head,cmpfun_t cmpfun)
{
	SYSERR(NULL,==,head,"head is null",-1);
	node_t *inext,*jnext,*min;
	void *temp = NULL;
	for(inext = head->after; inext != head->before; inext = inext->after)
	{
		min = inext;
		for(jnext = inext->after; jnext != head; jnext = jnext->after)
		{
			if(cmpfun(jnext->data,min->data) < 0)
				min = jnext;
		}

		if(min != inext)
		{
			temp = min->data;
			min->data = inext->data;
			inext->data = temp;
		}
	}
	return 0;
}

void free_dlist(node_t *list)
{
	 if (list == NULL) return;
	 node_t *cur = list->after;
	 while (cur != list) 
	 {
		 node_t *next = cur->after;

		 free(cur->data);
		 free(cur);        
		cur = next;											    
		 free(list);
	 }
}
