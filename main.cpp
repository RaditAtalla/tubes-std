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
double convertStringToDecimal(string timeStr) {

    double hours = stod(timeStr.substr(0, 2));
    double minutes = stod(timeStr.substr(2 + 1));

    return hours + (minutes / 60.0);
}

void addEvent(adrNode& root) {
    string eventName;
    string startTime, endTime;

    cout << "## ADD EVENT ##" << endl;

    cout << "Event name: ";
    cin.ignore();
    getline(cin, eventName);

    cout << "Start time (HH:MM): ";
    cin >> startTime;


    double decimalStartTime = convertStringToDecimal(startTime);

    cout << "End time (HH:MM): ";
    cin >> endTime;
    double decimalEndTime = convertStringToDecimal(endTime);

    if(decimalStartTime >= decimalEndTime){
        cout << "@ Insertion Failed, Start time must be less than end time";
    } else{
        adrNode p = createNode(decimalStartTime, decimalEndTime, eventName);
        insertNode(root, p);
    }


    cout << "\n\n";


}

void showSchedule(adrNode root) {
    cout << "## TODAY'S SCHEDULE ##" << endl;
    int cnt = totalEvents(root);
    cout << "@ You have " << cnt << " event(s)" << endl;
    displayTree(root);

    cout << "\n";
}

void updateEvent(adrNode& root) {
    string eventName, newEventName;
    string startTime, endTime;

    cout << "## UPDATE EVENT ##" << endl;
    cout << "Event name to update: ";
    cin >> eventName;

    adrNode event = searchNode(root, eventName);
    if(event) {
        cout << "new Event name: ";
        cin >> newEventName;
        cout << "New start time (HH:MM): ";
        cin >> startTime;
        cout << "New end time: (HH:MM): ";
        cin >> endTime;

        updateNode(root, event->info.eventName, newEventName, convertStringToDecimal(startTime), convertStringToDecimal(endTime));

    } else {
        cout << "@ Event not found" << endl;
    }

    cout << endl;
}

void deleteEvent(adrNode& root) {
    string eventName;

    cout << "## DELETE EVENT ##" << endl;
    cout << "Event name to delete: ";
    cin >> eventName;

    deleteNodeByName(root, eventName);

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
