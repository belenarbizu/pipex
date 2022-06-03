/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbizu- <barbizu-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 11:26:15 by barbizu-          #+#    #+#             */
/*   Updated: 2022/06/03 13:22:53 by barbizu-         ###   ########.fr       */
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

void	ft_error(char *str);
void	ft_child_process(int *fd, int *file, char **argv, char **envp);
void	ft_parent_process(int *fd, int *file, char **argv, char **envp);
char	*ft_find_path(char **envp);

#endif
