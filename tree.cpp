#include "tree.h"

void createTree(adrNode& root) {
    root = nullptr;
}
adrNode createNode(double startTime, double endTime, string eventName) {
    adrNode node = new Node;
    node->info.eventName = eventName;
    node->info.startTime = startTime;
    node->info.endTime = endTime;
    node->left = nullptr;
    node->right = nullptr;

    return node;
}

void insertNode(adrNode& root, adrNode node) {
    if(root == nullptr){
        root = node;
        cout << "@Insertion success, '" << node->info.eventName << "' successfully added\n" ;
    } else if(node->info.startTime < root->info.endTime &&
              node->info.endTime > root->info.startTime){
        cout << "@Insertion fail, event intersect with '" << root->info.eventName << "'\n";
        return;
    } else if(node->info.endTime <= root->info.startTime){
        insertNode(root->left, node);
    } else if(node->info.startTime >= root->info.endTime){
        insertNode(root->right, node);
    }
}

void printTime(double decimalTime) {
    int totalMinutes = round(decimalTime * 60);

    int hours = (totalMinutes / 60) % 24;
    int minutes = totalMinutes % 60;

    printf("%02d:%02d", hours, minutes);
}

void displayTree(adrNode root) {
    if(root != nullptr) {
        displayTree(root->left);
        if(root->info.eventName != "") {
            printTime(root->info.startTime);
            cout << " - ";
            printTime(root->info.endTime);
            cout << " " << root->info.eventName << "\n";
        }
        displayTree(root->right);
    }
}

adrNode searchNode(adrNode root, string eventName) {
    if(root == nullptr){
        return nullptr;
    }

    if(root->info.eventName == eventName){
        return root;
    }

    adrNode ans = searchNode(root->left, eventName);
    if(ans != nullptr) return ans;

    return searchNode(root->right, eventName);
}


adrNode getMinValue(adrNode& root){
    adrNode current = root;

    while(current && current->left != nullptr){
        current = current->left;
    }

    return current;
}

adrNode deleteNode(adrNode& root, double time){
    if(root == nullptr) return root;

    if(time < root->info.startTime - 1e-9){
        root->left = deleteNode(root->left, time);
    } else if(time > root->info.startTime + 1e-9){
        root->right = deleteNode(root->right, time);
    } else{
        if(root->left == nullptr){
            adrNode temp = root->right;
            delete root;
            return temp;
        } else if(root->right == nullptr){
            adrNode temp = root->left;
            delete root;
            return temp;
        }

        adrNode temp = getMinValue(root->right);

        root->info.startTime = temp->info.startTime;
        root->info.eventName = temp->info.eventName;
        root->info.endTime = temp->info.endTime;

        root->right = deleteNode(root->right, temp->info.startTime);
    }

    return root;
}

void deleteNodeByName(adrNode& root, string eventName) {
    adrNode target = searchNode(root, eventName);
    //target tidak ada
    if (target == nullptr) {
        cout << "@ Node deletion failed, '" << eventName << "' not found.\n";
        return;
    }

    double time = target->info.startTime;

    root = deleteNode(root, time);

    cout << "@ Node deletion success, '" << eventName << "' successfully deleted.\n";
}

bool isAvailable(adrNode root, double start, double end) {
    if (root == nullptr) return true;

    if (start < root->info.endTime && end > root->info.startTime) {
        return false;
    }

    return isAvailable(root->left, start, end) && isAvailable(root->right, start, end);
}


void updateNode(adrNode& root, string oldName, string newName,
                double newStart, double newEnd) {
    adrNode target = searchNode(root, oldName);

    //Node tidak ditemukan
    if (target == nullptr) {
        cout << "@ Update Event failed, Event'" << oldName << "' not found\n";
        return;
    }

    //starttime dan endtime baru sama dengan starttime dan endtime lama
    if (abs(target->info.startTime - newStart) < 1e-9 &&
        abs(target->info.endTime - newEnd) < 1e-9) {

        target->info.eventName = newName;
        cout << "@ Update Success.\n";
        return;
    }

    double oldStart = target->info.startTime;
    double oldEnd = target->info.endTime;
    string oldNameTemp = target->info.eventName;

    root = deleteNode(root, oldStart);

    //Cek apakah ada waktu kosong untuk node baru
    if (isAvailable(root, newStart, newEnd)) {
        adrNode newNode = createNode(newStart, newEnd, newName);
        insertNode(root, newNode);
        cout << "@ Update Success\n";
    }
    else {
        //jika tidak ada, maka insert kembali node yang dihapus tadi
        cout << "@ Update Failed, reverting deleted node '" << oldNameTemp << "'\n";

        adrNode restoreNode = createNode(oldStart, oldEnd, oldNameTemp);
        insertNode(root, restoreNode);
    }
}


int totalEvents(adrNode root){
    if(root == nullptr){
        return 0;
    }
    int cnt = 1;

    cnt += totalEvents(root->left);
    cnt += totalEvents(root->right);

    return cnt;
}
