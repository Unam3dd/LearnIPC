#include "ipc_pipes.h"

//////////////////////////////////
//
//	       INCLUDES
//
/////////////////////////////////

#include <stdio.h>
#include <unistd.h>

bool_t	pipes_create(int *fds)
{
	if (pipe(fds) < 0)
	{
		perror("pipe");
		return (FALSE);
	}
	return (TRUE);
}
