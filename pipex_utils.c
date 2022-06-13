/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbizu- <barbizu-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 16:14:09 by barbizu-          #+#    #+#             */
/*   Updated: 2022/06/09 11:12:54 by barbizu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

char	*ft_find_path(char **envp)
{
	int		i;
	char	*path_env;

	i = 0;
	while (!ft_strnstr(envp[i], "PATH=", 5))
		i++;
	path_env = ft_strnstr(envp[i], "PATH=", 5);
	return (path_env + 5);
}

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

void	ft_error(char *str)
{
	perror(str);
	exit(127);
}
