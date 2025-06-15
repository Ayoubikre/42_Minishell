/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wc_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 00:59:49 by noctis            #+#    #+#             */
/*   Updated: 2025/06/15 20:44:45 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parse.h"


char	**ft_get_wc_list(char *str)
{
	char	**t1;
	t_wc    *t2;
	char	cwd[PATH_MAX];

	if (!getcwd(cwd, sizeof(cwd)))
		return (NULL);
	
	
	t1=ft_files_list(cwd, str);
	if (!t1)
		return (NULL);
	ft_print_tab(t1);
	
	t2=NULL;
	if (ft_cmd_list(str, &t2) < 0)
		return (ft_free(t1), NULL);

	ft_print_list3(t2);
	
	// t = ft_filter_wc_list(str, t);
	// if (!t)
	// 	return (ft_free(t), NULL);

	
	// ft_sort_wc_list_final(t);
	return (ft_free_list2(&t2), t1);
}
