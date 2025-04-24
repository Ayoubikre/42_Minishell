/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_delet.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 02:49:05 by aakritah          #+#    #+#             */
/*   Updated: 2025/04/23 23:41:04 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/main.h"
#include "./include/parse.h"

void	leaks(void)
{
	system("leaks -q Minishell");
}

void	ft_print_list(t_token *data)
{
	if (!data)
		return ;
	ft_printf("----------------\n");
	while (data)
	{
		ft_printf(" %s : %d", data->value , data->type);
		ft_printf("\n----------------\n");
		data = data->next;
	}
}

void	print_tab(char **t)
{
	int	i;

	i = 0;
	if (!t)
		return ;
	ft_printf("----------------\n");
	while (t[i])
	{
		ft_printf("> %s <\n", t[i]);
		i++;
	}
	ft_printf("----------------\n");
}
