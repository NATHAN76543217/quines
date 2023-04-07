# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <libft.h>

# define PAYLOAD int payload() { return 0;}
# define STRINGS "# include <stdio.h>\n# include <stdlib.h>\n# include <fcntl.h>\n# include <unistd.h>\n# include <libft.h>\n\n# define PAYLOAD %s\n# define STRINGS \"%s\"\n\n# define COUNTER %d\n# define STR_HELPER(x) #x \n# define STRINGIFY(VALUE) STR_HELPER(VALUE)\n\n\n# define CODE %s\n\n# define START %s\n\n# define END(x) %s\n\n# define FT(x) CODE PAYLOAD int main(){ int fd = -1; int counter = COUNTER - 1; char *format_string = STRINGS; START /* Display */dprintf(fd, format_string, STRINGIFY(PAYLOAD), make_program(STRINGS), counter, STRINGIFY(CODE), STRINGIFY(START), STRINGIFY(END())); END(0) wrdestroy();return 0;}\n\n\n/*\n\tThis Macro will declare a main then write all this code page into a file named 'Grace_kid.c'\n*/\nFT()\n"

# define COUNTER 5
# define STR_HELPER(x) #x 
# define STRINGIFY(VALUE) STR_HELPER(VALUE)


# define CODE typedef struct str_list{void *malloc; struct str_list *next;} str_list; char *make_program(char *s) {int len = ft_strlen(s); int i; char *new; char *p; i = 0; new = wrmalloc(len * 2 + 1); if (new == ((void*)0)) return ((void*)0); p = new; while (i < len) {if (s[i] == '\n' || s[i] == '\t' || s[i] == '\"' || s[i] == '\\') {*p = '\\'; p++;} if (s[i] == '\n') *p = 'n'; else if (s[i] == '\t') *p = 't'; else if (s[i] == '\"') *p = '\"'; else if (s[i] == '\\') *p = '\\'; else *p = s[i]; p++; i++;} *p = '\0'; return new;}

# define START char *filename = ft_strjoin("Sully_", ft_strjoin(ft_itoa(counter), ".c")); if ((fd = open(filename, 0x0002 | 0x0400 | 0x0200 , 0000700 | 0000070)) < 0) return 0;

# define END(x) close(fd);system(ft_strjoin("gcc -Wall -Werror -Wextra -o Sully", ft_strjoin(ft_itoa(counter), ft_strjoin(" -DOSX -Ilib/libft/includes -Llib/libft -lft ", filename))));if (counter <= 0) return 0; system(ft_strjoin("./Sully", ft_itoa(counter)));

# define FT(x) CODE PAYLOAD int main(){ int fd = -1; int counter = COUNTER - 1; char *format_string = STRINGS; START /* Display */dprintf(fd, format_string, STRINGIFY(PAYLOAD), make_program(STRINGS), counter, STRINGIFY(CODE), STRINGIFY(START), STRINGIFY(END())); END(0) wrdestroy();return 0;}


/*
	This Macro will declare a main then write all this code page into a file named 'Grace_kid.c'
*/
FT()
