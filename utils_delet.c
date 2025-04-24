/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_delet.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 02:49:05 by aakritah          #+#    #+#             */
/*   Updated: 2025/04/24 09:43:09 by noctis           ###   ########.fr       */
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
		ft_printf( "cmd : %s , token : %d , precd : %d", data->value, data->type, data->prec);
		ft_printf("\n----------------\n");
		data = data->next;
	}
}

void	ft_print_list2(t_token *data)
{
	FILE *fd = fopen("./test/out.txt", "w+");
	if (!fd)
		return ; // handle fopen failure
	fprintf(fd,"----------------\n");
	while (data)
	{
		fprintf(fd, "cmd : %s , token : %d , precd : %d\n", data->value, data->type, data->prec);
		fprintf(fd,"----------------\n");
		data = data->next;
	}
	fclose(fd);
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
