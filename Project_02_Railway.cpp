
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

// =====================================
// CLASS 1: TRAIN
// =====================================

class Train {
public:
    int trainNumber;
    string trainName;
    string source;
    string destination;
    int totalSeats;
    int bookedSeats;
    double fare;

    // Constructor
    Train(int number, string name, string from,
          string to, int seats, double price) {

        trainNumber = number;
        trainName = name;
        source = from;
        destination = to;
        totalSeats = seats;
        bookedSeats = 0;
        fare = price;
    }

    int availableSeats() {
        return totalSeats - bookedSeats;
    }

    void displayTrain() {
        cout << "\nTrain Number: " << trainNumber;
        cout << "\nTrain Name: " << trainName;
        cout << "\nFrom: " << source;
        cout << "\nTo: " << destination;
        cout << "\nTotal Seats: " << totalSeats;
        cout << "\nAvailable Seats: " << availableSeats();
        cout << "\nTicket Fare: Rs. " << fare << endl;
    }
};


// =====================================
// CLASS 2: PILOT
// =====================================

class Pilot {
public:
    int pilotID;
    string pilotName;
    string experience;
    int assignedTrain;

    Pilot(int id, string name, string exp) {
        pilotID = id;
        pilotName = name;
        experience = exp;
        assignedTrain = -1;
    }

    void displayPilot() {
        cout << "\nPilot ID: " << pilotID;
        cout << "\nPilot Name: " << pilotName;
        cout << "\nExperience: " << experience;

        if (assignedTrain == -1)
            cout << "\nAssigned Train: Not Assigned\n";
        else
            cout << "\nAssigned Train: " << assignedTrain << endl;
    }
};


// =====================================
// CLASS 3: PASSENGER
// =====================================

class Passenger {
public:
    int passengerID;
    string passengerName;
    string mobileNumber;

    Passenger(int id, string name, string mobile) {
        passengerID = id;
        passengerName = name;
        mobileNumber = mobile;
    }

    void displayPassenger() {
        cout << "\nPassenger ID: " << passengerID;
        cout << "\nName: " << passengerName;
        cout << "\nMobile: " << mobileNumber << endl;
    }
};


// =====================================
// CLASS 4: TICKET
// =====================================

class Ticket {
public:
    int ticketID;
    int passengerID;
    int trainNumber;
    int seatNumber;
    double amount;
    string paymentMethod;
    string status;

    Ticket(int id, int pid, int tid,
           int seat, double price, string method) {

        ticketID = id;
        passengerID = pid;
        trainNumber = tid;
        seatNumber = seat;
        amount = price;
        paymentMethod = method;
        status = "Confirmed";
    }

    void displayTicket() {
        cout << "\n========== TICKET ==========";
        cout << "\nTicket ID: " << ticketID;
        cout << "\nPassenger ID: " << passengerID;
        cout << "\nTrain Number: " << trainNumber;
        cout << "\nSeat Number: " << seatNumber;
        cout << "\nAmount Paid: Rs. " << amount;
        cout << "\nPayment: " << paymentMethod;
        cout << "\nStatus: " << status;
        cout << "\n============================\n";
    }
};


// =====================================
// CLASS 5: TRAIN SERVICE
// =====================================

class ServiceRequest {
public:
    int requestID;
    int passengerID;
    int trainNumber;
    int seatNumber;
    string serviceType;
    string details;
    double amount;
    string status;

    ServiceRequest(int id, int pid, int tid,
                   int seat, string type,
                   string detail, double price) {

        requestID = id;
        passengerID = pid;
        trainNumber = tid;
        seatNumber = seat;
        serviceType = type;
        details = detail;
        amount = price;
        status = "Pending";
    }

    void displayRequest() {
        cout << "\nRequest ID: " << requestID;
        cout << "\nService: " << serviceType;
        cout << "\nTrain Number: " << trainNumber;
        cout << "\nSeat Number: " << seatNumber;
        cout << "\nDetails: " << details;
        cout << "\nAmount: Rs. " << amount;
        cout << "\nStatus: " << status << endl;
    }
};


// =====================================
// CLASS 6: RAILWAY MANAGEMENT SYSTEM
// =====================================

class RailwaySystem {

private:

    vector<Train> trains;
    vector<Pilot> pilots;
    vector<Passenger> passengers;
    vector<Ticket> tickets;
    vector<ServiceRequest> requests;

    int nextPassengerID = 101;
    int nextTicketID = 501;
    int nextRequestID = 901;

    // Find train using train number
    int findTrain(int number) {
        for (int i = 0; i < trains.size(); i++) {
            if (trains[i].trainNumber == number)
                return i;
        }
        return -1;
    }

    // Find passenger using passenger ID
    int findPassenger(int id) {
        for (int i = 0; i < passengers.size(); i++) {
            if (passengers[i].passengerID == id)
                return i;
        }
        return -1;
    }

    // Check passenger's confirmed ticket
    bool hasValidTicket(int pid, int tid) {
        for (int i = 0; i < tickets.size(); i++) {
            if (tickets[i].passengerID == pid &&
                tickets[i].trainNumber == tid &&
                tickets[i].status == "Confirmed")
                return true;
        }
        return false;
    }


public:

    // =================================
    // ADD TRAIN
    // =================================

    void addTrain() {
        int number, seats;
        string name, from, to;
        double fare;

        cout << "\nEnter Train Number: ";
        cin >> number;

        if (findTrain(number) != -1) {
            cout << "Train already exists!\n";
            return;
        }

        cin.ignore();

        cout << "Enter Train Name: ";
        getline(cin, name);

        cout << "Enter Source: ";
        getline(cin, from);

        cout << "Enter Destination: ";
        getline(cin, to);

        cout << "Enter Total Seats: ";
        cin >> seats;

        cout << "Enter Ticket Fare: ";
        cin >> fare;

        if (seats <= 0 || fare <= 0 || from == to) {
            cout << "Invalid train details!\n";
            return;
        }

        trains.emplace_back(number, name, from, to, seats, fare);

        cout << "\nTrain Added Successfully!\n";
    }


    // =================================
    // DISPLAY ALL TRAINS
    // =================================

    void displayTrains() {
        if (trains.empty()) {
            cout << "\nNo trains available!\n";
            return;
        }

        cout << "\n===== AVAILABLE TRAINS =====\n";

        for (int i = 0; i < trains.size(); i++) {
            trains[i].displayTrain();
        }
    }


    // =================================
    // ADD PILOT
    // =================================

    void addPilot() {
        int id;
        string name, experience;

        cout << "\nEnter Pilot ID: ";
        cin >> id;

        for (int i = 0; i < pilots.size(); i++) {
            if (pilots[i].pilotID == id) {
                cout << "Pilot ID already exists!\n";
                return;
            }
        }

        cin.ignore();

        cout << "Enter Pilot Name: ";
        getline(cin, name);

        cout << "Enter Experience: ";
        getline(cin, experience);

        pilots.emplace_back(id, name, experience);

        cout << "\nPilot Added Successfully!\n";
    }


    // =================================
    // ASSIGN PILOT TO TRAIN
    // =================================

    void assignPilot() {
        int pid, tid;

        cout << "\nEnter Pilot ID: ";
        cin >> pid;

        cout << "Enter Train Number: ";
        cin >> tid;

        int pilotIndex = -1;

        for (int i = 0; i < pilots.size(); i++) {
            if (pilots[i].pilotID == pid) {
                pilotIndex = i;
                break;
            }
        }

        int trainIndex = findTrain(tid);

        if (pilotIndex == -1 || trainIndex == -1) {
            cout << "\nPilot or Train Not Found!\n";
            return;
        }

        if (pilots[pilotIndex].assignedTrain != -1) {
            cout << "\nPilot is already assigned!\n";
            return;
        }

        for (int i = 0; i < pilots.size(); i++) {
            if (pilots[i].assignedTrain == tid) {
                cout << "\nTrain already has a pilot!\n";
                return;
            }
        }

        pilots[pilotIndex].assignedTrain = tid;

        cout << "\nPilot Assigned Successfully!\n";
    }


    // =================================
    // DISPLAY PILOTS
    // =================================

    void displayPilots() {
        if (pilots.empty()) {
            cout << "\nNo pilots registered!\n";
            return;
        }

        for (int i = 0; i < pilots.size(); i++) {
            pilots[i].displayPilot();
        }
    }


    // =================================
    // PASSENGER REGISTRATION + BOOKING
    // =================================

    void bookTicket() {
        if (trains.empty()) {
            cout << "\nNo trains available for booking!\n";
            return;
        }

        string name, mobile;
        int trainNo;

        cin.ignore();

        cout << "\nEnter Passenger Name: ";
        getline(cin, name);

        cout << "Enter Mobile Number: ";
        getline(cin, mobile);

        if (name.empty() || mobile.empty()) {
            cout << "Invalid passenger details!\n";
            return;
        }

        int passengerID = nextPassengerID++;

        passengers.emplace_back(passengerID, name, mobile);

        cout << "\nRegistration Successful!";
        cout << "\nYour Passenger ID: " << passengerID << endl;

        displayTrains();

        cout << "\nEnter Train Number to Book: ";
        cin >> trainNo;

        int index = findTrain(trainNo);

        if (index == -1) {
            cout << "\nTrain Not Found!\n";
            return;
        }

        if (trains[index].availableSeats() <= 0) {
            cout << "\nSorry! No Seats Available.\n";
            return;
        }

        int seatNumber = trains[index].bookedSeats + 1;

        cout << "\nTicket Fare: Rs. " << trains[index].fare;

        cout << "\nSelect Payment Method:";
        cout << "\n1. UPI";
        cout << "\n2. Card";
        cout << "\n3. Cash";
        cout << "\nEnter Choice: ";

        int choice;
        cin >> choice;

        string method;

        if (choice == 1)
            method = "UPI";
        else if (choice == 2)
            method = "Card";
        else if (choice == 3)
            method = "Cash";
        else {
            cout << "\nInvalid Payment Method!\n";
            return;
        }

        // Demo payment confirmation
        cout << "\nProcessing Demo Payment...\n";
        cout << "Payment Successful!\n";

        trains[index].bookedSeats++;

        tickets.emplace_back(
            nextTicketID,
            passengerID,
            trainNo,
            seatNumber,
            trains[index].fare,
            method
        );

        tickets.back().displayTicket();
        nextTicketID++;
    }


    // =================================
    // DISPLAY ALL TICKETS
    // =================================

    void displayTickets() {
        if (tickets.empty()) {
            cout << "\nNo Tickets Booked!\n";
            return;
        }

        for (int i = 0; i < tickets.size(); i++) {
            tickets[i].displayTicket();
        }
    }


    // =================================
    // BOOK TRAIN SERVICES
    // =================================

    void bookService() {
        int pid, tid, seat;

        cout << "\nEnter Passenger ID: ";
        cin >> pid;

        cout << "Enter Train Number: ";
        cin >> tid;

        cout << "Enter Seat Number: ";
        cin >> seat;

        if (findPassenger(pid) == -1 ||
            !hasValidTicket(pid, tid)) {
            cout << "\nValid Ticket Not Found!\n";
            return;
        }

        int trainIndex = findTrain(tid);

        if (trainIndex == -1 ||
            seat <= 0 ||
            seat > trains[trainIndex].bookedSeats) {
            cout << "\nInvalid Seat Number!\n";
            return;
        }

        int choice;
        string detail;
        double price;

        cout << "\n===== TRAIN SERVICES =====";
        cout << "\n1. Cleaning Service";
        cout << "\n2. Meal Service";
        cout << "\nEnter Choice: ";
        cin >> choice;

        cin.ignore();

        if (choice == 1) {
            cout << "\nEnter Cleaning Details: ";
            getline(cin, detail);

            price = 0;

            requests.emplace_back(
                nextRequestID++, pid, tid,
                seat, "Cleaning", detail, price
            );

            cout << "\nCleaning Request Sent Successfully!";
        }

        else if (choice == 2) {
            int quantity;

            cout << "\nEnter Meal Name: ";
            getline(cin, detail);

            cout << "Enter Quantity: ";
            cin >> quantity;

            if (quantity <= 0) {
                cout << "\nInvalid Quantity!\n";
                return;
            }

            price = quantity * 150;

            cout << "\nMeal Price: Rs. " << price;
            cout << "\nDemo Meal Payment Successful!\n";

            requests.emplace_back(
                nextRequestID++, pid, tid,
                seat, "Meal", detail, price
            );

            cout << "\nMeal Ordered Successfully!";
        }

        else {
            cout << "\nInvalid Service Choice!\n";
            return;
        }

        cout << "\nYour Request ID: "
             << nextRequestID - 1 << endl;
    }


    // =================================
    // DISPLAY SERVICE REQUESTS
    // =================================

    void displayServices() {
        if (requests.empty()) {
            cout << "\nNo Service Requests!\n";
            return;
        }

        cout << "\n===== SERVICE REQUESTS =====\n";

        for (int i = 0; i < requests.size(); i++) {
            requests[i].displayRequest();
        }
    }


    // =================================
    // UPDATE SERVICE STATUS
    // =================================

    void updateServiceStatus() {
        int id;

        cout << "\nEnter Request ID: ";
        cin >> id;

        for (int i = 0; i < requests.size(); i++) {
            if (requests[i].requestID == id) {
                requests[i].status = "Completed";

                cout << "\nService Status Updated Successfully!\n";
                return;
            }
        }

        cout << "\nRequest Not Found!\n";
    }


    // =================================
    // MAIN MENU
    // =================================

    void menu() {
        int choice;

        do {
            cout << "\n\n";
            cout << "====================================\n";
            cout << "     RAILWAY MANAGEMENT SYSTEM\n";
            cout << "====================================\n";

            cout << "\n1. Add Train";
            cout << "\n2. Display Trains";
            cout << "\n3. Add Pilot";
            cout << "\n4. Assign Pilot to Train";
            cout << "\n5. Display Pilots";
            cout << "\n6. Passenger Registration & Booking";
            cout << "\n7. Display Tickets";
            cout << "\n8. Book Cleaning / Meal Service";
            cout << "\n9. Display Service Requests";
            cout << "\n10. Update Service Status";
            cout << "\n0. Exit";

            cout << "\n\nEnter Your Choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    addTrain();
                    break;

                case 2:
                    displayTrains();
                    break;

                case 3:
                    addPilot();
                    break;

                case 4:
                    assignPilot();
                    break;

                case 5:
                    displayPilots();
                    break;

                case 6:
                    bookTicket();
                    break;

                case 7:
                    displayTickets();
                    break;

                case 8:
                    bookService();
                    break;

                case 9:
                    displayServices();
                    break;

                case 10:
                    updateServiceStatus();
                    break;

                case 0:
                    cout << "\nThank You For Using Railway System!\n";
                    break;

                default:
                    cout << "\nInvalid Choice! Try Again.\n";
            }

        } while (choice != 0);
    }
};


// =====================================
// MAIN FUNCTION
// =====================================

int main() {

    RailwaySystem railway;

    railway.menu();

    return 0;
}
