#pragma once

#include "tm.h"

namespace turing_machines {
	/*
		When building turing machine templates, remember:
			initial state = 0,
			accepting state = 1.
			You can use any other number for naming your States.

		Also don't forget to make transition(0, STATE, delta, delta, 'R') to go to the 2nd character of the tape
		and make a transition to the accepting state
	*/

	// when the tape contains a unary number (1 = 1, 2 = 11, 4 = 1111, 8 = 11111111, etc)
	// returns the unary number that's half of the input (rounded down)
	inline turing_machine divide_by_two() {
		turing_machine T( { 2, 3, 4, 5, 6, 7, 8 } );
		T.transitions_add(transition(0, 2, delta, delta, 'R'));
		T.transitions_add(transition(2, 3, '1', 'X', 'R'));
		T.transitions_add(transition(2, 8, delta, delta, 'L'));
		T.transitions_add(transition(3, 4, '1', '1', 'R'));
		T.transitions_add(transition(3, 7, delta, delta, 'L'));
		T.transitions_add(transition(4, 4, '1', '1', 'R'));
		T.transitions_add(transition(4, 5, delta, delta, 'L'));
		T.transitions_add(transition(5, 6, '1', delta, 'L'));
		T.transitions_add(transition(6, 6, '1', '1', 'L'));
		T.transitions_add(transition(6, 2, 'X', 'X', 'R'));
		T.transitions_add(transition(7, 8, 'X', delta, 'L'));
		T.transitions_add(transition(8, 1, delta, delta, 'S'));
		T.transitions_add(transition(8, 8, 'X', '1', 'L'));
		return T;
	}

	// accepts all words in the language L = { xx | x = (a, b)* }
	inline turing_machine is_double_word() {
		turing_machine T( { 2, 3, 4, 5, 6, 7, 8, 9, 10 } );
		T.transitions_add(transition(0, 2, delta, delta, 'R'));
		T.transitions_add(transition(2, 3, 'a', 'A', 'R'));
		T.transitions_add(transition(2, 3, 'b', 'B', 'R'));
		T.transitions_add(transition(2, 1, delta, delta, 'S'));
		T.transitions_add(transition(2, 6, 'A', 'A', 'L'));
		T.transitions_add(transition(2, 6, 'B', 'B', 'L'));
		T.transitions_add(transition(3, 3, 'a', 'a', 'R'));
		T.transitions_add(transition(3, 3, 'b', 'b', 'R'));
		T.transitions_add(transition(3, 4, delta, delta, 'L'));
		T.transitions_add(transition(3, 4, 'A', 'A', 'L'));
		T.transitions_add(transition(3, 4, 'B', 'B', 'L'));
		T.transitions_add(transition(4, 5, 'a', 'A', 'L')); 
		T.transitions_add(transition(4, 5, 'b', 'B', 'L'));
		T.transitions_add(transition(5, 2, 'A', 'A', 'R'));
		T.transitions_add(transition(5, 2, 'B', 'B', 'R'));
		T.transitions_add(transition(5, 5, 'a', 'a', 'L'));
		T.transitions_add(transition(5, 5, 'b', 'b', 'L'));
		T.transitions_add(transition(6, 6, 'A', 'a', 'L'));
		T.transitions_add(transition(6, 6, 'B', 'b', 'L'));
		T.transitions_add(transition(6, 7, delta, delta, 'R'));
		T.transitions_add(transition(7, 8, 'a', 'A', 'R'));
		T.transitions_add(transition(7, 9, 'b', 'B', 'R'));
		T.transitions_add(transition(7, 1, delta, delta, 'S'));
		T.transitions_add(transition(8, 8, delta, delta, 'R'));
		T.transitions_add(transition(8, 8, 'a', 'a', 'R'));
		T.transitions_add(transition(8, 8, 'b', 'b', 'R'));
		T.transitions_add(transition(8, 10, 'A', delta, 'L'));
		T.transitions_add(transition(9, 9, delta, delta, 'R'));
		T.transitions_add(transition(9, 9, 'a', 'a', 'R'));
		T.transitions_add(transition(9, 9, 'b', 'b', 'R'));
		T.transitions_add(transition(9, 10, 'B', delta, 'L'));
		T.transitions_add(transition(10, 7, 'A', 'A', 'R'));
		T.transitions_add(transition(10, 7, 'B', 'B', 'R'));
		T.transitions_add(transition(10, 10, delta, delta, 'L'));
		T.transitions_add(transition(10, 10, 'a', 'a', 'L'));
		T.transitions_add(transition(10, 10, 'b', 'b', 'L'));
		return T;
	}
}