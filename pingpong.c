#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char* argv[])
{
    int p2c[2], c2p[2];// 两条管道
    
    // create pipes
    if(pipe(p2c) == -1 || pipe(c2p) == -1){
    	fprintf(2, "Error: pipe() error.\n");
    	exit(1);
    }

    
    // fork函数创建子进程
    int pid = fork();
    if (pid == -1){
    	fprintf(2, "Error: fork() error.\n");
    	exit(1);
    }
    
    // child process
    if (pid == 0){
        char buffer[1];
        close(p2c[1]);
        close(c2p[0]);
        if(read(p2c[0], buffer, 1) == -1){
        	fprintf(2, "Error: read() error in child.\n");
        	exit(1);
        }
        
        close(p2c[0]);
        fprintf(0, "%d: received ping\n", getpid());
        if(write(c2p[1], buffer, 1) == -1){
        	fprintf(2, "Error: write() error in child.\n");
        	exit(1);
        }
        close(c2p[1]);
    }
    // parent process
    else {
        char buffer[1];
        buffer[0] = 'a';
        close(p2c[0]);
        close(c2p[1]);
        
        if(write(p2c[1], buffer, 1) == -1){
        	fprintf(2, "Error: write() error in parent.\n");
        	exit(1);
        }
        
        close(p2c[1]);
        wait(0);// 等待子进程完成
        
        if(read(c2p[0], buffer, 1) == -1){
        	fprintf(2, "Error: read() error in parent.\n");
        	exit(1);
        }
        close(c2p[0]);
        fprintf(0, "%d: received pong\n", getpid());

    }
    exit(0);
}
