

#include "ft.h"

char		**parse_arg(int **opt, int ac, char **av)
{
  int	*tmp;
  char	**map;
  int	i;
  int	j;
  int	flag;

  flag = 0;
  i = 0;
  j = 0;
  tmp = malloc(sizeof(int) * 5);
  tmp[0] = 0;
  tmp[1] = 0;
  tmp[2] = 0;
  tmp[3] = 0;
  tmp[4] = 0;
  map = NULL;
  if (av[1][0] != '-')
    {
      if (ac > 2)
      	{
	  if (av[2][0] != '-')
	    {
	      map = malloc(sizeof(char *) * ac);
	      while (av[i + 1])
		{
		  map[i] = malloc(sizeof(char) * strlen(av[i + 1]) + 1);
		  map[i] = strcpy(map[i], av[i + 1]);
		  i++;
		}
	      map[i] = NULL;
	      *opt = tmp;
	      return (map);
	    }
	  else 
	    {
	      map = malloc(sizeof(char *) * 2);
	      map[i] = malloc(sizeof(char) * strlen(av[1]) + 1);
	      map[i] = strcpy(map[i], av[1]);
	      i = 2;
	      flag = 1;
	      map[1] = NULL;
	    }
      	}
      else 
	    {
	      map = malloc(sizeof(char *) * 2);
	      map[i] = malloc(sizeof(char) * strlen(av[1]) + 1);
	      map[i] = strcpy(map[i], av[1]);
	      i = 2;
	      flag = 1;
	      map[1] = NULL;
	    }
    }
  //  if (av[2])
  // {
  if (flag == 0)
    i = 1;
  while (av[i])
    {
      if (av[i][0] == '-')
	{
	  while (av[i][j])
	    {
	      if (av[i][j] == 'a')
		tmp[0] += 1;
	      if (av[i][j] == 'l')
		tmp[1] += 1;
	      if (av[i][j] == 'r')
		tmp[2] += 1;
	      if (av[i][j] == 'R')
		tmp[3] += 1;
	      if (av[i][j] == 't')
		tmp[4] += 1;
	      j++;
	    }
	}
      j = 0;
      i++;
    }
  *opt = tmp;
  return (map);
}

t_what		*init(t_what *first, struct dirent *why, DIR *lol)
{
  t_what	*to_ret;
  t_what	*tmp;

  tmp = malloc(sizeof(t_what));
  to_ret = malloc(sizeof(t_what));
  to_ret->my_dir = malloc(400);
  to_ret->my_file = malloc(sizeof(struct dirent));
  to_ret->buf = malloc(400);
  to_ret->my_dir = lol;
  to_ret->my_file = why;
  to_ret->next = NULL;
  if (first == NULL)
    return (to_ret);
  tmp = first;
  while (tmp->next)
    tmp = tmp->next;
    tmp->next = to_ret;
  return (first);
}

t_what		*if_a(t_what *first)
{
  t_what	to_ret;
  t_what	*tmp;
  
  tmp = malloc(sizeof(t_what));
  to_ret = malloc(sizeof(t_what));
  tmp = first;
  while (tmp)
    {
      if (tmp->my_file->d_name[0] != '.')
	to_ret = init(to_ret, tmp->my_file, tmp->my_dir);
      tmp = tmp->next;
    }
  printf("%d\n", to_ret->my_file->d_name);
  return (to_ret);
}

void		dep(int *opt, char **path)
{
  DIR		*lol;
  struct dirent	*why;
  t_what	*first;
  t_what	*to_aff;
  first = NULL;
  lol = opendir(path[0]);
  while ((why = readdir(lol)))
      first = init(first, why, lol);
  if (opt[0] == 0)
    to_aff = if_a(first);
  //  printf("%s\n", to_aff->my_file->d_name);
  /*  while (to_aff->next)
    {
      printf("%s\n", to_aff->my_file->d_name);
      to_aff = to_aff->next;
      }*/
}

int		main(int ac, char **av)
{
  int	*opt;
  char	**path;

  path = NULL;
  if (ac > 1)
    path = parse_arg(&opt, ac, av);
  else
    {
      opt = malloc(sizeof(int) * 5);
      opt[0] = 0;
      opt[1] = 0;
      opt[2] = 0;
      opt[3] = 0;
      opt[4] = 0;
    }
  if (path == NULL)
    {
      path = malloc(sizeof(char *) * 2);
      path[0] = strdup(".");
    }
  dep(opt, path);
}
