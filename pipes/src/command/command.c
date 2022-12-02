#include "ipc_pipes.h"

//////////////////////////////////
//
//	       	INCLUDES
//
/////////////////////////////////

#include <stdio.h>
#include <string.h>

//////////////////////////////////
//
//	       	FUNCTIONS
//
/////////////////////////////////

cmd_t	*get_head(cmd_t *save)
{
	static cmd_t	*head = NULL;

	if (save)
		head = save;
	return (head);
}

cmd_t	*cmd_new(char *cmd)
{
	cmd_t *new = (cmd_t *)malloc(sizeof(cmd_t));
	if (!new)
		return (NULL);
	new->cmd = cmd;
	new->next = NULL;
	new->prev = NULL;
	new->pid = 0;
	new->id = 0;
	return (new);
}

bool_t	cmd_add(cmd_t **lst, cmd_t *new)
{
	cmd_t	*tmp = NULL;
	if (!lst)
		return (FALSE);
	if (!*lst)
	{
		*lst = new;
		(*lst)->prev = NULL;
		return (TRUE);
	}
	tmp = *lst;
	while (tmp && tmp->next)
		tmp = tmp->next;
	new->prev = tmp;
	new->next = NULL;
	new->id = tmp->id + 1;
	tmp->next = new;
	return (TRUE);
}

void	cmd_show_all(cmd_t *cmds)
{
	while (cmds)
	{
		printf("Command[%d] : %s\n", cmds->id, cmds->cmd);
		cmds = cmds->next;
	}
}

void	cmd_free(cmd_t *cmd)
{
	if (!cmd)
		return ;
	memset(cmd, 0, sizeof(cmd_t));
	free(cmd);
}

void	cmd_free_all(cmd_t **cmd)
{
	cmd_t	*next = NULL;

	if (!cmd)
		return ;
	while (*cmd)
	{
		next = (*cmd)->next;
		cmd_free(*cmd);
		*cmd = next;
	}
}
