#define BUFFER_SIZE 10000 // Tableau de taille 1000
#include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	size;
	char	*dest;

	i = 0;
	size = strlen(s);
	dest = malloc(sizeof(char) * len + 1);
	if (!(dest))
		return (NULL);
	while (len != 0 && start < size)
	{
		dest[i] = s[start];
		start++;
		i++;
		len--;
	}
	dest[i] = '\0';
	return (dest);
}

char	checkDouble(char *s1, char *s2)
{
	int		i = 0;
	int		j = 0;
	while (s1[i])
	{
		while(s2[j])
		{
			if(s1[i] == s2[j])
				return (s1[i]);
			j++;
		}
		j = 0;
		i++;
	}
	return ('\0');
}

int		findPriorities(char c)
{
	int		i = 1;
	char	alphabet[100] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	while (alphabet[i])
	{
		if (alphabet[i] == c)
			return (i + 1);
		i++;
	}
	return (0);
}

char		ft_findTriplon(char *s1, char *s2, char *s3)
{
	int 	i = 0;
	int		j = 0;
	int		k = 0;

	while (s1[i])
	{
		while (s2[j])
		{
			if (s1[i] == s2[j])
			{
				while (s3[k])
				{
					if (s1[i] == s3[k])
						return(s1[i]);
					k++;
				}
				k = 0;
			}
			j++;
		}
		j = 0;
		i++;
	}
	return ('\0');
}

char	ft_separateArray(char *str)
{
	char	s1[100];
	char	s2[100];
	char	s3[100];
	int		i = 0;
	int		j = 0;
	while (str[i] != '\n' && str[i])
	{
		s1[j] = str[i];
		j++;
		i++;
	}
	s1[j] = '\0';
	j = 0;
	i++;
	while (str[i] != '\n' && str[i])
	{
		s2[j] = str[i];
		j++;
		i++;
	}
	s2[j] = '\0';
	j = 0;
	i++;
	while ((str[i] != '\n' && str[i]) || str[i] != '\0')
	{
		s3[j] = str[i];
		j++;
		i++;
	}
	s3[j] = '\0';
	j = 0;
	return (ft_findTriplon(s1, s2, s3));
}

int main (int ac, char **av)
{
	FILE*	file = NULL;
	char	buf[BUFFER_SIZE] = "";
	int		len = 0;
	int		i = 0;
	char	*comp1;
	char	*comp2;
	int		sum = 0;
	char	tmp[100000];
    file = fopen(av[1], "r+");
    if (file != NULL)
    {
		while (fgets(buf, BUFFER_SIZE, file) != NULL)
		{	
			if (strchr(buf, '\n') != NULL || strchr(buf, '\0') != NULL)
			{
				strcat(tmp, buf);
				i++;
			}
			if (i == 3)
			{
				i = 0;
				sum += findPriorities(ft_separateArray(tmp));
				memset(tmp, 0, sizeof(tmp));
			}
		}
		fclose(file);
    }
    else
    {
        printf("Impossible d'ouvrir le fichier %s\n", av[1]);
    }
	
	printf("sum = %d\n", sum);
    return 0;
}
