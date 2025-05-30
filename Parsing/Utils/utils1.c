/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 02:59:30 by aakritah          #+#    #+#             */
/*   Updated: 2025/05/12 09:18:47 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"
#include "../../include/parse.h"

void	ft_free(char **t)
{
	int	i;

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
