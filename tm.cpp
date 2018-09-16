#include "tm.h"

turing_machine::turing_machine(std::set<State> s, std::vector<transition> T)
	{ states = s; transitions = T; initial = 0; states.insert(initial); accepting = 1; current = initial; tape_empty(); }
turing_machine::turing_machine(std::set<State> s)
	{ states = s; initial = 0; states.insert(initial); accepting = 1; current = initial; tape_empty(); }
turing_machine::turing_machine()
	{ initial = 0; states.insert(initial); accepting = 1; current = initial; tape_empty(); }
void turing_machine::tape_empty()
	{ pos = 0; for (int i=0; i<TAPESIZE; ++i) tape[i] = delta; }
void turing_machine::states_add(State s) 
	{ states.insert(s); }
void turing_machine::transitions_add(transition t)
	{ if (transition_check(t)) transitions.push_back(t); }
void turing_machine::transitions_add(std::vector<transition> T)
	{ for (auto t : T) transitions_add(t); }
void turing_machine::states_mark_initial(State s)
	{ auto search = states.find(s); if (search != states.end()) initial = *search; }
void turing_machine::tape_change(std::string input)
	{ tape_empty(); for (unsigned i=0; i < input.length(); ++i) tape[i+1] = input[i]; }

void turing_machine::tape_move(char d) {
	switch(d) {
		case 'L': if (pos > 0) --pos; break;
		case 'R': if (pos < TAPESIZE-1) ++pos; break;
		default: break;
	}
}

std::string turing_machine::run() {
	current = 0; pos = 0;
	bool finished = false;
	while (!finished) step(finished);
	if (current == accepting) return "accepted.";
	else return "rejected.";
}

std::string turing_machine::run_stepwise(std::ostream & out) {
	current = 0; pos = 0;
	bool finished = false;
	while (!finished) {
		tape_print(out);
		for (int i=0; i < pos; ++i) out << " ";
		out << '^' << std::endl;
		step(finished);
	}
	if (current == accepting) return "accepted.";
	else return "rejected.";
}

void turing_machine::step(bool & finished) {
	for (auto T : transitions) {
		if (T.current == current && T.read == tape[pos]) {
			current = T.next;
			tape[pos] = T.change;
			tape_move(T.direction);
			return;
		}
	}
	finished = true;
}

bool turing_machine::transition_check(transition t) {
	switch (t.direction) {
		case 'L': case 'R': case 'S': break;
		default: return false;
	}
	if ( states.find(t.current) == states.end()
		|| (states.find(t.next) == states.end() && t.next != accepting) )
		return false;
	return true;
}

void turing_machine::transitions_print(std::ostream & str) {
	str << std::endl;
	for (auto T : transitions) {
		str << T.current << " -> " << T.next << std::endl;
		str << "When reading '" << T.read
			<< "' change it to '" << T.change
			<< "' and move: " << T.direction << std::endl;
		str << std::endl;
	}
}

void turing_machine::tape_print(std::ostream & str) {
	int deltacount = 0;
	int i = 0;
	while (deltacount < 5 && i < TAPESIZE) {
		if (i >= 0 && i < TAPESIZE) {
			if (tape[i] == delta) ++deltacount;
			str << tape[i];
			++i;
		}
	}
	str << std::endl;
}

void turing_machine::print(std::ostream & str) {
	str << std::endl;
	str << "States: { ";
	for (auto s : states) str << s << ", "; 
	str << "}" << std::endl;
	str << "Initial: " << initial << std::endl;
	str << "Accepting: " << accepting << std::endl;
	str << transitions.size() << " transitions." << std::endl;
	str << "Current: " << current << std::endl;
	str << "On tape: " << tape[pos] << std::endl;
}