/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 10:41:17 by lsileoni          #+#    #+#             */
/*   Updated: 2023/06/02 17:41:03 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIG_H
# define SIG_H

void	rl_replace_line(const char *text, int clear_undo);
void	register_handler(unsigned char regtype);

enum e_handler
{
	HANDLER_DOC,
	HANDLER_SH,
	HANDLER_IGN,
	HANDLER_DFL,
};

#endif
