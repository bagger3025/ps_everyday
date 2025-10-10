PROBLEM=g

all: e_$(PROBLEM)
e_$(PROBLEM): $(PROBLEM).cpp
	g++ -O2 -std=c++17 -o $@ $<

ref: w_$(PROBLEM)
w_$(PROBLEM): $(PROBLEM)_ref.cpp
	g++ -O2 -std=c++17 -o $@ $<


%: %.cpp
	g++ -O2 -std=c++17 -o $@ $< -Wall

.PHONY: all ref
