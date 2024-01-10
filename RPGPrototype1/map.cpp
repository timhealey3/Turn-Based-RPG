#include <iostream>
#include <cstdlib>
#include <random>
#include "map.h"
// TODO implement Binary Space Partioning 
// BSP tree carves space into sets of succesive half space

// BSP is built by making Binary Tree where each node has a plane

// start with rectangular dungeon
// choose random direction and split into two sub dungeons
// split until smallest has same size we want
static const int MIN_LEAF_SIZE = 6;

struct Node {
	int x, y, width, height;
	Node* leftChild;
	Node* rightChild;

	Node(int _x, int _y, int _width, int _height)
		: x(_x), y(_y), width(_width), height(_height), leftChild(nullptr), rightChild(nullptr) {}
};


int randomNumber(int min, int max) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(min, max);
	return dis(gen);
}

bool partitionNode(Node* node) {
	if (node->leftChild != nullptr || node->rightChild != nullptr) {
		return false; // already split
	}

	// determine direction of split
	// if width > 25% larger than height, split vertically
	// if height is > 25% larger than width, split horizontally
	// otherwise... split randomly
	int randomValue = randomNumber(0, 100);
	bool splitH = randomValue > 50; // Assuming 0-99 range corresponds to true/false

	if (node->width > node->height && node->width / node->height > 1.25) {
		splitH = false;
	}
	else if (node->height > node->width && node->height / node->width >= 1.25) {
		splitH = true;
	}
	// max height or width for either one
	int max = (splitH ? node->height : node->width) - MIN_LEAF_SIZE;
	// if room too small to split
	if (max <= MIN_LEAF_SIZE) {
		return false;
	}
	// random number to split at
	int split = randomNumber(MIN_LEAF_SIZE, max);
	// create left and right children BASED ON SPLIT
	if (splitH) {
		node->leftChild = new Node(node->x, node->y, split, node->height);
		node->rightChild = new Node(node->x, node->y, split, node->height);
	}
	// TODO delete nodes when dont need them
	return true;
}

