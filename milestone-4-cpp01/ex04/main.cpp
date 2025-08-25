/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 14:33:32 by elagouch          #+#    #+#             */
/*   Updated: 2025/08/25 16:41:58 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <iostream>

// The funny thing that happens here is that if you're not careful, the func can
// replace text by strings that are contained in the search text, creating an
// infinite loop. I had to adapt the func to take care of that.
std::string replaceStrStr(std::string &str, const std::string &find,
                          const std::string &replaceBy) {
  if (find.empty()) {
    return str;
  }

  // No pointer arithmetics bc we can just use strings and a pos var
  // Also we need this to be a size_t otherwise C++ complains
  std::string result;
  size_t pos = 0;
  size_t found_pos;

  // std::string.find() returns npos when not found
  while ((found_pos = str.find(find, pos)) != std::string::npos) {
    result += str.substr(pos, found_pos - pos);
    result += replaceBy;

    pos = found_pos + find.length();
  }

  // Append any remaining text
  result += str.substr(pos);

  str = result;
  return str;
}

/*
 * Usage: sed <filename> <s1> <s2>
 */
int main(int argc, char *argv[]) {
  if (argc != 4) {
    std::cout << "Usage: sed <filename> <s1> <s2>" << std::endl;
    return 3;
  }
  std::string inFileName(argv[1]);
  std::string outFileName(inFileName + ".replace");
  std::string find(argv[2]);
  std::string replaceBy(argv[3]);

  // Arg checking
  if (inFileName.empty()) {
    std::cerr << "`filename` must not be empty." << std::endl;
  }
  if (find.empty()) {
    std::cerr << "`s1` must not be empty." << std::endl;
  }

  // I/O
  std::string inFileLine;
  std::ifstream inFile(inFileName.c_str());
  std::ofstream outFile((outFileName).c_str());

  if (!inFile.is_open()) {
    std::cerr << "Cannot open file '" << inFileName << "'." << std::endl;
    return 1;
  }
  if (!outFile.is_open()) {
    std::cerr << "Cannot open file '" << outFileName << "'." << std::endl;
    inFile.close();
    return 1;
  }

  // Reading, processing and writing
  while (getline(inFile, inFileLine)) {
    outFile << replaceStrStr(inFileLine, find, replaceBy);
    if (inFile.peek() != EOF)
      outFile << std::endl;
  }
  outFile << std::endl;

  inFile.close();
  outFile.close();
}
