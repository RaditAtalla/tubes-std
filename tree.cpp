#include "tree.h"

void createTree(adrNode& root) {
    root = nullptr;
}
adrNode createNode(int startTime, int endTime, string eventName) {
    adrNode node = new Node;
    node->info.eventName = eventName;
    node->info.startTime = startTime;
    node->info.endTime = endTime;
    node->left = nullptr;
    node->right = nullptr;

    return node;
}
void insertNode(adrNode& root, adrNode node) {
    // insert node only when there is no overlapping events
    if(root == nullptr) {
        root = node;
        cout << "@ Event added" << endl;
    } else if(node->info.startTime <= root->info.startTime && node->info.endTime <= root->info.startTime) {
        insertNode(root->left, node);
    } else if(node->info.startTime >= root->info.startTime && node->info.startTime >= root->info.endTime) {
        insertNode(root->right, node);
    } else {
        cout << "@ Failed adding event" << endl;
    }
}
void displayTree(adrNode root) {
    // Display the tree with left-root-right traversal. Ensuring the earliest event is shown first
    if(root != nullptr) {
        displayTree(root->left);
        if(root->info.eventName != "") {
            cout << "[" << root->info.startTime << " - " << root->info.endTime << "] " << root->info.eventName << endl;
        }
        displayTree(root->right);
    }
}
void updateNode(adrNode& root, adrNode& node, string eventName, int startTime, int endTime) {
    // If start time or end time is updated, then the node will be reinserted to the tree
    // TODO: refactor this garbage if possible
    if(node->info.startTime == startTime || node->info.endTime == endTime) {
        node->info.eventName = eventName;
        node->info.startTime = startTime;
        node->info.endTime = endTime;
    } else {
        freeNode(node);
        adrNode updatedNode = createNode(startTime, endTime, eventName);
        insertNode(root, updatedNode);
    }

    cout << "@ Event updated" << endl;
}
void freeNode(adrNode& node) {
    node->info.eventName = "";
}
adrNode searchNode(adrNode root, string eventName) {
    // lexicographical comparison to determine left or right child
    if(root == nullptr) {
        return nullptr;
    } else if(eventName < root->info.eventName) {
        return searchNode(root->left, eventName);
    } else if(eventName > root->info.eventName) {
        return searchNode(root->right, eventName);
    }

    return root;
}

// TODO: implement additional methods
