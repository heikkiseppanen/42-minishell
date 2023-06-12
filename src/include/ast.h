/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 11:23:45 by hseppane          #+#    #+#             */
/*   Updated: 2023/06/12 09:46:28 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  AST_H
# define  AST_H

# include "typedef.h"
# include "tokenizer.h"
# include "redir.h"

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
	int		size;
	t_redir	*array;
}	t_ast_redir;

typedef enum e_ast_node_type
{
	AST_PIPE,
	AST_COMMAND,
	AST_ARGS,
	AST_REDIR,
}	t_ast_node_type;

typedef union u_ast_data
{
	t_ast_branch	branch;
	t_ast_args		args;
	t_ast_redir		redir;
}	t_ast_data;

typedef struct s_ast_node
{
	t_ast_node_type	type;
	t_ast_data		data;
}	t_ast_node;

t_ast_node	*ast_node_new(t_ast_node_type type, t_ast_data data);
void		ast_node_del(t_ast_node *root);

t_ast_node	*ast_left(t_ast_node *node);
t_ast_node	*ast_right(t_ast_node *node);

t_ast_node	*parse_command(t_token **iterator);
t_err		parse_parameters(t_token **iterator, t_buf *argv, t_buf *redir);
t_err		parse_argument(t_token **iterator, t_buf *argv_out);
t_err		parse_redirection(t_token **iterator, t_buf *redir_out);
t_err		unexpect(const t_token *token);

char		*read_heredoc(const char *eof, size_t length);

t_ast_node	*parse_pipeline(t_token **iterator);
t_err		interpret_ast(t_ast_node *root);

void		ast_print(t_ast_node *node, int depth);

#endif
