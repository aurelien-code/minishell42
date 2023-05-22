/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumarin <aumarin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 17:59:35 by aumarin           #+#    #+#             */
/*   Updated: 2023/05/22 18:54:37 by aumarin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_right_cmd(t_line **tks)
{
	char	*cmd;
	t_line	*head;

	head = *tks;
	cmd = NULL;
	if (*tks && (*tks)->type != STR)
		(*tks) = (*tks)->next;
	while ((*tks) && (*tks)->type == STR)
	{
		cmd = ft_strjoin(cmd, " ");
		cmd = ft_strjoin(cmd, (*tks)->value);
		(*tks) = (*tks)->next;
	}
	*tks = head;
	return (cmd);
}

t_ast	*parse_pipe(char **left_cmd, char *right_cmd)
{
	t_ast	*ast;

	ast = ast_new_node(NODE_PIPE, NULL);
	if (!ast)
		return (NULL);
	ast->left = ast_new_node(NODE_CMD, *left_cmd);
	ast->right = ast_new_node(NODE_CMD, right_cmd);
	free(*left_cmd);
	*left_cmd = NULL;
	return (ast);
}

t_ast	*parse_rdrcts(t_operators r_type, char **left_cmd, char *right_cmd)
{
	t_ast		*ast;
	t_node_type	type;

	if (r_type == SINGLE_L_REDIRECT)
		type = NODE_REDIRECT_S_OUT;
	else if (r_type == DOUBLE_L_REDIRECT)
		type = NODE_REDIRECT_D_OUT;
	else if (r_type == SINGLE_R_REDIRECT)
		type = NODE_REDIRECT_S_IN;
	else if (r_type == DOUBLE_R_REDIRECT)
		type = NODE_REDIRECT_D_IN;
	else
		return (NULL);
	ast = ast_new_node(type, NULL);
	if (!ast)
		return (NULL);
	ast->left = ast_new_node(NODE_CMD, *left_cmd);
	ast->right = ast_new_node(NODE_CMD, right_cmd);
	free(*left_cmd);
	*left_cmd = NULL;
	return (ast);
}

t_ast	*parse(t_ast *ast, t_line **tks)
{
	int		i;
	char	*left_cmd;

	left_cmd = NULL;
	i = 0;
	while ((*tks))
	{
		if ((*tks)->type == PIPE_)
			ast[i] = *parse_pipe(&left_cmd, get_right_cmd(tks));
		else if ((*tks)->type >= 1 && (*tks)->type <= 4)
			ast[i] = *parse_rdrcts((*tks)->type, &left_cmd, get_right_cmd(tks));
		else
		{
			i--;
			left_cmd = ft_strjoin(left_cmd, " ");
			left_cmd = ft_strjoin(left_cmd, (*tks)->value);
		}
		i++;
		(*tks) = (*tks)->next;
	}
	if (left_cmd && i < get_ast_array_size(tks))
		ast[i] = *ast_new_node(NODE_CMD, left_cmd);
	return (ast);
}
