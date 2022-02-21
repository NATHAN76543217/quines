#include "quines_maker.h"
#define HEAD 0
#define STRLEN 1
#define MK_PROG 2

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return i;
}

char *realloc_str(char *str, int new_size)
{
    char    *tmp;
    int     i;

    i = -1;
    if (!(tmp = wrmalloc(new_size)))
    	return (0);
    ft_bzero(tmp, new_size);
    while (str[++i])
        tmp[i] = str[i];
    wrfree(str);
	// tmp[i] = '\0';
    return (tmp);
}

void	recur(int x, char *new, int *i)
{
	char res;

	if (x > 0)
	{
		res = x % 10 + '0';
		x /= 10;
		recur(x, new, i);
		new[*i] = res;
		*i += 1;
	}
}
char	*itoa(int x)
{
	char	*new;
	int		i;

	i = 0;
	if (!(new = malloc(11*sizeof(char) + 1)))
		return NULL;
	if (x < 0)
	{
		*new = '-';
		x *= -1;
		i++;
	}
	else if (x == 0)
		new[i++] = '0';
	recur(x, new, &i);
	new[i] = '\0';
	return new;
}

void	add_line(char **str, char *line)
{
	if (!*str)
	{
		*str = "\0";
		*(str + 1) = NULL;
	}
	*str = realloc_str(*str, ft_strlen(*str) + ft_strlen(line) + 2);
	ft_strlcpy(*str + ft_strlen(*str), line, ft_strlen(line) + 2);
	ft_strlcpy(*str + ft_strlen(*str), "\n", 2);
}

char	*make_program(char	*s)
{
	int		len;
	int		i;
	char	*new;
	char	*p;

	i = 0;
	len = ft_strlen(s);
	new = malloc(len * 2 + 1);
	p = new;
	while (i < len)
	{
		if (s[i] == '\n' || s[i] == '\t' || s[i] == '\"' || s[i] == '\\')
		{
			*p = '\\';
			p++;
		}
		if (s[i] == '\n')
			*p = 'n';
		else if (s[i] == '\t')
			*p = 't';
		else if (s[i] == '\"')
			*p = '\"';
		else if (s[i] == '\\')
			*p = '\\';
		else
			*p = s[i];
		p++;
		i++;
	}
	*p = '\0';
	return new;
}

void	write_in(t_quine *Q)
{
	int i;

	i = 0;
	dprintf(1, "WRITING\n");
	while (Q->funcs[i])
	{
		// dprintf(1, "Writing:%s\n", Q->funcs[i]);
		write(Q->fd, Q->funcs[i], ft_strlen(Q->funcs[i]));
		i++;
	}
	i=0;
	while (Q->str[i])
	{
		// dprintf(1, "Writing:%s\n", Q->str[i]);
		write(Q->fd, Q->str[i], ft_strlen(Q->str[i]));
		i++;
	}
}

void	ft_strcpy(char *dst, char *src)
{
	int i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
}
int		ft_strstr(char *hay, char *needle)
{
	int i;
	int y;

	y = 0;
	i = 0;
	while (hay[i])
	{
		while (hay[i] == needle[y])
		{
			i++;
			y++;
		}
		if (!needle[y])
			return i - y;
		y = 0;
		i++;	
	}
	return -1;
}
void	func_handle(t_quine *Q, char **line)
{
	int ndx;

	// dprintf(1,"line =%s\n", *line);
	ndx = ft_strstr(*line, "main");
	if (ndx >= 0)
	{
		dprintf(1, "make oldM\n");
		ft_strcpy(*line + ndx, "oldM");
	}
	add_line(&Q->funcs[Q->nb_func-1], *line);
	free(*line);
	get_next_line(Q->fd, line);
	// dprintf(1,"line =%s\n", *line);
	while (*line[0] != '}')
	{
		add_line(&Q->funcs[Q->nb_func-1], *line);
		free(*line);
		get_next_line(Q->fd, line);
		// dprintf(1,"line =%s\n", Q->funcs[Q->nb_func-1]);
	}
	add_line(&Q->funcs[Q->nb_func-1], *line);
	add_line(&Q->funcs[Q->nb_func-1], "\0");

}
void	parse(t_quine *Q)
{
	char    *line;

	line = NULL;
	while (get_next_line(Q->fd, &line) == 1)
	{
		if (line == NULL)
			continue ;
		if (line[0] == '#')
			add_line(&Q->funcs[HEAD], line);
		else if (!ft_strncmp(line, "int", 3) || !ft_strncmp(line, "char", 4) || !ft_strncmp(line, "void", 4))
		{
			Q->nb_func += 1;
			dprintf(1, "Fonction:%d\n", Q->nb_func);
			func_handle(Q, &line);
		}	
		free(line);
	}
}
char	*add_strings(int	count, ...)
{
	int		i;
	int		size;
	va_list	vl;
	va_list	sl;
	char	*new;
	char	*arg;

	i = 0;
	size = 0;
	va_start(vl, count);
	va_copy(sl, vl);
	while (i < count)
	{
		size += ft_strlen(va_arg(vl, char *));
		i++;
	}
	if (!(new = malloc(size + 1)))
		return NULL;
	i = 0;
	while (count > 0)
	{
		arg = (char *)va_arg(sl, char *);
		while (*arg != '\0')
		{
			new[i] = *arg;
			arg++;
			i++;
		}
		new[i] = '\0';
		count --;
	}
	va_end(vl);
	va_end(sl);
	return new;
}

void	add_replika(t_quine *Q)
{
	int		i;
	char	*main;
	char	*eof;

	eof = ");\n\treturn 0;\n}\n";
	main = "\0";
	i = 0;
	dprintf(1, "dprintf nb_str:%d\n", Q->nb_str);
	//format string
	Q->ptf = "\toldM();\n\tdprintf(1, ";
	Q->ptf = ft_strjoin(Q->ptf, add_strings(3, "str[", itoa(Q->nb_func + 1), "]"));
	while (i < Q->nb_func)
	{
		main = ft_strjoin("%s", main);
		i++;
	}
	i = 0;
	//ajoute les arg de dprintf
	dprintf(1, "add args, nb_func = %d\n", Q->nb_func);
	//arg print prog before main
	while (i < Q->nb_func)
	{
		Q->ptf = ft_strjoin(Q->ptf, add_strings(3, ", str[", itoa(i), "]"));
		// Q->ptf = ft_strjoin(Q->ptf, add_strings(3, ", make_program(str[", itoa(i), "])"));
		i++;
	}
	i = 0;
	//arg print in main
	while (i < Q->nb_func + 3)
	{
		Q->ptf = ft_strjoin(Q->ptf, add_strings(3, ", make_program(str[", itoa(i), "])"));
		i++;
	}
	Q->ptf = ft_strjoin(Q->ptf, add_strings(3, ", str[", itoa(i - 3), "]"));
	Q->ptf = ft_strjoin(Q->ptf, add_strings(3, ", str[", itoa(i - 1), "]"));
	//main
	i = 0;
	dprintf(1, "main    nb_str:%d\n", Q->nb_str);
	Q->str[Q->nb_str] = add_strings(3, "int	main(void)\n{\n\tchar *str[", itoa(Q->nb_func + Q->nb_str + 3), "];\n");
	main = add_strings(2, main, Q->str[Q->nb_str]);
	//ajouter fonction Q->funcs sous forme str dans main
	while (i < Q->nb_func + 3)
	{
		// dprintf(1, "%dfunc = %s\n", i, Q->funcs[i]);
		if (i < Q->nb_func)
			add_line(&Q->str[Q->nb_str], add_strings(5, "\tstr[", itoa(i), "] = \"", make_program(Q->funcs[i]), "\";"));
		//main format string
		add_line(&main, add_strings(5, "\tstr[", itoa(i), "] = \"", "%s", "\";"));
	// 	dprintf(1, "i = %d\n", i);
		i++;
	}
	// %s pour afficher code apres les string du main
	main = ft_strjoin(main, "%s%s");
	dprintf(1, "add_func done\n");
	//ajout des str dprintf et main sous forme str dans main
	i = Q->nb_func;
	add_line(&Q->str[Q->nb_str], add_strings(5, "\tstr[", itoa(i), "] = \"", make_program(Q->ptf), "\";"));
	i++;
	add_line(&Q->str[Q->nb_str], add_strings(5, "\tstr[", itoa(i), "] = \"", make_program(main), "\";"));
	i++;
	add_line(&Q->str[Q->nb_str], add_strings(5, "\tstr[", itoa(i), "] = \"", make_program(eof), "\";"));

	// add_line(&Q->str[Q->nb_func], add_strings(5, "\tstr[", itoa(i), "] = \"", "%s", "\";"));
	Q->nb_str += 1;
	Q->str[Q->nb_str] = Q->ptf;
	Q->nb_str +=1;
	dprintf(1, "EOF     nb_str:%d\n", Q->nb_str);
	add_line(&Q->str[Q->nb_str], eof);

}

int		init(t_quine *Q, char *av1)
{
	if ((Q->fd = open(av1, O_RDONLY)) < 0)
		return -1;
	dprintf(1, "FD = %d\n", Q->fd);
	if (!(Q->str = malloc(30 * sizeof(char *))))
		return(dprintf(1, "ERROR fd=%d errno = %d\n", Q->fd, errno));
	if (!(Q->funcs = malloc(30 * sizeof(char *))))
		return(dprintf(1, "ERROR fd=%d errno = %d\n", Q->fd, errno));
	Q->funcs[HEAD] = "#include <stdlib.h>\n";
	Q->funcs[STRLEN] = "size_t\tft_strlen(const char *s)\n{\n\tint	i;\n\n\ti = 0;\n\twhile (s[i])\n\t\ti++;\n\treturn i;\n}\n\n";
	Q->funcs[MK_PROG] = "char\t*make_program(char\t*s)\n{\n\tint\t\tlen;\n\tint\t\ti;\n\tchar\t*new;\n\tchar\t*p;\n\n\ti = 0;\n\tlen = ft_strlen(s);\n\tnew = malloc(len * 2 + 1);\n\tp = new;\n\twhile (i < len)\n\t{\n\t\tif (s[i] == '\\n' || s[i] == '\\t' || s[i] == '\\\"' || s[i] == '\\\\')\n\t\t{\n\t\t\t*p = '\\\\';\n\t\t\tp++;\n\t\t}\n\t\tif (s[i] == '\\n')\n\t\t\t*p = 'n';\n\t\telse if (s[i] == '\\t')\n\t\t\t*p = 't';\n\t\telse if (s[i] == '\\\"')\n\t\t\t*p = '\\\"';\n\t\telse if (s[i] == '\\\\')\n\t\t\t*p = '\\\\';\n\t\telse\n\t\t\t*p = s[i];\n\t\tp++;\n\t\ti++;\n\t}\n\t*p = '\\0';\n\treturn new;\n}\n\n";
	Q->nb_func = 3;
	Q->nb_str = 0;
	return 0;
}
//crée un fichier avec le programme passé en entré formaté pour etre auto-reproducteur
int	main(int ac, char** av)
{
	t_quine Q;

	if (ac != 2)
		return 0;
	init(&Q, av[1]);
	parse(&Q);
	add_replika(&Q);
	// dprintf(1, "HEAD = %s\n", str[HEAD]);
	dprintf(1, "%s\n", ft_strjoin("auto_", av[1]));
	close(Q.fd);
	if ((Q.fd = open(ft_strjoin("auto_", av[1]), O_RDWR | O_TRUNC | O_CREAT , S_IRWXU | S_IRWXG )) < 0)
		return(dprintf(1, "ERROR fd=%d errno = %d\n", Q.fd, errno));
	write_in(&Q);
	close(Q.fd);
	return 0;
}