/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 12:48:13 by hseppane          #+#    #+#             */
/*   Updated: 2023/05/29 11:25:34 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

# include "typedef.h"

typedef struct s_pipe
{
	int	read;
	int	write;
}	t_pipe;

t_err	pipe_init(t_pipe *empty);
t_err	pipe_close(t_pipe *pipe);

t_err	pipe_connect(int source, int target, int unused);

#endif
