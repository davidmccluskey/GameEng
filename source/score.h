#pragma once
using namespace std;

class Score {
private:
	float _score = -1000;
public:
	float getScore();
	void setScore(float score);
	void resetScore();
};