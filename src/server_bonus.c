/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalsami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 19:58:42 by ebalsami          #+#    #+#             */
/*   Updated: 2021/08/02 19:58:43 by ebalsami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk_bonus.h"

void	handler(int num, siginfo_t *info, void *ucontext)
{
	(void) ucontext;
	if (num == SIGUSR1)
		g_bites.symbol += g_bites.bit;
	g_bites.bit >>= 1;
	if (!g_bites.bit)
	{
		if (!g_bites.symbol)
			ft_putchar_fd('\n', 1);
		else
			ft_putchar_fd(g_bites.symbol, 1);
		g_bites.bit = 0b10000000;
		g_bites.symbol = 0;
	}
	usleep(50);
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sact;

	g_bites.symbol = 0;
	g_bites.bit = 0b10000000;
	sigemptyset(&sact.sa_mask);
	sact.sa_flags = SA_SIGINFO;
	sact.sa_sigaction = &handler;
	sigaction(SIGUSR1, &sact, 0);
	sigaction(SIGUSR2, &sact, 0);
	ft_putstr_fd("Server PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	while (1)
		pause();
}
