/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_bsq.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@42>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:28:59 by elagouch          #+#    #+#             */
/*   Updated: 2024/10/02 19:34:35 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef H_BSQ_H
# define H_BSQ_H

// BSQ functions
t_tile	bsq_map_char_to_tile(char c, t_tiles tiles);
t_tile	**bsq_map_init(t_coords coords);
t_map	*all_final(t_tile **map, t_tiles tiles, char **strs, t_coords coords);
t_map	*bsq_map_read(char *fname, int fsize);
t_map	*bsq_map_stdin_read(int fsize);
void	bsq_map_free(t_tile **map, t_coords coords);
void	bsq_smap_free(t_map *map);
void	bsq_map_put(t_map map);
void	bsq_solve(t_map map);
char	**bsq_read_split_free(char *fname, int fsize);
char	**bsq_read_split_free_stdin(int fsize);
int		bsq_handle_size(int fd, void *buff);
int		bsq_matrix_count(char **strs);
int		bsq_map_file_size(char *arg);

#endif
