#include"dev.h"
#include"menu.h"
#include"comm.h"
#include"dlist.h"
int main()
{
	node_t *devlist = load_dev();
	
	show_tdlist(devlist,showfun_dev_full);

	welcome_menu(devlist);
	
	if(save_dev(devlist) != 0)
		puts("保存设备失败");

	destroy_dlist(&devlist);

	return 0;

}


