#include "score.h"

float Score::getScore()
{
	return _score;
}

void Score::setScore(float score)
{
	_score += score;
}
