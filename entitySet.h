#pragma once
class entitySet
{
public:
	const char* walkFilePath;
	int maxWalkIndex;
	double walkTimeDelay;
	entitySet() {
		walkFilePath = "";
		maxWalkIndex = 0;
		walkTimeDelay = 1;
	}
	entitySet(const char* walkFilePath, int maxWalkIndex, double walkTimeDelay) {
		entitySet::walkFilePath = walkFilePath;
		entitySet::maxWalkIndex = maxWalkIndex;
		entitySet::walkTimeDelay = walkTimeDelay;
	}
};

