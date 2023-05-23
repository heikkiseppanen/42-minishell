/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 10:41:17 by lsileoni          #+#    #+#             */
/*   Updated: 2023/05/23 19:43:28 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

void	rl_replace_line (const char *text, int clear_undo);
void	register_handler(unsigned char regtype);

enum e_handler {
	HANDLER_DOC,
	HANDLER_SH,
	HANDLER_IGN,
	HANDLER_DFL,
};

#endif
