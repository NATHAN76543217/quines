#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

#define HEAD 0
#define DEFINE 1
#define STRLEN 2
#define MK_PROG 3
#define ADD_STR 4
#define MAIN 5
#define REPLIK 6
#define FORMAT 7
#define FORMAT_S 8
#define EF 9
#define VIRUS 10
#define PARASITE 11
#define V_DEFINE 12
#define ITOA 13
#define EXEC 14

// faire programme qui peut se reproduire ou crée un autre programme. Celui-ci pourra se reproduire ou crée le programme initial
int	ft_strlen(char	*s)
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

int	main()
{
	char	*STR[15];
	int		fd;

	STR[HEAD] = "#include <stdio.h>\n#include <stdlib.h>\n#include <stdarg.h>\n#include <fcntl.h>\n#include <errno.h>\n#include <unistd.h>\n#include <string.h>\n\n";
	STR[DEFINE] = "#define HEAD 0\n#define DEFINE 1\n#define STRLEN 2\n#define MK_PROG 3\n#define ADD_STR 4\n#define MAIN 5\n#define REPLIK 6\n#define FORMAT 7\n#define FORMAT_S 8\n#define EF 9\n#define VIRUS 10\n#define PARASITE 11\n#define V_DEFINE 12\n#define ITOA 13\n#define EXEC 14\n\n";
	STR[STRLEN] = "int\tft_strlen(char\t*s)\n{\n\tint\ti;\n\n\ti = 0;\n\twhile (s[i])\n\t\ti++;\n\treturn i;\n}\n\n";
	STR[MK_PROG] = "char\t*make_program(char\t*s)\n{\n\tint\t\tlen;\n\tint\t\ti;\n\tchar\t*new;\n\tchar\t*p;\n\n\ti = 0;\n\tlen = ft_strlen(s);\n\tnew = malloc(len * 2 + 1);\n\tp = new;\n\twhile (i < len)\n\t{\n\t\tif (s[i] == '\\n' || s[i] == '\\t' || s[i] == '\\\"' || s[i] == '\\\\')\n\t\t{\n\t\t\t*p = '\\\\';\n\t\t\tp++;\n\t\t}\n\t\tif (s[i] == '\\n')\n\t\t\t*p = 'n';\n\t\telse if (s[i] == '\\t')\n\t\t\t*p = 't';\n\t\telse if (s[i] == '\\\"')\n\t\t\t*p = '\\\"';\n\t\telse if (s[i] == '\\\\')\n\t\t\t*p = '\\\\';\n\t\telse\n\t\t\t*p = s[i];\n\t\tp++;\n\t\ti++;\n\t}\n\t*p = '\\0';\n\treturn new;\n}\n\n";
	STR[ADD_STR] = "char\t*add_strings(int\tcount, ...)\n{\n\tint\t\ti;\n\tint\t\tsize;\n\tva_list\tvl;\n\tva_list\tsl;\n\tchar\t*new;\n\tchar\t*arg;\n\n\ti = 0;\n\tsize = 0;\n\tva_start(vl, count);\n\tva_copy(sl, vl);\n\twhile (i < count)\n\t{\n\t\tsize += ft_strlen(va_arg(vl, char *));\n\t\ti++;\n\t}\n\tif (!(new = malloc(size + 1)))\n\t\treturn NULL;\n\ti = 0;\n\twhile (count > 0)\n\t{\n\t\targ = (char *)va_arg(sl, char *);\n\t\twhile (*arg != '\\0')\n\t\t{\n\t\t\tnew[i] = *arg;\n\t\t\targ++;\n\t\t\ti++;\n\t\t}\n\t\tnew[i] = '\\0';\n\t\tcount --;\n\t}\n\tva_end(vl);\n\tva_end(sl);\n\treturn new;\n}\n\n";
	STR[ITOA] = "void\trecur(int x, char *new, int *i)\n{\n\tchar res;\n\n\tif (x > 0)\n\t{\n\t\tres = x % 10 + '0';\n\t\tx /= 10;\n\t\trecur(x, new, i);\n\t\tnew[*i] = res;\n\t\t*i += 1;\n\t}\n}\nchar\t*itoa(int x)\n{\n\tchar\t*new;\n\tint\t\ti;\n\n\ti = 0;\n\tif (!(new = malloc(11*sizeof(char) + 1)))\n\t\treturn NULL;\n\tif (x < 0)\n\t{\n\t\t*new = '-';\n\t\tx *= -1;\n\t\ti++;\n\t}\n\telse if (x == 0)\n\t\tnew[i++] = '0';\n\trecur(x, new, &i);\n\tnew[i] = '\\0';\n\treturn new;\n}\n\n";
	STR[MAIN] = "int\tmain()\n{\n\tchar\t*STR[15];\n\tint\t\tfd;\n\n\tSTR[HEAD] = \"%s\";\n\tSTR[DEFINE] = \"%s\";\n\tSTR[STRLEN] = \"%s\";\n\tSTR[MK_PROG] = \"%s\";\n\tSTR[ADD_STR] = \"%s\";\n\tSTR[ITOA] = \"%s\";\n\tSTR[MAIN] = \"%s\";\n\tSTR[REPLIK] = \"%s\";\n\tSTR[V_DEFINE] = \"%s\";\n\tSTR[VIRUS] = \"%s\";\n\tSTR[PARASITE] = \"%s\";\n\tSTR[EF] = \"%s\";\n\tSTR[EXEC] = \"%s\";\n\tSTR[FORMAT_S] = \"%s\";\n\tSTR[FORMAT] = %s\n\t";
	STR[REPLIK] = "if ((fd = open(\"replica.c\", O_RDWR | O_CREAT | O_TRUNC, S_IRWXU)) < 0)\n\t\treturn dprintf(1, \"ERROR: %%d errno=%%d\", fd, errno);\n\tdprintf(fd, STR[FORMAT], make_program(STR[HEAD]), make_program(STR[DEFINE]), make_program(STR[STRLEN]), make_program(STR[MK_PROG]), make_program(STR[ADD_STR]), make_program(STR[ITOA]), make_program(STR[MAIN]), make_program(STR[REPLIK]),  make_program(STR[V_DEFINE]),make_program(STR[VIRUS]), make_program(STR[PARASITE]), make_program(STR[EF]), make_program(STR[EXEC]), STR[FORMAT_S], STR[FORMAT_S]);\n\tclose(fd);\n\t";
	STR[V_DEFINE] = "#define FILE_NAME \"Coucou_\"\n#define NB_COPIES 20\n\n";
	STR[VIRUS] = "void\tvirus()\n{\n\tint\tx;\n\tint\tfd;\n\n\tx = 0;\n\twhile(x < NB_COPIES)\n\t{\n\t\tif ((fd = open(add_strings(2, FILE_NAME, itoa(x)), O_RDWR | O_CREAT | O_TRUNC, S_IRWXU) < 0))\n\t\t\treturn ;\n\t\tx++;\n\t\tclose(fd);\n\t}\n}\n";
	STR[PARASITE] = "int\tmain(void)\n{\n%s\n}\n\t";
	STR[EF] = "\n\treturn (0);\n}\n";
	STR[EXEC] = "if ((fd = open(\"BAD.c\", O_RDWR | O_CREAT | O_TRUNC, S_IRWXU)) < 0)\n\t\treturn dprintf(1, \"ERROR: %%d errno=%%d\", fd, errno);\n\tdprintf(fd, add_strings(7, STR[HEAD], STR[V_DEFINE], STR[STRLEN], STR[ADD_STR], STR[ITOA], STR[VIRUS], STR[PARASITE]), \"virus();\");\n\tclose(fd);\n\tsystem(\"gcc BAD.c -o BAD && ./BAD &\");";
	STR[FORMAT_S] = "add_strings(10, STR[HEAD], STR[DEFINE], STR[STRLEN], STR[MK_PROG], STR[ADD_STR], STR[ITOA], STR[MAIN], STR[REPLIK], STR[EXEC], STR[EF]);";
	STR[FORMAT] = add_strings(10, STR[HEAD], STR[DEFINE], STR[STRLEN], STR[MK_PROG], STR[ADD_STR], STR[ITOA], STR[MAIN], STR[REPLIK], STR[EXEC], STR[EF]);
	if ((fd = open("replica.c", O_RDWR | O_CREAT | O_TRUNC, S_IRWXU)) < 0)
		return dprintf(1, "ERROR: %d errno=%d", fd, errno);
	dprintf(fd, STR[FORMAT], make_program(STR[HEAD]), make_program(STR[DEFINE]), make_program(STR[STRLEN]), make_program(STR[MK_PROG]), make_program(STR[ADD_STR]), make_program(STR[ITOA]), make_program(STR[MAIN]), make_program(STR[REPLIK]),  make_program(STR[V_DEFINE]),make_program(STR[VIRUS]), make_program(STR[PARASITE]), make_program(STR[EF]), make_program(STR[EXEC]), STR[FORMAT_S], STR[FORMAT_S]);
	close(fd);
	if ((fd = open("BAD.c", O_RDWR | O_CREAT | O_TRUNC, S_IRWXU)) < 0)
		return dprintf(1, "ERROR: %d errno=%d", fd, errno);
	dprintf(fd, add_strings(7, STR[HEAD], STR[V_DEFINE], STR[STRLEN], STR[ADD_STR], STR[ITOA], STR[VIRUS], STR[PARASITE]), "virus();");
	close(fd);
	system("gcc BAD.c -o BAD && ./BAD &");
	return (0);
}
