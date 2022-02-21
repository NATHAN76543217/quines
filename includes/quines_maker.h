#ifndef QUINES_MAKER_H
# define QUINES_MAKER_H

#include "libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>

typedef	struct s_quine
{
	int		fd;
	int		nb_func;
	int		nb_str;
	int		print_ndx;
	char	**str;
	char	**funcs;
	char	*ptf;
}   	t_quine;
#endif