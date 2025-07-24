/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paguiler <paguiler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 19:29:25 by paguiler          #+#    #+#             */
/*   Updated: 2025/05/25 18:00:36 by paguiler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c) // esta funcion busca el primer caracter c en la cadena s
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_strdup(const char *s) // esta funcion duplica la cadena s
{
	char	*copy;
	size_t	i;

	if (!s)
		return (NULL);
	copy = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (s[i])
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

char	*ft_strjoin(char *s1, char *s2) // esta funcion une dos cadenas s1 y s2
{
	char	*result;
	size_t	i;
	size_t	j;

	if (!s1 && !s2)
		return (NULL);
	result = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!result)
	{
		free(s1);
		return (NULL);
	}
	i = 0;
	while (s1 && s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
		result[i++] = s2[j++];
	result[i] = '\0';
	free(s1);
	return (result);
}

char	*ft_substr(const char *s, unsigned int start, size_t len) // esta funcion crea una subcadena de s desde el indice start con longitud len
{
	char	*sub;
	size_t	i;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))  // si el inicio es mayor que la longitud de s, devuelve una cadena vacía
		return (ft_strdup("")); // devolver una cadena vacía
	if (len > ft_strlen(s + start)) // si la longitud es mayor que la longitud restante de s, ajusta len
		len = ft_strlen(s + start); // ajustar la longitud a la longitud restante
	sub = (char *)malloc(sizeof(char) * (len + 1)); // reserva memoria para la subcadena
	if (!sub)
		return (NULL);
	i = 0;
	while (i < len && s[start + i]) // copia los caracteres de s a la subcadena
	{
		sub[i] = s[start + i]; // copiar caracteres de s a sub
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
