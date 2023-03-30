# include <stdio.h>
# include <stdlib.h>

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return i;
}

typedef struct s_list{
	void			*malloc;
	struct s_list	*next;
}	t_list;

t_list		**getUniqMalloc( void )
{
	static t_list* malloced = NULL;
	return &malloced;
}

void	delUniqMalloc( void )
{
	t_list**	malloced = getUniqMalloc();
	t_list*		tmp = NULL;

	while ((*malloced) != NULL)
	{
		tmp = (*malloced);
		free((*malloced)->malloc);
		(*malloced) = (*malloced)->next;
		free(tmp);
	}
}

char	*uniq_malloc( unsigned int size)
{
	t_list**	malloced = getUniqMalloc();
	t_list*		tmp = NULL;

	char * new = malloc(size);
	if (new == NULL)
		return NULL;

	if (*malloced == NULL)
	{
		*malloced = malloc(sizeof(t_list));
		if (*malloced == NULL)
		{
			free(new);
			return NULL;
		}
		(*malloced)->malloc = new;
		(*malloced)->next = NULL;
	}
	else
	{
		tmp = *malloced;
		while (tmp->next != NULL)
		{
			tmp = tmp->next;
		}
		tmp->next = malloc(sizeof(t_list));
		if (tmp->next == NULL)
		{
			free (new);
			return NULL;
		}
		tmp = tmp->next;
		tmp->malloc = new;
		tmp->next = NULL;
	}
	return new; 
}

char	*make_program(char	*s)
{
	int		len;
	int		i;
	char	*new;
	char	*p;

	i = 0;
	len = ft_strlen(s);
	new = uniq_malloc(len * 2 + 1);
	if (new == NULL)
		return NULL;
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

/*
	test the function
*/
int	tester( void )
{
	dprintf(2, "test done\n");
	return 2;
}

int main()
{
	char *includes = "# include <stdio.h>\n# include <stdlib.h>\n\n";
	char *common = "size_t\tft_strlen(const char *s)\n{\n\tint\ti;\n\n\ti = 0;\n\twhile (s[i])\n\t\ti++;\n\treturn i;\n}\n\ntypedef struct s_list{\n\tvoid\t\t\t*malloc;\n\tstruct s_list\t*next;\n}\tt_list;\n\nt_list\t\t**getUniqMalloc( void )\n{\n\tstatic t_list* malloced = NULL;\n\treturn &malloced;\n}\n\nvoid\tdelUniqMalloc( void )\n{\n\tt_list**\tmalloced = getUniqMalloc();\n\tt_list*\t\ttmp = NULL;\n\n\twhile ((*malloced) != NULL)\n\t{\n\t\ttmp = (*malloced);\n\t\tfree((*malloced)->malloc);\n\t\t(*malloced) = (*malloced)->next;\n\t\tfree(tmp);\n\t}\n}\n\nchar\t*uniq_malloc( unsigned int size)\n{\n\tt_list**\tmalloced = getUniqMalloc();\n\tt_list*\t\ttmp = NULL;\n\n\tchar * new = malloc(size);\n\tif (new == NULL)\n\t\treturn NULL;\n\n\tif (*malloced == NULL)\n\t{\n\t\t*malloced = malloc(sizeof(t_list));\n\t\tif (*malloced == NULL)\n\t\t{\n\t\t\tfree(new);\n\t\t\treturn NULL;\n\t\t}\n\t\t(*malloced)->malloc = new;\n\t\t(*malloced)->next = NULL;\n\t}\n\telse\n\t{\n\t\ttmp = *malloced;\n\t\twhile (tmp->next != NULL)\n\t\t{\n\t\t\ttmp = tmp->next;\n\t\t}\n\t\ttmp->next = malloc(sizeof(t_list));\n\t\tif (tmp->next == NULL)\n\t\t{\n\t\t\tfree (new);\n\t\t\treturn NULL;\n\t\t}\n\t\ttmp = tmp->next;\n\t\ttmp->malloc = new;\n\t\ttmp->next = NULL;\n\t}\n\treturn new; \n}\n\nchar\t*make_program(char\t*s)\n{\n\tint\t\tlen;\n\tint\t\ti;\n\tchar\t*new;\n\tchar\t*p;\n\n\ti = 0;\n\tlen = ft_strlen(s);\n\tnew = uniq_malloc(len * 2 + 1);\n\tif (new == NULL)\n\t\treturn NULL;\n\tp = new;\n\twhile (i < len)\n\t{\n\t\tif (s[i] == '\\n' || s[i] == '\\t' || s[i] == '\\\"' || s[i] == '\\\\')\n\t\t{\n\t\t\t*p = '\\\\';\n\t\t\tp++;\n\t\t}\n\t\tif (s[i] == '\\n')\n\t\t\t*p = 'n';\n\t\telse if (s[i] == '\\t')\n\t\t\t*p = 't';\n\t\telse if (s[i] == '\\\"')\n\t\t\t*p = '\\\"';\n\t\telse if (s[i] == '\\\\')\n\t\t\t*p = '\\\\';\n\t\telse\n\t\t\t*p = s[i];\n\t\tp++;\n\t\ti++;\n\t}\n\t*p = '\\0';\n\treturn new;\n}\n";
	char *functions[1];
	functions[0] = "/*\n\ttest the function\n*/\nint\ttester( void )\n{\n\tdprintf(2, \"test done\\n\");\n\treturn 2;\n}\n\n";
	char *format_string = "%s%s\n%sint main()\n{\n\tchar *includes = \"%s\";\n\tchar *common = \"%s\";\n\tchar *functions[1];\n\tfunctions[0] = \"%s\";\n\tchar *format_string = \"%s\";\n\t/*\n\t\tCall the tester of the function\n\t*/\n\ttester();\n\n\t/* Display includes */\n\n\tdprintf(1, format_string, includes, common, functions[0], make_program(includes), make_program(common), make_program(functions[0]), make_program(format_string));\n\tdelUniqMalloc();\n\treturn 0;\n}\n";
	/*
		Call the tester of the function
	*/
	tester();

	/* Display includes */

	dprintf(1, format_string, includes, common, functions[0], make_program(includes), make_program(common), make_program(functions[0]), make_program(format_string));
	delUniqMalloc();
	return 0;
}
