PROBLEM=g

all: ${PROBLEM}
${PROBLEM}: ${PROBLEM}.cpp
	g++ -O2 -std=c++17 -Wall -o $@ $<

ref: ref_${PROBLEM}
ref_${PROBLEM}: ${PROBLEM}_ref.cpp
	g++ -O2 -std=c++17 -Wall -o $@ $<
