#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class Patient {
public:
    int id, age;
    string name, disease, doctor, medicine;

    void addPatient() {
        cout << "Enter Patient ID: ";
        cin >> id;
        cin.ignore();

        cout << "Enter Name: ";
        getline(cin, name);

        cout << "Enter Age: ";
        cin >> age;
        cin.ignore();

        cout << "Enter Disease: ";
        getline(cin, disease);

        cout << "Enter Doctor Name: ";
        getline(cin, doctor);

        cout << "Enter Medicine: ";
        getline(cin, medicine);
    }

    void displayPatient() {
        cout << "\nID: " << id
             << "\nName: " << name
             << "\nAge: " << age
             << "\nDisease: " << disease
             << "\nDoctor: " << doctor
             << "\nMedicine: " << medicine << endl;
    }

    void writeToFile(ofstream &out) {
        out << id << endl
            << name << endl
            << age << endl
            << disease << endl
            << doctor << endl
            << medicine << endl;
    }

    void readFromFile(ifstream &in) {
        in >> id;
        in.ignore();

        getline(in, name);

        in >> age;
        in.ignore();

        getline(in, disease);
        getline(in, doctor);
        getline(in, medicine);
    }
};

int main() {
    vector<Patient> patients;
    int choice;

    // Load data from file
    ifstream infile("patients.txt");

    while (infile) {
        Patient p;
        p.readFromFile(infile);

        if (infile)
            patients.push_back(p);
    }

    infile.close();

    do {
        cout << "\n----- MEDICAL INFORMATION SYSTEM -----\n";
        cout << "1. Add Patient\n";
        cout << "2. Display All Patients\n";
        cout << "3. Search Patient\n";
        cout << "4. Delete Patient\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            Patient p;
            p.addPatient();
            patients.push_back(p);

            cout << "Patient added successfully!\n";
        }

        else if (choice == 2) {
            if (patients.empty()) {
                cout << "No records found!\n";
            } else {
                for (auto &p : patients) {
                    p.displayPatient();
                }
            }
        }

        else if (choice == 3) {
            int searchId;
            cout << "Enter Patient ID to search: ";
            cin >> searchId;

            bool found = false;

            for (auto &p : patients) {
                if (p.id == searchId) {
                    p.displayPatient();
                    found = true;
                    break;
                }
            }

            if (!found)
                cout << "Patient not found!\n";
        }

        else if (choice == 4) {
            int deleteId;
            cout << "Enter Patient ID to delete: ";
            cin >> deleteId;

            bool found = false;

            for (int i = 0; i < patients.size(); i++) {
                if (patients[i].id == deleteId) {
                    patients.erase(patients.begin() + i);
                    cout << "Patient deleted successfully!\n";
                    found = true;
                    break;
                }
            }

            if (!found)
                cout << "Patient not found!\n";
        }

    } while (choice != 5);

    // Save data to file
    ofstream outfile("patients.txt");

    for (auto &p : patients) {
        p.writeToFile(outfile);
    }

    outfile.close();

    cout << "Data saved to file. Exiting...\n";

    return 0;
}