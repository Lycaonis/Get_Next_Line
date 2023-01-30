/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selveren <selveren@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:33:36 by selveren          #+#    #+#             */
/*   Updated: 2023/01/30 13:00:39 by selveren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
//#include <stdio.h>
//#include <fcntl.h>

static char	*left_str(char *s, char c)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i] != '\0' && s[i] != c)
		i++;
	if (!s[i])
	{
		free(s);
		return (NULL);
	}
	str = (char *)malloc(1 * (ft_strlen(s) - i));
	if (!str)
		return (NULL);
	i++;
	while (s[i] != '\0')
		str[j++] = s[i++];
	str[j] = '\0';
	free(s);
	return (str);
}

static char	*new_line(char *s, char c)
{
	char	*str;
	int		i;

	i = 0;
	if (!s[i])
		return (NULL);
	while (s[i] != '\0' && s[i] != c)
		i++;
	str = (char *)malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i] != '\0' && s[i] != c)
	{
		str[i] = s[i];
		i++;
	}
	if (s[i] == c)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	*read_line(int fd, char *line)
{
	char	*str;
	int		i;

	str = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!str)
		return (NULL);
	i = 1;
	while (!ft_strchr(line, '\n') && i != 0)
	{
		i = read(fd, str, BUFFER_SIZE);
		if (i == -1)
		{
			free(str);
			return (NULL);
		}
		str[i] = '\0';
		line = ft_strjoin(line, str);
	}
	free(str);
	return (line);
}

char	*get_next_line(int fd)
{
	char		*str;
	static char	*line[4096];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line[fd] = read_line(fd, line[fd]);
	if (line[fd])
	{
		str = new_line(line[fd], '\n');
		line[fd] = left_str(line[fd], '\n');
		return (str);
	}
	return (NULL);
}

/*#include <stdio.h>
 int		main()
 {
     char *line;
     int fd1 = open("b.txt",O_RDONLY);
	 int fd2 = open("a.txt",O_RDONLY);
      line = get_next_line(fd1);
 	 printf("%s\n",line);
	 char *line2 = get_next_line(fd2);
 	 printf("%s\n",line2);
	    line = get_next_line(fd1);
 	 printf("%s\n",line);
	 	line2 = get_next_line(fd2);
 	 printf("%s\n",line2);
	// printf("%d\n",fd2);
	// printf("%d\n",fd1);
	
 	close(fd1);
 }*/