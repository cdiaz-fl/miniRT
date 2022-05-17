/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdiaz-fl <cdiaz-fl@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 14:07:25 by zcanales          #+#    #+#             */
/*   Updated: 2022/05/15 20:48:11 by cdiaz-fl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# define BUFFER_SIZE 1
char	*get_next_line(int fd);
char	*find_next_line(char *holder);
char	*save_holder(char *buf, char *holder);
char	*new_holder(char	*holder);
char	*read_file(int fd, char *holder);
void	get_rgb(void *object, char *s, char c);
void	get_pos(void *object, char **head, char c, char *s);
void	get_n_vec(void *object, char **head, char c, char *s);

/*char	*ft_strchr(char *s, int c);
size_t	ft_strlen(const char *s);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_strjoin(char *s1, char const *s2);
char	*ft_strdup(char *s);
*/
#endif
