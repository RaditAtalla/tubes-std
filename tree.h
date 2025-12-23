#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

#include "bits/stdc++.h"

using namespace std;

struct infotype {
    double startTime;
    double endTime;
    string eventName;
};

typedef struct Node* adrNode;

struct Node {
    adrNode left;
    adrNode right;
    infotype info;
};
// primitive tree methods
void createTree(adrNode& root);
adrNode createNode(double startTime, double endTime, string eventName);
void insertNode(adrNode& root, adrNode node);
void displayTree(adrNode root);
void updateNode(adrNode& root, string oldName, string newName,
                double newStart, double newEnd);
adrNode deleteNode(adrNode& root, double time);
void deleteNodeByName(adrNode &root, string eventName);
adrNode searchNode(adrNode root, string eventName);

// additional methods
int totalEvents(adrNode root);
void printTime(double decimalTime);
adrNode getMinValue(adrNode& root);
bool isAvailable(adrNode root, double start, double end);

#endif // TREE_H_INCLUDED
