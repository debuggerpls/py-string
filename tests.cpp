#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "py_string.h"
#include "doctest.h"

TEST_CASE("testing dummy function") {
    CHECK(return_val(1) == 1);
    CHECK(return_val(-1) == -1);
}