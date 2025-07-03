#include "get_next_line_bonus.h"

char	*copy_dt(char *buf, char *dt, size_t dt_size, size_t buf_size)
{
	char	*new_buf;
	size_t	i;
	size_t	j;

	i = 0;
	new_buf = malloc(buf_size + dt_size + 1);
	if (!new_buf)
		return (NULL);
	if (buf)
	{
		while (i < buf_size)
		{
			new_buf[i] = buf[i];
			i++;
		}
	}
	j = 0;
	while (j < dt_size)
	{
		new_buf[i + j] = dt[j];
		j++;
	}
	new_buf[i + j] = '\0';
	return (new_buf);
}

char	*join_line(char *buf, char *new_dt, size_t buf_size, size_t new_dt_size)
{
	char	*new_buf;

	new_buf = copy_dt(buf, new_dt, new_dt_size, buf_size);
	if (buf)
		free(buf);
	return (new_buf);
}

char	*update_buffer(char *buf, int buf_size, int pos)
{
	char	*new_buf;
	int		i;
	int		new_size;

	new_size = buf_size - pos - 1;
	if (new_size <= 0)
	{
		free(buf);
		return (NULL);
	}
	new_buf = malloc(new_size + 1);
	if (!new_buf)
	{
		free(buf);
		return (NULL);
	}
	i = 0;
	while (i < new_size)
	{
		new_buf[i] = buf[pos + i + 1];
		i++;
	}
	new_buf[i] = '\0';
	free(buf);
	return (new_buf);
}

char	*extract_line(char *buf, char **next_line, int buf_size, int pos)
{
	int		i;
	char	*new_buf;

	if (!buf || !next_line || pos >= buf_size || pos < 0)
		return (NULL);
	*next_line = malloc(pos + 2);
	if (!(*next_line))
	{
		free(buf);
		return (NULL);
	}
	i = 0;
	while (i <= pos)
	{
		(*next_line)[i] = buf[i];
		i++;
	}
	(*next_line)[i] = '\0';
	new_buf = update_buffer(buf, buf_size, pos);
	if (!new_buf && (buf_size - pos - 1 > 0))
	{
		free(*next_line);
		*next_line = NULL;
	}
	return (new_buf);
}

int	if_eof(t_buf *buf, char **new_line)
{
	int	i;

	if (!buf || !buf->dt || buf->dt_s <= 0)
		return (0);
	*new_line = malloc(buf->dt_s + 1);
	if (!(*new_line))
	{
		clear_buf(buf);
		return (-1);
	}
	i = 0;
	while (i < buf->dt_s)
	{
		(*new_line)[i] = buf->dt[i];
		i++;
	}
	(*new_line)[i] = '\0';
	clear_buf(buf);
	return (1);
}
