#include "get_next_line.h"

void	clear_buf(t_buf *buf)
{
	if (buf && buf->dt)
	{
		free(buf->dt);
		buf->dt = NULL;
		buf->dt_s = 0;
	}
}

int	has_next_line(t_buf *buf)
{
	int	pos;

	if (!buf || !buf->dt || buf->dt_s <= 0)
		return (-1);
	pos = 0;
	while (pos < buf->dt_s)
	{
		if (buf->dt[pos] == '\n')
			return (pos);
		pos++;
	}
	return (-1);
}

char	*process_line(t_buf *buf, int l_pos)
{
	char	*line;

	line = NULL;
	buf->dt = extract_line(buf->dt, &line, buf->dt_s, l_pos);
	if (!line)
	{
		clear_buf(buf);
		return (NULL);
	}
	buf->dt_s -= (l_pos + 1);
	if (buf->dt_s == 0)
		clear_buf(buf);
	return (line);
}

int	read_next(int fd, t_buf *buf, char **line)
{
	char	*tmp;
	int		bytes_read;

	tmp = malloc(BUFFER_SIZE);
	if (!tmp)
		return (-1);
	bytes_read = read(fd, tmp, BUFFER_SIZE);
	if (bytes_read < 0)
	{
		free(tmp);
		return (-1);
	}
	if (bytes_read == 0)
	{
		free(tmp);
		if (if_eof(buf, line) < 0)
			return (-1);
		return (0);
	}
	buf->dt = join_line(buf->dt, tmp, buf->dt_s, bytes_read);
	free(tmp);
	if (!buf->dt)
		return (-1);
	buf->dt_s += bytes_read;
	return (1);
}

char	*get_next_line(int fd)
{
	static t_buf	bf[FD_MAX] = {0};
	char			*line;
	int				l_pos;
	int				read_result;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd >= FD_MAX)
		return (NULL);
	line = NULL;
	while (1)
	{
		l_pos = has_next_line(&bf[fd]);
		if (l_pos >= 0)
		{
			line = process_line(&bf[fd], l_pos);
			if (bf[fd].dt_s == 0)
				clear_buf(&bf[fd]);
			return (line);
		}
		read_result = read_next(fd, &bf[fd], &line);
		if (read_result <= 0)
		{
			clear_buf(&bf[fd]);
			return (line);
		}
	}
}
