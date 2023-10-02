/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aagathe <aagathe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 17:19:09 by aagathe           #+#    #+#             */
/*   Updated: 2023/10/02 05:39:22 by aagathe          ###   ########.fr       */
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
	const int	name_size = ft_strlen(cmds->redr_in->filename);
	char		*buffer;
	int			pfd[2];

	if (pipe(pfd) < 0)
	{
		perror(TEMP_FILE_ERR);
		return ;
	}
	cmds->redr_in->pfd[0] = pfd[0];
	cmds->redr_in->pfd[1] = pfd[1];
	cmds->redr_in->fd = pfd[0];
	buffer = NULL;
	buffer = readline("> ");
	while (buffer)
	{
		if (!ft_strncmp(buffer, cmds->redr_in->filename, name_size + 1))
			break ;
		write(pfd[1], buffer, ft_strlen(buffer));
		write(pfd[1], "\n", 1);
		free(buffer);
		buffer = readline("> ");
	}
	if (!buffer)
		entry_error(cmds->redr_in->filename);
}

int	open_redr_in(t_cmd *cmds)
{
	int		ret;
	t_redr	*redr_in;
	char	*error;

	ret = 0;
	redr_in = cmds->redr_in;
	while (cmds->redr_in)
	{
		if (cmds->redr_in->type == S_REDIR_L)
			cmds->redr_in->fd = open(cmds->redr_in->filename, O_RDONLY);
		else
			write_entry(cmds);
		if (cmds->redr_in->fd < 0 && cmds->redr_in->type == 4 && ++ret)
		{
			error = ft_strjoin("minishell: ", cmds->redr_in->filename);
			perror(error);
			free(error);
		}
		cmds->redr_in = cmds->redr_in->next;
	}
	cmds->redr_in = redr_in;
	return (ret);
}

int	open_redr_out(t_cmd *cmds)
{
	int		ret;
	t_redr	*redr_out;
	char	*error;

	ret = 0;
	redr_out = cmds->redr_out;
	while (cmds->redr_out)
	{
		if (cmds->redr_out->type == S_REDIR_R)
			cmds->redr_out->fd = open(cmds->redr_out->filename,
					O_CREAT | O_TRUNC | O_WRONLY, 0660);
		else
			cmds->redr_out->fd = open(cmds->redr_out->filename,
					O_CREAT | O_WRONLY | O_APPEND, 0660);
		if (cmds->redr_out->fd < 0 && ++ret)
		{
			error = ft_strjoin("minishell: ", cmds->redr_out->filename);
			perror(error);
			free(error);
		}
		cmds->redr_out = cmds->redr_out->next;
	}
	cmds->redr_out = redr_out;
	return (ret);
}

int	open_files(t_cmd *cmds)
{
	int		ret;

	ret = 0;
	while (cmds)
	{
		ret += open_redr_in(cmds);
		ret += open_redr_out(cmds);
		cmds = cmds->next;
	}
	return (ret);
}
