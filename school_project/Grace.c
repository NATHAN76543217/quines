# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

# define STRINGS "# include <stdio.h>\n# include <stdlib.h>\n# include <fcntl.h>\n# include <unistd.h>\n\n# define STRINGS \"%s\"\n\n# define STR \"%s\"\n/*\n\tThis Macro will declare a main then write all this code page into a file named 'Grace_kid.c'\n*/\n%s\n\n\nFT\n"

# define STR "# define FT size_t ft_strlen(const char *s) {int i; i = 0; while(s[i])i++; return i;} typedef struct s_list{void *malloc; struct s_list *next;} t_list; t_list **getUniqMalloc( void ) {static t_list* malloced = NULL; return &malloced;} void delUniqMalloc(void) {t_list** malloced = getUniqMalloc(); t_list* tmp = NULL; while ((*malloced) != NULL) {tmp = (*malloced); free((*malloced)->malloc); (*malloced) = (*malloced)->next; free(tmp);}} char *uniq_malloc( unsigned int size) {t_list **malloced = getUniqMalloc(); t_list *tmp = NULL; char *new = malloc(size); if (new == NULL) return NULL; if (*malloced == NULL) {*malloced = malloc(sizeof(t_list)); if (*malloced == NULL) {free(new); return NULL;}(*malloced)->malloc = new; (*malloced)->next = NULL;} else {tmp = *malloced; while (tmp->next != NULL) {tmp = tmp->next;} tmp->next = malloc(sizeof(t_list)); if (tmp->next == NULL) {free (new); return NULL;} tmp = tmp->next; tmp->malloc = new; tmp->next = NULL;} return new;} char *make_program(char *s) {int len = ft_strlen(s); int i; char *new; char *p; i = 0; new = uniq_malloc(len * 2 + 1); if (new == NULL) return NULL; p = new; while (i < len) {if (s[i] == '\\n' || s[i] == '\\t' || s[i] == '\\\"' || s[i] == '\\\\') {*p = '\\\\'; p++;} if (s[i] == '\\n') *p = 'n'; else if (s[i] == '\\t') *p = 't'; else if (s[i] == '\\\"') *p = '\\\"'; else if (s[i] == '\\\\') *p = '\\\\'; else *p = s[i]; p++; i++;} *p = '\\0'; return new;} int main() {int fd = -1; char *format_string = STRINGS; if ((fd = open(\"Grace_kid.c\", O_RDWR | O_TRUNC | O_CREAT, S_IRWXU | S_IRWXG )) < 0) return EXIT_FAILURE;/* Display */ dprintf(fd, format_string, make_program(STRINGS), make_program(STR), STR ); close(fd); delUniqMalloc(); return 0;}"
/*
	This Macro will declare a main then write all this code page into a file named 'Grace_kid.c'
*/
# define FT size_t ft_strlen(const char *s) {int i; i = 0; while(s[i])i++; return i;} typedef struct s_list{void *malloc; struct s_list *next;} t_list; t_list **getUniqMalloc( void ) {static t_list* malloced = NULL; return &malloced;} void delUniqMalloc(void) {t_list** malloced = getUniqMalloc(); t_list* tmp = NULL; while ((*malloced) != NULL) {tmp = (*malloced); free((*malloced)->malloc); (*malloced) = (*malloced)->next; free(tmp);}} char *uniq_malloc( unsigned int size) {t_list **malloced = getUniqMalloc(); t_list *tmp = NULL; char *new = malloc(size); if (new == NULL) return NULL; if (*malloced == NULL) {*malloced = malloc(sizeof(t_list)); if (*malloced == NULL) {free(new); return NULL;}(*malloced)->malloc = new; (*malloced)->next = NULL;} else {tmp = *malloced; while (tmp->next != NULL) {tmp = tmp->next;} tmp->next = malloc(sizeof(t_list)); if (tmp->next == NULL) {free (new); return NULL;} tmp = tmp->next; tmp->malloc = new; tmp->next = NULL;} return new;} char *make_program(char *s) {int len = ft_strlen(s); int i; char *new; char *p; i = 0; new = uniq_malloc(len * 2 + 1); if (new == NULL) return NULL; p = new; while (i < len) {if (s[i] == '\n' || s[i] == '\t' || s[i] == '\"' || s[i] == '\\') {*p = '\\'; p++;} if (s[i] == '\n') *p = 'n'; else if (s[i] == '\t') *p = 't'; else if (s[i] == '\"') *p = '\"'; else if (s[i] == '\\') *p = '\\'; else *p = s[i]; p++; i++;} *p = '\0'; return new;} int main() {int fd = -1; char *format_string = STRINGS; if ((fd = open("Grace_kid.c", O_RDWR | O_TRUNC | O_CREAT, S_IRWXU | S_IRWXG )) < 0) return EXIT_FAILURE;/* Display */ dprintf(fd, format_string, make_program(STRINGS), make_program(STR), STR ); close(fd); delUniqMalloc(); return 0;}

FT
