/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wc_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 00:59:49 by noctis            #+#    #+#             */
/*   Updated: 2025/06/16 04:46:46 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parse.h"


char	**ft_get_wc_list(char *str)
{
	char	**t1;
	t_wc    *t2;
	char	**t3;
	char	cwd[PATH_MAX];

	if (!getcwd(cwd, sizeof(cwd)))
		return (NULL);
	
	t2=NULL;
	if (ft_cmd_list(str, &t2) < 0)
		return (NULL);
	
	t1=ft_files_list(cwd, t2);
	if (!t1)
		return (ft_free_list2(&t2), NULL);
	
	// ft_print_tab(t1);
	ft_print_list3(t2);
	



	// t1 = ft_filter_wc_list(t1, t2);
	// if (!t1)
	// 	return (ft_free_list2(&t2), NULL);
	
	t3 = ft_filter_wc_list(t1, t2);


	
	
	// ft_sort_wc_list_final(t);
	return (ft_free_list2(&t2), t1);
}

