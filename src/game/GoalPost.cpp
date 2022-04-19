#include "../../include/game/GoalPost.h"
#include "../../include/game/utility.h"
#include "../../include/game/GameParams.h"

GoalPost::GoalPost(int size) : size(size) {}

int GoalPost::pop() {
	//player id: 1, 2. if empty return 0
	if (post.size() == 0) {
		return 0;
	}

	int playerID = post[0];
	post.erase(post.begin());
	return playerID;
}

bool GoalPost::push(int id) {
	if(!inRange(post.size(), SIZE)) {
		return false;
	}
	post.push_back(id);
	return true;
}

vector<int> GoalPost::getPost() const {
	return post;
}
