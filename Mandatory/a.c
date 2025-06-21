char	**ft_split2(char const *s)
{
	long	i;
	long	k;
	char	**t;

	i = 0;
	k = 0;
	if (!s)
		return (NULL);
	printf(">count : %ld<\n",ft_count_split2(s));
	if ((ft_count_split2(s)) == -1)
		return (NULL);
	t = malloc((ft_count_split2(s) + 1) * sizeof(char *));
	if (!t)
		return (NULL);
	while (k < ft_count_split2(s))
	{
		while (s[i] && ft_isspace(s[i]))
			i++;
		t[k] = ft_copy_split2(s, &i);
		if (!t[k])
			return (ft_free(t), NULL);
		k++;
	}
	t[k] = NULL;
	return (t);
}

long	ft_count_split2(char const *s)
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
		if (ft_isspace(s[i]) == 0 && f == 0 && i_c == 0)
			ft_fix_norminet_2(&f, &count);
		else if (ft_isspace(s[i]))
			f = 0;
		i++;
	}
	if (i_c == 1)
		return (-1);
	return (count);
}

char	*ft_copy_split2(const char *s, long *i)
{
	long	j;
	long	k;
	long	i_c;
	char	q;
	char	*t;

	i_c = 0;
	k = 0;
	j = *i;
	while (s[j] && (ft_isspace(s[j]) == 0  || i_c == 1))
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


// ----------


int ft_isspace(int c)
{
	if((9 <= c && c <= 13) || c == 32)
		return 1;
	return 0;
}

// ----------


int	ft_check_string(char *str)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '\0')
		return (0);
	return (1);
}

// ----------


int	ft_check_if_ambiguous(char *str)
{
	int		i;
	int		s;
	int		f;
	char	**t;

	t = ft_split4(str);
	if (!t)
		return (-1);
	i = 0;
	while (t[i])
	{
		f = ft_check_q_status(t[i]);
		s = ft_count_split2(t[i]);
		if (f == 0 && s > 1)
			return (ft_free(t), -2);
		i++;
	}
	return (ft_free(t), 0);
}

// ----------


int	ft_check_buildin_cmd(char *t)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_strdup(t);
	if (!tmp1)
		return (-1);
	tmp2 = ft_remove_q(tmp1);
	if (!tmp1)
		return (free(tmp1), -1);
	if (ft_check_word("echo", tmp2) == 0)
		return (free(tmp2), 0);
	else if (ft_check_word("cd", tmp2) == 0)
		return (free(tmp2), 0);
	else if (ft_check_word("pwd", tmp2) == 0)
		return (free(tmp2), 0);
	else if (ft_check_word("export", tmp2) == 0)
		return (free(tmp2), 0);
	else if (ft_check_word("unset", tmp2) == 0)
		return (free(tmp2), 0);
	else if (ft_check_word("env", tmp2) == 0)
		return (free(tmp2), 0);
	else if (ft_check_word("exit", tmp2) == 0)
		return (free(tmp2), 0);
	return (free(tmp2), -1);
}