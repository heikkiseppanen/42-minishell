/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 07:52:30 by lsileoni          #+#    #+#             */
/*   Updated: 2023/06/02 17:42:17 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H
# include "libft.h"

typedef struct s_sym_state
{
  t_buf *buf;
	int		open;
	int		i;
	char	openchar;
}	t_sym_state;

typedef struct s_exp_state
{
	char	*env;
	char	*envres;
	int		i;
}	t_exp_state;

char	*str_expand(const char *string);
char	*arg_expand(const char *string);
char	**expand_arglist(char **argv);
int		handle_exp(t_sym_state *s_s, const char *string);
int		check_first_tok(t_sym_state *s_s, t_exp_state *e_s, const char *string);
void	check_underscore(t_sym_state *s_s,
			t_exp_state *e_s, const char *string);

#endif
