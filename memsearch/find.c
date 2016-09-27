#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	if (argc < 5) {
		fprintf(stdout, "usage: dumpmem pid start_addr length filaname\n");
		return -1;
	}

	/*get argvs*/
	off_t start_addr;
	int len;
	pid_t pid;
	pid = atoi(argv[1]);
	sscanf(argv[2], "%x", &start_addr);
	sscanf(argv[3], "%x", &len);
	
	/*attach the memory of pid*/
	int ptrace_ret;
	ptrace_ret = ptrace(PTRACE_ATTACH, pid, NULL, NULL);
	if (ptrace_ret == -1) {
		fprintf(stderr, "ptrace attach failed.\n");
		perror("ptrace");
		return -1;
	}
	if (waitpid(pid, NULL, 0) == -1) {
		fprintf(stderr, "waitpid failed.\n");
		perror("waitpid");
		ptrace(PTRACE_DETACH, pid, NULL, NULL);
		return -1;
	}
	
	/*open /proc/<pid>/mem to attach the memory*/
	int fd;
	char path[256] = {0};
	sprintf(path, "/proc/%d/mem", pid);
	fd = open(path, O_RDONLY);
	if (fd == -1) {
		fprintf(stderr, "open file failed.\n");
		perror("open");
		ptrace(PTRACE_DETACH, pid, NULL, NULL);
		return -1;
	}
	
	/*seek the file pointer*/
	off_t off;
	off = lseek(fd, start_addr, SEEK_SET);
	if (off == (off_t)-1) {
		fprintf(stderr, "lseek failed.\n");
		perror("lseek");
		ptrace(PTRACE_DETACH, pid, NULL, NULL);
		close(fd);
		return -1;
	}
	
	/*read mem*/
	unsigned char *buf = (unsigned char *)malloc(len);
	if (buf == NULL) {
		fprintf(stderr, "malloc failed.\n");
		perror("malloc");
		ptrace(PTRACE_DETACH, pid, NULL, NULL);
		close(fd);
		return -1;
	}
	int rd_sz;
	rd_sz = read(fd, buf, len);
	if (rd_sz < len) {
		fprintf(stderr, "read failed.\n");
		perror("read");
		ptrace(PTRACE_DETACH, pid, NULL, NULL);
		free(buf);
		close(fd);
		return -1;
	}
	
	/*now show mem*/
	int i = 0;
	FILE *fp = fopen(argv[4], "wb+");
	if (fp == NULL) {
		fprintf(stderr, "fopen failed.\n");
		perror("fopen");
		ptrace(PTRACE_DETACH, pid, NULL, NULL);
		free(buf);
		close(fd);
		return -1;
	}
	fwrite(buf, 1, len, fp);
	fclose(fp);
	
	ptrace(PTRACE_DETACH, pid, NULL, NULL);
	free(buf);
	close(fd);
	return 0;
}
