#define BUFFER_SIZE 10000 // Tableau de taille 1000
#include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

static void	free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i] != NULL)
		free(tab[i++]);
	free(tab);
}

static size_t	ft_countwords(char const *s, char c)
{
	size_t	i;
	size_t	count_words;

	i = 0;
	count_words = 0;
	while (s[i])
	{
		if ((s[i] != c && s[i + 1] == c) || (s[i] != c && s[i + 1] == '\0'))
			count_words++;
		i++;
	}
	return (count_words);
}

static char	*ft_sizewords(char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	count_size;
	char	*tab_str;

	i = 0;
	j = 0;
	count_size = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
			count_size++;
		i++;
	}
	tab_str = malloc(sizeof(char) * count_size + 1);
	if (!(tab_str))
		return (NULL);
	i = 0;
	while (s[i] != '\0' && s[i] != c)
	{
		tab_str[i] = s[i];
		i++;
	}
	tab_str[i] = '\0';
	return (tab_str);
}

char	**ft_split2(char **tab, int i)
{
	tab[i] = NULL;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	char	**tab;

	i = 0;
	tab = calloc(sizeof(char *), (ft_countwords(s, c) + 1));
	if (!(tab))
		return (NULL);
	while (*s)
	{
		while (*s != '\0' && *s == c)
			s++;
		if (*s != c && *s != '\0')
		{
			tab[i] = ft_sizewords(s, c);
			if (!(tab[i]))
			{
				free_tab(tab);
				return (0);
			}
			i++;
			while (*s && *s != c)
				s++;
		}
	}
	return (ft_split2(tab, i));
}

int			containOtherPair(char **s1, char **s2)
{
	int		i1 = atoi(s1[0]);
	int		i2 = atoi(s1[1]);
	int		j1 = atoi(s2[0]);
	int		j2 = atoi(s2[1]);

	if (i1 < j1 && i2 < j1)
		return (0);
	else if (j1 < i1 && j2 < i1)
		return (0);
	return (1);
}

int		separatePairs(char *str)
{
	char	elf1[strlen(str)];
	char	elf2[strlen(str)];
	int		i = 0;
	int		j = 0;

	while (str[i] != ',')
	{
		elf1[j] = str[i];
		i++;
		j++;
	}
	j = 0;
	i++;
	while (str[i])
	{
		elf2[j] = str[i];
		i++;
		j++;
	}
	return(containOtherPair(ft_split(elf1, '-'), ft_split(elf2, '-')));
}

int main (int ac, char **av)
{
	FILE*	file = NULL;
	char	buf[BUFFER_SIZE] = "";
	int		nPairs = 0;
    file = fopen(av[1], "r+");
    if (file != NULL)
    {
		while (fgets(buf, BUFFER_SIZE, file) != NULL)
		{	
			nPairs += separatePairs(buf);
		}
		fclose(file);
    }
    else
    {
        printf("Impossible d'ouvrir le fichier %s\n", av[1]);
    }
	
	printf("number of pairs = %d\n", nPairs);
    return 0;
}
