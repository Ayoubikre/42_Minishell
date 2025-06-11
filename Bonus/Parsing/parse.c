/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 02:15:07 by aakritah          #+#    #+#             */
/*   Updated: 2025/06/10 21:42:19 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"
#include "../include/parse.h"

t_token	*ft_parse(char *str, t_extra *x)
{
	t_token	*data;

	data = NULL;
	if (ft_tokenize(str, &data, x) < 0)
	{
		if (x->exit_status != 258)
			x->exit_status = 1;
		return (ft_free_list(&data), NULL);
	}
					printf("1\n");

	if (ft_expand(&data, x) < 0)
	{
		x->exit_status = 1;
		return (ft_free_list(&data), NULL);
	}
					printf("2\n");

	// if (ft_filter_list(&data) < 0)
	// {
	// 	x->exit_status = 1;
	// 	return (ft_free_list(&data), NULL);
	// }
	// 				printf("3\n");

	// if (ft_filter_list2(&data) < 0)
	// {
	// 	x->exit_status = 1;
	// 	return (ft_free_list(&data), NULL);
	// }
	// 				printf("4\n");

	return (data);
}

int	ft_check_string(char *str)
{
	int	i;

	i = 0;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '\0')
		return (0);
	return (1);
}
