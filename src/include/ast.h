/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 11:23:45 by hseppane          #+#    #+#             */
/*   Updated: 2023/04/28 15:07:13 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  AST_H
# define  AST_H

# include "typedef.h"
# include "lexer.h"
# include "redirection.h"

# include <libft.h>

# define AST_INITIAL_NODES 8
# define AST_INITIAL_ARGC 4

typedef struct s_ast_node	t_ast_node;

typedef struct s_ast_branch
{
	t_ast_node	*left;
	t_ast_node	*right;
}	t_ast_branch;

typedef struct s_ast_args
{
	int		argc;
	char	**argv;
}	t_ast_args;

typedef struct s_ast_redir
{
	int 	size;
	t_redir	*array;
}	t_ast_redir;

typedef enum e_ast_node_type
{
	AST_PIPE,
	AST_COMMAND,
	AST_ARGS,
	AST_REDIR,
}	e_ast_node_type;

typedef union u_ast_data
{
	t_ast_branch	branch;
	t_ast_args		args;
	t_ast_redir		redir;
}	u_ast_data;

typedef struct s_ast_node
{
	e_ast_node_type	type;
	u_ast_data		data;
}	t_ast_node;

t_ast_node	*ast_node_new(e_ast_node_type type, u_ast_data data);
void		ast_node_del(t_ast_node *root);

t_ast_node	*ast_left(t_ast_node *node);
t_ast_node	*ast_right(t_ast_node *node);

t_ast_node	*parse_pipeline(t_lexer *input);

e_err		interpret_ast(t_ast_node *root);

void		ast_print(t_ast_node *node, int depth);

#endif