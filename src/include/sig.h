/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 10:41:17 by lsileoni          #+#    #+#             */
/*   Updated: 2023/05/18 18:59:53 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

void	init_sighandler(void);
void	rl_replace_line (const char *text, int clear_undo);
void	reset_sighandler(void);
void	dfl_handler(void);
void	ign_handler(void);
void	doc_handler(void);

#endif
