/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 23:05:38 by cheyo             #+#    #+#             */
/*   Updated: 2024/12/23 21:16:58 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minitalk.h>

void	handle_ping_back(int sugoma)
{
	(void)sugoma;
}

void	send_data(const char *pid, const char *data)
{
	int				i;
	int				target;
	unsigned char	c;

	target = ft_atoi(pid);
	while (*data)
	{
		c = (unsigned char)*data;
		i = 7;
		while (i >= 0)
		{
			if (((c >> i--) & 1) == 0)
				kill(target, SIGUSR1);
			else
				kill(target, SIGUSR2);
			pause();
			usleep(25);
		}
		data++;
	}
}

int	main(int argc, char *argv[])
{
	char	*str;

	if (argc != 3)
		return (1);
	str = argv[2];
	ft_printf("Message : %s\n", str);
	ft_printf("PID : %s\n", argv[1]);
	signal(SIGUSR1, handle_ping_back);
	send_data(argv[1], argv[2]);
	return (0);
}
