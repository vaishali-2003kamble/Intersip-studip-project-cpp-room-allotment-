#include <iostream>
#include <map>
#include <set>
#include <string>
#include <limits>
using namespace std;

struct Booking {
    string host;
    string startTime;
    string endTime;
    int chairs;
};

class RoomBookingSystem {
private:
    map<int, Booking> rooms;
    set<int> availableRooms;

public:
    void addRoom(int roomNumber) {
        if (rooms.find(roomNumber) == rooms.end() && availableRooms.find(roomNumber) == availableRooms.end()) {
            availableRooms.insert(roomNumber);
            cout << "Room " << roomNumber << " added successfully.\n";
        } else {
            cout << "Room " << roomNumber << " already exists.\n";
        }
    }

    void removeRoom(int roomNumber) {
        if (rooms.find(roomNumber) != rooms.end()) {
            cout << "Room " << roomNumber << " is currently booked and cannot be removed.\n";
        } else if (availableRooms.erase(roomNumber)) {
            cout << "Room " << roomNumber << " removed successfully.\n";
        } else {
            cout << "Room " << roomNumber << " does not exist.\n";
        }
    }

    void bookRoom(int roomNumber, const string& host, const string& startTime, const string& endTime, int chairs) {
        if (availableRooms.find(roomNumber) != availableRooms.end()) {
            Booking booking = {host, startTime, endTime, chairs};
            rooms[roomNumber] = booking;
            availableRooms.erase(roomNumber);
            cout << "Room " << roomNumber << " booked successfully.\n";
        } else {
            cout << "Room " << roomNumber << " is not available for booking.\n";
        }
    }

    void checkRoomStatus(int roomNumber) {
        if (rooms.find(roomNumber) != rooms.end()) {
            cout << "Room " << roomNumber << " is booked.\n";
            cout << "Host: " << rooms[roomNumber].host << "\n";
            cout << "Start Time: " << rooms[roomNumber].startTime << "\n";
            cout << "End Time: " << rooms[roomNumber].endTime << "\n";
            cout << "Chairs: " << rooms[roomNumber].chairs << "\n";
        } else if (availableRooms.find(roomNumber) != availableRooms.end()) {
            cout << "Room " << roomNumber << " is available.\n";
        } else {
            cout << "Room " << roomNumber << " does not exist in the system.\n";
        }
    }

    void releaseRoom(int roomNumber) {
        if (rooms.find(roomNumber) != rooms.end()) {
            rooms.erase(roomNumber);
            availableRooms.insert(roomNumber);
            cout << "Room " << roomNumber << " released successfully.\n";
        } else {
            cout << "Room " << roomNumber << " is not currently booked.\n";
        }
    }

    void displayAvailableRooms() {
        cout << "Available Rooms:\n";
        if (availableRooms.empty()) {
            cout << "No available rooms.\n";
            return;
        }

        // Using an iterator for C++98 compatibility
        for (set<int>::iterator it = availableRooms.begin(); it != availableRooms.end(); ++it) {
            cout << "Room " << *it << "\n";
        }
    }
};

int main() {
    RoomBookingSystem system;
    int choice;

    do {
        cout << "\nMenu:\n";
        cout << "1. Add Room\n";
        cout << "2. Remove Room\n";
        cout << "3. Book Room\n";
        cout << "4. Check Room Status\n";
        cout << "5. Release Room\n";
        cout << "6. Display Available Rooms\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Check for invalid input
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please try again.\n";
            continue;
        }

        switch (choice) {
            case 1: {
                int roomNumber;
                cout << "Enter room number to add: ";
                cin >> roomNumber;
                system.addRoom(roomNumber);
                break;
            }
            case 2: {
                int roomNumber;
                cout << "Enter room number to remove: ";
                cin >> roomNumber;
                system.removeRoom(roomNumber);
                break;
            }
            case 3: {
                int roomNumber, chairs;
                string host, startTime, endTime;
                cout << "Enter room number to book: ";
                cin >> roomNumber;
                cin.ignore();
                cout << "Enter host name: ";
                getline(cin, host);
                cout << "Enter start time: ";
                getline(cin, startTime);
                cout << "Enter end time: ";
                getline(cin, endTime);
                cout << "Enter number of chairs: ";
                cin >> chairs;
                system.bookRoom(roomNumber, host, startTime, endTime, chairs);
                break;
            }
            case 4: {
                int roomNumber;
                cout << "Enter room number to check status: ";
                cin >> roomNumber;
                system.checkRoomStatus(roomNumber);
                break;
            }
            case 5: {
                int roomNumber;
                cout << "Enter room number to release: ";
                cin >> roomNumber;
                system.releaseRoom(roomNumber);
                break;
            }
            case 6:
                system.displayAvailableRooms();
                break;
            case 7:
                cout << "Exiting the system. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 7);

    return 0;
}

