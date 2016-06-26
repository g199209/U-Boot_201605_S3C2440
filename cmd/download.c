#include <common.h>
#include <command.h>

static int do_download(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	int i;

	if(argc == 1)
		printf("param:\nu : U-Boot;\nl : Linux;\nf : File System.\n");

	const char * const cmd_uboot[5] = {
		"nfs 30000000 /home/gmf/nfs/u-boot.bin",
		"protect off all",
		"erase 0 +$filesize",
		"cp.b 30000000 0 $filesize",
		"reset",
	};

	const char * const cmd_linux[4] = {
		"nfs 30008000 /home/gmf/nfs/uImage",
		"nand erase 60000 300000",
		"nand write.jffs2 30008000 60000 300000",
		"bootm 30008000",
	};

	switch(*argv[1]) {
	case 'u':
	case 'U':
		for(i = 0; i < 5; i++)
		{
			printf("\n##########\n");
			printf(cmd_uboot[i]);
			printf("\n##########\n");
			run_command(cmd_uboot[i], 0);
		}
		break;
	
	case 'l':
	case 'L':
		for(i = 0; i < 4; i++)
		{   
			printf("\n##########\n");
			printf(cmd_linux[i]);
			printf("\n##########\n");
			run_command(cmd_linux[i], 0);
		}
		break;

	case 'f':
	case 'F':
		break;
	}
	return 0;
}

U_BOOT_CMD(
	download,	2,	1,	do_download,
	"Download File (Uboot, Linux or FS)",
	" - Download File:\nu : U-Boot;\nl : Linux;\nf : File System.\n"
);
