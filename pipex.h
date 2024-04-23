/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:46:41 by mkaoukin          #+#    #+#             */
/*   Updated: 2024/04/22 17:07:27 by mkaoukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *src);
char	*ft_strjoinn(char *s1, char *s2);
char	*ft_strjoin(char *s1, char *s2);
void	ft_exit(int l, char *err);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int	ft_strncmp(const char *s1, const char *s2, size_t n);

typedef struct s_fd
{
	int			file;
	int			id1;
	int			id2;
	int			file1;
	int			p[2];
	char		*path1;
	char		*path2;
	char		*av2;
	char		*av3;
	char		*line;
}			t_fd;

void	parsing(char **av, char **env, t_fd *fd);
void	parsing_b(char **av, char **env, t_fd *fd, int ac);
char	*get_next_line(int fd);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strjo_or_cat(char *s1, char *s2);
int		ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *str, int flag);
char	*ft_strdup(const char *src);
void	free_all(char **p); ////

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 13
# endif

#endif