#include <iostream>
#include <string>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../class/password.h"

TEST_CASE("Generated password can be generated at a fixed length ", "[password]") {
    password p1;

    p1.type (LOWERCASE_ALPHA | UPPERCASE_ALPHA | NUMERIC);
    p1.length (12);

    try
    {
      p1.generate ();
    }

    catch (pwdgenerr err)
    {
      cerr << "Error: " << *err.message () << '\n';
      cout <<  err.value ();
    }

    std::ostringstream oss;
    oss << p1;
    std::string tmp = oss.str();

    REQUIRE(tmp.length() == 12);
}
