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
void deleteNodeByName(adrNode &root, string eventName);
adrNode searchNode(adrNode root, string eventName);

// additional methods
int totalEvents(adrNode root);

#endif // TREE_H_INCLUDED
