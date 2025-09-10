#include<stdio.h>
#include"dlist.h"
#include"comm.h"
#include"menu.h"
#include"dev.h"



int welcome_menu(node_t *devlist)
{
	int select = 0;
	while(1)
	{
		system("clear");
		printf("\t\t***************************************\n");
		printf("\t\t***************************************\n");
		printf("\t\t*********欢迎登陆设备管理系统**********\n");
		printf("\t\t************1 管理员登陆***************\n");
		printf("\t\t************2 用户  登陆***************\n");
		printf("\t\t************0 退出  系统***************\n");
		printf("\t\t***************************************\n");
		printf("\t\t***************************************\n");
		printf("\t\t请选择：");
		if(scanf("%d",&select) != 1)
		{
			getchar();
			continue;
		}
		getchar();
		switch(select)
		{
			case 0:
				return 0;;
			case 1:
				login_menu(devlist);
				break;
			default:
				puts("无效选择，按回车继续");
				getchar();
		}
	}
}

int login_menu(node_t *devlist)
{
	int i;
	char name[16];
	char pass[16];
	for (i = 0;i < 3;i++)
	{
		system("clear");
		printf("============== 管理员登陆 ==================\n");
		printf("用户名 ：\n");
		if(fgets(name,sizeof(name),stdin) == NULL)
			return -1;
		name[strcspn(name,"\n")] = '\0';

		printf("密码：\n");
		if(fgets(pass,sizeof(pass),stdin) == NULL)
			return -1;
		pass[strcspn(pass,"\n")] = '\0';

		if(strcmp(name,ADMIN_NAME) == 0 && strcmp(pass,ADMIN_PASS) == 0)
		{
			admin_menu(devlist);
			return 0;
		}
		else
		{
			printf("用户名或密码错误,按回车继续\n");
			getchar();
		}
	}
	printf("连续三次错误，程序退出");
	return -1;
}

int admin_menu(node_t *devlist)
{
	int choice;
	while(1)
{
	system("clear");
	puts("================== 管理员菜单 ==================");
	puts("1  添加新设备");
	puts("2  删除设备");
	puts("3  修改设备");
	puts("4  显示设备");
	puts("5  查找设备");
	puts("0  返回");
	puts(" 请选择 ");
	if(scanf("%d",&choice) != 1)
	{
		getchar();
		continue;
	}
	getchar();

	switch(choice)
	{
case 1: add_dev_menu(devlist);break;
case 2: del_dev_menu(devlist);break;
case 3:	update_dev_menu(devlist);break;
case 4:	show_dev_menu(devlist);break;
case 5: find_dev_menu(devlist);break;
case 0: return 0;
default :puts("error");getchar();
	}
}
}
int add_dev_menu(node_t *devlist)
{
		device_t dev;
		system("clear");
		
		puts("-----------请输入新设备信息-------------");

		printf("ID:");
		scanf("%d",&dev.dev_id);
		save_dev(devlist);
		getchar();//吞scanf的回车

		printf("IP:");
		fgets(dev.dev_ip,sizeof(dev.dev_ip),stdin);
		save_dev(devlist);
		dev.dev_ip[strcspn(dev.dev_ip,"\n")] = 0;//返回出现\n的地方，并替换成0.

		printf("TYPE:");
		fgets(dev.dev_type,sizeof(dev.dev_type),stdin);
		save_dev(devlist);
		dev.dev_type[strcspn(dev.dev_type,"\n")] = 0;

		printf("NAME:");
		fgets(dev.dev_name,sizeof(dev.dev_name),stdin);
		save_dev(devlist);
		dev.dev_name[strcspn(dev.dev_name,"\n")] = 0;

		printf("POWER:");
		scanf("%f",&dev.dev_power_ele);getchar();
		save_dev(devlist);

		printf("VALUE:");
		scanf("%f",&dev.cur_value);getchar();
		save_dev(devlist);

		if(add_dev(devlist,&dev) == 0)
		{
			puts("添加成功");
			show_hdlist(devlist,showfun_dev_full);
			save_dev(devlist);
		}
		else
		{
			puts("添加失败");
		}
		puts("按回车继续");
		getchar();
		save_dev(devlist);
		return 0;
}


int del_dev_menu(node_t *devlist)
{
	int mode;
	device_t dev = {0};
	cmpfun_t cmp;
	int ret;

	while (1)
	{
		system("clear");
		puts("========== 删除设备 ==========");
		puts("1 按设备编号删除");
		puts("2 按设备名删除");
		puts("3 按设备类型删除");
		puts("0 返回上级");
		printf("请选择：");

		if (scanf(" %d",&mode) != 1)
		{
			getchar();
			continue;
		}
		if(mode == 0)
			return 0;
		if(mode < 1 || mode > 3)
		{
			getchar();
			continue;
		}
		switch (mode)
		{
		case 1:
			printf("请输入设备编号：");
			scanf("%d", &dev.dev_id);
			getchar();
			break;
		case 2:
			printf("请输入设备名称：");
			scanf("%63s",dev.dev_name);
			getchar();
			dev.dev_name[strcspn(dev.dev_name,"\n")] = '\0';
			break;
		case 3:
			printf("请输入设备类型：");
			scanf(" %63s",dev.dev_type);
			getchar();
			dev.dev_type[strcspn(dev.dev_type,"\n")] = '\0';
			break;
		default:
			puts("无效选择！");
			continue;
			int del = 0;
			node_t *cur;
			while ((cur = delete_vdlist(devlist,&dev,cmp)) != NULL && cur != devlist)
			{
				free(cur->data);
				free(cur);
				++del;
			}
			printf("已删除 %d 个节点\n", del);
		}
		ret = del_dev(devlist,mode,dev);
		if (ret == 0)
			puts("删除成功！");
		else
			puts("未找到匹配设备！");

		show_hdlist(devlist,showfun_dev_full);
		getchar();
		save_dev(devlist);

	}
}

int update_dev_menu(node_t *devlist)
{
	int mode,id;
	device_t newdev = {0};

	while (1)
	{
		system("clear");
		puts("---------修改设备----------");
		puts("1 修改设备名");
		puts("2 修改设备类型");
		puts("3 修改设备IP");
		puts("0 返回");
		printf("请选择：");

		if (scanf("%d",&mode) != 1)
		{
			getchar();
			continue;
		}
		if (mode == 0)
			return 0;
		if (mode < 1 || mode > 3)
		{
			getchar();
			continue;
		}

		printf("请输入待修改设备ID");
		scanf("%d",&id);
		getchar();

		switch (mode)
		{
		case 1:
			printf("新设备名：");
			fgets(newdev.dev_name,sizeof(newdev.dev_name),stdin);
			newdev.dev_name[strcspn(newdev.dev_name,"\n")] = '\0';
			break;
		case 2:
			printf("新设备类型：");
			fgets(newdev.dev_type, sizeof(newdev.dev_type),stdin);
			newdev.dev_type[strcspn(newdev.dev_type,"\n")] = '\0';
			break;
		case 3:
			printf("新设备IP：");
			fgets(newdev.dev_ip, sizeof(newdev.dev_ip),stdin);
			newdev.dev_ip[strcspn(newdev.dev_ip, "\n")] = '\0';
			break;
		}

		switch (mode)
		{
		case 1: update_dev(devlist,id,(updatefun_t)UPDATE(dev_name),&newdev);
				break;
		case 2: update_dev(devlist,id,(updatefun_t)UPDATE(dev_type),&newdev);
				break;
		case 3: update_dev(devlist,id,(updatefun_t)UPDATE(dev_ip),&newdev);
				break;
		}

		puts("修改成功");
		show_hdlist(devlist, showfun_dev_full);
		getchar();
	}
}

static void flush()
{
	while(getchar() != '\n')
		;
}

int show_dev_menu(node_t *devlist)
{
	char choice;

	while (1) 
	{
		system("clear");
		puts("========== 排序设备 ==========");
		puts("1 按设备号排序");
		puts("2 按设备名排序");
		puts("3 按设备类型排序");
		puts("q 返回上级");
		printf("请选择：");

		scanf("%c",&choice);
		flush();

		// 根据选择调用排序并显示
		switch (choice)
		{
		case '1': sort_dev(devlist, cmpDevId);
			break;
		case '2': sort_dev(devlist, cmpDevName);
			break;
		case '3': sort_dev(devlist, cmpDevType);
			break;
		case 'q':
				return 0;
		}

		puts("\n排序后设备列表：");
		show_hdlist(devlist,showfun_dev_full);

		puts("按回车返回");
		getchar();
		save_dev(devlist);
		return 0;
	}
}
int find_dev_menu(node_t *devlist)
{
	char buf[64];
	device_t dev = {0};
	int choice;
	while (1) {
		system("clear");
		puts("========== 查找设备 ==========");
		puts("1 按设备号查找");
		puts("2 按设备名查找");
		puts("3 按设备类型查找");
		puts("q 返回上级");
		printf("请选择：");

		if (scanf(" %c", buf) != 1)
			continue;

		choice = buf[0] - '0';
		if (choice < 1 || choice > 3)
		{ 
			puts("无效选择！"); getchar(); continue;
		}

		 //读取查询关键字
		switch (choice)
		{
		case 1:
			printf("请输入设备编号：");
			scanf("%d", &dev.dev_id);
			getchar();
			break;
		case 2:
			printf("请输入设备名称：");
			scanf(" %s", buf);
			getchar();
			strcpy(dev.dev_name,buf);
			break;
		case 3:
			printf("请输入设备类型：");
			scanf(" %s", buf);
			getchar();
			strcpy(dev.dev_type,buf);
			break;
		}

		 // 根据关键字生成新链表（返回链表头）
		node_t *result = NULL;
		switch (choice)
		{
		case 1: result = find_dev(devlist,cmpDevId,&dev); break;
		case 2: result = find_dev(devlist,cmpDevName,&dev);  break;
		case 3: result = find_dev(devlist,cmpDevType,&dev);  break;
		}

		
		 // 显示结果
		if (result)
		{
			puts("\n===== 查询结果 =====");
			show_hdlist(result, showfun_dev_full);
		}
		else
		{
			puts("未找到匹配设备！");
		}

		free_dlist(result);
		puts("按回车继续...");
		getchar();
		save_dev(devlist);
		return 0;
		}
}
