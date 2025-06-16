/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 18:05:31 by aakritah          #+#    #+#             */
/*   Updated: 2025/06/16 03:30:38 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parse.h"

int	ft_is_hidden(t_wc *data)
{
	if (!data || !data->value)
		return (-1);
	if (data->value[0] == '.')
		return (1);
	return (0);
}

int	ft_get_wc_list_size(const char *cwd, int	 f)
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
		if (f == 1 && key->d_name[0] == '.')
			count++;
		else if (f == 0 && key->d_name[0] != '.')
			count++;
	}
	closedir(dir);
	return (count);
}

int	ft_get_wc_list_filled(char **t, int s, const char *cwd, int	 f)
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


char **ft_files_list(const char *cwd, t_wc *data)
{
	int		s;
	int 	f;
	char **t;
	
	f = ft_is_hidden(data);
	s = ft_get_wc_list_size(cwd, f);
	if (s == -1)
		return (NULL);
	t = malloc((s + 1) * sizeof(char *));
	if (!t)
		return (NULL);
	if (ft_get_wc_list_filled(t, s, cwd, f) == -1)
		return (ft_free(t), NULL);
	ft_sort_wc_list_final(t);
	return t;
}
