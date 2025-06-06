/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:29:56 by aakritah          #+#    #+#             */
/*   Updated: 2025/06/06 15:45:05 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
void	ft_free(char **t);


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

// long	ft_count_split4(char const *s)
// {
// 	long	i;
// 	long	f;
// 	long	i_c;
// 	char	q;
// 	long	count;

// 	i = 0;
// 	f = 0;
// 	i_c = 0;
// 	count = 0;
// 	while (s[i])
// 	{
//         if ((s[i] == '\'' || s[i] == '\"') && i_c == 0)
//         {
//             (f) = !(f);
//             q=s[i];            
//         	(i_c) = !(i_c);
//             // i++;
//         }
//         else if (i_c == 1 && s[i] == q)
//         {
//             (f) = !(f);           
//         	(i_c) = !(i_c);
//             i++;
//         }
//         if(f==0)
//         {
//             f=1;
// 		    printf("\n\t\t > %c <\n", s[i]);
//             count++;
//         }
//         i++;   
//     }
// 	return (count);
// }

long ft_count_split4(char const *s)
{
    long i = 0;
    long count = 0;
    int in_quote = 0;
    char quote_char = 0;

    while (s[i])
    {
        if (!in_quote && (s[i] == '\'' || s[i] == '\"'))
        {
            in_quote = 1;
            quote_char = s[i];
            count++; // Count the quoted substring
        }
        else if (in_quote && s[i] == quote_char)
        {
            in_quote = 0;
            quote_char = 0;
        }
        else if (!in_quote )
        {
            // Start of a non-quoted segment
            count++;
            // Skip the entire non-quoted segment
            while (s[i] && s[i] != '\'' && s[i] != '\"')
                i++;
            continue; // Avoid incrementing i again
        }
        i++;
    }
    return (count);
}

char	*ft_copy_split4(const char *s, char c, long *i)
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

char	**ft_split4(char const *s)
{
	long	i;
	long	k;
	char	**t;

	i = 0;
	k = 0;
	if (!s)
		return (NULL);
    printf(">%ld<",ft_count_split4(s));
	// if ((ft_count_split4(s, c)) == -1)
	// 	return (NULL);
	// t = malloc((ft_count_split4(s, c) + 1) * sizeof(char *));
	// if (!t)
	// 	return (NULL);
	// while (k < ft_count_split4(s, c))
	// {
	// 	while (s[i] && s[i] == c)
	// 		i++;
	// 	t[k] = ft_copy_split4(s, c, &i);
	// 	if (!t[k])
	// 		return (ft_free(t), NULL);
	// 	k++;
	// }
	// t[k] = NULL;
	// return (t);
	return (NULL);
}





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

int	main(void)
{
	char **t = ft_split4("abc\'\'   \'a\'  \"ab\'c\"abc");
	ft_print_tab(t);
}