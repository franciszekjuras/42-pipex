/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjuras <fjuras@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 18:38:47 by fjuras            #+#    #+#             */
/*   Updated: 2022/05/28 14:02:14 by fjuras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stddef.h>
# include <stdarg.h>

typedef unsigned long long	t_ull;

typedef enum e_strtoi_err
{
	FT_STRTOI_BASE = 0x01,
	FT_STRTOI_OVERFLOW = 0x02,
	FT_STRTOI_EMPTY = 0x04
}	t_strtoi_err;

typedef struct s_ft_argparse
{
	char	arg;
	char	count;
	char	**params;
}	t_ft_argparse;

/*argparse*/
t_ft_argparse	*ft_argparse(int argc, char **argv);
t_ft_argparse	*ft_argparse_find(t_ft_argparse *args, char arg);
t_ft_argparse	*ft_argparse_free(t_ft_argparse *args);

/*get_next_line*/
char			*ft_get_next_line(int fd);
void			*ft_gnl_close(int fd);

/*printf*/
int				ft_dprintf(int fd, const char *fstr, ...);
int				ft_printf(const char *fstr, ...);

void			ft_swapi(int *a, int *b);
void			ft_swapp(void **p1, void **p2);
unsigned int	ft_absu(int n);
t_ull			ft_absull(long long n);
int				ft_abs(int n);
int				ft_max(int n1, int n2);
int				ft_min(int n1, int n2);
double			ft_fmax(double n1, double n2);
double			ft_fmin(double n1, double n2);
int				ft_isascii(int c);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isprint(int c);
int				ft_isspace(int c);
int				ft_islower(int c);
int				ft_isupper(int c);
int				ft_isinset(int c, const char *set);
int				ft_idxinset(int c, const char *set);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
int				ft_putcharn_fd(char c, int fd);
int				ft_putncharn_fd(char c, int n, int fd);
int				ft_putstrn_fd(char *s, int fd);
int				ft_putendln_fd(char *s, int fd);
int				ft_putnbrn_fd(int n, int fd);
int				ft_strempty(const char *s);
int				ft_toupper(int c);
int				ft_tolower(int c);
char			*ft_strtoupper(char *s);
char			*ft_strtolower(char *s);
int				ft_atoi(const char *np);
char			ft_numtochar(int n);
char			*ft_lltoa_base_buf(long long n, int base, char *buf, int size);
char			*ft_ulltoa_base_buf(
					unsigned long long n, int base, char *buf, int size);

int				ft_chartonum_base(char c, int base);
int				ft_strtoi_parse_prefix_e( char **npp, int *base, int *err);
long long		ft_strtoll_e(
					const char *np, char **ep, int base, int *err);
t_ull			ft_strtoull_e(
					const char *np, char **ep, int base, int *err);
long long		ft_strtonum(
					char **npp, long long min, long long max, int *err);

/**
 * @brief convert string to floating point number represented by integer
 * base and power of 10
 * 
 * @param np string
 * @param base pointer to store base number
 * @param pow pointer to store power
 * @param err pointer to store error status
 * @return char* pointer past end of valid number
 */
char			*ft_strtofp(char *np, long long *base, int *pow10, int *err);

/**
 * @brief 
 * Allocate memory for \p number of objects of size \p size
 * and initilize it with 0s.
 * 
 * @param number length of allocated array
 * @param size size of single array element
 * @return void* pointer to allocated memory
 */
void			*ft_calloc(size_t number, size_t size);

/**
 * @brief
 * Free elements of NULL terminated array of pointers
 * and the array itself.
 * 
 * @param arr array of pointers
 */
void			*ft_freeparr(void **arr);

/**
 * @brief 
 * Allocate and return string representing the integer received as an argument.
 * 
 * @param n integer to convert
 * @return char* pointer to string representing the integer
 */
char			*ft_itoa(int n);

/**
 * @brief Set len bytes in memory with 0
 * 
 * @param b memory address
 * @param len number of bytes
 */
void			ft_bzero(void *b, size_t len);

/**
 * @brief  
 * Find byte c (as unsigned char) in block of memory
 * starting from b, spanning len bytes. 
 * 
 * @param b address of memory
 * @param c character to search for
 * @param len number of bytes to search
 * @return void* pointer to first occurence of byte c or NULL if not found
 */
void			*ft_memchr(const void *b, int c, size_t len);

/**
 * @brief  
 * Find last occurence of byte c (as unsigned char) in block of memory
 * starting from b, spanning len bytes. 
 * 
 * @param b address of memory
 * @param c character to search for
 * @param len number of bytes to search
 * @return void* pointer to last occurence of byte c or NULL if not found
 */
void			*ft_memrchr(const void *b, int c, size_t len);

/**
 * @brief Set n bytes in memory with c
 * 
 * @param b pointer to memory start
 * @param c byte to set
 * @param n number of bytes
 * @return void* b
 */
void			*ft_memset(void *b, int c, size_t n);

/**
 * @brief 
 * Copy bytes from src to dst, stopping at * character c (incl.).
 * If character c is not found, copy len bytes
 * 
 * @param dst copy destination
 * @param src copy source
 * @param c character to stop at
 * @param len maximal number of bytes to copy
 * @return void* pointer to byte after copied c in dest or NULL
 * if character c wasn't found
 */
void			*ft_memccpy(void *dst, const void *src, int c, size_t len);

/**
 * @brief 
 * Compare memory pointed by b1 with memory pointed by b2.
 * If all len bytes are equal, return 0. Otherwise return difference
 * between first not equal bytes (treated as unsigned char)
 * 
 * @param b1 first compared memory address
 * @param b2 second compared memory address 
 * @param len number of compared bytes
 * @return int difference between first not equal bytes
 * or 0 if all bytes are equal
 */
int				ft_memcmp(const void *b1, const void *b2, size_t len);

/**
 * @brief 
 * Copy len bytes between non overlaping blocks of memory
 * This implemenation uses ft_memmove internally, so memory actually can overlap.
 * 
 * @param dst copy destination
 * @param src copy source
 * @param len number of bytes
 * @return void* pointer to destination
 */
void			*ft_memcpy(void *dst, const void *src, size_t len);

/**
 * @brief Copy len bytes between possibly overlaping blocks of memory
 * 
 * @param dst copy destination
 * @param src copy source
 * @param len number of bytes
 * @return void* pointer to destination
 */
void			*ft_memmove(void *dst, const void *src, size_t len);

/**
 * @brief Allocate and join two paths, adding slash if necessary.
 * Does not handle relative paths in a special way
 * 
 * @param s1 first part of path
 * @param s2 second part of path
 * @return char* joined path string
 */
char			*ft_pathjoin(char const *s1, char const *s2);

/**
 * @brief
 * Return pointer to first occurence of character c
 * or NULL if not found
 * 
 * @param s string
 * @param c searched character
 * @return char* pointer to first found character
 */
char			*ft_strchr(const char *s, int c);

/**
 * @brief Return pointer to last occurence of character c
 * or NULL if not found
 * 
 * @param s string
 * @param c searched character
 * @return char* pointer to last found character
 */
char			*ft_strrchr(const char *s, int c);

/**
 * @brief Append string src to dst, NUL-terminating the result,
 * respecting maximal size of destination dstsize. 
 * 
 * @param dst string to append to
 * @param src string to be appended
 * @param dstsize destination buffer size
 * @return size_t sum of lengths of both strings
 * (if ft_strlen(dst) >= dstsize, then dstsize is treated as dst string length)
 */
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);

/**
 * @brief Copy up to dstsize - 1 characters from the string src to dst,
 * NUL-terminating the result if dstsize is not 0.
 * 
 * @param dst destination address
 * @param src string to copy
 * @param dstsize desination buffer size
 * @return size_t length of source string 
 */
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);

/**
 * @brief Duplicate string
 * 
 * @param str string to duplicate
 * @return char* pointer to duplicated string
 */
char			*ft_strdup(const char *str);

/**
 * @brief Duplicate string of maximal length `len`
 * 
 * @param str string to duplicate
 * @param len maximal length of string
 * @return char* pointer to duplicated string
 */
char			*ft_strndup(const char *str, size_t len);

/**
 * @brief 
 * Allocate and return string intialized with 0s that can hold `len` characters
 * (`len + 1` including termination character)
 * @return char* pointer to empty string
 */
char			*ft_stralloc(size_t len);

/**
 * @brief 
 * Allocate and join strings s1 and s2.
 * 
 * @param s1 first string
 * @param s2 second string
 * @return char* pointer to joined string
 */
char			*ft_strjoin(char const *s1, char const *s2);

/**
 * @brief Return length of string
 * 
 * @param s string
 * @return size_t length of string
 */
size_t			ft_strlen(const char *s);

/**
 * @brief Same as ft_strlen, but returns nothing greater than maxlen.
 * 
 * @param s string
 * @param maxlen maximal number of characters to check
 * @return size_t length of string or maxlen if no termination found
 */
size_t			ft_strnlen(const char *s, size_t maxlen);

/**
 * @brief Compare strings s1 and s2
 * 
 * @param s1 first string
 * @param s2 second string
 * @return int difference between first not matching characters
 * or 0 if strings are equal
 */
int				ft_strcmp(const char *s1, const char *s2);

/**
 * @brief Compare strings s1 and s2, comparing no more
 * than len characaters (as unsigned char)
 * 
 * @param s1 first string
 * @param s2 second string
 * @param len max number of characters to compare
 * @return int difference between first not matching characters
 * or 0 if strings are equal up to len characters
 */
int				ft_strncmp(const char *s1, const char *s2, size_t len);

/**
 * @brief
 * Allocate and return a null-terminated array of newly allocated strings
 * obtained by splitting `str` using the character `delim` as a delimiter.
 * 
 * @param str string to split
 * @param delim delimiting character
 * @return char** pointer to array of strings
 */
char			**ft_split(char const *str, char delim);

char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));

char			*ft_striteri(char *s, void (*f)(unsigned int, char*));

/**
 * @brief 
 * Locate the first occurrence of the string little in the string big,
 * where not more than len characters are searched.
 * 
 * @param big string to search
 * @param little searched string
 * @param len maximal number of characters to search in big
 * @return char* pointer to the first character of the first occurrence 
 * of little in big or NULL if not found.
 * If little is an empty string, return big.
 */
char			*ft_strnstr(const char *big, const char *little, size_t len);

/**
 * @brief 
 * Allocate and trim string using characters in `set`
 * 
 * @param str original string
 * @param set characters set to trim string
 * @return char* pointer to trimmed string
 */
char			*ft_strtrim(char const *str, char const *set);

/**
 * @brief 
 * Allocate and return a substring from the string `s`.
 * beginning at index `start` and of maximum size `len`.
 * 
 * @param s original string
 * @param start substring offset
 * @param len maximal length of substring
 * @return char* pointer to allocated substring
 */
char			*ft_substr(char const *s, unsigned int start, size_t len);

#endif
