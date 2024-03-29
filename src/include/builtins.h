/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:50:42 by lsileoni          #+#    #+#             */
/*   Updated: 2023/06/02 18:00:22 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include <stdio.h>
# include "libft.h"

int	change_directory(const char	*pathname);
int	echo(char **argv);
int	put_cwd(void);
int	export_var(char *str);
int	put_env(char	**envp);
int	unset_var(char	**argv);
int	exit_cmd(char	**argv);

#endif
