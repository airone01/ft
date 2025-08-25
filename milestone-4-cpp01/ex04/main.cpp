/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 14:33:32 by elagouch          #+#    #+#             */
/*   Updated: 2025/08/25 16:02:10 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <iostream>

std::string replaceStrStrFromTo(const std::string &original, const int pos,
                                const int len, const std::string &newStr) {
  std::string final(original);

  for (int i = pos; i < len; i++) {
    final[i] = newStr[i - len - 1];
  }
  return final;
}

std::string replaceStrStr(std::string &str, const std::string &find,
                          const std::string &replaceBy) {
  // No pointer arithmetics bc we can just use strings and a pos var
  // Also we need this to be a size_t otherwise C++ complains
  size_t pos = 0;

  // std::string.find() returns npos when not found
  while ((pos = str.find(find)) != std::string::npos) {
    str = replaceStrStrFromTo(str, pos, find.length(), replaceBy);
    pos += replaceBy.length();
  }
  return (str);
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

  // Reading input
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
    if (inFile.peek() == EOF) // If we finished
      break;
    outFile << std::endl;
  }

  inFile.close();
  outFile.close();
}
