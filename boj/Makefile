PROBLEM=29765


all: e_${PROBLEM}
e_%: files/%.cpp
	g++ -O2 -std=c++17 -o $@ $< -Wall

ref: w_${PROBLEM}
w_%: files/%_ref.cpp
	g++ -O2 -std=c++17 -o $@ $< -Wall

.PHONY: all ref
