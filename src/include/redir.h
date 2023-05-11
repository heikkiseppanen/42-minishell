/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:14:31 by hseppane          #+#    #+#             */
/*   Updated: 2023/05/10 12:03:11 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIR_H
# define REDIR_H

# include "typedef.h"

typedef enum e_redir_op
{
	REDIR_OUT_APPEND,
	REDIR_OUT_TRUNC,
	REDIR_IN_FILE,
	REDIR_IN_HEREDOC,
} e_redir_op;

typedef struct s_redir
{
	e_redir_op	operation;
	int			file_descriptor;
	const char	*argument;
}	t_redir;

void	redir_del(t_redir *instances, int size);

e_err	redir_execute(const t_redir *instance);

#endif
