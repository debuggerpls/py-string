### py-string, header-only python string library for cpp

Header-only library to interact with strings in python-like
matter.

#### NOTE
Most methods on `py_str::String` instances change the original string.
This is done to reduce the allocations for new strings when
manipulating them. 

This library does not have performance
in mind (and any performace improvements are welcome),
but it still should not waste resources. 

Thus use `copy()` on the original `py_str::String` before you start 
manipulating it, if you want to keep the original unchanged.
