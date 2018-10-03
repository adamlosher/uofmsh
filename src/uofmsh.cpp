#include <iostream>

#include "uofmsh.hpp"
#include "helpers.hpp"

namespace uofmsh {

// User input loop
int Shell::start() {
  // The line to be read from input
  std::string input;

  bool reading_input = true;

  // Read commands until the shell is exited via exit or an interrupt
  while (reading_input) {
    // Print the prompt first
    std::cout << this->prompt;

    // Get user input
    std::getline(std::cin >> std::ws, input);

    auto commands = helpers::split(input, " \t\n");

    for (auto i = commands.begin(); i != commands.end(); i++) {
      auto element = *i;
      helpers::trim(element, " \t\n");
      auto index = i - commands.begin();
      std::cout << index << ": " << element << "\n";
    }

    // Break out of input loop if command is exit
    if (input.compare("exit") == 0) {
      std::cout << "exit" << "\n";
      reading_input = false;
    }
  }

  return EXIT_SUCCESS;
}

//fork and exec function
//Chapter 3 slide 20
int Shell::runSimpleCommand(std::vector<std::string> args) {
  (void)args;
  pid_t pid;

  //fork a child process
  pid = fork();

  if (pid < 0){//an error occurred
    std::cerr << "Fork failed\n";
    return 1;
  }
  else if (pid == 0){//child process
    execlp("/bin/ls", "ls", NULL);
  }
  else {//parent process
    //parent will wait for child to complete
    wait(NULL);
    std::cout << "Child Complete \n";
  }

  // if (pid < 0) {//an error occurred
  //   fprintf(std:: stderr, "Fork failed\n");
  //   return 1;
  // }
  // else if(pid == 0){//child process
  //   std::cout <<"child: " << pid << "\n";
  //   if(execvp (args[0].args) < 0){
  //     printf("exec error\n");
  //   }
  // }
  // else {//parent process
  //   if(wait(0) > 0){
  //     printf("wait error\n");
  //   }
  //   std::cout << "parent" << pid << "\n";
  //   printf("Child Complete\n");
  // }

  return 0;
}

} // namespace uofmsh

