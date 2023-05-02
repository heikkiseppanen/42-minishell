/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:50:42 by lsileoni          #+#    #+#             */
/*   Updated: 2023/05/02 18:47:42 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
#include <unistd.h>
#include <stdio.h>
#include "libft.h"

int	change_directory(const char	*pathname);
int	echo(char **argv);
int	put_cwd();
int	export_var(char *str);
int	put_env(char	**envp);

#endif
