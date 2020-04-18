#!/bin/bash
f1() {
cat > $1 << EOF
#include <map>
#include <string>

using namespace std;

struct __metric {
    unsigned int id;
    std::string name;
    std::string help;
    std::map<std::string, std::string> tags;
};

using metric_tags = std::map<std::string, std::string>;
__metric counter_metric_map[] {
EOF
}

f2() {
cat > $1 << EOF
struct __metric {
    unsigned int id;
    char * name;
    char * help;
    char * tags;
};

__metric counter_metric_map[] {
EOF
}

f1r() {
for i in `seq 1 $2` ; do
echo '{ 1 , "hello1", "world1" , metric_tags { { "tag1k" , "tag1v"} } },';
echo '{ 2 , "hello2", "world2" , metric_tags {} },';
done >> $1
}

f2r() {
for i in `seq 1 $2` ; do
echo '{ 1 , (char *)"hello1", (char *)"world1" , (char *)"{{\"tag1k\",\"tag1v\"}}" },';
echo '{ 2 , (char *)"hello2", (char *)"world2" , (char *)"{}" },';
done >> $1
}


fend() {
cat >> $1 << EOF
};

int main() {
    return 0;
}
EOF
}

f1 test_map1.cpp
f2 test_map2.cpp

NR=1000
f1r test_map1.cpp $NR
f2r test_map2.cpp $NR
fend test_map1.cpp
fend test_map2.cpp

for O in 0 2 3 ; do
  for i in 1 2 ; do
    echo -n test_map"$i"_O$O":  " 
    echo -n `/usr/bin/time --verbose g++ test_map$i.cpp -O$O -o test_map"$i"_O$O 2>&1 | grep "wall clock"`
    du test_map"$i"_O$O | awk '{print " . Size: "$1}'
  done
done

#ls -l tuple_test[12345]_O[023]

for O in 0 2 ; do
  for i in 1 2 ; do
    echo -n test_map"$i"_O$O":  "
    /usr/bin/time --verbose ./test_map"$i"_O$O 2>&1 | grep "Maximum resident set size"
  done
done

