/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 12:48:13 by hseppane          #+#    #+#             */
/*   Updated: 2023/05/08 14:58:02 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

# include "typedef.h"

typedef struct s_pipe
{
	int	read;
	int	write;
} t_pipe;

e_err	pipe_init(t_pipe *empty);
e_err	pipe_close(t_pipe *pipe);

e_bool	pipe_is_valid(t_pipe *pipe);
e_err	pipe_connect(int source, int target, int unused);

#endif
