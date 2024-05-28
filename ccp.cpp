#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

class Patient {
public:
    string name;
    int age;
    double height;
    double weight;
    string painArea;
    string additionalInfo;
    bool isUnderObservation;

    Patient(const string& n, int a, double h, double w, const string& pArea, const string& addInfo)
        : name(n), age(a), height(h), weight(w), painArea(pArea), additionalInfo(addInfo), isUnderObservation(false) {}
};

class Doctor {
public:
    string name;
    string specialty;
    vector<string> availableSlots;
    vector<string> surgerySlots;

    Doctor(const string& n, const string& s, const vector<string>& slots, const vector<string>& sSlots)
        : name(n), specialty(s), availableSlots(slots), surgerySlots(sSlots) {}
};

class Appointment {
public:
    string time;
    Patient patient;
    Doctor doctor;

    Appointment(const string& t, const Patient& p, const Doctor& d) : time(t), patient(p), doctor(d) {}
};

class Surgery {
public:
    string time;
    Patient patient;
    Doctor doctor;

    Surgery(const string& t, const Patient& p, const Doctor& d) : time(t), patient(p), doctor(d) {}
};

class HospitalManagementSystem {
private:
    vector<Doctor> doctors;
    queue<Appointment> appointments;
    queue<Surgery> surgeries;
    vector<pair<string, string>> doctorAppointments;
    vector<pair<string, string>> doctorSurgeries;
    vector<Doctor> emergencyDoctors;
    vector<Patient> patientsUnderObservation;

public:
    HospitalManagementSystem() {

        doctors.push_back(Doctor("Doc Aashir", "General", { "09:00 AM", "10:00 AM", "11:00 AM", "12:00 PM", "01:00 PM" }, { "02:00 PM", "03:00 PM" }));
        doctors.push_back(Doctor("Doc Izhan", "Cardiologist", { "09:30 AM", "10:30 AM", "11:30 AM", "12:30 PM", "01:30 PM" }, { "02:30 PM", "03:30 PM" }));
        doctors.push_back(Doctor("Doc Doofenshmitz", "Orthopedist", { "10:00 AM", "11:00 AM", "12:00 PM", "01:00 PM", "02:00 PM" }, { "03:00 PM", "04:00 PM" }));
        doctors.push_back(Doctor("Doc Freaky", "Neurologist", { "09:15 AM", "10:15 AM", "11:15 AM", "12:15 PM", "01:15 PM" }, { "02:15 PM", "03:15 PM" }));
        doctors.push_back(Doctor("Doc Shareef", "Dermatologist", { "09:45 AM", "10:45 AM", "11:45 AM", "12:45 PM", "01:45 PM" }, { "02:45 PM", "03:45 PM" }));
        doctors.push_back(Doctor("Doc ChunChunwala", "Pediatrician", { "08:30 AM", "09:30 AM", "10:30 AM", "11:30 AM", "12:30 PM" }, { "01:30 PM", "02:30 PM" }));
        doctors.push_back(Doctor("Doc Hizler", "Psychiatrist", { "09:50 AM", "10:50 AM", "11:50 AM", "12:50 PM", "01:50 PM" }, { "02:50 PM", "03:50 PM" }));
        doctors.push_back(Doctor("Doc Jamshed", "Surgeon", { "08:00 AM", "09:00 AM", "10:00 AM", "11:00 AM", "12:00 PM" }, { "01:00 PM", "02:00 PM", "03:00 PM", "04:00 PM" }));
        doctors.push_back(Doctor("Dr. Bones", "Surgeon", {}, { "10:00", "12:00", "14:00" }));
        doctors.push_back(Doctor("Dr. Knife n bones", "Surgeon", {}, { "11:00", "13:00", "15:00" }));
        doctors.push_back(Doctor("Dr. Potato Fingers", "Surgeon", {}, { "09:00", "12:00", "16:00" }));


        emergencyDoctors.push_back(Doctor("Doc Aashir", "Emergency", { "09:00 AM", "10:00 AM", "11:00 AM", "12:00 PM", "01:00 PM" }, {}));
        emergencyDoctors.push_back(Doctor("Doc Scream", "Emergency", { "09:30 AM", "10:30 AM", "11:30 AM", "12:30 PM", "01:30 PM" }, {}));
        emergencyDoctors.push_back(Doctor("Doc Pain", "Emergency", { "10:00 AM", "11:00 AM", "12:00 PM", "01:00 PM", "02:00 PM" }, {}));
        emergencyDoctors.push_back(Doctor("Doc Cat", "Emergency", { "09:15 AM", "10:15 AM", "11:15 AM", "12:15 PM", "01:15 PM" }, {}));
        emergencyDoctors.push_back(Doctor("Doc Banana", "Emergency", { "08:30 AM", "09:30 AM", "10:30 AM", "11:30 AM", "12:30 PM" }, {}));
        emergencyDoctors.push_back(Doctor("Doc Chernobyl", "Emergency", { "09:50 AM", "10:50 AM", "11:50 AM", "12:50 PM", "01:50 PM" }, {}));
    }

    void bookAppointment(Patient& patient) {

        string specialty;
        if (patient.painArea == "head") specialty = "Neurologist";
        else if (patient.painArea == "heart") specialty = "Cardiologist";
        else if (patient.painArea == "bones") specialty = "Orthopedist";
        else if (patient.painArea == "skin") specialty = "Dermatologist";
        else specialty = "General";

        for (auto& doctor : doctors) {
            if (doctor.specialty == specialty) {
                for (const string& slot : doctor.availableSlots) {
                    if (find(doctorAppointments.begin(), doctorAppointments.end(), make_pair(doctor.name, slot)) == doctorAppointments.end()) {
                        doctorAppointments.push_back(make_pair(doctor.name, slot));
                        appointments.push(Appointment(slot, patient, doctor));
                        cout << "Appointment booked with Dr. " << doctor.name << " at " << slot << endl;
                        return;
                    }
                }
            }
        }
        cout << "No available slots for the requested specialty. Please try another time." << endl;
    }

    void deleteAppointment(const string& patientName, const string& doctorName, const string& timeSlot) {
        queue<Appointment> tempQueue;
        bool found = false;

        while (!appointments.empty()) {
            Appointment appt = appointments.front();
            appointments.pop();
            if (appt.patient.name == patientName && appt.doctor.name == doctorName && appt.time == timeSlot) {
                auto it = find(doctorAppointments.begin(), doctorAppointments.end(), make_pair(doctorName, timeSlot));
                if (it != doctorAppointments.end()) {
                    doctorAppointments.erase(it);
                }
                found = true;
            }
            else {
                tempQueue.push(appt);
            }
        }

        appointments = tempQueue;

        if (found) {
            cout << "Appointment deleted successfully." << endl;
        }
        else {
            cout << "Appointment not found." << endl;
        }
    }

    void rescheduleAppointment(const string& patientName, const string& doctorName, const string& oldTimeSlot, const string& newTimeSlot) {
        queue<Appointment> tempQueue;
        bool found = false;

        while (!appointments.empty()) {
            Appointment appt = appointments.front();
            appointments.pop();
            if (appt.patient.name == patientName && appt.doctor.name == doctorName && appt.time == oldTimeSlot) {
                auto it = find(doctorAppointments.begin(), doctorAppointments.end(), make_pair(doctorName, oldTimeSlot));
                if (it != doctorAppointments.end()) {
                    doctorAppointments.erase(it);
                }
                doctorAppointments.push_back(make_pair(doctorName, newTimeSlot));
                appointments.push(Appointment(newTimeSlot, appt.patient, appt.doctor));
                found = true;
                cout << "Appointment rescheduled successfully." << endl;
            }
            else {
                tempQueue.push(appt);
            }
        }

        appointments = tempQueue;

        if (!found) {
            cout << "Appointment not found." << endl;
        }
    }

    void assignEmergencyDoctor(Patient& patient) {
        for (auto& doctor : emergencyDoctors) {
            for (const string& slot : doctor.availableSlots) {
                if (find(doctorAppointments.begin(), doctorAppointments.end(), make_pair(doctor.name, slot)) == doctorAppointments.end()) {
                    doctorAppointments.push_back(make_pair(doctor.name, slot));
                    appointments.push(Appointment(slot, patient, doctor));
                    cout << "Emergency appointment booked with Dr. " << doctor.name << " at " << slot << endl;
                    cout << "Patient Details:" << endl;
                    cout << "Name: " << patient.name << endl;
                    cout << "Age: " << patient.age << endl;
                    cout << "Height: " << patient.height << " cm" << endl;
                    cout << "Weight: " << patient.weight << " kg" << endl;
                    cout << "Pain Area: " << patient.painArea << endl;
                    cout << "Additional Info: " << patient.additionalInfo << endl;
                    return;
                }
            }
        }
        cout << "No available emergency slots. Please wait or try another time." << endl;
    }

    void checkAndAssignEmergencyDoctor(Patient& patient, const string& doctorName) {
        bool doctorAvailable = false;

        for (auto& doctor : doctors) {
            if (doctor.name == doctorName) {
                doctorAvailable = true;
                break;
            }
        }

        if (!doctorAvailable) {
            assignEmergencyDoctor(patient);
        }
    }

    void putUnderObservation(const string& patientName, const string& doctorName) {
        queue<Appointment> tempQueue;
        bool found = false;

        while (!appointments.empty()) {
            Appointment appt = appointments.front();
            appointments.pop();
            if (appt.patient.name == patientName && appt.doctor.name == doctorName) {
                appt.patient.isUnderObservation = true;
                patientsUnderObservation.push_back(appt.patient);
                found = true;
                cout << "Patient " << patientName << " is now under observation by Dr. " << doctorName << "." << endl;
            }
            tempQueue.push(appt);
        }

        appointments = tempQueue;

        if (!found) {
            cout << "Patient or appointment not found." << endl;
        }
    }

    void checkPatientConditionAndReassign(const string& patientName, bool conditionSerious) {
        for (auto& patient : patientsUnderObservation) {
            if (patient.name == patientName && conditionSerious) {
                for (auto& doctor : doctors) {
                    if (doctor.name != patient.name) {
                        assignEmergencyDoctor(patient);
                        return;
                    }
                }
            }
        }
        cout << "Patient is not under observation or condition is not serious." << endl;
    }

    void scheduleSurgery(Patient& patient) {
        // Assign a surgeon based on availability
        for (auto& doctor : doctors) {
            if (doctor.specialty == "Surgeon") {
                for (const string& slot : doctor.surgerySlots) {
                    if (find(doctorSurgeries.begin(), doctorSurgeries.end(), make_pair(doctor.name, slot)) == doctorSurgeries.end()) {
                        doctorSurgeries.push_back(make_pair(doctor.name, slot));
                        surgeries.push(Surgery(slot, patient, doctor));
                        cout << "Surgery scheduled with Dr. " << doctor.name << " at " << slot << endl;
                        return;
                    }
                }
            }
        }
        cout << "No available surgery slots. Please try another time." << endl;
    }

    void cancelSurgery(const string& patientName, const string& doctorName, const string& timeSlot) {
        queue<Surgery> tempQueue;
        bool found = false;

        while (!surgeries.empty()) {
            Surgery surg = surgeries.front();
            surgeries.pop();
            if (surg.patient.name == patientName && surg.doctor.name == doctorName && surg.time == timeSlot) {
                auto it = find(doctorSurgeries.begin(), doctorSurgeries.end(), make_pair(doctorName, timeSlot));
                if (it != doctorSurgeries.end()) {
                    doctorSurgeries.erase(it);
                }
                found = true;
            }
            else {
                tempQueue.push(surg);
            }
        }

        surgeries = tempQueue;

        if (found) {
            cout << "Surgery cancelled successfully." << endl;
        }
        else {
            cout << "Surgery not found." << endl;
        }
    }

    void rescheduleSurgery(const string& patientName, const string& doctorName, const string& oldTimeSlot, const string& newTimeSlot) {
        queue<Surgery> tempQueue;
        bool found = false;

        while (!surgeries.empty()) {
            Surgery surg = surgeries.front();
            surgeries.pop();
            if (surg.patient.name == patientName && surg.doctor.name == doctorName && surg.time == oldTimeSlot) {
                auto it = find(doctorSurgeries.begin(), doctorSurgeries.end(), make_pair(doctorName, oldTimeSlot));
                if (it != doctorSurgeries.end()) {
                    doctorSurgeries.erase(it);
                }
                doctorSurgeries.push_back(make_pair(doctorName, newTimeSlot));
                surgeries.push(Surgery(newTimeSlot, surg.patient, surg.doctor));
                found = true;
                cout << "Surgery rescheduled successfully." << endl;
            }
            else {
                tempQueue.push(surg);
            }
        }

        surgeries = tempQueue;

        if (!found) {
            cout << "Surgery not found." << endl;
        }
    }
};

void displayMenu() {
    cout << "\nHospital Management System\n";
    cout << "1. Appointment Management\n";
    cout << "2. Emergency Care\n";
    cout << "3. Surgery Scheduling\n";
    cout << "0. Exit\n";
    cout << "Enter your choice: ";
}

void handleAppointmentManagement(HospitalManagementSystem& hms) {
    int choice;
    cout << "\nAppointment Management\n";
    cout << "1. Book an Appointment\n";
    cout << "2. Delete an Appointment\n";
    cout << "3. Reschedule an Appointment\n";
    cout << "0. Back to Main Menu\n";
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();

    string name, painArea, additionalInfo, doctorName, oldTimeSlot, newTimeSlot;
    int age;
    double height, weight;

    switch (choice) {
    case 1:
        cout << "Enter patient name: ";
        getline(cin, name);
        cout << "Enter age: ";
        cin >> age;
        cout << "Enter height (in cm): ";
        cin >> height;
        cout << "Enter weight (in kg): ";
        cin >> weight;
        cin.ignore();
        cout << "Enter the area of pain (e.g., head, heart, bones, skin): ";
        getline(cin, painArea);
        cout << "Enter any additional information: ";
        getline(cin, additionalInfo);

        {
            Patient patient(name, age, height, weight, painArea, additionalInfo);
            hms.bookAppointment(patient);
        }
        break;
    case 2:
        cout << "Enter patient name: ";
        getline(cin, name);
        cout << "Enter doctor name: ";
        getline(cin, doctorName);
        cout << "Enter time slot: ";
        getline(cin, oldTimeSlot);
        hms.deleteAppointment(name, doctorName, oldTimeSlot);
        break;
    case 3:
        cout << "Enter patient name: ";
        getline(cin, name);
        cout << "Enter doctor name: ";
        getline(cin, doctorName);
        cout << "Enter old time slot: ";
        getline(cin, oldTimeSlot);
        cout << "Enter new time slot: ";
        getline(cin, newTimeSlot);
        hms.rescheduleAppointment(name, doctorName, oldTimeSlot, newTimeSlot);
        break;
    case 0:
        return;
    default:
        cout << "Invalid choice. Please try again." << endl;
    }
}

void handleEmergencyCare(HospitalManagementSystem& hms) {
    int choice;
    cout << "\nEmergency Care\n";
    cout << "1. Assign Emergency Doctor\n";
    cout << "2. Put Patient Under Observation\n";
    cout << "3. Check Patient Condition and Reassign\n";
    cout << "0. Back to Main Menu\n";
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();

    string name, doctorName;
    int age;
    double height, weight;
    string painArea, additionalInfo;
    bool conditionSerious;

    switch (choice) {
    case 1:
        cout << "Enter patient name: ";
        getline(cin, name);
        cout << "Enter age: ";
        cin >> age;
        cout << "Enter height (in cm): ";
        cin >> height;
        cout << "Enter weight (in kg): ";
        cin >> weight;
        cin.ignore();
        cout << "Enter the area of pain (e.g., head, heart, bones, skin): ";
        getline(cin, painArea);
        cout << "Enter any additional information: ";
        getline(cin, additionalInfo);

        {
            Patient patient(name, age, height, weight, painArea, additionalInfo);
            hms.assignEmergencyDoctor(patient);
        }
        break;
    case 2:
        cout << "Enter patient name: ";
        getline(cin, name);
        cout << "Enter doctor name: ";
        getline(cin, doctorName);
        hms.putUnderObservation(name, doctorName);
        break;
    case 3:
        cout << "Enter patient name: ";
        getline(cin, name);
        cout << "Is the condition serious? (1 for Yes, 0 for No): ";
        cin >> conditionSerious;
        hms.checkPatientConditionAndReassign(name, conditionSerious);
        break;
    case 0:
        return;
    default:
        cout << "Invalid choice. Please try again." << endl;
    }
}

void handleSurgeryScheduling(HospitalManagementSystem& hms) {
    int choice;
    cout << "\nSurgery Scheduling\n";
    cout << "1. Schedule a Surgery\n";
    cout << "2. Cancel a Surgery\n";
    cout << "3. Reschedule a Surgery\n";
    cout << "0. Back to Main Menu\n";
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();

    string name, doctorName, oldTimeSlot, newTimeSlot;
    int age;
    double height, weight;
    string painArea, additionalInfo;

    switch (choice) {
    case 1:
        cout << "Enter patient name: ";
        getline(cin, name);
        cout << "Enter age: ";
        cin >> age;
        cout << "Enter height (in cm): ";
        cin >> height;
        cout << "Enter weight (in kg): ";
        cin >> weight;
        cin.ignore();
        cout << "Enter the area of pain (e.g., head, heart, bones, skin): ";
        getline(cin, painArea);
        cout << "Enter any additional information: ";
        getline(cin, additionalInfo);

        {
            Patient patient(name, age, height, weight, painArea, additionalInfo);
            hms.scheduleSurgery(patient);
        }
        break;
    case 2:
        cout << "Enter patient name: ";
        getline(cin, name);
        cout << "Enter doctor name: ";
        getline(cin, doctorName);
        cout << "Enter time slot: ";
        getline(cin, oldTimeSlot);
        hms.cancelSurgery(name, doctorName, oldTimeSlot);
        break;
    case 3:
        cout << "Enter patient name: ";
        getline(cin, name);
        cout << "Enter doctor name: ";
        getline(cin, doctorName);
        cout << "Enter old time slot: ";
        getline(cin, oldTimeSlot);
        cout << "Enter new time slot: ";
        getline(cin, newTimeSlot);
        hms.rescheduleSurgery(name, doctorName, oldTimeSlot, newTimeSlot);
        break;
    case 0:
        return;
    default:
        cout << "Invalid choice. Please try again." << endl;
    }
}

int main() {
    HospitalManagementSystem hms;
    int choice;

    while (true) {
        displayMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            handleAppointmentManagement(hms);
            break;
        case 2:
            handleEmergencyCare(hms);
            break;
        case 3:
            handleSurgeryScheduling(hms);
            break;
        case 0:
            cout << "Exiting the system. Goodbye!" << endl;
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}