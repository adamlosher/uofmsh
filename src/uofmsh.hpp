#ifndef UOFMSH_H
#define UOFMSH_H

#include <algorithm>
#include <unordered_map>
#include <string>
#include <vector>

#include "helpers.hpp"

namespace uofmsh {

// Represents a shell's data and methods
class Shell {
  // This shell's current prompt
  std::string prompt;

  // Redirection operators
  std::unordered_map<char, std::string> redirection = {
    { '<', "LEFT" },
    { '>', "RIGHT" },
    { '|', "PIPE" }
  };

  public:

    // @return  a new shell instance with the given prompt
    explicit Shell(const std::string &prompt) : prompt(prompt) { }

    // @return  a new shell instance with the default prompt
    Shell() : prompt("uofmsh> ") { }

    // Starts the user input loop
    //
    // @return  the shell's exit status
    int start();

    // @return  this shell's prompt
    std::string getPrompt() {
      return this->prompt;
    }

    // Adds input to the shell, then runs the inputed commands
    // void run(const std::string &input) {
    //   auto commands = helpers::split(input, ";");

    //   for (auto &c : commands) {
    //     helpers::trim(c, " \t");
    //
    //   }
    // }

   // Parses a command into elements
   //
   // @return   the command elements
   std::vector<std::string> parse(const std::string &command) {
     std::vector<std::string> elements;

     std::string substring;
     for (const auto &c : command) {
       if (redirection.count(c) == 0) // If not a redirection operator, then collect the next character
         substring.push_back(c);
       else if (std::isspace(c) != 0) // Skip whitespace
         continue;
       else {
        helpers::trim(substring, " \t");       // Trim whitspace from the last command
        elements.push_back(substring);         // Add the last command
        elements.push_back(std::string(1, c)); // Add the redirection operator
        substring = "";                        // Reset our substring
       }
     }

     helpers::trim(substring, " \t"); // Trim the final command
     elements.push_back(substring);   // Add the final command

     return elements;
   }

};

} // namespace uofmsh

#endif
