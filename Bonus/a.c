/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:29:56 by aakritah          #+#    #+#             */
/*   Updated: 2025/06/11 21:15:11 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>



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

int	ft_valid(char *str, char *t)
{
	int		i;
	int		j;
	int		k;
	int		f;
	char	**rs;

	i = 0;
	j = 0;
	k = 0;
	f = 0;
	rs = ft_split4(str);
	if (!rs)
		return (-1);
	while (rs[k])
	{
		f = ft_check_q_status(rs[i]);
		if (f == 0)
		{
			i = ft_consume_1(rs[k], t, &j);
			if (i == -1)
				return (-1);
			else if (i == 0)
				return (0);
		}
		else
		{
			i = ft_consume_2(rs[k], t, &j);
			if (i == -1)
				return (-1);
			else if (i == 0)
				return (0);
		}
		k++;
	}
	return (1);
}

int	ft_count_wc_match(char *str, char **t)
{
	int	i;
	int	count;
	int	f;

	i = 0;
	count = 0;
	while (t[i])
	{
		f = ft_valid(str, t[i]);
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
	int		i=0;
	int		j=0;
	int		s=0;
	int		f;
	char	**t2;

	s = ft_count_wc_match(str, t);
	if (s == -1)
		return (NULL);
	t2 = malloc((s + 1) * sizeof(char *));
	if (!t2)
		return (NULL);
	i = 0;
	j = 0;
	while (t[i])
	{
		f = ft_valid(str, t[i]);
		if (f == -1)
			return (NULL);
		else if (f == 1)
		{
			t2[j] = strdup(t[i]);
			i++;
		}
		j++;
	}
	t2[j] = NULL;
	return (t2);
}

int main()
{
    int i;
    char **rs;
    char *str="*a*b";

	char **t = malloc((10 + 1) * sizeof(char *));
    t[0]=strdup("iiiiiaab");
    t[1]=strdup("..a..b");
    t[2]=strdup("ab");
    t[3]=strdup("ab.");
    t[4]=strdup("kldjsfa");
    t[5]=strdup("..");
    t[6]=strdup(".a b.");
    t[7]=strdup("a.b");
    t[8]=strdup("faklsab");
    t[9]=strdup("asdsklfjbdsf");
    t[10]=NULL;
    
    rs = ft_filter_wc_list(str, t);
    i=0;
    while(rs[i])
    {
        printf("%s \n", rs[i]);
        i++;        
    }
    return 0;
}