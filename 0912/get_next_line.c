/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtsubasa <mtsubasa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 02:15:30 by mtsubasa          #+#    #+#             */
/*   Updated: 2024/09/12 02:38:12 by mtsubasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


char ft_strchr()
{
	return();
}

char ft_strjoin(save, buff)
{
	return();
}


char *get_line(fd,*save)
{
	char	*buff;
	int		bytes;
	char	*tmp;


	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	while (!save || !ft_strchr(save, '\n'))
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes == -1)
			return (NULL);
		if (bytes == 0)
			break ;
		buff[bytes] = '\0';
		tmp = ft_strjoin(save, buff);
		if (!tmp)
			return (NULL);
		free(save);
		save = tmp;
	}
	return (save);
}


char	*get_next_line(fd)
{
	char	*line;
	static char	*save;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	save = get_line(fd, save);
	if (!save)
	{
		free(save);
		return (NULL);
	}
	save = save_str(save);
	return (line);
}
