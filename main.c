/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:18:28 by aakritah          #+#    #+#             */
/*   Updated: 2025/04/03 00:59:09 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	leaks(void)
{
	system("leaks -q a");
}
int	main(int ac, char **av, char **env)
{
	atexit(leaks);
	char	*t;
	int		i;

	i = 0;
	while (i < 2)
	{
		t = readline("enter here > ");
		i++;
	}
	rl_clear_history();
	printf("\n----------------\n");
	printf("> %s <", t);
	printf("\n----------------\n");
}
