#pragma once

#include <set>
#include <vector>
#include <string>
#include <iostream>

typedef unsigned int State;
struct transition {
	transition() {}
	transition(State curr, State n, char r, char c, char d)
		{ current = curr; next = n; read = r; change = c; direction = d; }
	State current, next;
	char direction;
	char read;
	char change;
};

#define TAPESIZE 1000
#define delta '_'

class turing_machine {
	public:
		turing_machine();
		turing_machine(std::set<State> s);
		turing_machine(std::set<State> s, std::vector<transition> T);
		std::string run();
		std::string run_stepwise(std::ostream & out);
		void tape_change(std::string input);
		void tape_empty();
		void tape_move(char d);
		void tape_print(std::ostream & str);
		void states_add(State s);
		void states_mark_initial(State s);
		void transitions_add(transition t);
		void transitions_add(std::vector<transition> T);
		void transitions_print(std::ostream & str);
		void print(std::ostream & str);
	private:
		bool transition_check(transition t);
		void step(bool & finished);
	private:
		char tape[TAPESIZE];
		int pos;
		std::set<State> states;
		State initial;
		State accepting;
		State current;
		std::vector<transition> transitions;
};