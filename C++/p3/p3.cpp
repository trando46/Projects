// Bao Tran Do
// File: p3.cpp
// Purpose: The purpose for this is to create a priority queue system that
//      triage for a hospital emergency room. The triage nurse is going to
//      determine the patient's priority based on their injury or illness and
//      get the patient's full name along with the priority level
// Input: Ask the user to select the command-line prompt and enter information
//      for that prompt
// Process: Takes the user input and execute the prompt that the user choose

#include "PatientPriorityQueue.h"
#include "Patient.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

void welcome();
// Prints welcome message.
// IN: none
// MODIFY: none
// OUTPUT: prints the welcoming message

void goodbye();
// Prints goodbye message.
// IN: none
// MODIFY: none
// OUTPUT: prints the goodbye message

void help();
// Prints help menu.
// IN: none
// MODIFY: none
// OUTPUT: prints the help menu

bool processLine(string, PatientPriorityQueue &);
// Process the line entered from the user or read from the file.
// IN: pass in a string and a reference to the object
// MODIFY: none
// OUTPUT: return true or false

void addPatientCmd(string, PatientPriorityQueue &);
// Adds the patient to the waiting room.
// IN: pass in a string and a reference to the object
// MODIFY: none
// OUTPUT: none

void peekNextCmd(PatientPriorityQueue &);
// Displays the next patient in the waiting room that will be called.
// IN: a reference to the object
// MODIFY: none
// OUTPUT: none

void removePatientCmd(PatientPriorityQueue &);
// Removes a patient from the waiting room and displays the name on the screen.
// IN: a reference to the object
// MODIFY: none
// OUTPUT: none

void showPatientListCmd(PatientPriorityQueue &);
// Displays the list of patients in the waiting room.
// IN: a reference to the object
// MODIFY: none
// OUTPUT: none

void execCommandsFromFileCmd(string, PatientPriorityQueue &); 
// Reads a text file with each command on a separate line and executes the
// lines as if they were typed into the command prompt.
// IN: pass in a string and a reference to the object
// MODIFY: none
// OUTPUT: none

string delimitBySpace(string &);
// Delimits (by space) the string from user or file input.
// IN: a reference to the object
// MODIFY: none
// OUTPUT: none

const string MINIMAL = "minimal";   // const string for minimal
const string URGENT = "urgent";     // const string for urgent
const string EMERGENCY = "emergency";   // const string for emergency
const string IMMEDIATE = "immediate";   // const string for immediate
const string ADD = "add";       // const string for add

int main() {
	// declare variables
	string line;

	// welcome message
	welcome();

	// process commands
	PatientPriorityQueue priQueue;
	do {
		cout << "\ntriage> ";
		getline(cin, line);
	} while (processLine(line, priQueue));

	// goodbye message
	goodbye();
}

bool processLine(string line, PatientPriorityQueue &priQueue) {
	// get command
	string cmd = delimitBySpace(line);
	if (cmd.length() == 0) {
		cout << "Error: no command given.";
		return false;
	}
	
	// process user input
	if (cmd == "help")
		help();
	else if (cmd == "add")
		addPatientCmd(line, priQueue);
	else if (cmd == "peek")
		peekNextCmd(priQueue);
	else if (cmd == "next")
		removePatientCmd(priQueue);
	else if (cmd == "list")
		showPatientListCmd(priQueue);
	else if (cmd == "load")
		execCommandsFromFileCmd(line, priQueue);
	else if (cmd == "quit")
		return false;
	else
		cout << "Error: unrecognized command: " << cmd << endl;

	return true;
}

void addPatientCmd(string line, PatientPriorityQueue &priQueue) { 
	string priority, name; 

	// get priority and name
	priority = delimitBySpace(line);
	if (priority.length() == 0 || priority == ADD) {
		cout << "Error: no priority code given.\n";
		return;
	}

	name = line;
	if (name.length() == 0) {
		cout << "Error: no patient name given.\n";
		return;
	}

    if(name == IMMEDIATE || name == EMERGENCY
        || name == URGENT || name == MINIMAL ){
        cout << "Error: no patient name given.\n";
        return;
    } else if(name.length() > 0){
        if(priority == IMMEDIATE){
            priQueue.add(Patient::Level::IMMEDIATE,name);
        } else if(priority == EMERGENCY) {
            priQueue.add(Patient::Level::EMERGENCY,name);
        } else if(priority == URGENT){
            priQueue.add(Patient::Level::URGENT,name);
        } else if(priority == MINIMAL) {
            priQueue.add(Patient::Level::MINIMAL,name);
        } else {
            cout << "Error: incorrect priority.\n";
            return;
        }
        cout << "Added patient \"" << name << "\" the priority system\n";
    }
}

void peekNextCmd(PatientPriorityQueue &priQueue) {
    if(priQueue.size() == 0){
        cout << "There are no patients in the waiting area.\n";
        return;
    } else {
        cout << "Highest priority patient to be called next: "
               << priQueue.peek().displayName() << endl;
    }
}

void removePatientCmd(PatientPriorityQueue &priQueue) {
    //Check if there are any patients left
    if(priQueue.size() == 0){
        cout << "There are no patients in the waiting area.\n";
    } else {
        cout << "This patient will now be seen: "
            << priQueue.remove().displayName()<< endl;
    }

}

void showPatientListCmd(PatientPriorityQueue &priQueue) {
	cout << "# patients waiting: " << priQueue.size() << endl;
	cout << "  Arrival #   Priority Code   Patient Name\n"
		  << "+-----------+---------------+--------------+\n";
    cout << priQueue.to_string();
}

void execCommandsFromFileCmd(string filename, PatientPriorityQueue &priQueue) {
	ifstream infile;
	string line;

	// open and read from file
	infile.open(filename);
	if (infile) {
		while (getline(infile, line)) {
			cout << "\ntriage> " << line << "\n";
			// process file input 
			processLine(line, priQueue);
		} 
	} else {
		cout << "Error: could not open file.\n";
	}
	// close file
	infile.close();
}

string delimitBySpace(string &s) {
	unsigned pos = 0;
	char delimiter = ' ';
	string result = ""; 

	pos = s.find(delimiter);
	if (pos != string::npos) {
		result = s.substr(0, pos);
		s.erase(0, pos + 1);
	}
	return result;
}

void welcome() {
	cout << "Welcome!\n";
	cout << "The triage nurse is going to the determine the patient's\n";
	cout << "priority based on their injury or illness and get the patient's\n";
	cout << "full name along with the priority level. \n" ;
}

void goodbye() {
    cout << "Thank for using! Hope you have a nice stay!\n";
}	

void help() {
	cout << "add <priority-code> <patient-name>\n"
<< "            Adds the patient to the triage system.\n"
<< "            <priority-code> must be one of the 4 accepted priority codes:\n"
<< "                1. immediate 2. emergency 3. urgent 4. minimal\n"
<< "            <patient-name>: patient's full legal name (may contain spaces)"
   "\n"
<< "next        Announces the patient to be seen next. Takes into account the\n"
<< "            type of emergency and the patient's arrival order.\n"
<< "peek        Displays the patient that is next in line, but keeps in queue\n"
<< "list        Displays the list of all patients that are still waiting\n"
<< "            in the order that they have arrived.\n"
<< "load <file> Reads the file and executes the command on each line\n"
<< "help        Displays this menu\n"
<< "quit        Exits the program\n";
}
