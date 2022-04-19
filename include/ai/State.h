#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

class State {
	public:
		bool has_key(string);
		double get(string, int);
		void set(string, double, int);
		int size();
		void readPolicy();
		void savePolicy();
	private:
		unordered_map<string, double> state_vals; //move policy; matches game states to its value
};
