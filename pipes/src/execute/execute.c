#include "ipc_pipes.h"

//////////////////////////////////
//
//	      INCLUDES
//
/////////////////////////////////

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>

int	execute_commands(cmd_t *commands)
{
	cmd_t	*save = NULL;

	if (!commands)
		return (1);
	save = commands;
	while (commands)
	{
		if (commands->next)
			if (!pipes_create(commands->fds))
				return (1);
		commands->pid = fork();
		if (exec_cmd(commands))
			perror("exec_cmd");
		commands = commands->next;
	}
	return (wait_process(save));
}

int		exec_cmd(cmd_t *cmd)
{
	cmd_t			*head = NULL;
	char			*name = NULL;

	if (!cmd->pid)
	{
		if (cmd->prev)
			fd_dup(cmd->prev->fds[0], STDIN_FILENO);
		if (cmd->next) {
			if (close(cmd->fds[0]) < 0)
				perror("close");
			fd_dup(cmd->fds[1], STDOUT_FILENO);
		}
		name = get_binary_name(cmd->cmd);
		execlp(name, cmd->cmd, NULL);
		perror("execlp");
		head = get_head(NULL);
		cmd_free_all(&head);
		exit(errno);
	}
	if (((cmd->id & 1) && cmd->prev) || (!cmd->next && cmd->prev)) {
		if (close(cmd->prev->fds[0]) < 0)
			perror("close");
	} else if ((!(cmd->id & 1) && cmd->prev) || (!cmd->next && cmd->prev)) {
		if (close(cmd->prev->fds[0]) < 0)
			perror("close");
	}
	if (cmd->next)
		close(cmd->fds[1]);
	return (0);
}

int		wait_process(cmd_t	*commands)
{
	int	status = 0;

	while (commands) {
		waitpid(commands->pid, &status, 0);
		commands = commands->next;
	}
	return (WEXITSTATUS(status));
}

bool_t	fd_dup(int fd, int io)
{
	if (dup2(fd, io) < 0) {
		perror("dup2");
		return (FALSE);
	}
	if (close(fd) < 0) {
		perror("close");
		return (FALSE);
	}
	return (TRUE);
}

char	*get_binary_name(char *str)
{
	static char	buf[0x100];
	char		*name = NULL;
	size_t		len =  0;

	if (!str)
		return (NULL);
	len = strlen(str);
	strncpy(buf, str, len);
	buf[len] = 0;
	name = strtok(buf, " \t");
	return (name);
}
