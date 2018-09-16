#include <iostream>
#include <sstream>
#include "tm.h"
#include "turing_machines.h"

State convert_char_to_state(char c) {
	std::stringstream strv; strv << c;
	State s; strv >> s;
	return s;
}

turing_machine menu_choose_template(std::istream & inStr, std::ostream & out) {
	std::string in;
	out << "Enter a number corresponding to a turing machine: " << std::endl
		<< "1) Divide by two" << std::endl
		<< "2) L = { xx | x = (a, b)* }" << std::endl;
	getline(inStr, in, '\n');
	switch (in[0]) {
		case '1': return turing_machines::divide_by_two();
		case '2': return turing_machines::is_double_word();
		default: return turing_machine();
	}
}

transition menu_maketransition(std::istream & inStr, std::ostream & out) {
	transition T;
	std::string in;
	out << "From state: ";
	getline(inStr, in, '\n');
	T.current = convert_char_to_state(in[0]);
	out << "To state: ";
	getline(inStr, in, '\n');
	T.next = convert_char_to_state(in[0]);
	out << "When reading: ";
	getline(inStr, in, '\n');
	T.read = in[0];
	out << "Change to: ";
	getline(inStr, in, '\n');
	T.change = in[0];
	out << "And move position (L/R/S): ";
	getline(inStr, in, '\n');
	T.direction = in[0];
	return T;
}

void menu_help(std::ostream & out) {
	out << std::endl
		<< "All commands and a short description:" << std::endl
		<< "tms: \t shows a menu to load one of the pre-made turing machines" << std::endl
		<< "add: \t adds a state to the turing machine (without transitions)" << std::endl
		<< "trans <current state> <next state> <read old character> <changed new character> <direction (L/R/S)>: \t quickly add a transition" << std::endl
		<< "transition: \t shows a help menu to add a transition" << std::endl
		<< "transitions: \t prints all existing transitions" << std::endl
		<< "changetape <input>: \t put input on the tape, excluding left and right side empty characters" << std::endl
		<< "print: \t prints tape" << std::endl
		<< "show: \t prints turing machine" << std::endl
		<< "run: \t runs turing machine from initial state and from the beginning of the tape" << std::endl
		<< "step: \t runs turing machine and shows every step" << std::endl
		<< "help: \t shows this help menu" << std::endl
		<< "end: \t quits" << std::endl
		<< std::endl;
}

void menu(std::istream & inStr, std::ostream & out) {
	turing_machine TM;
	out << "This is a program where you can load, modify and run turing machines. "
		<< "type 'help' for a list of commands." << std::endl;
	while (true) {
		std::string in;
		getline(inStr, in, '\n');
		// available template turing machines
		if (in.substr(0, 4) == "tms") TM = menu_choose_template(inStr, out);
		// change turing machine
		else if (in.substr(0, 4) == "add ") TM.states_add(convert_char_to_state(in[4]));
		else if (in.substr(0, 6) == "trans ") TM.transitions_add(transition(in[6], in[8], in[10], in[12], in[14]));
		else if (in.substr(0, 16) == "transitions") TM.transitions_print(out);
		else if (in.substr(0, 10) == "transition") TM.transitions_add(menu_maketransition(inStr, out));
		// change tape, print tape, print machine, run machine
		else if (in.substr(0, 11) == "changetape ") TM.tape_change(in.substr(11));
		else if (in.substr(0, 5) == "print") TM.tape_print(out);
		else if (in.substr(0, 4) == "show") TM.print(out);
		else if (in.substr(0, 3) == "run") out << "The tape is " << TM.run() << std::endl;
		else if (in.substr(0, 4) == "step") out << "The tape is " << TM.run_stepwise(out) << std::endl;
		// help, end or error
		else if (in.substr(0,4) == "help") menu_help(out);
		else if (in.substr(0,3) == "end") return;
		else if (!in.empty()) out << "Error: invalid input" <<std::endl;
	}
}

int main(int argc, char** argv) {
    menu(std::cin, std::cout);
    return 0;
}
