#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <utility>
#include <ctime>
#include <cstdlib>
#include "Dict.h"
#include "State.h"
#include "../game/Game.h"

class Bot : public Player {
	public:
		Bot(string name_str, int id);
		//Bot(string name_str, double rand_move_pct);

		void reset();
		//Pre-condition: none
		//Post-condition: empties states from training round,
		//resets its score and ball count

		void add_state(string state);
		//Pre-condition: takes an input state
		//Post-condition: stores state to track the current training round

		void feedReward(State &state, double reward);
		//Pre-condition: takes a double reward representing the outcome of the next state
		//Post-condition: backpropagates the reward to the stored game states, updating
		//its policy dictionary accordingly

		Move chooseMove(State &state, unordered_map<string, Move> options);
		//Pre-condition: takes a dictionary of moves and corresponding game states
		//Post-condition: chooses a move randomly or the best move according to its policy
		//the proportion of random moves is the Bot's explore_rate


		unordered_map<string, double> getStateVals() const;
		//Pre-condition: none
		//Post-condition: returns stateVals dictionary

		vector<string> getStates() const;
		//Pre-condition: none
		//Post-condition: returns states 2d vector

		void readPolicy(string filename);
		//Pre-condition: takes filename of policy
		//Post-condition: sets state_vals to policy in filename

		string rotate(string state);
		//Pre-condition: takes string state
		//Post-condition: returns state rotated by 90deg about z-axis

		string name;
 		bool quiet = false;
 
	private:
		double alpha = 0.2; //learning rate
		double gamma = 0.9; //decay rate
		double explore_rate = 0.3; //random move rate

		unordered_map<string, double> state_vals;
		vector<string> states; //tracks training round
		unordered_map<int, int> rotate_indices;
};
