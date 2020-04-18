This tests show the amount of code generated with:
* vector of tuple (explicitly created) of strings
* vector of tuple (implicitly created) of strings
* vector of tuple (implicitly created) of const strings
* vector of tuple (implicitly created) of char pointers
* array of structs of char pointers

Size is checked at various optimization level.

It also run some the binaries with /usr/bin/time to display how much memory is being used

An example:
```
$ sh make_tuple_tests.sh 
tuple_test1_O0:  Elapsed (wall clock) time (h:mm:ss or m:ss): 0:02.75 . Size: 436
tuple_test2_O0:  Elapsed (wall clock) time (h:mm:ss or m:ss): 0:01.04 . Size: 308
tuple_test3_O0:  Elapsed (wall clock) time (h:mm:ss or m:ss): 0:01.15 . Size: 308
tuple_test4_O0:  Elapsed (wall clock) time (h:mm:ss or m:ss): 0:00.75 . Size: 436
tuple_test5_O0:  Elapsed (wall clock) time (h:mm:ss or m:ss): 0:00.24 . Size: 428
tuple_test1_O2:  Elapsed (wall clock) time (h:mm:ss or m:ss): 0:04.72 . Size: 364
tuple_test2_O2:  Elapsed (wall clock) time (h:mm:ss or m:ss): 0:05.51 . Size: 248
tuple_test3_O2:  Elapsed (wall clock) time (h:mm:ss or m:ss): 0:05.64 . Size: 248
tuple_test4_O2:  Elapsed (wall clock) time (h:mm:ss or m:ss): 0:00.98 . Size: 428
tuple_test5_O2:  Elapsed (wall clock) time (h:mm:ss or m:ss): 0:00.35 . Size: 428
tuple_test1_O3:  Elapsed (wall clock) time (h:mm:ss or m:ss): 0:07.34 . Size: 428
tuple_test2_O3:  Elapsed (wall clock) time (h:mm:ss or m:ss): 0:05.12 . Size: 248
tuple_test3_O3:  Elapsed (wall clock) time (h:mm:ss or m:ss): 0:06.04 . Size: 248
tuple_test4_O3:  Elapsed (wall clock) time (h:mm:ss or m:ss): 0:01.04 . Size: 428
tuple_test5_O3:  Elapsed (wall clock) time (h:mm:ss or m:ss): 0:00.35 . Size: 428
tuple_test1_O0:  	Maximum resident set size (kbytes): 3552
tuple_test2_O0:  	Maximum resident set size (kbytes): 3408
tuple_test3_O0:  	Maximum resident set size (kbytes): 3216
tuple_test4_O0:  	Maximum resident set size (kbytes): 3008
tuple_test5_O0:  	Maximum resident set size (kbytes): 1616
tuple_test1_O2:  	Maximum resident set size (kbytes): 3448
tuple_test2_O2:  	Maximum resident set size (kbytes): 3304
tuple_test3_O2:  	Maximum resident set size (kbytes): 3044
tuple_test4_O2:  	Maximum resident set size (kbytes): 2984
tuple_test5_O2:  	Maximum resident set size (kbytes): 1592
```

A second example with slightly later strings:
```
$ sh make_tuple_tests.sh 
tuple_test1_O0:  Elapsed (wall clock) time (h:mm:ss or m:ss): 0:02.46 . Size: 620
tuple_test2_O0:  Elapsed (wall clock) time (h:mm:ss or m:ss): 0:01.28 . Size: 496
tuple_test3_O0:  Elapsed (wall clock) time (h:mm:ss or m:ss): 0:01.28 . Size: 496
tuple_test4_O0:  Elapsed (wall clock) time (h:mm:ss or m:ss): 0:00.72 . Size: 616
tuple_test5_O0:  Elapsed (wall clock) time (h:mm:ss or m:ss): 0:00.26 . Size: 608
tuple_test1_O2:  Elapsed (wall clock) time (h:mm:ss or m:ss): 0:04.21 . Size: 548
tuple_test2_O2:  Elapsed (wall clock) time (h:mm:ss or m:ss): 0:05.15 . Size: 432
tuple_test3_O2:  Elapsed (wall clock) time (h:mm:ss or m:ss): 0:05.22 . Size: 432
tuple_test4_O2:  Elapsed (wall clock) time (h:mm:ss or m:ss): 0:01.18 . Size: 612
tuple_test5_O2:  Elapsed (wall clock) time (h:mm:ss or m:ss): 0:00.39 . Size: 608
tuple_test1_O3:  Elapsed (wall clock) time (h:mm:ss or m:ss): 0:07.25 . Size: 612
tuple_test2_O3:  Elapsed (wall clock) time (h:mm:ss or m:ss): 0:06.81 . Size: 432
tuple_test3_O3:  Elapsed (wall clock) time (h:mm:ss or m:ss): 0:05.12 . Size: 432
tuple_test4_O3:  Elapsed (wall clock) time (h:mm:ss or m:ss): 0:00.96 . Size: 612
tuple_test5_O3:  Elapsed (wall clock) time (h:mm:ss or m:ss): 0:00.34 . Size: 608
tuple_test1_O0:  	Maximum resident set size (kbytes): 4612
tuple_test2_O0:  	Maximum resident set size (kbytes): 4468
tuple_test3_O0:  	Maximum resident set size (kbytes): 4532
tuple_test4_O0:  	Maximum resident set size (kbytes): 2996
tuple_test5_O0:  	Maximum resident set size (kbytes): 1524
tuple_test1_O2:  	Maximum resident set size (kbytes): 4604
tuple_test2_O2:  	Maximum resident set size (kbytes): 4292
tuple_test3_O2:  	Maximum resident set size (kbytes): 4388
tuple_test4_O2:  	Maximum resident set size (kbytes): 2980
tuple_test5_O2:  	Maximum resident set size (kbytes): 1564
```
