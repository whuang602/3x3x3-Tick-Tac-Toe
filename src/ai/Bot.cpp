#include "../../include/ai/Bot.h"
#include "../../include/ai/State.h"

using namespace std;

Bot::Bot(string name_str, int id): Player(id){
	name = name_str;
	for(int i = 0; i < 27; i++){
		this->rotate_indices[i] =
			((i % 9) % 3) * 9 +
			((i / 3) % 3) * 3 +
			(2 - (i / 9));
	}
}

void Bot::reset(){
	states = {};
	playerBallCount = 0;
	score = 0;
}

void Bot::add_state(string state){
	states.push_back(state);
}

vector<string> Bot::getStates() const {
	return states;
}

void Bot::feedReward(State &stateDict, double reward) {
	string state;
	for (int i = states.size() - 1; i >= 0; i--) {
		state = states[i];

		//cout << "updating dict entry" << endl;
		if(!stateDict.has_key(state)){
			stateDict.set(state, 0, playerGetId());
		}

		double currentVal = stateDict.get(state, playerGetId());
		double newVal = currentVal + alpha * (gamma * reward - currentVal);

		stateDict.set(state, newVal, playerGetId());
		reward = newVal;
	}
}

Move Bot::chooseMove(State &stateDict, unordered_map<string, Move> possible_moves){
	// if policy is empty then do random:
	srand(time(0));

	if(possible_moves.size() == 0){
		cerr << "no possible moves ya dingus" << endl;
		exit(1);
	}

	if(stateDict.size() == 0 || (rand() % 100) <= explore_rate * 100){
		unordered_map<string, Move>::iterator item = possible_moves.begin();
		
		int move_index = rand() % possible_moves.size();
		advance(item, move_index);

		return item->second;
	}

	string g_key;
	bool foundValue = false;

	for(pair<string, Move> state_move : possible_moves){
		if(stateDict.has_key(state_move.first) &&
			(!foundValue ||
			stateDict.get(state_move.first, playerGetId()) >
			stateDict.get(g_key, playerGetId()))) {

			g_key = state_move.first;	
			foundValue = true;
		}
	}
	return possible_moves[g_key];
}


unordered_map<string, double> Bot::getStateVals() const {
	return state_vals;	
}

string Bot::rotate(string state){
	string rotated = state;
	for(int i = 0; i < 27; i++){
		rotated[this->rotate_indices[i]] = state[i];
	}
	return rotated;
}
