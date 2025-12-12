#include "tree.h"

void createTreef(adrNode& root) {
    root = nullptr;
}
adrNode createNode(string eventName, int startTime, int endTime) {
    adrNode p = new Node;
    p->info.eventName = eventName;
    p->info.startTime = startTime;
    p->info.endTime = endTime;
    p->right = nullptr;
    p->left = nullptr;

    return p;
}
void insertNode(adrNode& root, adrNode p) {
    if(root = nullptr) {
        root = p;
    } else if(p->info.startTime < root->info.startTime && p->info.endTime < root->info.startTime) {
        insertNode(root->left, p);
    } else if(p->info.startTime > root->info.startTime && p->info.startTime > root->info.endTime ) {
        insertNode(root->right, p);
    } else {
        cout << "@ Waktu bertabrakan!" << endl;
    }
}
void deleteNode(adrNode& root, adrNode& p) {
    p->info.endTime = 0;
    p->info.startTime = 0;
    p->info.eventName = "";
}
void displayTree(adrNode root) {
    if(root != nullptr) {
        displayTree(root->left);
        cout << "Kegiatan : " << root->info.eventName << endl;
        cout << "Mulai : " << root->info.startTime<< endl;
        cout << "Selesai : " << root->info.endTime << endl;
        displayTree(root->right);
    }
}
adrNode search(adrNode root, string eventName) {
    if(root == nullptr) {
        return nullptr;
    } else if (root->info.eventName == eventName) {
        return root
    } else {
        search(root->left);
        search(root->right);
    }
}
void nextEvent(adrNode root, int time) {
    if(root->right == nullptr && root->info.startTime > time) {
        cout << "Kegiatan : " << root->info.eventName << endl;
        cout << "Mulai : " << root->info.startTime<< endl;
        cout << "Selesai : " << root->info.endTime << endl;
    } else {
        nextEvent(root->right, time);
    }
}
void freeTime(adrNode root);
