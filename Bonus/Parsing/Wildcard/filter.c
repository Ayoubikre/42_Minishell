/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 22:59:03 by noctis            #+#    #+#             */
/*   Updated: 2025/06/11 21:19:26 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parse.h"

// int	ft_consume_1(char *rs, char t, int *i)
// {
// }

// int	ft_consume_2(char *rs, char t, int *i)
// {
// 	char	*rs2;
// 	int		s;
// 	int		k;

// 	rs2 = ft_remove_q(rs);
// 	if (!rs2)
// 		return (-1);
// 	s = ft_strlen(rs2);
// 	k = ft_strncmp(rs2, t + *i, s);
// 	if (k != 0)
// 		return (-1);
// 	else
// 		*i += s;
// 	return (1);
// }

// int	ft_valid(char *str, char *t)
// {
// 	int		i;
// 	int		j;
// 	int		k;
// 	int		f;
// 	char	**rs;

// 	i = 0;
// 	j = 0;
// 	k = 0;
// 	f = 0;
// 	rs = ft_split4(str);
// 	if (!rs)
// 		return (-1);
// 	while (rs[k])
// 	{
// 		f = ft_check_q_status(rs[i]);
// 		if (f == 0)
// 		{
// 			i = ft_consume_1(rs[k], t, &j);
// 			if (i == -1)
// 				return (-1);
// 			else if (i == 0)
// 				return (0);
// 		}
// 		else
// 		{
// 			i = ft_consume_2(rs[k], t, &j);
// 			if (i == -1)
// 				return (-1);
// 			else if (i == 0)
// 				return (0);
// 		}
// 		k++;
// 	}
// 	return (1);
// }

// int	ft_count_wc_match(char *str, char **t)
// {
// 	int	i;
// 	int	count;
// 	int	f;

// 	i = 0;
// 	count = 0;
// 	while (t[i])
// 	{
// 		f = ft_valid(str, t[i]);
// 		if (f == -1)
// 			return (-1);
// 		else if (f == 1)
// 			count++;
// 		i++;
// 	}
// 	return (count);
// }

char	**ft_filter_wc_list(char *str, char **t)
{
	// int		i;
	// int		j;
	// int		s;
	// int		f;
	// char	**t2;

	// s = ft_count_wc_match(str, t);
	// if (s == -1)
	// 	return (ft_free(t), NULL);
	// t2 = malloc((s + 1) * sizeof(char *));
	// if (!t2)
	// 	return (ft_free(t), NULL);
	// i = 0;
	// j = 0;
	// while (t[i])
	// {
	// 	f = ft_valid(str, t[i]);
	// 	if (f == -1)
	// 		return (ft_free(t2), ft_free(t), NULL);
	// 	else if (f == 1)
	// 	{
	// 		t2[j] = ft_strdup(t[i]);
	// 		i++;
	// 	}
	// 	j++;
	// }
	// t2[j] = NULL;
	// return (ft_free(t), t2);
}
