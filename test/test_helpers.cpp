// Tests for any helper functions

// Include Catch
#include "Catch2/single_include/catch2/catch.hpp"

// Our helpers
#include "../src/helpers.cpp"

SCENARIO("Splitting a string by a string of delimiters") {
  std::vector<std::string> output;

  GIVEN("A string containing the delimiters") {
    const std::string input  = "veni,\nvidi, vici";
    const std::string delims = " ,\n";
    output = uofmsh::helpers::split(input, delims);

    WHEN("The string is split") {
      THEN("It is split by the delimiters") {
        REQUIRE(output.size() == 3);

        REQUIRE(output[0] == "veni");
        REQUIRE(output[1] == "vidi");
        REQUIRE(output[2] == "vici");
      }
    }
  }

  GIVEN("A string consisting of the delimiters") {
    const std::string input  = "!@#$%^&*";
    const std::string delims = "!@#$%^&*";
    output = uofmsh::helpers::split(input, delims);

    WHEN("The string is split") {
      THEN("It collects nothing") {
        REQUIRE(output.size() == 0);
      }
    }
  }

  GIVEN("An empty string") {
    const std::string input  = "";
    const std::string delims = " ";
    output = uofmsh::helpers::split(input, delims);

    WHEN("The string is split") {
      THEN("It collects nothing") {
        REQUIRE(output.size() == 0);
      }
    }
  }
}

SCENARIO("Trimming a string of by a group of delimiters") {
  std::string str, trimmed, delims;

  GIVEN("A string with spaces on the left") {
    str     = "   space on the left";
    trimmed = "space on the left";
    delims  = "\n\t ";

    uofmsh::helpers::trim(str, delims);

    WHEN("The string is trimmed") {
      THEN("It removes the leading spaces") {
        REQUIRE(str.compare(trimmed) == 0);
      }
    }
  }

  GIVEN("A string with $'s on the right") {
    str     = "cash$$$$$$";
    trimmed = "cash";
    delims  = "$";

    uofmsh::helpers::trim(str, delims);

    WHEN("The string is trimmed") {
      THEN("It removes the trailing $'s") {
        REQUIRE(str.compare(trimmed) == 0);
      }
    }
  }

  GIVEN("A string surrounded by whitespace") {
    str     = "\t   doggos\n    \t\f";
    trimmed = "doggos";
    delims  = " \t\f\n";

    uofmsh::helpers::trim(str, delims);

    WHEN("The string is trimmed") {
      THEN("It removes the whitespace") {
        REQUIRE(str.compare(trimmed) == 0);
      }
    }
  }
}

SCENARIO("Trimming whitespace from a string") {
  std::vector<std::string> withWhiteSpace, withOutWhiteSpace;

  GIVEN("Strings with whitespace") {
    withWhiteSpace    = { "  a", "b  ", "  ab  ", "  a  b  " };
    withOutWhiteSpace = { "a",   "b",   "ab",     "a  b" };

    WHEN("The strings are trimmed of whitespace") {
      for (auto &s : withWhiteSpace)
        uofmsh::helpers::trimWhiteSpace(s);

      THEN("The whitespace is removed from the edges of the string") {
        for (int i = 0; i < 4; i++)
          REQUIRE(withWhiteSpace[i].compare(withOutWhiteSpace[i]) == 0);
      }
    }
  }
}
