/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbizu- <barbizu-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 11:26:15 by barbizu-          #+#    #+#             */
/*   Updated: 2022/06/09 11:14:36 by barbizu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>
# include "libft/libft.h"

char	*ft_paths_arg(char **paths_sep, char **arg, char **envp);
void	ft_child_process(int *fd, int *file, char **argv, char **envp);
void	ft_parent_process(int *fd, int *file, char **argv, char **envp);
char	*ft_find_path(char **envp);
void	ft_pipex(int *fd, char **argv, char **envp);
void	free_matrix(char **matrix);
void	ft_error(char *str);

#endif
