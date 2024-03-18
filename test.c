#include <stdio.h>
#include <stdlib.h>
#include <string.h>

# include "./libft/libft.h"
#define SPECIAL_CHARS "|><"
/*Parcourt la chaine et compte le nombre de char speciaux (> >> < << |) qui sont attaches*/
int special_len(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i]) {
		if ((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i + 1] == '<'))
		{
			if (str[i - 1] != ' ' || str[i + 2] != ' ')
				count++;
			i += 2;
		}
		if (str[i] == '>' || str[i] == '<' || str[i] == '|')
		{
			if (str[i - 1] != ' ' || str[i + 1] != ' ')
				count++;
		}
		i++;
	}
	return (count);
}
char *add_space(char *str)
{
	int i;
	int j;
	int len_str;
	char *new_str;

	i = 0;
	j = 0;
	len_str = ft_strlen(str) + special_len(str) + 1;
	new_str = (char *)malloc(sizeof(char) * len_str);
	if (!new_str)
		return (NULL);

    while (str[i]) {
        if ((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i + 1] == '<')) {
            if (i == 0 || str[i - 1] != ' ')
                new_str[j++] = ' ';
            new_str[j++] = str[i++];
            new_str[j++] = str[i++];
        } else if ((str[i] == '>' || str[i] == '<' || str[i] == '|') && str[i + 1] == ' ') {
            new_str[j++] = str[i++];
        } else if (str[i] == '>' || str[i] == '<' || str[i] == '|') {
            if (i == 0 || str[i - 1] != ' ')
                new_str[j++] = ' ';
            new_str[j++] = str[i++];
        } else {
            new_str[j++] = str[i++];
        }
    }

    new_str[j] = '\0'; // Terminer la nouvelle chaîne avec un caractère nul

    return new_str;
}





int main() {
    char str1[] = "commande <<sortie.txt"; // commande << sortie.txt
    char str2[] = "commande sortie.txt>>"; // commande sortie.txt >>
    char str3[] = "commande <<sortie.txt>>"; // commande << sortie.tx t>>
    char str4[] = "commande <sortie.txt"; // commande < sortie.txt
    char str5[] = "commande sortie.txt>"; // commande sortie.txt >
    char str6[] = "commande |sortie.txt"; // commande | sortie.txt
    char str7[] = "commande| sortie.txt"; // commande | sortie.txt

    // Appel de la fonction add_space pour chacune des chaînes
    printf("%s\n", add_space(str1));
    printf("%s\n", add_space(str2));
    printf("%s\n", add_space(str3));
    printf("%s\n", add_space(str4));
    printf("%s\n", add_space(str5));
    printf("%s\n", add_space(str6));
    printf("%s\n", add_space(str7));

    return 0;
}


