/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 11:39:27 by lsileoni          #+#    #+#             */
/*   Updated: 2023/05/03 15:15:11 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft.h"

typedef struct s_shell_state
{
	t_htable	*envp;
	char		**environ_copy;
	int			pipeline_err;
}	t_shell_state;

char	**htable_to_environ(t_htable *envp);

#endif
