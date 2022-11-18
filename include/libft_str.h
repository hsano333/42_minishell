/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_str.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano </var/mail/hsano>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 14:53:05 by hsano             #+#    #+#             */
/*   Updated: 2022/11/18 19:47:17 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_STR_H
# define LIBFT_STR_H
# include <unistd.h>

int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *str, int *long_over_flag);
long	ft_atol(const char *str, int *long_over_flag);
float	ft_atof(const char *str, int *error);
double	ft_atod(const char *str, int *error);
char	*ft_itoa(int n);
void	ft_itoa_no_memory(int n, char *p, char *r);
char	*ft_strdup(const char *s1);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
int		ft_free_split(char **split);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *s);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_ltoa(long n, char *p);
int		ft_isdigitstr(char *str);
#endif
