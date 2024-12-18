/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_control.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 21:06:05 by myuen             #+#    #+#             */
/*   Updated: 2024/12/18 19:46:28 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIG_CONTROL_H
# define SIG_CONTROL_H

void	handle_signal(int sig);
int		setup_signals(void);

#endif
