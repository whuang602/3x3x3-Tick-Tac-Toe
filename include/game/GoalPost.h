#pragma once

#include <vector>
using namespace std;

class GoalPost {
	public:
		GoalPost(int size);
		int pop(); //player id: 1, 2. if empty return 0
		bool push(int id);
		vector<int> getPost() const;
	private:
		vector<int> post;
		const int size;
};
