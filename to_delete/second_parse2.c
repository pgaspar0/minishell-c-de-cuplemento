
static bool	is_special_char(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

static int	get_token_length(const char *s)
{
	if (*s == '<' && *(s + 1) == '<')
		return (2); // Handle '<<' as one token
	if (*s == '>' && *(s + 1) == '>')
		return (2); // Handle '>>' as one token
	if (is_special_char(*s))
		return (1); // Handle single special characters
	int len = 0;
	while (s[len] && !is_special_char(s[len]))
		len++;
	return (len); // Handle normal words
}

static size_t	count_tokens(const char *s)
{
	size_t	count = 0;

	while (*s)
	{
		while (*s && (*s == ' ')) // Skip leading spaces
			s++;
		if (*s)
		{
			count++;
			s += get_token_length(s); // Move pointer to the end of the token
		}
	}
	return (count);
}

char	**ft_parse2(const char *s)
{
	char	**matrix;
	size_t	token_count;
	size_t	i = 0;
	int		token_len;

	if (!s)
		return (NULL);
	token_count = count_tokens(s);
	matrix = (char **)malloc((token_count + 1) * sizeof(char *));
	if (!matrix)
		return (NULL);
	while (*s)
	{
		while (*s && (*s == ' ')) // Skip spaces
			s++;
		if (*s)
		{
			token_len = get_token_length(s);
			matrix[i++] = ft_substr(s, 0, token_len);
			s += token_len;
		}
	}
	matrix[i] = NULL; // Null-terminate the matrix
	return (matrix);
}