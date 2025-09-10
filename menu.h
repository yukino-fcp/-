#ifndef MENU_H
#define MENU_H
#include"comm.h"
#include"dlist.h"
#include"dev.h"

#define UPDATE(field) do{strcpy(((device_t*)dst)->field,((device_t*)src)->field);}while(0)

int welcome_menu(node_t *devlist);

int login_menu(node_t *devlist);

int admin_menu(node_t *devlist);

int add_dev_menu(node_t *devlist);

int del_dev_menu(node_t *devlist);

int update_dev_menu(node_t *devlist);

int show_dev_menu(node_t *devlist);

int find_dev_menu(node_t *devlist);

void showfun_dev_full(const void *data);

int cmpDevId(const void *, const void *);

int cmpDevName(const void *, const void *);

int cmpDevType(const void *, const void *);


#endif
