#ifndef DEV_H
#define DEV_H

#include"dlist.h"
#include"comm.h"
#define UPDATENAME 1
#define UPDATETYPE 2
#define UPDATEIP 3
#define UPDATEVALUE 4
#define UPDATEPOWER 5
typedef struct device
{
	int dev_id;
	char dev_status;
	float cur_value;

	char dev_name[32];
	char dev_type[32];
	char dev_ip[16];
	float dev_power_ele;
}device_t;



int generate_id();//产生id

node_t *load_dev();//加载设备

int save_dev(node_t *head);

int add_dev(node_t * head, const device_t * newdev);

node_t *find_dev(node_t *head,cmpfun_t cmpfun,const device_t *cmpdev);

void show_dev(node_t *head,showfun_t showfun);

int sort_dev(node_t *head,cmpfun_t cmpfun);

int update_dev(node_t *head, int id, int updatemode, const device_t *newdev);

void showfun_dev_full(const void *data);

int del_dev(node_t *head, int mode, device_t dev);
#endif	
