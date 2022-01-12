/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magomed <magomed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 13:37:46 by magomed           #+#    #+#             */
/*   Updated: 2022/01/12 11:58:25 by magomed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strlen(const char *c)
{
	int	i;

	i = 0;
	while (c[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strnstr(const char *h, const char *n, int len)
{
	int	i;
	int	j;

	i = 0;
	if (!n[0])
		return ((char *)h);
	while (i < len && h[i])
	{
		j = 0;
		while (i + j < len && h[i + j] == n[j])
		{
			j++;
		}
		if (!n[j])
			return ((char *)&h[i]);
		i++;
	}
	return (NULL);
}

char	*ft_strjoinfree(char *s1, char *s2)
{
	char	*new;
	int		i;
	int		j;

	if (!(s1 && s2))
		return (NULL);
	new = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!new)
		print_error("Error: malloc error!");
	i = 0;
	j = 0;
	while (s1[i])
		new[j++] = s1[i++];
	i = 0;
	while (s2[i])
		new[j++] = s2[i++];
	new[j] = '\0';
	return (new);
}

char	**find_path(char **envr)
{
	int 	i;
	char	*tmp;
	char	**path;

	i = -1;
	tmp = malloc(sizeof(char));
	if (!tmp)
		print_error("Error: malloc error!");
	tmp[0] = '\0';
	while (envr[++i])
	{
		tmp = ft_strnstr(envr[i], "PATH=", 6);
		if (tmp)
			break ;
	}
	if (!envr[i])
		print_error("Error: no path in envr!");
	path = ft_split(tmp + 5, ':');
	i = -1;
	while (path[++i])
		path[i] = ft_strjoinfree(path[i], "/");
	return (path);
}

char	*identify_cmd(char *cmd, char **path)
{
	int		i;
	char	*tmp;

	i = -1;
	while (path[++i])
	{
		tmp = ft_strjoinfree(path[i], cmd);
		if (access(tmp, F_OK) == 0)
		{
			free(cmd);
			return (tmp);
		}
		else
			free(tmp);
	}
	if (!path[i])
		print_error("Error: command not found!");
	return (NULL);
}
