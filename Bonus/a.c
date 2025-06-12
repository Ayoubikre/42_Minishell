/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:29:56 by aakritah          #+#    #+#             */
/*   Updated: 2025/06/12 01:22:37 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>


// ----------------------------------------------------
long	ft_count_split2(char const *s, char c);
void	ft_fix_norminet_2(long *n2, long *n1);

char	*ft_copy_split2(const char *s, char c, long *i);
void	ft_fix_norminet_1(char *a, char const *b, long *n1);

char	**ft_split2(char const *s, char c)
{
	long	i;
	long	k;
	char	**t;

	i = 0;
	k = 0;
	if (!s)
		return (NULL);
	if ((ft_count_split2(s, c)) == -1)
		return (NULL);
	t = malloc((ft_count_split2(s, c) + 1) * sizeof(char *));
	if (!t)
		return (NULL);
	while (k < ft_count_split2(s, c))
	{
		while (s[i] && s[i] == c)
			i++;
		t[k] = ft_copy_split2(s, c, &i);
		if (!t[k])
			return ( NULL);
		k++;
	}
	t[k] = NULL;
	return (t);
}

long	ft_count_split2(char const *s, char c)
{
	long	i;
	long	f;
	long	i_c;
	char	q;
	long	count;

	i = 0;
	f = 0;
	i_c = 0;
	count = 0;
	while (s[i])
	{
		if ((s[i] == '\'' || s[i] == '\"') && i_c == 0)
			ft_fix_norminet_1(&q, s + i, &i_c);
		else if (i_c == 1 && s[i] == q)
			i_c = !i_c;
		if (s[i] != c && f == 0 && i_c == 0)
			ft_fix_norminet_2(&f, &count);
		else if (s[i] == c)
			f = 0;
		i++;
	}
	if (i_c == 1)
		return (-1);
	return (count);
}

char	*ft_copy_split2(const char *s, char c, long *i)
{
	long	j;
	long	k;
	long	i_c;
	char	q;
	char	*t;

	i_c = 0;
	k = 0;
	j = *i;
	while (s[j] && (s[j] != c || i_c == 1))
	{
		if ((s[j] == '\'' || s[j] == '\"') && i_c == 0)
			ft_fix_norminet_1(&q, s + j, &i_c);
		else if (i_c == 1 && s[j] == q)
			i_c = !i_c;
		j++;
	}
	t = malloc((j - *i + 1) * 1);
	if (!t)
		return (NULL);
	while (*i < j)
		t[k++] = s[(*i)++];
	t[k] = '\0';
	return (t);
}
void	ft_fix_norminet_1(char *a, char const *b, long *n1)
{
	*a = *b;
	(*n1) = !(*n1);
}

void	ft_fix_norminet_2(long *n2, long *n1)
{
	(*n1)++;
	(*n2)++;
}


char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	size_t	s1;
	char	*t;

	i = 0;
	s1 = strlen(s);
	t = NULL;
	while (i < s1 + 1)
	{
		if (s[i] == (char)c)
			t = (char *)(s + i);
		i++;
	}
	return (t);
}

void	ft_print_tab(char **t)
{
	int	i;

	i = 0;
	if (!t)
		return ;
	while (t[i])
	{
		printf("\n\t\t > %s <\n", t[i]);
		i++;
	}
}

// ----------------------------------------------------


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
	char	**rs1;
	char	**rs2;

	i = 0;
	j = 0;
	k = 0;
	f = 0;
	// rs = ft_split4(str);
	// if (!rs2)
	// 	return (-1);
	
	rs1=ft_split2(str, '/');
	if(!rs1)
		return -1;
	ft_print_tab(rs1);

	
	// while (rs[k])
	// {
	// 	f = ft_check_q_status(rs[i]);
	// 	if(f==0 && ft_strrchr(rs[k], '/'))
	// 		break;
	// 	if (f == 0)
	// 	{
	// 		i = ft_consume_1(rs[k], t, &j);
	// 		if (i == -1)
	// 			return (-1);
	// 		else if (i == 0)
	// 			return (0);
	// 	}
	// 	else
	// 	{
	// 		i = ft_consume_2(rs[k], t, &j);
	// 		if (i == -1)
	// 			return (-1);
	// 		else if (i == 0)
	// 			return (0);
	// 	}
	// 	k++;
	// }
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
    char *str="*a/*b";

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
	// ft_print_tab(rs);
    return 0;
}