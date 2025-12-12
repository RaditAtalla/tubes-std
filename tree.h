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

void createTreef(adrNode& root);
adrNode createNode(string eventName, int startTime, int endTime);
void insertNode(adrNode& root, adrNode p);
void deleteNode(adrNode& root, adrNode p);
void displayTree(adrNode root);
adrNode search(string eventName);
void nextEvent(adrNode root, int time);
void freeTime(adrNode root);


#endif // TREE_H_INCLUDED
