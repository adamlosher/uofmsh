// Include Catch
#include "Catch2/single_include/catch2/catch.hpp"

#include "../src/uofmsh.cpp"

SCENARIO("Setting the shell prompt") {

  GIVEN("A prompt to use") {
    const std::string prompt = "~> ";

    WHEN("A shell is created with the prompt") {
      uofmsh::Shell shell(prompt);

      THEN("It has the supplied prompt") {
        REQUIRE(shell.getPrompt().compare(prompt) == 0);
      }
    }

    WHEN("A shell is created without the prompt") {
      uofmsh::Shell shell;

      THEN("It has the default prompt") {
        REQUIRE(shell.getPrompt() == "uofmsh> ");
      }
    }
  }
}

SCENARIO("Parsing a shell command") {

  std::vector<std::string> elements;

  GIVEN("A shell instance") {

    uofmsh::Shell shell;

    WHEN("It parses a simple command") {
      auto command = "ls -lh";

      elements = { "ls -lh" };

      THEN("The command isn't changed") {
        REQUIRE(shell.parse(command) == elements);
      }
    }

    WHEN("It parses a command with redirection and pipes") {
      auto command = "ls -lh | grep *.c | grep *.h > tmp > file";

      elements = {
        "ls -lh",
        "|",
        "grep *.c",
        "|",
        "grep *.h",
        ">",
        "tmp",
        ">",
        "file"
      };

      THEN("The command is split by pipes and redirection") {
        REQUIRE(shell.parse(command) == elements);
      }
    }
  }
}
