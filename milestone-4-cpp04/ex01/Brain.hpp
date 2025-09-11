/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 15:16:13 by elagouch          #+#    #+#             */
/*   Updated: 2025/09/10 15:18:34 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _Brain_HPP_
#define _Brain_HPP_

#include <string>

class Brain {
public:
  Brain();
  Brain(Brain const &other);
  ~Brain();

  Brain &operator=(const Brain &other);

  void setIdea(int index, const std::string &idea);
  const std::string &getIdea(int index) const;
  void printIdeas(int count = 5) const;

private:
  std::string _ideas[100];
};

#endif
