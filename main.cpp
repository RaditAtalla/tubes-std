#include "tree.h"

void showMenu() {
    cout << "===== EVENT MANAGER =====" << endl;
    cout << "1. Add event" << endl;
    cout << "2. Show schedule" << endl;
    cout << "3. Update event" << endl;
    cout << "4. Delete event" << endl;
    cout << "0. Exit" << endl;
    cout << "Input: ";
}

void addEvent(adrNode& root) {
    string eventName;
    int startTime, endTime;

    cout << "## ADD EVENT ##" << endl;
    cout << "Event name: " << endl;
    cin >> eventName;
    cout << "Start time: " << endl;
    cin >> startTime;
    cout << "End time: " << endl;
    cin >> endTime;

    adrNode event = createNode(startTime, endTime, eventName);
    insertNode(root, event);

    cout << endl;
}

void showSchedule(adrNode& root) {
    cout << "## TODAY'S SCHEDULE ##" << endl;
    cout << "@ You have x event(s)" << endl;
    displayTree(root);

    cout << endl;
}

void updateEvent(adrNode& root) {
    string eventName, newEventName;
    int startTime, endTime;

    cout << "## UPDATE EVENT ##" << endl;
    cout << "Event name to update: " << endl;
    cin >> eventName;

    adrNode event = searchNode(root, eventName);
    if(event) {
        cout << "new Event name: " << endl;
        cin >> newEventName;
        cout << "New start time: " << endl;
        cin >> startTime;
        cout << "New end time: " << endl;
        cin >> endTime;

        updateNode(root, event, newEventName, startTime, endTime);
    } else {
        cout << "@ Event not found" << endl;
    }

    cout << endl;
}

void deleteEvent(adrNode& root) {
    string eventName;

    cout << "## DELETE EVENT ##" << endl;
    cout << "Event name to delete: " << endl;
    cin >> eventName;

    adrNode event = searchNode(root, eventName);
    freeNode(event);

    cout << "@ Event deleted" << endl;
    cout << endl;
}

int main()
{
    int input = -1;
    adrNode root;
    createTree(root);

    do {
        showMenu();
        cin >> input;
        cout << endl;

        switch(input) {
        case 1:
            addEvent(root);
            break;
        case 2:
            showSchedule(root);
            break;
        case 3:
            updateEvent(root);
            break;
        case 4:
            deleteEvent(root);
            break;
        case 0:
            cout << "@ Good bye" << endl;
            break;
        default:
            cout << "@ Pick only between 0-4" << endl;
        }

    } while(input != 0);

    return 0;
}
