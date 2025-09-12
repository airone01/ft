/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 15:16:13 by elagouch          #+#    #+#             */
/*   Updated: 2025/09/12 16:19:45 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _Brain_HPP_
#define _Brain_HPP_

#include <string>

class Brain {
public:
  Brain();
  Brain(Brain const &);
  ~Brain();

  Brain &operator=(const Brain &);

private:
  std::string _ideas[100];
};

#endif
