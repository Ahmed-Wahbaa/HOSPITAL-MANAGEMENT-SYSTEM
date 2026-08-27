#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

// ========== ENUMERATIONS ========== //
enum Department {
    CARDIOLOGY,
    NEUROLOGY,
    ORTHOPEDICS,
    PEDIATRICS,
    EMERGENCY,
    GENERAL
};

enum RoomType {
    GENERAL_WARD,
    ICU,
    PRIVATE_ROOM,
    SEMI_PRIVATE
};

// ========== EMERGENCY CASE CLASS ========== //
// Advanced Feature: priority_queue
class EmergencyCase {
private:
    int patientId;
    int severity;

public:
    EmergencyCase(int pid, int s);

    int getPatientId() const;
    int getSeverity() const;

    // Higher severity = higher priority
    bool operator<(const EmergencyCase& other) const;
};


// ========== PATIENT CLASS ========== //
class Patient {
private:
    int id;
    string name;
    int age;
    string contact;

    // Data Structures
    stack<string> medicalHistory;
    queue<string> testQueue;
    vector<string> prescriptions;

    bool isAdmitted;
    RoomType roomType;

    // Advanced Feature: Billing
    double bill;

public:
    // Constructor
    Patient(int pid, string n, int a, string c) {
    id = pid;
    name = n;
    age = a;
    contact = c;
    isAdmitted = false;
    bill = 0;
}

    // ========== ORIGINAL FEATURES ========== //

    void admitPatient(RoomType type) {
    if (isAdmitted) {
        cout << "Patient is already admitted." << endl;
        return;
    }

    isAdmitted = true;
    roomType = type;

    addMedicalRecord("Patient admitted to hospital");

    switch (type) {
        case GENERAL_WARD:
            addBill(500);
            break;

        case ICU:
            addBill(3000);
            break;

        case PRIVATE_ROOM:
            addBill(1500);
            break;

        case SEMI_PRIVATE:
            addBill(1000);
            break;
    }
}
    void dischargePatient() {
    if (!isAdmitted) {
        cout << "Patient is not currently admitted." << endl;
        return;
    }

    isAdmitted = false;
    addMedicalRecord("Patient discharged from hospital");
}

    void addMedicalRecord(string record) {
    medicalHistory.push(record);
}

    void requestTest(string testName){
        testQueue.push(testName);
        addMedicalRecord("Test requested: " + testName);

    }
    string performTest(){
        if(testQueue.empty()){
            return "No tests pending";
        }
        string testname =testQueue.front();
        testQueue.pop();
        addMedicalRecord("Test performed: " + testname);
        addBill(300);

        return testname;

    }

    void displayHistory() {
    cout << "Medical History for " << name
         << " (ID: " << id << "):" << endl;

    stack<string> tempHistory = medicalHistory;

    while (!tempHistory.empty()) {
        cout << "- " << tempHistory.top() << endl;
        tempHistory.pop();
    }
}

    int getId() {
    return id;
}

string getName() {
    return name;
}

    bool getAdmissionStatus() {
    return isAdmitted;
}


    // ========== NEW FEATURES ========== //

    // Medical Tests
    void displayPendingTests(){
        queue<string>tmp_testQ=testQueue;
        cout<<"Pending Tests: "<<endl;
        if(tmp_testQ.empty()){
            cout<<"No tests pending"<<endl;
            return;
        }
        while(!tmp_testQ.empty()){
            cout<<"- "<<tmp_testQ.front()<<endl;
            tmp_testQ.pop();

        }
    }

    // Prescriptions
    void addPrescription(string medicine){
        prescriptions.push_back(medicine);
        addMedicalRecord("Prescription added: " + medicine);
        addBill(100);
    }

    void displayPrescriptions(){
        if(prescriptions.empty()){
            cout<<"No prescriptions."<<endl;
            return;
        }
        cout<<"Prescriptions: "<<endl;
        for (int i = 0; i < prescriptions.size(); i++)
        {
           cout<<"- "<<prescriptions[i]<<endl;
        }


    }

    // Billing
    void addBill(double amount) {
    bill += amount;
}

double getBill() {
    return bill;
}

void displayBill() {
    cout << "========== PATIENT BILL ==========" << endl;
    cout << "Patient ID: " << id << endl;
    cout << "Patient Name: " << name << endl;
    cout << "Total Bill: $" << bill << endl;
    cout << "==================================" << endl;
}

    // Additional Getters
    int getAge() {
    return age;
}

string getContact() {
    return contact;
}

RoomType getRoomType() {
    return roomType;
}
};


// ========== DOCTOR CLASS ========== //
class Doctor {
private:
    int id;
    string name;
    Department department;

    // Queue of patients waiting for doctor
    // Patients waiting for this doctor
    queue<int> appointmentQueue;

public:

    // Constructor
    Doctor(int did, string n, Department d);
    Doctor(int did, string n, Department d) {
        id = did;
        name = n;
        department = d;
        // Add appointment
    void addAppointment(int patientId) {
        appointmentQueue.push(patientId);
    }

    // Doctor sees next patient
    int seePatient() {
        if (appointmentQueue.empty()) {
            return -1;
        }
        int patientId = appointmentQueue.front();
        appointmentQueue.pop();
        return patientId;
    }

    // Cancel appointment
    void cancelAppointment(int patientId) {
        if (appointmentQueue.empty()) {
            cout << "No appointments available." << endl;
            return;
        }

        queue<int> temp;
        bool found = false;

        while (!appointmentQueue.empty()) {
            int current = appointmentQueue.front();
            appointmentQueue.pop();

            if (current == patientId && !found) {
                found = true;
            } else {
                temp.push(current);
            }
        }

        appointmentQueue = temp;

        if (found) {
            cout << "Appointment cancelled successfully." << endl;
        } else {
            cout << "Appointment not found." << endl;
        }
    }

    // Display appointments
    void displayAppointments() {
        if (appointmentQueue.empty()) {
            cout << "No appointments." << endl;
            return;
        }

        queue<int> temp = appointmentQueue;
        cout << "Appointment Queue:" << endl;
        while (!temp.empty()) {
            cout << "- Patient ID: " << temp.front() << endl;
            temp.pop();
        }
    }
    }

    // ========== ORIGINAL FEATURES ========== //
    
  
};

class EmergencyCase {
public:
    int patientId;
    int severity; // 1 = highest priority

    EmergencyCase(int id, int s) {
        patientId = id;
        severity = s;
    }

    // Overload < operator for Priority Queue
    bool operator<(const EmergencyCase& other) const {
        return severity > other.severity;
    }
};

// ========== HOSPITAL CLASS ========== //
class Hospital {
private:

    // Main collections
    vector<Patient> patients;
    vector<Doctor> doctors;

    // Original emergency queue
    queue<int> emergencyQueue;

    // Advanced emergency queue
    priority_queue<EmergencyCase> priorityEmergencyQueue;

    // Counters
    int patientCounter;
    int doctorCounter;

    // ========== ROOM MANAGEMENT ========== //

    int generalRooms;
    int icuRooms;
    int privateRooms;
    int semiPrivateRooms;


public:

    // Constructor
    Hospital(){
    patientCounter = 1;
    doctorCounter = 1;

    // Initial room availability
    generalRooms = 20;
    icuRooms = 5;
    privateRooms = 10;
    semiPrivateRooms = 10;
    }


    // =====================================================
    // ORIGINAL FEATURES
    // ===================================================== //

    int registerPatient(string name, int age, string contact) {
        patients.push_back(Patient(patientCounter, name, age, contact));
        cout << "Patient registered with ID: " << patientCounter << endl;
        return patientCounter++;
        }

    int addDoctor(string name, Department dept){

        doctors.push_back(Doctor(doctorCounter, name, dept));
        cout << "Doctor added with ID: " << doctorCounter << endl;
        return doctorCounter++;
    }


    void admitPatient(  int patientId,RoomType type){
               // Check if patient exists
    Patient* patient = findPatient(patientId);

    if (patient == nullptr) {
        cout << "Patient not found." << endl;
        return;
    }

    // Check if patient is already admitted
    if (patient->getAdmissionStatus()) {
        cout << "Patient is already admitted." << endl;
        return;
    }

    // Check room availability
    if (!isRoomAvailable(type)) {
        cout << "No room available for the selected room type." << endl;
        return;
    }

    // Admit patient
    patient->admitPatient(type);

    cout << "Patient admitted successfully." << endl;
    }




    void addEmergency(int patientId){
        emergencyQueue.push(patientId);
        cout << "Emergency patient added: " << patientId << endl;
    };

    int handleEmergency(){
        if (emergencyQueue.empty()) {
            cout << "No emergency cases." << endl;
            return -1;
        }
        int pId = emergencyQueue.front();
        emergencyQueue.pop();
        return pId;
    };

    void bookAppointment(int doctorId,int patientId ){
        Doctor* doc = findDoctor(doctorId);
        if (doc == nullptr) {
            cout << "Doctor not found." << endl;
            return;
        }
        doc->addAppointment(patientId);
        cout << "Appointment booked successfully for Patient " << patientId << endl;
    };

    void displayPatientInfo(
        int patientId
    );

    void displayDoctorInfo(
        int doctorId
    );


    // =====================================================
    // NEW FEATURE 1
    // Find Patient
    // ===================================================== //

    Patient* findPatient( int patientId ){
        for(int i=0;i<patients.size();i++){
            if(patients[i].getId()==patientId){
                return &patients[i];
            }
        }
        return nullptr ;
    }



    // =====================================================
    // NEW FEATURE 2
    // Find Doctor
    // ===================================================== //

    Doctor* findDoctor(int doctorId){
        for(int i=0;i<doctors.size();i++){
            if(doctors[i].getId()==doctorId){
                return &doctors[i];
            }
        }
        return nullptr ;
    }




    // =====================================================
    // NEW FEATURE 3
    // Search Patient By Name
    // ===================================================== //

    void searchPatientByName(string name){

        bool found=false;
        for(int i=0;i<patients.size();i++){
            if(patients[i].getName()==name){
                cout<<"Patient found: "<<endl;
                displayPatientInfo(patients[i].getId());
                found=true;
            }
        }
        if(!found){
            cout<<"No patient found with name: "<<name<<endl;
        }
    }




    // =====================================================
    // NEW FEATURE 4
    // Discharge Patient
    // ===================================================== //

    void dischargePatient(int patientId){
          Patient* patient = findPatient(patientId);

    if (patient == nullptr) {
        cout << "Patient not found." << endl;
        return;
    }

    if (!patient->getAdmissionStatus()) {
        cout << "Patient is not currently admitted." << endl;
        return;
    }

    patient->dischargePatient();

    cout << "Patient discharged successfully." << endl;

    }




    // =====================================================
    // NEW FEATURE 5
    // Request Medical Test
    // ===================================================== //

    void requestPatientTest(
        int patientId,
        string testName
    );


    // =====================================================
    // NEW FEATURE 6
    // Perform Medical Test
    // ===================================================== //

    void performPatientTest(
        int patientId
    );


    // =====================================================
    // NEW FEATURE 7
    // Display Pending Tests
    // ===================================================== //

    void displayPatientTests(
        int patientId
    );


    // =====================================================
    // NEW FEATURE 8
    // Add Prescription
    // ===================================================== //

    void prescribeMedicine(
        int patientId,
        string medicine
    );


    // =====================================================
    // NEW FEATURE 9
    // Display Prescriptions
    // ===================================================== //

    void displayPrescriptions(
        int patientId
    );


    // =====================================================
    // NEW FEATURE 10
    // Patient Bill
    // ===================================================== //

    void displayPatientBill(
        int patientId
    );


    // =====================================================
    // NEW FEATURE 11
    // Priority Emergency
    // ===================================================== //

    void addPriorityEmergency(int patientId,int severity){
        priorityEmergencyQueue.push(EmergencyCase(patientId, severity));
        cout << "Priority emergency added." << endl;
    };


    // =====================================================
    // NEW FEATURE 12
    // Handle Priority Emergency
    // ===================================================== //

    int handlePriorityEmergency(){
        if (priorityEmergencyQueue.empty()) {
            cout << "No priority emergency cases." << endl;
            return -1;
        }
        EmergencyCase topCase = priorityEmergencyQueue.top();
        priorityEmergencyQueue.pop();
        return topCase.patientId;
    };


    // =====================================================
    // NEW FEATURE 13
    // Room Availability
    // ===================================================== //

    bool isRoomAvailable(RoomType type){
        switch (type) {
        case GENERAL_WARD:
            return generalRooms > 0;

        case ICU:
            return icuRooms > 0;

        case PRIVATE_ROOM:
            return privateRooms > 0;

        case SEMI_PRIVATE:
            return semiPrivateRooms > 0;
    }

    return false;
    }




    // =====================================================
    // NEW FEATURE 14
    // Display Room Status
    // ===================================================== //

    void displayRoomStatus(){
    cout << "========== ROOM STATUS ==========" << endl;
    cout << "General Ward: " << generalRooms << endl;
    cout << "ICU: " << icuRooms << endl;
    cout << "Private Rooms: " << privateRooms << endl;
    cout << "Semi-Private Rooms: " << semiPrivateRooms << endl;
    cout << "=================================" << endl;
    }


    // =====================================================
    // NEW FEATURE 15
    // Display All Patients
    // ===================================================== //

    void displayAllPatients();


    // =====================================================
    // NEW FEATURE 16
    // Display All Doctors
    // ===================================================== //

    void displayAllDoctors();


    // =====================================================
    // NEW FEATURE 17
    // Display Doctor Appointments
    // ===================================================== //

    void displayDoctorAppointments(
        int doctorId
    );


    // =====================================================
    // NEW FEATURE 18
    // Cancel Appointment
    // ===================================================== //

    void cancelAppointment(
        int doctorId,
        int patientId
    );


    // =====================================================
    // NEW FEATURE 19
    // Doctor Sees Next Patient
    // ===================================================== //

    void doctorSeePatient(
        int doctorId
    );


    // =====================================================
    // NEW FEATURE 20
    // Hospital Statistics
    // ===================================================== //

    void displayStatistics();
};


// ========== MAIN PROGRAM ========== //
int main() {

    Hospital hospital;


    // =====================================================
    // TEST CASE 1
    // Registering patients
    // ===================================================== //

    int p1 =
        hospital.registerPatient(
            "John Doe",
            35,
            "555-1234"
        );

    int p2 =
        hospital.registerPatient(
            "Jane Smith",
            28,
            "555-5678"
        );

    int p3 =
        hospital.registerPatient(
            "Mike Johnson",
            45,
            "555-9012"
        );


    // =====================================================
    // TEST CASE 2
    // Adding doctors
    // ===================================================== //

    int d1 =
        hospital.addDoctor(
            "Dr. Smith",
            CARDIOLOGY
        );

    int d2 =
        hospital.addDoctor(
            "Dr. Brown",
            NEUROLOGY
        );

    int d3 =
        hospital.addDoctor(
            "Dr. Lee",
            PEDIATRICS
        );


    // =====================================================
    // TEST CASE 3
    // Admitting patients
    // ===================================================== //

    hospital.admitPatient(
        p1,
        PRIVATE_ROOM
    );

    hospital.admitPatient(
        p2,
        ICU
    );

    // Try admitting already admitted patient
    hospital.admitPatient(
        p1,
        SEMI_PRIVATE
    );


    // =====================================================
    // TEST CASE 4
    // Booking appointments
    // ===================================================== //

    hospital.bookAppointment(
        d1,
        p1
    );

    hospital.bookAppointment(
        d1,
        p2
    );

    hospital.bookAppointment(
        d2,
        p3
    );

    // Invalid doctor
    hospital.bookAppointment(
        999,
        p1
    );

    // Invalid patient
    hospital.bookAppointment(
        d1,
        999
    );


    // =====================================================
    // TEST CASE 5
    // Handling medical tests
    // ===================================================== //

    hospital.requestPatientTest(
        p1,
        "Blood Test"
    );

    hospital.requestPatientTest(
        p1,
        "X-Ray"
    );

    hospital.requestPatientTest(
        p1,
        "MRI"
    );

    hospital.displayPatientTests(
        p1
    );

    hospital.performPatientTest(
        p1
    );

    hospital.displayPatientTests(
        p1
    );


    // =====================================================
    // TEST CASE 6
    // Emergency cases
    // ===================================================== //

    hospital.addEmergency(p3);

    hospital.addEmergency(p1);

    int emergencyPatient =
        hospital.handleEmergency();

    emergencyPatient =
        hospital.handleEmergency();

    emergencyPatient =
        hospital.handleEmergency();

    // No more emergencies


    // =====================================================
    // TEST CASE 7
    // Discharging patients
    // ===================================================== //

    hospital.dischargePatient(
        p1
    );


    // =====================================================
    // TEST CASE 8
    // Displaying information
    // ===================================================== //

    hospital.displayPatientInfo(
        p1
    );

    hospital.displayPatientInfo(
        p2
    );

    hospital.displayPatientInfo(
        999
    );


    hospital.displayDoctorInfo(
        d1
    );

    hospital.displayDoctorInfo(
        d2
    );

    hospital.displayDoctorInfo(
        999
    );


    // =====================================================
    // TEST CASE 9
    // Doctor seeing patients
    // ===================================================== //

    hospital.displayDoctorAppointments(
        d1
    );

    hospital.doctorSeePatient(
        d1
    );

    hospital.displayDoctorAppointments(
        d1
    );


    // =====================================================
    // TEST CASE 10
    // Search Patient
    // ===================================================== //

    hospital.searchPatientByName(
        "John Doe"
    );

    hospital.searchPatientByName(
        "Unknown Patient"
    );


    // =====================================================
    // TEST CASE 11
    // Prescriptions
    // ===================================================== //

    hospital.prescribeMedicine(
        p1,
        "Paracetamol"
    );

    hospital.prescribeMedicine(
        p1,
        "Antibiotic"
    );

    hospital.displayPrescriptions(
        p1
    );


    // =====================================================
    // TEST CASE 12
    // Patient Billing
    // ===================================================== //

    hospital.displayPatientBill(
        p1
    );

    hospital.displayPatientBill(
        p2
    );


    // =====================================================
    // TEST CASE 13
    // Priority Emergency
    // ===================================================== //

    hospital.addPriorityEmergency(
        p1,
        2
    );

    hospital.addPriorityEmergency(
        p2,
        5
    );

    hospital.addPriorityEmergency(
        p3,
        3
    );

    hospital.addPriorityEmergency(
        p1,
        4
    );


    // =====================================================
    // TEST CASE 14
    // Handle Priority Emergencies
    // ===================================================== //

    hospital.handlePriorityEmergency();

    hospital.handlePriorityEmergency();

    hospital.handlePriorityEmergency();

    hospital.handlePriorityEmergency();


    // =====================================================
    // TEST CASE 15
    // Room Management
    // ===================================================== //

    hospital.displayRoomStatus();


    // =====================================================
    // TEST CASE 16
    // Display All Patients
    // ===================================================== //

    hospital.displayAllPatients();


    // =====================================================
    // TEST CASE 17
    // Display All Doctors
    // ===================================================== //

    hospital.displayAllDoctors();


    // =====================================================
    // TEST CASE 18
    // Cancel Appointment
    // ===================================================== //

    hospital.cancelAppointment(
        d1,
        p2
    );


    // =====================================================
    // TEST CASE 19
    // More Doctor Appointments
    // ===================================================== //

    hospital.displayDoctorAppointments(
        d1
    );

    hospital.displayDoctorAppointments(
        d2
    );


    // =====================================================
    // TEST CASE 20
    // Hospital Statistics
    // ===================================================== //

    hospital.displayStatistics();


    // =====================================================
    // TEST CASE 21
    // Edge Cases
    // ===================================================== //

    Hospital emptyHospital;

    emptyHospital.displayPatientInfo(
        1
    );

    emptyHospital.displayDoctorInfo(
        1
    );

    emptyHospital.handleEmergency();

    emptyHospital.handlePriorityEmergency();

    emptyHospital.searchPatientByName(
        "John Doe"
    );

    emptyHospital.displayAllPatients();

    emptyHospital.displayAllDoctors();

    emptyHospital.displayStatistics();


    return 0;
}
