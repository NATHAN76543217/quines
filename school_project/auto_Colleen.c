# include <stdlib.h>
# include <stdio.h>
size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return i;
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

int     tester( void )
{
    dprintf(2, "test done\n");
    return 2;
}

int oldM()
{
    /*
        Call the tester of the function
    */
    tester();
    return 0;
}

int	main(void)
{
	char *str[8];
	str[0] = "#include <stdlib.h>\n# include <stdio.h>\n";
	str[1] = "size_t\tft_strlen(const char *s)\n{\n\tint\ti;\n\n\ti = 0;\n\twhile (s[i])\n\t\ti++;\n\treturn i;\n}\n\n";
	str[2] = "char\t*make_program(char\t*s)\n{\n\tint\t\tlen;\n\tint\t\ti;\n\tchar\t*new;\n\tchar\t*p;\n\n\ti = 0;\n\tlen = ft_strlen(s);\n\tnew = malloc(len * 2 + 1);\n\tp = new;\n\twhile (i < len)\n\t{\n\t\tif (s[i] == '\\n' || s[i] == '\\t' || s[i] == '\\\"' || s[i] == '\\\\')\n\t\t{\n\t\t\t*p = '\\\\';\n\t\t\tp++;\n\t\t}\n\t\tif (s[i] == '\\n')\n\t\t\t*p = 'n';\n\t\telse if (s[i] == '\\t')\n\t\t\t*p = 't';\n\t\telse if (s[i] == '\\\"')\n\t\t\t*p = '\\\"';\n\t\telse if (s[i] == '\\\\')\n\t\t\t*p = '\\\\';\n\t\telse\n\t\t\t*p = s[i];\n\t\tp++;\n\t\ti++;\n\t}\n\t*p = '\\0';\n\treturn new;\n}\n\n";
	str[3] = "int     tester( void )\n{\n    dprintf(2, \"test done\\n\");\n    return 2;\n}\n\n";
	str[4] = "int oldM()\n{\n    /*\n        Call the tester of the function\n    */\n    tester();\n    return 0;\n}\n\n";
	str[5] = "\toldM();\n\tdprintf(1, str[6], str[0], str[1], str[2], str[3], str[4], make_program(str[0]), make_program(str[1]), make_program(str[2]), make_program(str[3]), make_program(str[4]), make_program(str[5]), make_program(str[6]), make_program(str[7]), str[5], str[7]";
	str[6] = "%s%s%s%s%sint\tmain(void)\n{\n\tchar *str[8];\n\tstr[0] = \"%s\";\n\tstr[1] = \"%s\";\n\tstr[2] = \"%s\";\n\tstr[3] = \"%s\";\n\tstr[4] = \"%s\";\n\tstr[5] = \"%s\";\n\tstr[6] = \"%s\";\n\tstr[7] = \"%s\";\n%s%s";
	str[7] = ");\n\treturn 0;\n}\n";
	oldM();
	dprintf(1, str[6], str[0], str[1], str[2], str[3], str[4], make_program(str[0]), make_program(str[1]), make_program(str[2]), make_program(str[3]), make_program(str[4]), make_program(str[5]), make_program(str[6]), make_program(str[7]), str[5], str[7]);
	return 0;
}
