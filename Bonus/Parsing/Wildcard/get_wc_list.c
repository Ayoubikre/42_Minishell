/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wc_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 00:59:49 by noctis            #+#    #+#             */
/*   Updated: 2025/06/13 21:50:55 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parse.h"

int	ft_get_wc_list_size(const char *cwd)
{
	DIR				*dir;
	struct dirent	*key;
	int				count;

	count = 0;
	dir = opendir(cwd);
	if (!dir)
		return (-1);
	while (1)
	{
		key = readdir(dir);
		if (!key)
			break ;
		count++;
	}
	closedir(dir);
	return (count);
}

int	ft_get_wc_list_filled(char **t, int s, const char *cwd)
{
	int				i;
	DIR				*dir;
	struct dirent	*key;

	i = 0;
	dir = opendir(cwd);
	if (!dir)
		return (-1);
	while (1)
	{
		key = readdir(dir);
		if (!key)
			break ;
		t[i] = ft_strdup(key->d_name);
		if (!t[i])
			return (-1);
		i++;
	}
	t[i] = NULL;
	closedir(dir);
	return (0);
}

void	ft_sort_wc_list_final(char **t)
{
	int		i;
	int		s;
	char	*tmp;

	s = ft_strlen_2(t);
	while (s >= 0)
	{
		i = 1;
		while (i < s)
		{
			if (ft_strcmp(t[i], t[i - 1]) < 0)
			{
				tmp = t[i];
				t[i] = t[i - 1];
				t[i - 1] = tmp;
			}
			i++;
		}
		s--;
	}
}

char	**ft_get_wc_list(char *str)
{
	int		s;
	char	**t;
	t_wc    *data;
	char	cwd[PATH_MAX];

	data=NULL;
	if (!getcwd(cwd, sizeof(cwd)))
		return (NULL);
	s = ft_get_wc_list_size(cwd);
	if (s == -1)
		return (NULL);
	t = malloc((s + 1) * sizeof(char *));
	if (!(t))
		return (NULL);
	if (ft_get_wc_list_filled(t, s, cwd) == -1)
		return (ft_free(t), NULL);
		
	// ft_sort_wc_list_final(t);
		
	if (ft_initialize_list2(str, &data) < 0)
		return (ft_free(t), NULL);

	ft_print_list3(data);
	
	// t = ft_filter_wc_list(str, t);
	// if (!t)
	// 	return (ft_free(t), NULL);
		
	ft_sort_wc_list_final(t);
	return (ft_free_list2(&data), t);
}


