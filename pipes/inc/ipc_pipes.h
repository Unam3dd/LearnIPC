#ifndef IPC_PIPES_H
#define IPC_PIPES_H

//////////////////////////////////
//
//	       	INCLUDES
//
/////////////////////////////////

#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>

//////////////////////////////////
//
//	       	TYPEDEFS
//
/////////////////////////////////

typedef enum bool_t		bool_t;
typedef struct cmd_t 	cmd_t;

//////////////////////////////////
//
//	       	ENUM
//
/////////////////////////////////

enum bool_t
{
	FALSE,
	TRUE
};

//////////////////////////////////
//
//	       	STRUCTS 
//
/////////////////////////////////

struct cmd_t
{
	cmd_t		*next;
	cmd_t		*prev;
	char		*cmd;
	int			fds[2];
	pid_t		pid;
	int			id;
};

//////////////////////////////////
//
//	     COMMAND DATASET
//
/////////////////////////////////

cmd_t	*get_head(cmd_t *save);
cmd_t	*cmd_new(char *cmd);
bool_t	cmd_add(cmd_t **lst, cmd_t *new);
void	cmd_show_all(cmd_t *cmds);
void	cmd_free(cmd_t *cmd);
void	cmd_free_all(cmd_t **cmd);

//////////////////////////////////
//
//	     PARSING
//
/////////////////////////////////

cmd_t	*parse_command(int ac, char **av);

//////////////////////////////////
//
//	     PIPES
//
/////////////////////////////////

bool_t	pipes_create(int *fds);

//////////////////////////////////
//
//	    EXECUTE
//
/////////////////////////////////

char	*get_binary_name(char *str);
int		execute_commands(cmd_t *commands);
int		exec_cmd(cmd_t *cmd);
int		wait_process(cmd_t	*commands);
bool_t	fd_dup(int fd, int io);

#endif
