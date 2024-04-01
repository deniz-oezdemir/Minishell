#include <stdio.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	estEntreGuillemets(const char *str)
{
	int	len_str;

	len_str = ft_strlen(str);
	if ((str[0] == '"' && str[len_str - 1] == '"')
		|| (str[0] == '\'' && str[len_str - 1] == '\''))
		return (1);
	else
		return (0);
}
int main() {
    // Test de la fonction
    const char *chaine1 = "hello";
    const char *chaine2 = "'hello'";
    const char *chaine3 = "'hello";
    const char *chaine4 = "hello'";
    const char *chaine5 = "\"hello\"";
    const char *chaine6 = "\"hello";

    printf("chaine1 : %s est entre guillemets ? %d\n", chaine1, estEntreGuillemets(chaine1));
    printf("chaine2 : %s est entre guillemets ? %d\n", chaine2, estEntreGuillemets(chaine2));
    printf("chaine3 : %s est entre guillemets ? %d\n", chaine3, estEntreGuillemets(chaine3));
    printf("chaine4 : %s est entre guillemets ? %d\n", chaine4, estEntreGuillemets(chaine4));
    printf("chaine5 : %s est entre guillemets ? %d\n", chaine5, estEntreGuillemets(chaine5));
    printf("chaine6 : %s est entre guillemets ? %d\n", chaine6, estEntreGuillemets(chaine6));

    return 0;
}
