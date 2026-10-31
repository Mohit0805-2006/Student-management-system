#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#include <cstdio>
using namespace std;

const string FILE_NAME = "students.txt";

struct Student {
    int rollNo;
    string name;
    int age;
    string course;
    string email;
};

bool rollNumberExists(int rollNo) {
    ifstream file(FILE_NAME);
    Student s;
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string roll;
        if (getline(ss, roll, '|') && stoi(roll) == rollNo) {
            return true;
        }
    }
    return false;
}

void addStudent() {
    Student s;

    cout << "\nEnter roll number: ";
    cin >> s.rollNo;

    if (rollNumberExists(s.rollNo)) {
        cout << "A student with this roll number already exists.\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter name: ";
    getline(cin, s.name);
    cout << "Enter age: ";
    cin >> s.age;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter course: ";
    getline(cin, s.course);
    cout << "Enter email: ";
    getline(cin, s.email);

    ofstream file(FILE_NAME, ios::app);
    if (!file) {
        cout << "Error: unable to open data file.\n";
        return;
    }

    file << s.rollNo << '|' << s.name << '|' << s.age << '|'
         << s.course << '|' << s.email << '\n';

    cout << "Student record added successfully.\n";
}

void displayStudents() {
    ifstream file(FILE_NAME);
    if (!file) {
        cout << "\nNo student records found yet.\n";
        return;
    }

    string line;
    bool found = false;

    cout << "\n--------------- STUDENT RECORDS ---------------\n";
    cout << "Roll No.\tName\t\tAge\tCourse\t\tEmail\n";
    cout << "------------------------------------------------\n";

    while (getline(file, line)) {
        stringstream ss(line);
        string roll, name, age, course, email;

        getline(ss, roll, '|');
        getline(ss, name, '|');
        getline(ss, age, '|');
        getline(ss, course, '|');
        getline(ss, email);

        cout << roll << "\t\t" << name << "\t\t" << age
             << "\t" << course << "\t\t" << email << '\n';
        found = true;
    }

    if (!found) cout << "No student records found.\n";
}

void updateStudent() {
    int targetRoll;
    cout << "\nEnter roll number of student to update: ";
    cin >> targetRoll;

    ifstream inFile(FILE_NAME);
    if (!inFile) {
        cout << "No student records found.\n";
        return;
    }

    ofstream tempFile("students_temp.txt");
    string line;
    bool found = false;

    while (getline(inFile, line)) {
        stringstream ss(line);
        string roll, name, age, course, email;
        getline(ss, roll, '|');
        getline(ss, name, '|');
        getline(ss, age, '|');
        getline(ss, course, '|');
        getline(ss, email);

        if (stoi(roll) == targetRoll) {
            Student s;
            s.rollNo = targetRoll;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter new name: ";
            getline(cin, s.name);
            cout << "Enter new age: ";
            cin >> s.age;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter new course: ";
            getline(cin, s.course);
            cout << "Enter new email: ";
            getline(cin, s.email);

            tempFile << s.rollNo << '|' << s.name << '|' << s.age << '|'
                     << s.course << '|' << s.email << '\n';
            found = true;
        } else {
            tempFile << line << '\n';
        }
    }

    inFile.close();
    tempFile.close();

    if (found) {
        remove(FILE_NAME.c_str());
        rename("students_temp.txt", FILE_NAME.c_str());
        cout << "Student record updated successfully.\n";
    } else {
        remove("students_temp.txt");
        cout << "Student with this roll number was not found.\n";
    }
}

void deleteStudent() {
    int targetRoll;
    cout << "\nEnter roll number of student to delete: ";
    cin >> targetRoll;

    ifstream inFile(FILE_NAME);
    if (!inFile) {
        cout << "No student records found.\n";
        return;
    }

    ofstream tempFile("students_temp.txt");
    string line;
    bool found = false;

    while (getline(inFile, line)) {
        stringstream ss(line);
        string roll;
        getline(ss, roll, '|');

        if (stoi(roll) == targetRoll) {
            found = true;
        } else {
            tempFile << line << '\n';
        }
    }

    inFile.close();
    tempFile.close();

    if (found) {
        remove(FILE_NAME.c_str());
        rename("students_temp.txt", FILE_NAME.c_str());
        cout << "Student record deleted successfully.\n";
    } else {
        remove("students_temp.txt");
        cout << "Student with this roll number was not found.\n";
    }
}

int main() {
    int choice;

    do {
        cout << "\n========== STUDENT MANAGEMENT SYSTEM ==========\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Update Student\n";
        cout << "4. Delete Student\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number from 1 to 5.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: updateStudent(); break;
            case 4: deleteStudent(); break;
            case 5: cout << "Thank you for using Student Management System.\n"; break;
            default: cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
