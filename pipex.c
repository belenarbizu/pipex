#include <stdio.h>
#include <unistd.h>

void	ft_error(char *str)
{
	perror(str);
	exit(EXIT_SUCCESS);
}

void	ft_child_process(int *fd, int *file, char **argv)
{
	file[0] = open(argv[1], O_RDONLY); //argv[1] actúa como stdin que solo lee
	if (file[0] == -1)
		ft_error("Error en Child File");
}

void	ft_parent_process(int *fd, int *file, char **argv)
{
	file[1] = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0744) //O_CREAT crea el archivo, le doy permisos 744??
	if (file[1] == -1)
		ft_error("Error en Parent File");
}

int	main(int argc, char **argv, char **envp)
{
	int	fd[2];
	int	file[2];
	int	childPid;

	if (argc != 5)
		ft_error("Error en Argc: ./pipex arch1 cmd1 cmd2 arch2");
	if (pipe(fd) < 0)
		ft_error("Error en Pipe");
	childPid = fork();
	if (childPid == -1)
		ft_error("Error en Fork");
	else if (childPid == 0)
		ft_child_process(fd, file, argv);
	else
		ft_parent_process(fd, file, argv);
}
