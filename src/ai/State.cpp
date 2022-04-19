#include "../../include/ai/State.h"
#include "fstream"
#include <string>
#include <iostream>
#include <regex>
#include <sstream>

string invert(string state) {
    for (int i = 0; i < state.size(); ++i) {
        if (state[i] == '1') {
            state[i] = '2';
        }
        else if (state[i] == '2') {
            state[i] = '1';
        }
    }
    return state;
}

bool State::has_key(string state) {
    return state_vals.find(state) != state_vals.end() 
        || state_vals.find(invert(state)) != state_vals.end();
}

double State::get(string state, int player = 1) {
    if (player == 2) {
        state = invert(state);
    }

    return state_vals[state];
}

void State::set(string state, double val, int player) {
    if (player == 2) {
        state = invert(state);
    }
    state_vals[state] = val;
}

int State::size() {
    return state_vals.size();
}

void State::savePolicy() {
	std::cout << "saving " << state_vals.size() << " state-val pairs.\n";
	ofstream file("src/ai/policy.txt");

   	file << state_vals.size() << endl;
	for(pair<std::string, double> sv_pair : state_vals){
		file << sv_pair.second << " ";
		file << sv_pair.first << endl;
	}

	file.close();
}

void State::readPolicy(){
	ifstream file("src/ai/policy.txt");
	double dummy_val;
	string dummy_state;
	int pair_count;
	file >> pair_count;

	for(int i = 0; i < pair_count; i++){
		file >> dummy_val;
		file >> dummy_state;

		state_vals[dummy_state] = dummy_val;
	}
	file.close();
}
