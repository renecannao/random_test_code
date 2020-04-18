#!/bin/bash

f1() {
cat > $1 << EOF
#include <tuple>
#include <vector>
#include <string>

using namespace std;
EOF
}

#strings
f1s() {
echo 'vector<tuple<string,string>> myvec = vector<tuple<string,string>> {' >> $1
}

#strings const
f1cs() {
echo 'vector<tuple<const string,const string>> myvec = vector<tuple<const string,const string>> {' >> $1
}

# char pointers
f1c() {
echo 'vector<tuple<char *,char *>> myvec = vector<tuple<char *,char *>> {' >> $1
}

f1sc() {
cat >> $1 << EOF
typedef struct {
    char *p0;
    char *p1;
} two_char_ptrs;

two_char_ptrs myvec[] = {
EOF
}

f2() {
cat >> $1 << EOF
};

int main() {
    return 0;
}
EOF
}

f3() {
for i in `seq 1 $2`; do
 # echo "make_tuple(\"hello$i\",\"world$i\"),"
  echo "make_tuple(\"hello_hello_hello_hello_$i\",\"world_world_world_world_$i\"),"
done >> $1
}
 
f4() {
for i in `seq 1 $2`; do
#  echo "{\"hello$i\",\"world$i\"},"
  echo "{\"hello_hello_hello_hello_$i\",\"world_world_world_world_$i\"},"
done >> $1
}

f5() {
for i in `seq 1 $2`; do
#  echo "{(char *)\"hello$i\",(char *)\"world$i\"},"
  echo "{(char *)\"hello_hello_hello_hello_$i\",(char *)\"world_world_world_world$i\"},"
done >> $1
}


VS=5000
for i in 1 2 3 4 5; do f1 tuple_test$i.cpp ; done
for i in 1 2 ; do f1s tuple_test$i.cpp ; done
f1cs tuple_test3.cpp
f1c tuple_test4.cpp
f1sc tuple_test5.cpp
f3 tuple_test1.cpp $VS 
for i in 2 3 ; do f4 tuple_test$i.cpp $VS ; done
for i in 4 5 ; do f5 tuple_test$i.cpp $VS ; done
for i in 1 2 3 4 5; do f2 tuple_test$i.cpp ; done

for O in 0 2 3 ; do
  for i in 1 2 3 4 5 ; do
    echo -n tuple_test"$i"_O$O":  "	
    echo -n `/usr/bin/time --verbose g++ tuple_test$i.cpp -O$O -o tuple_test"$i"_O$O 2>&1 | grep "wall clock"`
	du tuple_test"$i"_O$O | awk '{print " . Size: "$1}'
  done
done

#ls -l tuple_test[12345]_O[023]

for O in 0 2 ; do
  for i in 1 2 3 4 5 ; do
    echo -n tuple_test"$i"_O$O":  "
	/usr/bin/time --verbose ./tuple_test"$i"_O$O 2>&1 | grep "Maximum resident set size"
  done
done

