#include <minirt.h>

static int	is_sep(const char *delim, char c)
{
	while (*delim)
	{
		if (c == *delim)
			return (1);
		delim++;
	}
	return (0);
}

static int	get_word_num(const char *line, const char *delim)
{
	int	ret;

	ret = 0;
	while (*line)
	{
		while (*line && is_sep(delim, *line))
			line++;
		if (*line)
			ret++;
		while (*line && !is_sep(delim, *line))
			line++;
	}
	return (ret);
}

static int	get_word_len(const char *line, const char *delim)
{
	int	ret;

	ret = 0;
	while (line[ret] && !is_sep(delim, line[ret]))
		ret++;
	return(ret);
}

static int	word_split(char *line, char *delim, char **ret, int index)
{
	int	j;

	ret[index] = malloc(sizeof(char) * get_word_len(line, delim));
	if (!ret[index])
		return (0);
	j = -1;
	while (!is_sep(delim, line[++j]))
		ret[index][j] = line[j];
	ret[index][j] = '\0';
	return (1);
}

char	**ft_split_alt(char *line, char *delim)
{
	char	**ret;
	int		word_num;
	int		i;

	word_num = get_word_num(line, delim);
	ret = malloc(sizeof(char *) * (word_num + 1));
	i = 0;
	while (i < word_num)
	{
		while (is_sep(delim, *line))
			line++;
		if (word_split(line, delim, ret, i) == 0)
			arg_error("Error at ft_split_alt");
		while (*line && !is_sep(delim, *line))
			line++;
		i++;
	}
	ret[i] == NULL;
	return (ret);
}