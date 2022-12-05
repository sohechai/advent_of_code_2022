#define BUFFER_SIZE 10000
#include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

int		findNumberToMoove(const char *str)
{
	int		i = 5;
	int		j = 0;
	int		nb = 0;
	char	tmp[5];

	while (str[i] != ' ')
	{
		tmp[j] = str[i];
		i++;
		j++;
	}
	nb = atoi(tmp);
	memset(tmp, '\0', sizeof(tmp));
	return (nb);
}

int		findStartStack(const char *str)
{
	int		i = 2;
	int		j = 0;
	int		nb = 0;
	char	tmp[2];

	while (str[i] != ' ')
	{
		tmp[j] = str[i];
		i++;
		j++;
	}
	nb = atoi(tmp);
	memset(tmp, '\0', sizeof(tmp));
	return (nb);
}

int		findEndStack(const char *str)
{
	int		i = 2;
	int		j = 0;
	int		nb = 0;
	char	tmp[2];

	while (str[i])
	{
		tmp[j] = str[i];
		i++;
		j++;
	}
	nb = atoi(tmp);
	memset(tmp, '\0', sizeof(tmp));
	return (nb);
}

void 	freeTab(char **tab)
{
	int i;

	i = 0;
	while (tab[i++])
		tab[i] = 0;
	tab[i] = 0;
}

char	**execInstructions(char **stacks, int nb, int startStack, int endStack)
{
	int		i = 0;
	int		j = 0;
	int		k = 0;
	char	*tmp;

	if (!(tmp = malloc(sizeof(char*) * nb + 1)))
		printf("error malloc\n");
	while (stacks[i])
	{
		if (i == startStack)
			break;
		i++;
	}
	i--;
	j = strlen(stacks[i]) - nb;
	while(nb > 0 && stacks[i][j] != '\0') {
		tmp[k] = stacks[i][j];
		stacks[i][j] = '\0';
		nb--;
		j++;
		k++;
	}
	tmp[k] = '\0';
	for(int i = 0; stacks[i]; i++) {
		if (i + 1 == endStack)
		{
			stacks[i] = strcat(stacks[i], tmp);
			break ;
		}
	}
	free(tmp);
	return (stacks);
}

int main (int ac, char **av)
{
	FILE*	file = NULL;
	char	buf[BUFFER_SIZE] = "";
	char	tmp[100][100] = {
		"ZPMHR",
		"PCJB",
		"SNHGLCD",
		"FTMDQSRL",
		"FSPQBTZM",
		"TFSZBG",
		"NRV",
		"PGLTDVCM",
		"WQNJFML",
	};
	// char	tmp[100][4] = {
	// 	"ZN",
	// 	"MCD",
	// 	"P",
	// };
		
	char	**stacks;
	char	**tmpstacks;

	if (!(stacks = (char**)malloc(sizeof(char*) * sizeof(tmp) + 1)))
		return (0);
	if (!(tmpstacks = (char**)malloc(sizeof(char*) * sizeof(tmp) + 1)))
		return (0);

	for (int i = 0; i < 9; i++) {
		stacks[i] = tmp[i];
	}
	stacks[9] = NULL;
	printf("----\nSTACKS = \n");
	for (int i = 0; i < 9; i++) {
		printf("%s\n", stacks[i]);
	}
	printf("----\n");

    file = fopen(av[1], "r+");
    if (file != NULL)
    {
		while (fgets(buf, BUFFER_SIZE, file) != NULL)
		{	
			if (strchr(buf, 'm'))
			{
				tmpstacks = execInstructions(
					stacks,
					findNumberToMoove(buf),
					findStartStack(strrchr(buf, 'm')),
					findEndStack(strrchr(buf, 'o'))
				);
				stacks = tmpstacks;
			}
		}
		fclose(file);
    }
    else
    {
        printf("Impossible d'ouvrir le fichier %s\n", av[1]);
    }

	printf("----\nSTACKS RESULTS = \n----\n");
	for (int i = 0; i < 9; i++) {
		printf("%s\n", stacks[i]);
	}
	printf("----\n");

	free(stacks);
    return 0;
}
