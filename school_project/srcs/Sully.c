# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include "libft.h"

# ifndef LIBFT_PATH
# define LIBFT_PATH
#endif

# define STRINGS "# include <stdio.h>\n# include <stdlib.h>\n# include <fcntl.h>\n# include <unistd.h>\n# include \"libft.h\"\n\n# ifndef LIBFT_PATH\n# define LIBFT_PATH\n#endif\n\n# define STRINGS %s\n\n# define COUNTER %d\n# define STR_HELPER(x) #x \n# define STRINGIFY(VALUE) STR_HELPER(VALUE)\n\n\n# define CODE %s\n\n# define START %s\n\n# define END(x) %s\n\n# define FT(x) CODE int main(){ int fd = -1; int counter = COUNTER; char *format_string = STRINGS; char* current_filename = __FILE__; START if ((fd = open(filename, O_RDWR | O_TRUNC | O_CREAT, S_IRWXU | S_IRWXG)) < 0) return 0; /* Display */dprintf(fd, format_string, ft_quote(make_program(STRINGS)), counter, STRINGIFY(CODE), STRINGIFY(START), STRINGIFY(END())); close(fd);system(ft_strjoin(\"clang -Wall -Werror -Wextra -o Sully\", ft_strjoin(ft_itoa(counter), ft_strjoin(\" \", ft_strjoin(filename, ft_strjoin(\" -DLIBFT_PATH=\\\"\\\"\", ft_strjoin(ft_quote(STRINGIFY(LIBFT_PATH)), ft_strjoin(\"\\\"\\\" -DOSX -I\", ft_strjoin(STRINGIFY(LIBFT_PATH), ft_strjoin(\"/lib/libft/includes -L\", ft_strjoin(STRINGIFY(LIBFT_PATH), \"/lib/libft -lft \")))))))))));END(0) wrdestroy();return 0;}\n\n\n/*\n\tThis Macro will create a slitly different version of himself which will reproduce itself\n*/\nFT(0)\n"

# define COUNTER 5
# define STR_HELPER(x) #x 
# define STRINGIFY(VALUE) STR_HELPER(VALUE)


# define CODE typedef struct str_list{void *malloc; struct str_list *next;} str_list; char *make_program(char *s) {int len = ft_strlen(s); int i = 0; char *new = ((void*)0); char *p = ((void*)0); new = wrmalloc(len * 2 + 1); if (new == ((void*)0)) return ((void*)0); p = new; while (i < len) {if (s[i] == '\n' || s[i] == '\t' || s[i] == '\"' || s[i] == '\\') {*p = '\\'; p++;} if (s[i] == '\n') *p = 'n'; else if (s[i] == '\t') *p = 't'; else if (s[i] == '\"') *p = '\"'; else if (s[i] == '\\') *p = '\\'; else *p = s[i]; p++; i++;} *p = '\0'; return new;}

# define START if (!ft_strcmp(current_filename, ft_strjoin("Sully_", ft_strjoin(ft_itoa(counter), ".c"))))counter--;if (counter < 0) return 0; char *filename = ft_strjoin("Sully_", ft_strjoin(ft_itoa(counter), ".c"));

# define END(x) if (counter <= 0) return 0;system(ft_strjoin("./Sully", ft_itoa(counter)));

# define FT(x) CODE int main(){ int fd = -1; int counter = COUNTER; char *format_string = STRINGS; char* current_filename = __FILE__; START if ((fd = open(filename, O_RDWR | O_TRUNC | O_CREAT, S_IRWXU | S_IRWXG)) < 0) return 0; /* Display */dprintf(fd, format_string, ft_quote(make_program(STRINGS)), counter, STRINGIFY(CODE), STRINGIFY(START), STRINGIFY(END())); close(fd);system(ft_strjoin("clang -Wall -Werror -Wextra -o Sully", ft_strjoin(ft_itoa(counter), ft_strjoin(" ", ft_strjoin(filename, ft_strjoin(" -DLIBFT_PATH=\"\"", ft_strjoin(ft_quote(STRINGIFY(LIBFT_PATH)), ft_strjoin("\"\" -DOSX -I", ft_strjoin(STRINGIFY(LIBFT_PATH), ft_strjoin("/lib/libft/includes -L", ft_strjoin(STRINGIFY(LIBFT_PATH), "/lib/libft -lft ")))))))))));END(0) wrdestroy();return 0;}


/*
	This Macro will create a slitly different version of himself which will reproduce itself
*/
FT(0)
