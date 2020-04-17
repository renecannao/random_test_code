This tests show the amount of code generated with:
* vector of tuple (explicitly created) of strings
* vector of tuple (implicitly created) of strings
* vector of tuple (implicitly created) of const strings
* vector of tuple (implicitly created) of char pointers
* array of structs of char pointers

Size is checked at various optimization level.

It also run some the binaries with /usr/bin/time to display how much memory is being used
