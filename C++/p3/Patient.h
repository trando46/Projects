// Bao Tran Do
// File: Patient.h
// November 3, 2020
// Specification file for the Patient class used to create an object of Patient
//      that contains the patient's name, arrival order, and priority.

#ifndef P3_PATIENT_H
#define P3_PATIENT_H

#include <string>
#include <sstream>
#include <iomanip>
using std::setw;
using namespace std;

class Patient {

public:

    enum Level{IMMEDIATE = 1, EMERGENCY = 2, URGENT = 3, MINIMAL = 4};
    // enum class to hold the priority code with its representation of level

    Patient(Level priorityCode = MINIMAL,string name = "");
    // Constructor that takes in two parameters
    // precondition:: priorityCode and name is an empty string
    // postcondition: the strings are now filled when values are passed in
    bool operator > (const Patient & right);
    // Overloaded assignment operator that a compare the two objects if one
    // is greater than the other. Since this is a min heap I have to reverse the
    // > to < when checking for the priority code so that this can be sorted
    // in a min heap fashion.
    // precondition: nothing to compare to
    // postcondition: return true if condition is met
    bool operator < ( const Patient & right);
    // Overloaded assignment operator that a compare the two objects if one
    // is less than the other. Similarly to the > overloaded assignment operator
    // I have to treat this as a min heap and reverse the < to > when checking
    // for the priority code so that this can be sorted in a min heap fashion.
    // precondition: nothing to compare to
    // postcondition: return true if condition is met
    void setArrival(int);
    // Set the arrival order of the patient
    // precondition: is empty
    // postcondition: contain the number of patients total (the arrival order
    //          of the patient
    string to_string();
    // Returns the string representation of the Patient class
    // precondition: none
    // postcondition: returns the string representation
    string displayName();
    // Returns the string representation the patient's name
    // precondition: none
    // postcondition: returns the string representation
    int getArrival();
    // Returns the arrival order of the patient
    // precondition: none
    // postcondition: returns the arrival order
    void setPriorityCode(Level code);
    // Set the priority code of the patient
    // precondition: is empty
    // postcondition: contain the priority code
    string getPriorityCode();
    // Returns the string representation the priority code from level order
    // precondition: level order
    // postcondition: returns the string representation
    void setName(string);
    // Set the name of the patient
    // precondition: is empty
    // postcondition: contain the patient's name

private:

    int arrivalOrder;       // Assigned arrival number
    Level priorityCode;       // Patient's assigned priority
    string name;        // Patient's full name
};

Patient::Patient(Level priorityCode, string name) {
    this -> priorityCode = priorityCode;
    this -> name = name;
}

bool Patient::operator > (const Patient & right) {
    return (priorityCode < right.priorityCode)
           || (priorityCode == right.priorityCode
               && arrivalOrder < right.arrivalOrder);
}

bool Patient::operator < (const Patient & right) {
    return (priorityCode > right.priorityCode)
           || (priorityCode == right.priorityCode
               && arrivalOrder > right.arrivalOrder);
}

string Patient::to_string(){
    stringstream ss;

    ss << setw(7) << getArrival() << "       " << left << setw(16)
       << getPriorityCode()<< displayName() << endl;
    return ss.str();
}

void Patient::setArrival(int arrival) {
    arrivalOrder = arrival;
}

string Patient::displayName(){
    stringstream ss;
    ss << name;
    return ss.str();
}

int Patient::getArrival() {
    return arrivalOrder;
}

void Patient::setPriorityCode(Level code){
    priorityCode = code;
}
string Patient::getPriorityCode() {
    string value;
    if(priorityCode == 1){
        value = "immediate";
    } else if(priorityCode == 2){
        value = "emergency";
    } else if(priorityCode == 3){
        value = "urgent";
    } else if(priorityCode == 4){
        value = "minimal";
    }
    return value;
}

void Patient::setName(string name) {
    this->name = name;
}

#endif //P3_PATIENT_H
