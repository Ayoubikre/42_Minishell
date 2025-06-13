/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:29:56 by aakritah          #+#    #+#             */
/*   Updated: 2025/06/13 02:51:43 by noctis           ###   ########.fr       */
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
char	*ft_copy_split4(char const *s, int *k);

int	ft_count_split4(char const *s);



char	**ft_split4(char const *str)
{
	int		i;
	int		s;
	int		k;
	char	**t;

	if (!str)
		return (NULL);
	i = 0;
	k = 0;
	s = ft_count_split4(str);
	t = malloc((s + 1) * sizeof(char *));
	if (!t)
		return (NULL);
	while (i < s)
	{
		t[i] = ft_copy_split4(str, &k);
		if (!t[i])
			return ( NULL);
		i++;
	}
	t[i] = NULL;
	return (t);
}

int	ft_count_split4(char const *s)
{
	int		i;
	int		count;
	char	q_c;

	i = 0;
	count = 0;
	q_c = 0;
	while (s[i])
	{
		count++;
		if (s[i] == '\'' || s[i] == '\"')
		{
			q_c = s[i++];
			while (s[i] && s[i] != q_c)
				i++;
			i++;
		}
		else
		{
			while (s[i] && !(s[i] == '\'' || s[i] == '\"'))
				i++;
		}
	}
	return (count);
}

char	*ft_copy_split4(char const *s, int *k)
{
	int		i;
	int		j;
	char	*t;
	char	q_c;

	i = (*k);
	if (s[*k] == '\'' || s[*k] == '\"')
	{
		q_c = s[(*k)++];
		while (s[*k] && s[*k] != q_c)
			(*k)++;
		(*k)++;
	}
	else
		while (s[*k] && !(s[*k] == '\'' || s[*k] == '\"'))
			(*k)++;
	t = malloc((((*k) - i + 1) + 1));
	if (!t)
		return (NULL);
	j = 0;
	while (i < *k)
		t[j++] = s[i++];
	t[j] = '\0';
	return (t);
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
int	ft_check_q_status(char *t)
{
	int	i;

	if (!t)
		return (0);
	if (t[0] == '\"')
		i = 2;
	else if (t[0] == '\'')
		i = 1;
	else
		i = 0;
	return (i);
}
int	ft_check_slash(char *t)
{
	int	i;

	i = 0;
	while (t[i])
	{
		if (t[i] == '/')
			return (1);
		i++;
	}
	return (0);
}
// ----------------------------------------------------


// // int	ft_consume_1(char *rs, char t, int *i)
// // {
// // }

// // int	ft_consume_2(char *rs, char t, int *i)
// // {
// // 	char	*rs2;
// // 	int		s;
// // 	int		k;

// // 	rs2 = ft_remove_q(rs);
// // 	if (!rs2)
// // 		return (-1);
// // 	s = ft_strlen(rs2);
// // 	k = ft_strncmp(rs2, t + *i, s);
// // 	if (k != 0)
// // 		return (-1);
// // 	else
// // 		*i += s;
// // 	return (1);
// // }

// int	ft_valid(char *str, char *t)
// {
// 	int		i;
// 	int		j;
// 	int		k;
// 	int		f_q;
// 	int		f_s;
// 	int		valid;
	
// 	char	**rs1;
// 	char	**rs2;
// 	char *tmp;

// 	i = 0;
// 	j = 0;
// 	k = 0;
// 	f_q = 0;
// 	f_s = 0;
// 	valid = 1;


// 	rs1=ft_split4(str);
// 	if(!rs1)
// 		return -1;
	
// 	while(rs1[i])
// 	{
// 		f_q=ft_check_q_status(rs1[i]);
// 		// f_s=ft_check_slash(rs1[i]);
// 		j=0;

// 		if(f_q!=0)
// 		{
// 			// tmp=ft_remove_q(rs[i]);
// 			while(*t)
// 			{
// 				printf("%c - %c\n", *t, rs1[i][j]);
// 				// int s=strlen(rs[i]);
// 				if(*t!=rs1[i][j])
// 					return 0;
// 				j++;
// 				t++;
// 			}
			
// 		}
// 		else
// 		{
// 			while


// 		}
// 		i++;
// 	}

// 	return (1);
// }


int match_with_star(const char *pattern, const char **filename_ptr)
{
    const char *p = pattern;
    const char *f = *filename_ptr;
    const char *star_p = NULL;
    const char *star_f = NULL;

    while (*f && *p)
    {
        if (*p == '*')
        {
            star_p = ++p;
            star_f = f;
        }
        else if (*p == *f)
        {
            p++;
            f++;
        }
        else if (star_p)
        {
            p = star_p;
            f = ++star_f;
        }
        else
        {
            return 0;
        }
    }

    // Skip remaining * in pattern
    while (*p == '*') p++;

    if (*p == '\0')
    {
        *filename_ptr = f; // advance filename if match succeeds
        return 1;
    }

    return 0;
}


int ft_valid( char *pattern,  char *filename)
{
	
char **chunks = ft_split4(pattern); // ["u", "*", "u"]
int i = 0;
const char *f = filename;

while (chunks[i])
{
    int is_quoted = ft_check_q_status(chunks[i]);

    if (is_quoted)
    {
        // Match chunk literally (including any '*')
        int len = strlen(chunks[i]);
        if (strncmp(f, chunks[i], len) != 0)
            return 0;
        f += len;
		// f+=2;
    }
    else
    {
        // Chunk may contain '*'
        if (!match_with_star(chunks[i], &f))
            return 0;
    }
    i++;
}

return *f == '\0';

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
    char **rs1;
    // char *str="*a\'/*\'/\'*b\'\"\"";
    char *str="u*ii*ii*u";

	char **t = malloc((10 + 1) * sizeof(char *));
    t[0]=strdup("usdfasdfiifsdfaiiiaaaiu");
    t[1]=strdup("..a..b");
    t[2]=strdup("u*u");
    t[3]=strdup("ab.");
    t[4]=strdup("kldjsfa");
    t[5]=strdup("..");
    t[6]=strdup(".a b.");
    t[7]=strdup("a.b");
    t[8]=strdup("faklsab");
    t[9]=strdup("asdsklfjbdsf");
    t[10]=NULL;
    
    // rs = ft_filter_wc_list(str, t);
    // i=0;
	// ft_print_tab(rs);

	if(ft_valid(str, t[2])== 1)
		printf("valid\n");
	else
		printf("not valid\n");


    return 0;
}