../cxxtest-3.10.1/cxxtestgen.pl --error-printer -o export.cpp ./export.h
g++ -g --std=c++0x -m32 -L ../../triangle/extern/v8 -I ../cxxtest-3.10.1/ -I ../src/ -I ../../triangle/extern/v8/include -o ./export ./export.cpp -lv8 -lpthread

../cxxtest-3.10.1/cxxtestgen.pl --error-printer -o converters.cpp ./converters.h
g++ -g --std=c++0x -m32 -L ../../triangle/extern/v8 -I ../cxxtest-3.10.1/ -I ../src/ -I ../../triangle/extern/v8/include -o ./converters ./converters.cpp -lv8 -lpthread

../cxxtest-3.10.1/cxxtestgen.pl --error-printer -o typeinfo.cpp ./typeinfo.h
g++ -g --std=c++0x -m32 -L ../../triangle/extern/v8 -I ../cxxtest-3.10.1/ -I ../src/ -I ../../triangle/extern/v8/include -o ./typeinfo ./typeinfo.cpp -lv8 -lpthread
