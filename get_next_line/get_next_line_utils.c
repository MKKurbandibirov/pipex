/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magomed <magomed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 11:17:44 by nfarfetc          #+#    #+#             */
/*   Updated: 2022/01/12 11:58:25 by magomed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr( char *str, int ch)
{
	int	i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == (char)ch)
			return ((char *)(str + i));
		i++;
	}
	if (str[i] == (char)ch)
		return ((char *)(str + i));
	return (NULL);
}

int	str_len(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

char	*checker(char *rem)
{
	if (!rem)
	{
		rem = malloc(sizeof(char));
		rem[0] = '\0';
	}
	return (rem);
}

char	*ft_strjoinfree(char *s1, char *s2)
{
	char	*new;
	int		i;
	int		j;

	s1 = checker(s1);
	if (!(s1 && s2))
		return (NULL);
	new = malloc((str_len(s1) + str_len(s2) +1) * sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		new[j++] = s1[i++];
	i = 0;
	while (s2[i])
		new[j++] = s2[i++];
	new[j] = '\0';
	free(s1);
	return (new);
}
