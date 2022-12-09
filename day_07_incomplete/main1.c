#define BUFFER_SIZE 10000
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
#include <stdbool.h>     

int		g_index;
char	*indexStr;

/**
** STRUCT & FUNCTIONS
*/
typedef struct 		element element;
struct				element
{
    char				*name;
	char				*directories_inside;
	int					size;
	element				*prev;
    element				*next;
};
 
typedef element*	llist;

typedef struct
{
	element				 *first;
	element				 *last;
}					dblist;

typedef struct 		tab tab;
struct				tab
{
    char				*name;
    tab					*next;
};
 
typedef tab*		lltab;

void 	init(dblist *l)
{
   l->first = NULL;
   l->last = NULL;
}

void 	pushBack(dblist *l, char *dirName)
{
	element *new = malloc(sizeof(element));
	if(!new)
		exit(EXIT_FAILURE);
	new->name = dirName;
	new->directories_inside = (char *)malloc(sizeof(char) * 100000);
	new->next = NULL;
	new->prev = l->last;
	if(l->last)
		l->last->next = new;
	else
		l->first = new;
	l->last = new;
}

void	view(dblist list)
{
   element	*pelem = list.first;
   while(pelem)
   {
		printf("dir name = [%s] ", pelem->name);
		printf("dir inside = [%s] ", pelem->directories_inside);
		printf("size = [%d] \n", pelem->size);
    	pelem = pelem->next;
   }
}

lltab	addNewTab(lltab tabList, char *dirName)
{
	tab		*newDir = malloc(sizeof(tab));

	newDir->name = dirName;
	newDir->next = NULL;
	if (tabList == NULL) {
		return newDir;
	}
	else {
		tab		*tmp = tabList;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = newDir;
		return tabList;
	}
}

void	printlList(llist list)
{
    element		*tmp = list;
    while(tmp != NULL)
    {
        printf("dir name = [%s] ", tmp->name);
		printf("dir inside = [%s] ", tmp->directories_inside);
		printf("size = [%d] \n", tmp->size);
        tmp = tmp->next;
    }
}

int		ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	while (dest[i] != '\0')
		i++;
	j = 0;
	while (src[j] != '\0')
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

void	addDirectoriesInside(dblist *list, char *dirName, char *dirInsideName)
{
    element		*tmp = list->first;
	char		*tmpStr;
	char		*dirToAdd;

	if (!(tmpStr = malloc(sizeof(char*) * 100000 + 1)))
		return ;
	if (!(dirToAdd = malloc(sizeof(char*) * 100000)))
		return ;
	dirToAdd = strcat(dirInsideName, "#");
    while(tmp)
    {
        if (strcmp(tmp->name, dirName) == 0) {
			if (tmp->directories_inside != NULL) {
				tmpStr = ft_strcat(tmp->directories_inside, dirToAdd);
				tmp->directories_inside = tmpStr;
			}
			else
				tmp->directories_inside = strdup(dirToAdd);
		}
        tmp = tmp->next;
    }
	if (dirToAdd)
		free(dirToAdd);
}

void	addSizeToDir(dblist *list, char *dirName, int size)
{
    element		*tmp = list->first;

    while(tmp)
    {
        if (strcmp(tmp->name, dirName) == 0) {
			tmp->size += size;
		}
        tmp = tmp->next;
    }
}

int		finDirSize(dblist *list, char *dirName)
{
    element		*tmp = list->first;

    while(tmp)
    {
        if (strcmp(tmp->name, dirName) == 0)
			return (tmp->size);
        tmp = tmp->next;
    }
	return (0);
}


void	addSubDirSize(dblist *list) // add sub files / dir from the end of list
{
    element		*tmp = list->last;
	char		*subDir;
	char		*cpy;

    while(tmp)
    {
		cpy = strdup(tmp->directories_inside);
        subDir = strtok(cpy, "#");
		while ( subDir != NULL ) {
			tmp->size += finDirSize(list, subDir);
			subDir = strtok ( NULL, "#" );
		}
        tmp = tmp->prev;
    }
}

void	addSize(dblist *list)
{
    element		*tmp = list->first;
	char		*subDir;
    while(tmp != NULL)
    {
        subDir = strtok(tmp->directories_inside, "#");

		while ( subDir != NULL ) {
			tmp->size += finDirSize(list, subDir);
			subDir = strtok ( NULL, "#" );
		}
        tmp = tmp->next;
    }
}

int		addOnlyMaxSizeFiles(dblist *list, int max)
{
    element		*tmp = list->first;
	int			sum  = 0;

    while(tmp)
    {
        if (tmp->size <= max)
			sum += tmp->size;
        tmp = tmp->next;
    }
	return (sum);
}

/**
** UTILS
*/
char	*ft_cutString(char *str, int c)
{
	int		len = 0;
	int		i = strlen(str) - 1;
	int		j = 0;
	char	*tmp;

	while (i > 0) {
		if (str[i] == c)
			break;
		len++;
		i--;
	}
	i = strlen(str) - len;
	if (!(tmp = malloc(sizeof(char*) * len + 1)))
		return (NULL);
	while (str[i] != '\n') {
		if (str[i] == c)
			break;
		tmp[j] = str[i];
		j++;
		i++;
	}
	tmp[j] = '\0';
	return (tmp);
}

char		*strCatWithInt(char *str, char c)
{
	char		*dest;
	int			i = 0;

	if (!(dest = malloc(sizeof(char*) * strlen(str) + 4)))
		return (NULL);
	while (str[i]) {
		dest[i] = str[i];
		i++;
	}
	dest[i] = c;
	i++;
	dest[i] = '\0';
	return (dest);
}

char* 	itoa(int i, char b[])
{
    char const digit[] = "0123456789";
    char* p = b;
    if(i < 0) {
        *p++ = '-';
        i *= -1;
    }
    int shifter = i;
    do {
        ++p;
        shifter = shifter / 10;
    } while(shifter);
    *p = '\0';
    do {
        *--p = digit [i % 10];
        i = i / 10;
    } while(i);
    return b;
}

int			doesExist(lltab list, char *name)
{
    tab		*tmp = list;
	char	*indexStr;
	int		i = 0;
    while(tmp != NULL)
    {
        if (strnstr(tmp->name, name, strlen(name)) != NULL) // does exist
			i++;
        tmp = tmp->next;
    }
	return (i);
}

int		main (int ac, char **av)
{
	dblist	dirList;
	// llist	dirList = NULL;
	lltab	tabList = NULL;
	FILE*	file = NULL;
	char	buf[BUFFER_SIZE] = "";
	char	*currentDir = NULL;
	char	**tab;
	int		nb = 0;

	init(&dirList);
	if (!(indexStr = malloc(sizeof(char*) * 100)))
		return (0);
    file = fopen(av[1], "r+");
    if (file != NULL)
    {
		while (fgets(buf, BUFFER_SIZE, file) != NULL)
		{
			if (strstr(buf, "cd ") != NULL) { // cd + alpha
				if (buf[5] >= 97 && buf[5] <= 122) {
					if (doesExist(tabList, ft_cutString(buf, ' ')) != 0) {
						itoa(doesExist(tabList, ft_cutString(buf, ' ')), indexStr);
						tabList = addNewTab(tabList, strcat(ft_cutString(buf, ' '), indexStr));
						pushBack(&dirList, strcat(ft_cutString(buf, ' '), indexStr));
						currentDir = strcat(ft_cutString(buf, ' '), indexStr);
					}
					else { // doesnt exist
						tabList = addNewTab(tabList, ft_cutString(buf, ' '));
						pushBack(&dirList, ft_cutString(buf, ' '));
						currentDir = ft_cutString(buf, ' ');
					}
				}
			}
			else if (((strstr(buf, "dir ") != NULL))) { // dir inside
				if (doesExist(tabList, ft_cutString(buf, ' ')) != 0) {
					itoa(doesExist(tabList, ft_cutString(buf, ' ')) + 1, indexStr);
					tabList = addNewTab(tabList, strcat(ft_cutString(buf, ' '), indexStr));
					addDirectoriesInside(&dirList, currentDir, strcat(ft_cutString(buf, ' '), indexStr));
				}
				else {
					itoa(1, indexStr);
					tabList = addNewTab(tabList, strcat(ft_cutString(buf, ' '), indexStr));
					addDirectoriesInside(&dirList, currentDir, strcat(ft_cutString(buf, ' '), indexStr));
				}
			}
			else if (ft_isdigit(buf[0]) == 1) { // size of file inside
				addSizeToDir(&dirList, currentDir, atoi(buf));
			}
		}
		fclose(file);
   		}
    else
    {
        printf("Impossible d'ouvrir le fichier %s\n", av[1]);
    }

	addSubDirSize(&dirList);
	printf("=========\n\n");
	view(dirList);
	printf("=========\n");
	printf("sum = [%d]", addOnlyMaxSizeFiles(&dirList, 100000));

    return 0;
}
