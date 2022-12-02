#include "ipc_pipes.h"
#include <string.h>

//////////////////////////////////
//
//	       INCLUDES
//
/////////////////////////////////

cmd_t	*parse_command(int ac, char **av)
{
	cmd_t	*cmd = NULL;
	cmd_t	*new = NULL;
	char	*token = NULL;

	for (int i = 1; i < ac; i++) {
		new = NULL;
		token = strtok(av[i], "|");
		while (token) {
			new = cmd_new(token);
			cmd_add(&cmd, new);
			token = strtok(NULL, "|");
		}
	}
	return (cmd);
}
