/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:14:31 by hseppane          #+#    #+#             */
/*   Updated: 2023/05/29 11:23:42 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIR_H
# define REDIR_H

# include "typedef.h"

typedef enum e_redir_op
{
	REDIR_NULL,
	REDIR_OUT_APPEND,
	REDIR_OUT_TRUNC,
	REDIR_IN_FILE,
	REDIR_IN_HEREDOC,
}	t_redir_op;

typedef struct s_redir
{
	t_redir_op	operation;
	int			file_descriptor;
	const char	*argument;
}	t_redir;

void	redir_del(t_redir *instances, int size);

t_err	redir_execute(const t_redir *instance);

#endif
