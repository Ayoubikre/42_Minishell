/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:18:28 by aakritah          #+#    #+#             */
/*   Updated: 2025/04/03 05:55:31 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/main.h"
#include "./include/parse.h"

void	leaks(void)
{
	system("leaks -q Minishell");
}

int	main(int ac, char **av, char **env)
{
	char	*t;
	int		i;

	atexit(leaks);
	i = 0;
	while (i < 1)
	{
		t = readline("Minishell > ");
		if (!t)
			break ;
		ft_parse(t);
		add_history(t);
		free(t);
		i++;
	}
	return (0);
}
