/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 02:15:07 by aakritah          #+#    #+#             */
/*   Updated: 2025/05/09 17:37:34 by aakritah         ###   ########.fr       */
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
		ft_free_list(&data);
		return (NULL);
	}
	// if (ft_filter_list(&data) < 0)
	// {
	// 	ft_free_list(&data);
	// 	return (NULL);
	// }
	// if (ft_filter_list2(&data) < 0)
	// {
	// 	ft_free_list(&data);
	// 	return (NULL);
	// }
	return (data);
}
