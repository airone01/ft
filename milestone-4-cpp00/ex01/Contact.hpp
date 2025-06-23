/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 13:01:41 by elagouch          #+#    #+#             */
/*   Updated: 2025/06/22 14:35:54 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>

class Contact {

private:
  std::string _first_name;
  std::string _last_name;
  std::string _nickname;
  std::string _phone;
  std::string _secret;

public:
  Contact(std::string first_name, std::string last_name, std::string nickname,
          std::string phone, std::string secret);
  Contact();
  ~Contact();

  std::string getFirstName();
};
