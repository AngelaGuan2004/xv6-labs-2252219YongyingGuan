#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int 
main(int argc, char* argv[])
{
    if (argc != 2) { // 参数个数
        fprintf(2, "Usage: sleep times(1 argument)\n");
    }
    int time = atoi(*++argv); // 指向时间数值的字符串
    if (sleep(time) != 0) {
        fprintf(2, "Error in sleep sys_call!\n");
    }
    exit(0);
}
