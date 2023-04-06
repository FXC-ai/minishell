/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_lexer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:58:03 by vgiordan          #+#    #+#             */
/*   Updated: 2023/04/06 11:25:24 by fcoindre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static int  is_quote(char c)
{
	return (c == '\'' || c == '"');
}

int count_chr(const char *str, char c)
{
	int count;
	int i;
	int in_quote;
	char quote;

	count = 0;
	i = 0;
	in_quote = 0;
	quote = '\0';
	while (str[i] != '\0')
	{
		if (str[i] == c && in_quote == 0)
		{
			count++;
		}
		if (is_quote(str[i]) == 1 && in_quote == 0)
		{
			in_quote = 1;
			quote = str[i];
			i++;
		}
		if (str[i] == quote && in_quote == 1)
		{
			in_quote = 0;
			quote = '\0';
		}
		i++;
	}
	if (str[i-1] != c)
	{
		count++;
	}
	return count;
}

static char	*word_dup(const char *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

static int process(char const *s, char **result, char c)
{
	int i = 0;
	int j = 0;
	int words_count;
	int start = 0;
	int in_quotes = 0;
	char quote_char = '\0';

	words_count = count_chr(s, c);
	while (s[i])
	{
		
		
		if ((s[i] == '\'' || s[i] == '\"') && !in_quotes)
		{
			in_quotes = 1;
			quote_char = s[i];
		}
		else if ((s[i] == '\'' || s[i] == '\"') && in_quotes && s[i] == quote_char)
		{
			in_quotes = 0;
		}
		else if (!in_quotes && s[i] == c)
		{
			if (j < words_count)
			{
				result[j++] = word_dup(s, start, i);
				if (!result[j - 1])
				{
					freemalloc(result, j - 1);
					return (-1);
				}
			}
			while (s[i + 1] && s[i + 1] == ' ' && !in_quotes)
				i++;
			start = i + 1;
		}
		i++;
	}
	if (in_quotes == 1)
		return (-2);
	if (!in_quotes && j < words_count)
	{
		result[j++] = word_dup(s, start, i);
		if (!result[j - 1])
		{
			freemalloc(result, j - 1);
			return (-1);
		}
	}
	result[j] = NULL;
	return (0);
}

char	**ft_split_lexer(char const *s, char c)
{
	char	**result;
	int     r;

	result = malloc((count_chr(s, c) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	r = process(s, result, c);
	if (r == -1)
		return (NULL);
	if (r == -2)
	{
		printf("Please close \" or \'\n");
		return (NULL);
	}
		
	return (result);
}

