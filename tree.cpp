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
        cout << "Acara berhasil ditambahkan\n";
    } else if(node->info.startTime < root->info.endTime &&
              node->info.endTime > root->info.startTime){
        cout << "INSERT NODE FAIL\n";
        cout << "Acara bertabrakan dengan " << root->info.eventName << "\n";
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
        root->info.endTime = temp->info.endTime;
        root->info.eventName = temp->info.eventName;

        root->right = deleteNode(root->right, temp->info.startTime);
    }

    return root;
}

void deleteNodeByName(adrNode& root, string eventName) {
    adrNode target = searchNode(root, eventName);

    if (target == nullptr) {
        cout << "Gagal menghapus: Event '" << eventName << "' tidak ditemukan.\n";
        return;
    }

    double time = target->info.startTime;

    root = deleteNode(root, time);

    cout << "Event '" << eventName << "' berhasil dihapus.\n";
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

    if (target == nullptr) {
        cout << "Update Gagal: Event '" << oldName << "' tidak ditemukan.\n";
        return;
    }

    if (abs(target->info.startTime - newStart) < 1e-9 &&
        abs(target->info.endTime - newEnd) < 1e-9) {

        target->info.eventName = newName;
        cout << "Update Berhasil: Nama event diubah.\n";
        return;
    }

    double oldStart = target->info.startTime;
    double oldEnd = target->info.endTime;
    string backupName = target->info.eventName;

    root = deleteNode(root, oldStart);

    if (isAvailable(root, newStart, newEnd)) {
        adrNode newNode = createNode(newStart, newEnd, newName);
        insertNode(root, newNode);
        cout << "Update Berhasil: Jadwal dipindahkan.\n";
    }
    else {
        cout << "Update Gagal: Waktu baru bentrok dengan jadwal lain!\n";
        cout << "Mengembalikan data lama...\n";

        adrNode oldNode = createNode(oldStart, oldEnd, backupName);
        insertNode(root, oldNode);
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
