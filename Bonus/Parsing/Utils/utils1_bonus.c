/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 02:59:30 by aakritah          #+#    #+#             */
/*   Updated: 2025/06/26 20:45:47 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main_bonus.h"
#include "../../include/parse_bonus.h"

void	ft_free(char **t)
{
	int	i;

	if (!t)
		return ;
	i = 0;
	while (t[i])
	{
		free(t[i]);
		i++;
	}
	free(t);
}

void	ft_free2(char **t, int s)
{
	int	i;

	i = 0;
	while (i < s)
	{
		free(t[i]);
		i++;
	}
	free(t);
}

char	**ft_set_charset(void)
{
	char	**charset;

	charset = malloc(sizeof(char *) * 8);
	if (!charset)
		return (NULL);
	charset[0] = ">>";
	charset[1] = "<<";
	charset[2] = ">";
	charset[3] = "<";
	charset[4] = "|";
	charset[5] = "\"";
	charset[6] = "\'";
	charset[7] = NULL;
	return (charset);
}

char	**ft_set_charset2(void)
{
	char	**charset;

	charset = malloc(sizeof(char *) * 2);
	if (!charset)
		return (NULL);
	charset[0] = "*";
	charset[1] = NULL;
	return (charset);
}

int	ft_isspace(int c)
{
	if ((9 <= c && c <= 13) || c == 32)
		return (1);
	return (0);
}
