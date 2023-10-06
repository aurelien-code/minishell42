/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagathe <aagathe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 17:19:09 by aagathe           #+#    #+#             */
/*   Updated: 2023/10/06 00:59:48 by aagathe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	entry_error(const char *filename)
{
	char	*error;
	char	*error2;
	char	*nb_line;

	nb_line = ft_itoa(history_size(0));
	error = ft_strjoin("minishell: warning: here-document at the line ",
			nb_line);
	free(nb_line);
	error2 = ft_strjoin(error, " delimited by end-of-file (wanted `");
	free(error);
	error = ft_strjoin(error2, filename);
	free(error2);
	error2 = ft_strjoin(error, "')");
	free(error);
	ft_putendl_fd(error2, 2);
	free(error2);
}

void	write_entry(t_cmd *cmds)
{
	const int	name_size = ft_strlen(cmds->redr->filename);
	char		*buffer;
	int			pfd[2];

	if (pipe(pfd) < 0)
	{
		perror(TEMP_FILE_ERR);
		return ;
	}
	cmds->redr->pfd[0] = pfd[0];
	cmds->redr->pfd[1] = pfd[1];
	cmds->redr->fd = pfd[0];
	buffer = NULL;
	buffer = readline("> ");
	while (buffer)
	{
		if (!ft_strncmp(buffer, cmds->redr->filename, name_size + 1))
			break ;
		write(pfd[1], buffer, ft_strlen(buffer));
		write(pfd[1], "\n", 1);
		free(buffer);
		buffer = readline("> ");
	}
	if (!buffer)
		entry_error(cmds->redr->filename);
}

int	open_redr(t_redr *redr)
{
	char	*error;

	if (redr->type == S_REDIR_R)
		redr->fd = open(redr->filename, O_CREAT | O_TRUNC | O_WRONLY, 0660);
	else if (redr->type == D_REDIR_R)
		redr->fd = open(redr->filename, O_CREAT | O_WRONLY | O_APPEND, 0660);
	else
		redr->fd = open(redr->filename, O_RDONLY);
	if (redr->fd < 0)
	{
		error = ft_strjoin("minishell: ", redr->filename);
		perror(error);
		free(error);
		return (1);
	}
	return (0);
}

int	open_files(t_cmd *cmds, int pfd[4], int nb_cmds)
{
	t_redr	*redr;

	redr = cmds->redr;
	while (redr)
	{
		if (redr->type == D_REDIR_L)
			write_entry(cmds);
		redr = redr->next;
	}
	redr = cmds->redr;
	while (redr)
	{
		if (redr->type == 3 || redr->type == 4 || redr->type == 5)
			if (open_redr(redr))
				return (close_files(cmds, pfd, nb_cmds), 1);
		redr = redr->next;
	}
	return (0);
}
