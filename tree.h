#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

#include <iostream>

using namespace std;

struct infotype {
    int startTime;
    int endTime;
    string eventName;
};

typedef struct Node* adrNode;

struct Node {
    adrNode left;
    adrNode right;
    infotype info;
};

// basic methods
void createTree(adrNode& root);
adrNode createNode(int startTime, int endTime, string eventName);
void insertNode(adrNode& root, adrNode node);
void displayTree(adrNode root);
void updateNode(adrNode& root, adrNode& node, string eventName, int startTime, int endTime);
void freeNode(adrNode& node);
adrNode searchNode(adrNode root, string eventName);

// additional methods
int totalEvents(adrNode root);

#endif // TREE_H_INCLUDED
