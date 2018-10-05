#ifndef UOFMSH_H
#define UOFMSH_H

#include <iostream>

#include <algorithm>
#include <set>
#include <string>
#include <vector>
#include <regex>

#include "helpers.hpp"

namespace uofmsh {

// Represents a shell's data and methods
class Shell {
  // This shell's current prompt
  std::string prompt;

  // Redirection operators
  std::set<char> redirection = { '>', '<', '|' };

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
    void run(const std::string &input) {

      auto lines = helpers::split(input, ";");

      for (auto l : lines)
        std::cout << "line: " << l << "\n";

      std::vector<std::vector<std::string>> commands;

      for (auto &command : lines) {
        helpers::trimWhiteSpace(command);
        commands.push_back(parse(command));
        std::cout << command << "\n";
      }

      for (auto i : commands) {
        std::cout << "command: ";

        for (auto j : i)
          std::cout << "element: " << j << " ";

        std::cout << "\n";
      }

      // Blindly support a very limited format for commands
      // Valid formats
      //   command
      //   command > output
      //   command < input
      //   command | command
      for (auto const &command : commands) {
        switch (command.size()) {
          case 1:
            std::cout << "simple\n";
            // runSimpleCommand(commands[0]);
            break;
          case 3:
            switch (command[1][0]) {
              case '|':
                std::cout << "pipe\n";
                // runSimplePipe(command[0], command[2]);
                break;
              case '<':
                std::cout << "Left\n";
                // runSimpleRedirectLeft(command[0], command[2]);
                break;
              case '>':
                std::cout << "Right\n";
                // runSimpleRedirectLeft(command[0], command[2]);
                break;
            }
            break;
          default:
            std::cout << "\nError! Command too complicated or syntax error.\n";
        }
      }

    }

   // Parses a command into elements by splitting by redirection operators
   //
   //   parse("cat file | grep *.c > output")
   //
   //     => { "cat file", "|", "grep *.c", ">", "output" }
   //
   // @return   the command elements, including redirection operators
   std::vector<std::string> parse(std::string command) {
     std::vector<std::string> elements;

     std::regex regex("([><|]|[^><|]+)");  // matches delimiters or consecutive non-delimiters

     std::regex_iterator<std::string::iterator>
       rit(command.begin(), command.end(), regex);

     std::regex_iterator<std::string::iterator> rend;

     while (rit!=rend) {
       std::string s = rit->str();
       helpers::trimWhiteSpace(s);

       if (s.size() > 0)
         elements.push_back(s);

       ++rit;
     }

     if (elements.size() == 1 && redirection.count(elements[0][0]) != 0)
       elements.clear();

     return elements;
   }

};

} // namespace uofmsh

#endif
