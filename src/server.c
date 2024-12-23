/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheyo <cheyo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 23:06:01 by cheyo             #+#    #+#             */
/*   Updated: 2024/12/21 13:03:19 by cheyo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minitalk.h>

int8_t	g_c;

static void	print_art(void)
{
	ft_printf("\x1B[33m _____ ______   ___  ________   ___  _________ ");
	ft_printf(" ________  ___       ___  __       \n");
	ft_printf("|\\   _ \\  _   \\|\\  \\|\\   ___  \\|\\  \\|\\");
	ft_printf("___   ___\\\\   __  \\|\\  \\     |\\  \\|\\  \\     \n");
	ft_printf("\\ \\  \\\\\\__\\ \\  \\ \\  \\ \\  \\\\ \\  \\ \\  \\|___");
	ft_printf(" \\  \\_\\ \\  \\|\\  \\ \\  \\    \\ \\  \\/  /|_   \n");
	ft_printf(" \\ \\  \\\\|__| \\  \\ \\  \\ \\  \\\\ \\  \\ \\  \\   \\ ");
	ft_printf("\\  \\ \\ \\   __  \\ \\  \\    \\ \\   ___  \\  \n");
	ft_printf("  \\ \\  \\    \\ \\  \\ \\  \\ \\  \\\\ \\  \\ \\  \\   \\ ");
	ft_printf("\\  \\ \\ \\  \\ \\  \\ \\  \\____\\ \\  \\\\ \\  \\ \n");
	ft_printf("   \\ \\__\\    \\ \\__\\ \\__\\ \\__\\\\ \\__\\ \\__\\   ");
	ft_printf("\\ \\__\\ \\ \\__\\ \\__\\ \\_______\\ \\__\\\\ \\__\\\n");
	ft_printf("    \\|__|     \\|__|\\|__|\\|__| \\|__|\\|__|    \\|__|");
	ft_printf("  \\|__|\\|__|\\|_______|\\|__| \\|__|\n\n\n\x1B[0m");
}

static void	print_id(int pid)
{
	char	*text;

	text = "Server listening on PID : ";
	while (*text)
	{
		usleep(50000);
		ft_printf("%c", *text);
		text++;
	}
	ft_printf("%d\n\n", pid);
}

static void	get_data(int signum, siginfo_t *info, void *con)
{
	static int8_t	bit;

	(void)con;
	if (signum != SIGUSR1 && signum != SIGUSR2)
		return ;
	if (g_c < 0)
	{
		g_c = 0;
		bit = 7;
	}
	if (signum == SIGUSR1)
		g_c <<= 1;
	else
		g_c = (g_c << 1) + 1;
	bit--;
	if (bit < 0)
	{
		write(1, &g_c, 1);
		g_c = 0;
		bit = 7;
	}
	usleep(10);
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	minitalk;
	int					pid;
	sigset_t			mask;

	g_c = -1;
	sigemptyset(&mask);
	pid = getpid();
	minitalk.sa_sigaction = get_data;
	minitalk.sa_mask = mask;
	minitalk.sa_flags = SA_SIGINFO;
	print_art();
	print_id(pid);
	sigaction(SIGUSR1, &minitalk, NULL);
	sigaction(SIGUSR2, &minitalk, NULL);
	while (1)
		pause();
}
