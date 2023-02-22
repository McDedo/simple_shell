# ifndef _SHELL_H_
# définir  _SHELL_H_

# inclure  < stdio.h >
# inclure  < stdlib.h >
# inclure  < unistd.h >
# inclure  < chaîne.h >
# inclure  < sys/types.h >
# inclure  < sys/wait.h >
# inclure  < sys/stat.h >
# inclure  < limites.h >
# inclure  < fcntl.h >
# inclure  < errno.h >

/* pour les tampons de lecture/écriture */
# définir  READ_BUF_SIZE  1024
# définir  WRITE_BUF_SIZE  1024
# définir  BUF_FLUSH - 1

/* pour le chaînage de commandes */
# définir  CMD_NORM 	0
# définir  CMD_OR 		1
# définir  CMD_AND 		2
# définir  CMD_CHAIN 	​​3

/* pour convert_number() */
# définir  CONVERT_LOWERCASE 	1
# définir  CONVERT_UNSIGNED 	2

/* 1 si vous utilisez le système getline() */
# définir  USE_GETLINE  0
# définir  USE_STRTOK  0

# définir  HIST_FILE 	" .simple_shell_history "
# définir  HIST_MAX 	4096

 caractère externe **environ ;


/* *
* struct liststr - liste liée individuellement
* @num : le champ numérique
* @str : une chaîne
* @next : pointe vers le nœud suivant
 */
 structure typedef liststr
{
	nombre entier ;
	char *str;
	struct liststr *suivant ;
} liste_t ;

/* *
*struct passinfo - contient des pseudo-arguments à passer dans une fonction,
* permettant un prototype uniforme pour la structure de pointeur de fonction
*@arg : une chaîne générée à partir de getline contenant des arguments
*@argv : un tableau de chaînes générées à partir de arg
*@path : un chemin de chaîne pour la commande actuelle
*@argc : le nombre d'arguments
*@line_count : le nombre d'erreurs
*@err_num : le code d'erreur pour les exit()s
*@linecount_flag : si on compte cette ligne d'entrée
*@fname : le nom du fichier du programme
*@env : liste chaînée copie locale d'environ
*@environ : copie modifiée personnalisée d'environ à partir de LL env
*@history : le nœud d'historique
*@alias : le nœud d'alias
*@env_changed : activé si environ a été modifié
*@status : le statut de retour de la dernière commande exécutée
*@cmd_buf : adresse du pointeur vers cmd_buf, activé si chaînage
*@cmd_buf_type : CMD_type ||, &&, ;
*@readfd : le fd à partir duquel lire l'entrée de ligne
*@histcount : le nombre de lignes d'historique
 */
 structure typedef passinfo
{
	caractère *arg ;
	caractère **argv ;
	char *chemin ;
	int argc ;
	 entier non signé line_count ;
	int err_num ;
	int linecount_flag ;
	char *fname;
	list_t *env;
	list_t *historique ;
	list_t *alias ;
	caractère **environ ;
	int env_changed ;
	état entier ;

	char **cmd_buf; /* pointeur vers cmd ; tampon de chaîne, pour la gestion de la mémoire */
	entier cmd_buf_type ; /* Type_CMD ||, &&, ; */
	int readfd;
	int hiscount ;
} info_t ;

# définir  INFO_INIT \
{ NULL , NULL , NULL , 0 , 0 , 0 , 0 , NULL , NULL , NULL , NULL , NULL , 0 , 0 , NULL , \
	0 , 0 , 0 }

/* *
*struct builtin - contient une chaîne intégrée et une fonction associée
*@type : l'indicateur de commande intégré
*@func : la fonction
 */
 structure typedef intégrée
{
	caractère *type ;
	int (*fonc)( info_t *);
} table_intégrée ;


/* toem_shloop.c */
int  hsh ( info_t *, char **);
int  find_builtin ( info_t *);
void  find_cmd ( info_t *);
void  fork_cmd ( info_t *);

/* toem_parser.c */
int  is_cmd ( info_t *, char *);
char * dup_chars ( char *, int , int );
char * find_path ( info_t *, char *, char *);

/* loophsh.c */
int  loophsh ( char **);

/* toem_errors.c */
void  _eputs ( char *);
int  _eputchar ( char );
int  _putfd ( char c, int fd);
int  _putsfd ( char *str, int fd);

/* toem_string.c */
int  _strlen ( char *);
int  _strcmp ( char *, char *);
char * starts_with ( const  char *, const  char *);
char * _strcat ( char *, char *);

/* toem_string1.c */
char * _strcpy ( char *, char *);
char * _strdup ( const  char *);
void  _puts ( char *);
entier  _putchar ( char );

/* toem_exits.c */
char * _strncpy ( char *, char *, int );
char * _strncat ( char *, char *, int );
char * _strchr ( char *, char );

/* toem_tokenizer.c */
char ** strtow ( char *, char *);
char ** strtow2 ( char *, char );

/* toem_realloc.c */
char * _memset ( char *, char , entier non signé  );
void  ffree ( char **);
void * _realloc ( void *, entier non signé  , entier non signé ); 

/* toem_memory.c */
int  bfree ( void **);

/* toem_atoi.c */
entier  interactif ( info_t *);
int  is_delim ( char , char *);
entier  _isalpha ( entier );
int  _atoi ( char *);

/* toem_errors1.c */
int  _erratoi ( char *);
void  print_error ( info_t *, char *);
int  print_d ( entier , entier );
char * convert_number ( entier long  , entier , entier ) ;
void  remove_comments ( char *);

/* toem_builtin.c */
int  _masortie ( info_t *);
int  _mycd ( info_t *);
int  _monaide ( info_t *);

/* toem_builtin1.c */
int  _myhistory ( info_t *);
int  _myalias ( info_t *);

/* toem_getline.c */
ssize_t  get_input ( info_t *);
int  _getline ( info_t *, char **, size_t *);
void  sigintHandler ( int );

/* toem_getinfo.c */
vide  clear_info ( info_t *);
void  set_info ( info_t *, char **);
void  free_info ( info_t *, int );

/* toem_environ.c */
char * _getenv ( info_t *, const  char *);
int  _myenv ( info_t *);
int  _mysetenv ( info_t *);
int  _myunsetenv ( info_t *);
int  populate_env_list ( info_t *);

/* toem_getenv.c */
char ** get_environ ( info_t *);
int  _unsetenv ( info_t *, char *);
int  _setenv ( info_t *, char *, char *);

/* toem_history.c */
char * get_history_file ( info_t *info);
int  write_history ( info_t *info);
int  read_history ( info_t *info);
int  build_history_list ( info_t *info, char *buf, int linecount);
int  renumber_history ( info_t *info);

/* toem_lists.c */
list_t * add_node ( list_t **, const  char *, int );
list_t * add_node_end ( list_t **, const  char *, int );
size_t  print_list_str ( const  list_t *);
int  delete_node_at_index ( list_t **, entier non signé  );
void  free_list ( list_t **);

/* toem_lists1.c */
size_t  list_len ( const  list_t *);
char ** list_to_strings ( list_t *);
size_t  print_list ( const  list_t *);
list_t * node_starts_with ( list_t *, char *, char );
ssize_t  get_node_index ( list_t *, list_t *);

/* toem_vars.c */
int  is_chain ( info_t *, char *, size_t *);
void  check_chain ( info_t *, char *, size_t *, size_t , size_t );
int  replace_alias ( info_t *);
int  replace_vars ( info_t *);
int  replace_string ( char **, char *);

# endif

