/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:29:12 by elagouch          #+#    #+#             */
/*   Updated: 2025/06/18 13:33:10 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "cub3d.h"

/*******************************************************************************
 *                             Function Prototypes                             *
 ******************************************************************************/

/*
** p_color.c
*/

/**
 * @brief Parses a color configuration line (F/C) and extracts RGB values
 * @param data Main data structure to populate
 * @param line The line containing color configuration
 * @param id Color identifier ("F " for floor, "C " for ceiling)
 * @return true on parsing error, false on success
 */
bool	parse_color_line(t_data *data, char *line, const char *id);

/**
 * @brief Validates that color string contains only valid RGB digits
 * @param data Main data structure (for error reporting)
 * @param color The color string to validate
 * @return true if invalid characters found, false if valid
 */
bool	check_color_line(t_data *data, char *color);

/*
** p_file.c
*/

/**
 * @brief Processes a configuration line (textures NO/SO/WE/EA or colors F/C)
 * @param data Main data structure to populate
 * @param line The configuration line to process
 * @return true on parsing error, false on success
 */
bool	process_config_line(t_data *data, char *line);

/**
 * @brief Open and parses a file
 *
 * @param data App data
 * @param file File to open
 * @return int 1 on failure, 0 otherwise
 */
int		read_file(t_data *data, const char *file);

/*
** p_flood_fill.c
*/

/**
 * @brief Creating a copy of the map for checking
 *
 * @param data App data containing the map to copy
 * @return true if creating map failed, false if map is created
 */
char	**create_map_copy(t_data *data);

/*
** p_map.c
*/

/**
 * @brief Checks if a line appears to be part of the map section
 * @param line The line to analyze
 * @return true if line contains map characters (0,1,N,S,E,W), false otherwise
 */
bool	looks_like_map_line(char *line);

/**
 * @brief Processes a single line from the file (config or map data)
 * @param data Main data structure to populate
 * @param line Current line being processed
 * @param map_section_started Pointer to flag tracking if map section has begun
 * @param buffer Map buffer to store map lines
 * @return true on error, false on success
 */
bool	process_single_line(t_data *data, char *line,
			bool *map_section_started, t_map_buffer *buffer);

/**
 * @brief Comprehensive map validation using flood fill algorithm
 *
 * @param data App data containing the map to validate
 * @return true if map validation fails, false if map is valid
 */
bool	fill_map(t_data *data, int fd);

/*
** p_map_{m,b}.c
*/

/**
 * @brief Condition for the validation of a config line
 *
 * @param trimmed String to check
 * @returns bool Whether it's a config line or not
 */
bool	config_line_condition(char *trimmed);

/*
** p_map_check.c
*/

/**
 * @brief Comprehensive map validation using flood fill algorithm
 *
 * @param data App data containing the map to validate
 * @return true if map validation fails, false if map is valid
 */
bool	check_map_validity(t_data *data);

/**
 * @brief Recursively performs flood fill algorithm on a 2D character map.
 *
 * @param map_copy 2D character array (map copy to avoid modifying original)
 * @param x Starting x-coordinate (column)
 * @param y Starting y-coordinate (row)
 * @param data Additional data structure for flood fill parameters
 * @return true if successful, false on error or invalid coordinates
 */
bool	flood_fill_recursive(char **map_copy, int x, int y, t_data *data);

/*
** p_map_utils.c
*/

/**
 * @brief Doubles the buffer capacity and reallocates memory
 * @param buffer The map buffer to expand
 * @return true on memory allocation failure, false on success
 */
bool	expand_buffer(t_map_buffer *buffer);

/**
 * @brief Adds a line to the buffer and updates max width tracking
 * @param buffer The map buffer to add to
 * @param line The line to add (will be duplicated)
 * @return true on error, false on success
 */
bool	add_line_to_buffer(t_map_buffer *buffer, char *line);

/**
 * @brief Frees all allocated memory in the map buffer
 * @param buffer The map buffer to free
 */
void	free_map_buffer(t_map_buffer *buffer);

/**
 * @brief Transfers buffer contents to main data structure
 * and sets map dimensions
 * @param data Main data structure to populate with map data
 * @param buffer Source buffer containing map lines
 * @return true on memory allocation failure, false on success
 */
bool	buffer_to_data(t_data *data, t_map_buffer *buffer);

/*
** p_texture.c
*/

/**
 * @brief Parses a texture path from a line
 *
 * @param data App data
 * @param line Line to parse
 * @param cardinal Cardinal direction
 * @return true On error
 * @return false On success
 */
bool	parse_texture_path(t_data *data, char *line, const char *cardinal);

/*
** p_validation.c
*/

/**
 * @brief Validate that all required configuration is present
 *
 * @param data App data structure to validate
 * @return true if configuration is incomplete, false if complete
 */
bool	validate_config_completeness(t_data *data);

/**
 * @brief Check if all texture paths are properly set
 *
 * @param data App data structure
 * @return true if textures missing, false if all present
 */
bool	check_texture_completeness(t_data *data);

/**
 * @brief Check if colors are properly configured
 *
 * @param data App data structure
 * @return true if colors missing, false if properly set
 */
bool	check_color_completeness(t_data *data);

#endif // !PARSING_H