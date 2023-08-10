/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 12:54:26 by aumarin           #+#    #+#             */
/*   Updated: 2023/05/24 12:02:28 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*ast_new_node(t_node_type type, char *value)
{
	t_ast	*node;

	node = ft_calloc(1, sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	node->left = NULL;
	node->right = NULL;
	node->result = NULL;
	node->value = ft_strdup(value);
	return (node);
}

/*
	(*tokens)->type = 1-4	= REDIRECTS
	(*tokens)->type = 6		= PIPE_
*/
int	get_ast_array_size(t_line **tokens)
{
	int		size;
	t_line	*head;

	size = 1;
	head = *tokens;
	while ((*tokens))
	{
		if ((*tokens)->type && (*tokens)->type >= 1 && (*tokens)->type <= 4)
			size++;
		else if ((*tokens)->type == PIPE_)
			size++;
		(*tokens) = (*tokens)->next;
	}
	*tokens = head;
	return (size);
}
