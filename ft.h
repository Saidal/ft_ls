
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>


typedef struct		s_what
{
  DIR		*my_dir;
  struct dirent	*my_file;
  struct stat	*buf;
  struct s_what *next;
}			t_what;
