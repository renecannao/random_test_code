This tests show the amount of code generated with:
* array with strings and maps
* array with char pointers, one of which point to a JSON

Size is checked at various optimization level.

It also run some the binaries with /usr/bin/time to display how much memory is being used

Note: there is no JSON library included for the processing of the JSON

An example:

```
$ sh make_test_map.sh 
test_map1_O0:  Elapsed (wall clock) time (h:mm:ss or m:ss): 0:04.34 . Size: 716
test_map2_O0:  Elapsed (wall clock) time (h:mm:ss or m:ss): 0:00.09 . Size: 220
test_map1_O2:  Elapsed (wall clock) time (h:mm:ss or m:ss): 0:23.22 . Size: 336
test_map2_O2:  Elapsed (wall clock) time (h:mm:ss or m:ss): 0:00.12 . Size: 220
test_map1_O3:  Elapsed (wall clock) time (h:mm:ss or m:ss): 0:23.98 . Size: 336
test_map2_O3:  Elapsed (wall clock) time (h:mm:ss or m:ss): 0:00.14 . Size: 220
test_map1_O0:  	Maximum resident set size (kbytes): 3644
test_map2_O0:  	Maximum resident set size (kbytes): 1440
test_map1_O2:  	Maximum resident set size (kbytes): 3292
test_map2_O2:  	Maximum resident set size (kbytes): 1440
```
