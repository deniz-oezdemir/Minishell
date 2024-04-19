#include "minishell.h"

/* create custom libft functions with get_grbg instead of malloc / ft_calloc*/

char	*grbg_strdup(const char *s)
{
	size_t	len;
	size_t	i;
	char	*dest;

	i = 0;
	len = ft_strlen(s) + 1;
	//dest = malloc(sizeof(char) * len);
	dest = get_grbg(len, sizeof(char));
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

char	*grbg_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*dest;

	i = 0;
	if (ft_strlen(s) < start)
		return (grbg_strdup(""));
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	//dest = malloc(sizeof(char) * (len + 1));
	dest = get_grbg(len + 1, sizeof(char));
	if (!dest)
		return (NULL);
	while (i < len)
	{
		dest[i] = s[start + i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static int	get_len(long n)
{
	size_t	len;

	len = 0;
	if (n < 0)
	{
		len += 1;
		n = -n;
	}
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static	char	*fill_the_array(int len, char *dest, int n )
{
	int	i;

	i = 0;
	if (n < 0)
	{
		dest[0] = '-';
		n = n * (-1);
		i = 1;
	}
	dest[len] = '\0';
	len -= 1;
	while (len >= i)
	{
		dest[len] = (n % 10) + '0';
		n /= 10;
		len--;
	}
	return (dest);
}

char	*grbg_itoa(int n)
{
	char	*dest;
	size_t	len;
	long	num;

	if (n == -2147483648)
		return (dest = grbg_strdup("-2147483648"));
	if (n == 0)
		return (dest = grbg_strdup("0"));
	num = n;
	len = get_len(num);
	dest = get_grbg(len + 1, sizeof(char));
	if (!dest)
		return (NULL);
	dest = fill_the_array(len, dest, num);
	return (dest);
}

char	*grbg_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*dest;

	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	//dest = malloc(sizeof(char) * len);
	dest = get_grbg(sizeof(char), len);
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, s1, ft_strlen(s1) + 1);
	ft_strlcat(dest, s2, len);
	return (dest);
}
