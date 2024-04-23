/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:06:29 by mkaoukin          #+#    #+#             */
/*   Updated: 2024/04/20 16:18:31 by mkaoukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlen(const char *str, int flag)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (flag == 0)
	{
		while (str[i])
			i++;
	}
	else
	{
		while (str[i] && str[i] != '\n')
			i++;
	}
	return (i);
}

void	ft_exit(int l, char *err)
{
	int	i;

	i = 0;
	if (l == 0)
		exit (0);
	else
	{
		while (err[i])
		{
			write(2, &err[i], 1);
			i++;
		}
		exit (1);
	}
}

static void	command2(t_fd	*fd, char **av, char **env)
{
	char	**cmd2;

	close(fd->p[1]);
	dup2(fd->p[0], 0);
	fd->file1 = open(av[4], O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd->file1 < 0)
		ft_exit(1, "ERROR IN OUTFILE\n");
	cmd2 = ft_split(av[3], ' ');
	dup2(fd->file1, 1);
	if (execve(fd->path2, cmd2, env) == -1)
		ft_exit(1, "ERROR IN CMD2\n");
	close(fd->p[0]);
	close(fd->file1);
}

static void	command1(t_fd	*fd, char **av, char **env)
{
	char	**cmd1;

	close(fd->p[0]);
	fd->file = open(av[1], O_RDWR);
	if (fd->file < 0)
		ft_exit(1, "ERROR IN INFILE\n");
	dup2(fd->file, 0);
	dup2(fd->p[1], 1);
	cmd1 = ft_split(av[2], ' ');
	if (execve(fd->path1, cmd1, env) == -1)
		ft_exit(1, "ERROR IN CMD1\n");
	close(fd->p[1]);
	close(fd->file);
}
void f()
{
	system("leaks pipex");
}

int	main(int ac, char **av, char **env)
{
	atexit(f);
	t_fd	fd;

	if (ac == 5)
	{
		parsing(av, env, &fd);
		if (pipe(fd.p) == -1)
			ft_exit(1, "ERROR PIPE\n");
		fd.id1 = fork ();
		if (fd.id1 == 0)
			command1(&fd, av, env);
		fd.id2 = fork ();
		if (fd.id2 == 0)
			command2(&fd, av, env);
		close (fd.p[1]);
		close (fd.p[0]);
		wait(NULL);
		wait(NULL);
		free (fd.path1);
		free (fd.path2);
	}
	else
		write (2, "Error_Argc\n", 10);
}
