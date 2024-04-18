#include "minishell.h"

/* create custom libft functions with get_grbg instead of malloc / ft_calloc*/

char	*grbg_strdup(t_prompt *prompt, const char *s)
{
	size_t	len;
	size_t	i;
	char	*dest;

	i = 0;
	len = ft_strlen(s) + 1;
	//dest = malloc(sizeof(char) * len);
	dest = get_grbg(&(prompt->grbg_lst), len, sizeof(char));
	if (dest == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
