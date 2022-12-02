#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(void)
{
	char	buf[0x10] = {0};
	size_t	len;
	int		fds[2];
	pid_t	pid;

	if (pipe(fds) < 0) {
		perror("pipe");
		return (1);
	}

	pid = fork();
	
	if (!pid)
	{
		// we don't need to read
		close(fds[0]);

		write(fds[1], "hello", 5);
		close(fds[1]);
		exit(0);
	}
	wait(NULL);

	// we don't need to write
	close(fds[1]);

	len = read(fds[0], buf, sizeof(buf));
	if (len < 0) {
		perror("read");
		return (1);
	}

	close(fds[0]);

	printf("%s\n", buf);
	
	return (0);
}
