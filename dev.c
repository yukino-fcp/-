#include"dev.h"
#include"comm.h"
#include"dlist.h"

void showfun_dev_full(const void *data)
{
	const device_t *d = (const device_t *)data;
	printf("%d\t%s\t%s\t%s\t%.2f\t%.2f\n",
	d->dev_id, d->dev_ip, d->dev_type,
	d->dev_name, d->dev_power_ele, d->cur_value);
}

int cmpDevId(const void *a,const void *b)
{
	const device_t *dp1 = (const device_t *)a;
	const device_t *dp2 = (const device_t *)b;
	return dp1->dev_id - dp2->dev_id;
}
int cmpDevName(const void *a, const void *b)
{
	return strcmp(((const device_t *)a)->dev_name, ((const device_t
					*)b)->dev_name);
}

int cmpDevType(const void *a, const void *b)
{
	return strcmp(((const device_t *)a)->dev_type, ((const device_t
					*)b)->dev_type);
}





static int device_id = 1000;
int device_id_min;
int generate_id()
{
	return ++device_id;
}
node_t *load_dev(void)
{
	node_t *devlist = create_dlist();
	SYSERR(NULL,==,devlist,"error",NULL);
	FILE *fp = fopen(DEV_FILE,"r");
	if (!fp)
	{ 
		fp = fopen(DEV_FILE, "w");
		if (fp)
		{
			fprintf(fp,"%u\n",device_id_min);
			fclose(fp);
		}
		return devlist;
	}

	device_t dev;
	while (fscanf(fp,"%d %63s %63s %63s %f %f",
				&dev.dev_id,
				dev.dev_ip,
				dev.dev_type,
				dev.dev_name,
				&dev.dev_power_ele,
				&dev.cur_value) == 6)
	{
		insert_tdlist(devlist,&dev,sizeof(device_t));
	}
	fclose(fp);
	return devlist;
}

int save_dev(node_t *head)
{
	SYSERR(NULL,==,head,"head is null",-1);
	FILE *devfile = fopen(DEV_FILE,"w");
	SYSERR(NULL,==,devfile,"open error",-1);
	fprintf(devfile,"%u\n",device_id_min);

	head = head->after;
	while(head != NULL && head->data != NULL)
	{
		device_t *dev = (device_t *)head->data;
		fprintf(devfile,"%d %s %s %s %f %f\n",
						dev->dev_id,
						dev->dev_ip,
						dev->dev_type,
						dev->dev_name,
						dev->dev_power_ele,
						dev->cur_value);
	head = head->after;
	}
		fclose(devfile);
		return 0;
	
}

int add_dev(node_t *head,const device_t *newdev)
{	
	SYSERR(NULL,==,head,"head error",-1);
	SYSERR(NULL,==,newdev,"newdev is null",-1);
	return insert_tdlist(head,newdev,sizeof(device_t));
}

node_t *find_dev(node_t * head, cmpfun_t cmpfun, const device_t *cmpdev)
{
	SYSERR(NULL,==,head,"head error",NULL);
	SYSERR(NULL,==,cmpfun,"cmp error",NULL);
	SYSERR(NULL,==,cmpdev,"dev error",NULL);

	node_t *found_dev = create_dlist();
	SYSERR(NULL,==,found_dev,"malloc error",NULL);
	node_t *ret = head;
	while(NULL != (ret = find_vdlist(ret,cmpdev,cmpfun)))
	{
		insert_tdlist(found_dev,ret->data,sizeof(device_t));
	}
	return found_dev;
}

int del_dev(node_t *head,int mode,device_t dev)
{
	SYSERR(NULL,==,head,"head is null",-1);

	cmpfun_t cmp;
	switch(mode)
	{
		case 1:
			cmp = cmpDevId;
			break;
		case 2:
			cmp = cmpDevName;
			break;
		case 3:
			cmp = cmpDevType;
			break;
		default:
			return -1;
	}
	int del = 0;
	node_t *cur;
	while((cur = delete_vdlist(head,&dev,cmp)) != NULL && cur != head)
	{
		free(cur->data);
		free(cur);
		++del;
	}
		return del ? 0 : -1;
}

node_t *update_dev(node_t *head,int id,updatefun_t updatefun,const device_t *updatedev)
{
	device_t dev = {.dev_id = id};
	node_t *result = find_vdlist(head,cmpDevId,&dev);

	SYSERR(NULL,==,result,"result error",NULL);
	updatefun(result->data,updatedev);
	return result;
}


int sort_dev(node_t *head,cmpfun_t cmpfun)
{
	SYSERR(NULL,==,head,"head is null",-1);
	SYSERR(NULL,==,cmpfun,"cmpfun is null",-1);
	selectSort_dlist(head,cmpfun);
	return 0;
}


void show_dev(node_t *head,showfun_t showfun)
{
	SYSERR(NULL,==,head,"head is null", );
	SYSERR(NULL,==,showfun,"showfun is null", );
	
	printf("-----------------device list--------------------\n");
	show_hdlist(head,showfun);
	printf("------------------------------------------------\n");
}

