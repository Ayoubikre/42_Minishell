/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 18:05:31 by aakritah          #+#    #+#             */
/*   Updated: 2025/06/15 18:28:45 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parse.h"

int	ft_is_hidden(char *t)
{
	if (!t)
		return (-1);
	if (t[0] == '.')
		return (1);
	return (0);
}

int	ft_get_wc_list_size(const char *cwd, char *str)
{
	DIR				*dir;
	struct dirent	*key;
	int				count;
	int				f;

	f = ft_is_hidden(str);
	count = 0;
	dir = opendir(cwd);
	if (!dir)
		return (-1);
	while (1)
	{
		key = readdir(dir);
		if (!key)
			break ;
		if (f == 1 && key->d_name[0] == '.')
			count++;
		else if (f == 0 && key->d_name[0] != '.')
			count++;
	}
	printf("%d\n", count);
	closedir(dir);
	return (count);
}

int	ft_get_wc_list_filled(char **t, int s, const char *cwd, char *str)
{
	int				i;
	DIR				*dir;
	struct dirent	*key;
	int				f;

	f = ft_is_hidden(str);
	i = 0;
	dir = opendir(cwd);
	if (!dir)
		return (-1);
	while (1)
	{
		key = readdir(dir);
		if (!key)
			break ;
		if (f == 1 && key->d_name[0] == '.')
		{
			t[i] = ft_strdup(key->d_name);
			if (!t[i])
				return (-1);
			i++;
		}
		else if (f == 0 && key->d_name[0] != '.')
		{
			t[i] = ft_strdup(key->d_name);
			if (!t[i])
				return (-1);
			i++;
		}
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


char **ft_files_list(const char *cwd, char *str)
{
	int		s;
	char **t;
	
	s = ft_get_wc_list_size(cwd, str);
	if (s == -1)
		return (NULL);
	t = malloc((s + 1) * sizeof(char *));
	if (!t)
		return (NULL);
	if (ft_get_wc_list_filled(t, s, cwd, str) == -1)
		return (ft_free(t), NULL);
	ft_sort_wc_list_final(t);
	return t;
}
