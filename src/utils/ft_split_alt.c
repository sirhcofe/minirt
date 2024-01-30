/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_alt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthor <jthor@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 06:23:30 by jthor             #+#    #+#             */
/*   Updated: 2024/01/29 06:23:32 by jthor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static int	is_sep(char c, char *sep)
{
	while (*sep)
	{
		if (*sep == c)
			return (1);
		sep++;
	}
	return (0);
}

static int	word_count(char const *s, char *sep)
{
	int	ret;

	ret = 0;
	while (*s)
	{
		while (*s && (is_sep(*s, sep) == 1))
			s++;
		if (*s)
		{
			ret++;
			while (*s && (is_sep(*s, sep) == 0))
				s++;
		}
	}
	return (ret);
}

static int	word_len(char const *s, char *sep)
{
	int	ret;

	ret = 0;
	while (*s && (is_sep(*s, sep) == 0))
	{
		ret++;
		s++;
	}
	return (ret);
}

static int	word_split(char const *str, char *sep, char **ret, int i)
{
	int	j;

	ret[i] = malloc((word_len(str, sep) + 1) * sizeof(char));
	if (!ret[i])
	{
		j = 0;
		while (j < i)
		{
			free(ret[j]);
			j++;
		}
		free(ret[i]);
		free(ret);
		return (0);
	}
	j = 0;
	while (*str && (is_sep(*str, sep) == 0))
		ret[i][j++] = *str++;
	ret[i][j] = '\0';
	return (1);
}

char	**ft_split_alt(char *str, char *sep)
{
	char	**ret;
	int		words;
	int		i;

	if (!str)
		return (NULL);
	words = word_count(str, sep);
	ret = malloc((words + 1) * sizeof(char *));
	if (!ret)
		return (NULL);
	i = 0;
	while (i < words)
	{
		while (is_sep(*str, sep) == 1)
			str++;
		if (word_split(str, sep, ret, i) == 0)
			arg_error("Error at ft_split_alt");
		while (*str && (is_sep(*str, sep) == 0))
			str++;
		i++;
	}
	ret[i] = NULL;
	return (ret);
}
