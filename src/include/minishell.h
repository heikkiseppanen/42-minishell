/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 11:39:27 by lsileoni          #+#    #+#             */
/*   Updated: 2023/06/05 11:23:47 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "typedef.h"

# include <libft.h>

typedef struct s_shell_state
{
	t_htable	*envp;
	int			pipeline_err;
	int			heredoc_done;
}	t_shell_state;

t_err	ms_init(void);

char	**htable_to_environ(t_htable *envp);

#endif
