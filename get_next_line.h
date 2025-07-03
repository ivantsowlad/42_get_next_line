#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef FD_MAX
#  define FD_MAX 1024
# endif

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdarg.h>
# include <stddef.h>
# include <string.h>

typedef struct s_buf
{
	int		dt_s;
	char	*dt;
}	t_buf;

// get_next_line.c
char	*get_next_line(int fd);
int		has_next_line(t_buf *buf);
void	clear_buf(t_buf *buf);
char	*process_line(t_buf *buf, int l_pos);
int		read_next(int fd, t_buf *buf, char **line);

// get_next_line_utils.c
char	*join_line(char *buf, char *addme, size_t s_buf, size_t s_addme);
char	*update_buffer(char *buf, int s_buf, int pos);
char	*extract_line(char *buf, char **next_line, int s_buf, int pos);
char	*copy_dt(char *buf, char *dt, size_t dt_size, size_t buf_size);
int		if_eof(t_buf *buf, char **new_line);

#endif
