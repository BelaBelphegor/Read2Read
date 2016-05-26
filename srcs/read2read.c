#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdint.h>
#include <signal.h>

void fuckit(int signum)
{
	printf("Ahah lol!\n");
	return ;
}

ssize_t read(int fildes, void *buf, size_t nbyte)
{
	if (signal(SIGSEGV, fuckit) && signal(SIGINT, fuckit) == SIG_ERR)
	{
		printf("PLS'O'PLS GOD!\n");
		return (0);
	}
	printf("[Read2Read HOOK] Called.\n");
	static ssize_t (*read2read)(int fildes, void *buf, size_t nbyte) = NULL;
	if (!read2read)
		read2read = dlsym(RTLD_NEXT, "read");
	ssize_t value = read2read(fildes, buf, nbyte);
	printf("[Read2Read HOOK] Return.\n");
	signal(SIGSEGV, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	return (value);
}
