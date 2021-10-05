/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmylonas <dmylonas@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 20:31:06 by dmylonas          #+#    #+#             */
/*   Updated: 2021/10/05 00:20:32 by dmylonas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	endofstring_terminate(pid_t server_pid)
{
	int	count;

	count = 8;
	// sends 8 zeros to server
	while (count--)
	{
		usleep(1);
		kill(server_pid, SIGUSR2);
	}
	write(1, "\n", 1);
	exit(EXIT_SUCCESS);
}

// sends SIGUSR1 for binary num 1 and SIGUSR2 for 0
void	send_bit(char *s, pid_t pid)
{
	static int				i = 8;
	// c is a char inside the input string
	static char				c;
	static char				*str;
	static pid_t			server_pid;

	// if s exists, it goes in only in the first bit
	if (s)
	{
		str = s;
		server_pid = pid;
		c = *str;
	}
	// because if c 
	if (c)
	{
		// if i = 0, that means that's the end of the byte, char
		if (!i)
		{
			i = 8;
			c = *(++str);
			// if c = 0, means it's the end of str, so c = '\0'
			if (!c)
				endofstring_terminate(server_pid);
		}
		// we check if !c, cause if c == 0 then only the endofstring_terminate sends signals so this function loops around 8 times for no reason
		if ((c >> --i & 1) == 1)
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
	}
}

void	handle_signal(int sig, siginfo_t *siginfo, void *unused)
{
	static int	received_bytes = 0;

	(void)siginfo;
	(void)unused;
	if (sig == SIGUSR1)
	{
		write(1, "\rAcks received: ", 16);
		ft_putnbr_fd(++received_bytes, 1);
	}
	//When client receives signal from server, it always calls send_bit(0, 0), its 0, 0 since the str and pid are all passed into static variables
	send_bit(0, 0);
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;

	if (argc != 3 || !(ft_atoi(argv[1]) > 1 && ft_atoi(argv[1]) <= 4194304))
	{
		write(1, "BRUH wrong input\n", 17);
		return (0);
	}
	if (!ft_strlen(argv[2]))
		exit(0);

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handle_signal;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);

	ft_putstr_fd("Send Bytes   : ", 1);
	ft_putnbr_fd(ft_strlen(argv[2]), 1);
	write(1, "\n", 1);
	send_bit(argv[2], ft_atoi(argv[1]));
	while (1)
		pause();
	return (0);
}
