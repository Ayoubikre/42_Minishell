/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 02:15:07 by aakritah          #+#    #+#             */
/*   Updated: 2025/04/24 09:42:23 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"
#include "../include/parse.h"

void	ft_parse(char *str)
{
	t_token	*data;

	data = NULL;
	if (ft_tokenize(str, &data) < 0)
	{
		ft_free_list(&data);
		return ;
	}
	ft_print_list(data);
	
	ft_shunting_yard(&data) ;


	ft_print_list(data);
	ft_free_list(&data);
}
