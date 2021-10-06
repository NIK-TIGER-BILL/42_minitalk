/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalsami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 19:58:33 by ebalsami          #+#    #+#             */
/*   Updated: 2021/08/02 19:58:33 by ebalsami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void	bit_changer(int num)
{
	(void) num;
	g_bites.bit >>= 1;
}

struct sigaction	options(unsigned long int *len, char **argv)
{
	struct sigaction	sact;

	*len = (ft_strlen(argv[2]) + 1);
	sigemptyset(&sact.sa_mask);
	sact.sa_flags = 0;
	sact.sa_handler = &bit_changer;
	g_bites.pid = ft_atoi(argv[1]);
	return (sact);
}

int	main(int argc, char **argv)
{
	struct sigaction	sact;
	unsigned long int	len;

	if (argc < 3)
		return (-1);
	sact = options(&len, argv);
	sigaction(SIGUSR1, &sact, 0);
	while (len--)
	{
		g_bites.bit = 0b10000000;
		while (g_bites.bit)
		{
			if (*argv[2] & g_bites.bit)
				kill(g_bites.pid, SIGUSR1);
			else
				kill(g_bites.pid, SIGUSR2);
			pause();
			usleep(50);
		}
		argv[2]++;
	}
	return (0);
}
