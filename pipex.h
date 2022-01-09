/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magomed <magomed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 13:26:15 by magomed           #+#    #+#             */
/*   Updated: 2022/01/09 19:28:15 by magomed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
//# include <sys/wait.h>

typedef struct s_pipex
{
	int		fd1;
	int		fd2;
	char	**cmd1;
	char	**cmd2;
	char	**argv;
	int		fd[2];
	
}	t_pipex;

int		ft_strlen(const char *c);
char	*ft_strnstr(const char *h, const char *n, int len);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char const *s, char c)

#endif