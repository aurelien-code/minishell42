/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 00:20:37 by aumarin           #+#    #+#             */
/*   Updated: 2023/08/27 00:29:30 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	write_history(const char *input)
{
	const char	*filename = ".minishell_history";
	int			fd;
	ssize_t		writelen;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (-1);
	writelen = write(fd, input, strlen(input));
	if (writelen == -1)
	{
		close(fd);
		return (-1);
	}
	write(fd, "\n", 1);
	close(fd);
	return (0);
}
