#include "ipc_pipes.h"
#include <stdio.h>
#include <unistd.h>

int main(int ac, char **av)
{
	cmd_t	*commands = NULL;
	int		status = 0;

	if (ac < 2)
		return (dprintf(2, "usage : %s <command> | <command>\n", av[0]), 1);
	commands = parse_command(ac, av);
	get_head(commands);
	cmd_show_all(commands);
	status = execute_commands(commands);
	cmd_free_all(&commands);
	commands = NULL;
	close(0);
	close(1);
	close(2);
	return (status);
}
