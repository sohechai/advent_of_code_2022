#define BUFFER_SIZE 10000
#include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

int			checkDouble(char *str)
{
	int		j = 0;
	if (strcmp(str, "") == 0) {
		printf("str est null \n");
		return (1);
	}
	for (int i = 0; str[i]; i++) {
		while (str[j]) {
			if (str[i] == str[j] && j != i) {
				return (1);
			}
			j++;
		}
		j = 0;
	}
	return (0);
}

int			checkMarker(char *str)
{
	int		i = 0;
	int		k = 0;
	char	*tmp;

	if (!(tmp = malloc(sizeof(char*) * 4 + 1)))
		return (0);
	while (str[i]) {
		tmp[k] = str[i];
		if (k == 3) {
			tmp[4] = '\0';
			if (checkDouble(tmp) == 0)
				return (i + 1);
			i -= 3;
			k = -1;
		}
		k++;
		i++;
	}
	return (0);
}

int main (int ac, char **av)
{
	FILE*	file = NULL;
	char	buf[BUFFER_SIZE] = "";
	char	marker[3];

    file = fopen(av[1], "r+");
    if (file != NULL)
    {
		while (fgets(buf, BUFFER_SIZE, file) != NULL)
		{
			printf("[%d]\n", checkMarker(buf));
		}
		fclose(file);
    }
    else
    {
        printf("Impossible d'ouvrir le fichier %s\n", av[1]);
    }

    return 0;
}
