/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 22:59:03 by noctis            #+#    #+#             */
/*   Updated: 2025/06/13 21:41:44 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parse.h"


// ----------------------

// ----------------------


int ft_valide(char *str, char *s2)
{
    return 1;
}

// ----------------------

int	ft_count_wc_match(char *str, char **t)
{
	int	i;
	int	count;
	int	f;

	i = 0;
	count = 0;
	while (t[i])
	{
		f = ft_valide(str, t[i]);
		if (f == -1)
			return (-1);
		else if (f == 1)
			count++;
		i++;
	}
	return (count);
}

char	**ft_filter_wc_list(char *str, char **t)
{
	int		i;
	int		j;
	int		s;
	int		f;
	char	**t2;
    t_wc    *data;

    data=NULL;

    
	s = ft_count_wc_match(str, t);
	if (s == -1)
		return (ft_free(t), NULL);

        
	t2 = malloc((s + 1) * sizeof(char *));
	if (!t2)
		return (ft_free(t), NULL);

        
	if (ft_initialize_list2(str, &data) < 0)
		return (ft_free(t2), ft_free(t), NULL);


	// i = 0;
	// j = 0;
	// while (t[i])
	// {
	// 	f = ft_valide(str, t[i]);
	// 	if (f == -1)
	// 		return (ft_free(t2), ft_free(t), NULL);
	// 	else if (f == 1)
	// 	{
	// 		t2[j] = ft_strdup(t[i]);
	// 		j++;
	// 	}
	// 	i++;
	// }
	// t2[j] = NULL;

    	ft_print_list3(data);

    
	return (ft_free_list2(&data),ft_free(t), t2);
}
