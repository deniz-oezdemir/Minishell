#include <stdio.h>   // Pour printf
#include <stdlib.h>

void print_str_array(char **arr) {
    printf("[");
    for (int i = 0; arr[i] != NULL; i++) {
        printf("%s, ", arr[i]);
    }
    printf("]\n");
}
size_t	get_len_arr(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		i++;
	}
	return i;
}

char **del_str_from_array(char **array, int pos, int count)
{
	int	new_size;
	int	i;
	int	j;
	char	**temp;


	j = 0;
	i = 0;
	new_size = get_len_arr(array) - count;
	temp = (char **)malloc((new_size + 1) * sizeof(char *));
	if (temp == NULL)
		return (NULL);
	while (array[i])
	{
		if (i < pos || i >= pos + count)
		{
			temp[j] = array[i];
			j++;
		}
		i++;
	}
	temp[j] = NULL;
	return (temp);
}





int main() {
    // Tableau de chaînes de caractères de test
    char *array[] = {"Bonjour", "mon", "ami", "comment", "vas-tu", "?"};
    int pos = 2;  // Position de départ de la suppression
    int count = 3;  // Nombre de chaînes de caractères à supprimer

    // Affichage du tableau d'origine
    printf("Tableau d'origine :\n");
    print_str_array(array);
    printf("\n");

    // Appel de la fonction del_str_from_array pour supprimer les chaînes de caractères
    char **newArray = del_str_from_array(array, pos, count);
    if (newArray == NULL) {
        printf("Erreur lors de la suppression des chaînes de caractères.\n");
        return 1;
    }

    // Affichage du nouveau tableau
    printf("Nouveau tableau :\n");
    print_str_array(newArray);

    // Libération de la mémoire du nouveau tableau
    for (int i = 0; newArray[i] != NULL; ++i) {
        free(newArray[i]);
    }
    free(newArray); // Libération de la mémoire allouée pour le nouveau tableau

    return 0;
}




















/*@Leo: Deniz commented the whole file out because of compilation error

#include <stdio.h>
#include <stdlib.h>
#include <string.h>




commande <<sortie.txt
commande sortie.txt >>
commande <<sortie.txt >>
commande <sortie.txt
commande sortie.txt >
commande |sortie.txt
commande| sortie.txt




# include "./libft/libft.h"
#define SPECIAL_CHARS "|><"
//Parcourt la chaine et compte le nombre de char speciaux (> >> < << |) qui sont attaches
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
	while (str[i])
	{
		if ((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i + 1] == '<'))
		{
			if (i == 0 || str[i - 1] != ' ')
			{
				new_str[j++] = ' ';
				new_str[j++] = str[i++];
				new_str[j++] = str[i++];
			}
			else if(str[i + 2] != ' ')
			{
				new_str[j++] = str[i++];
				new_str[j++] = str[i++];
				new_str[j++] = ' ';
			}
		}
		else if ((str[i] == '>' || str[i] == '<' || str[i] == '|') && str[i - 1] != ' ')
		{
			new_str[j++] = ' ';
			new_str[j++] = str[i++];
		}
		else if ((str[i] == '>' || str[i] == '<' || str[i] == '|') && str[i + 1] != ' ')
		{
			new_str[j++] = str[i++];
			new_str[j++] = ' ';

		}
		else
			new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	return (new_str);
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
*/
