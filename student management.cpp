#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Student {
public:
    int id;
    string name;
    int age;
    string course;

    void input() {
        cout << "Enter ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Age: ";
        cin >> age;
        cin.ignore();
        cout << "Enter Course: ";
        getline(cin, course);
    }

    void display() {
        cout << "\nID: " << id
             << "\nName: " << name
             << "\nAge: " << age
             << "\nCourse: " << course << endl;
    }
};

// Save all students to file
void saveToFile(vector<Student> &students) {
    ofstream file("students.txt");
    for (auto &s : students) {
        file << s.id << endl
             << s.name << endl
             << s.age << endl
             << s.course << endl;
    }
    file.close();
}

// Load students from file
void loadFromFile(vector<Student> &students) {
    ifstream file("students.txt");
    Student s;
    while (file >> s.id) {
        file.ignore();
        getline(file, s.name);
        file >> s.age;
        file.ignore();
        getline(file, s.course);
        students.push_back(s);
    }
    file.close();
}

// Add student
void addStudent(vector<Student> &students) {
    Student s;
    s.input();
    students.push_back(s);
    saveToFile(students);
    cout << "Student added successfully!\n";
}

// Display all students
void displayStudents(vector<Student> &students) {
    if (students.empty()) {
        cout << "No records found!\n";
        return;
    }
    for (auto &s : students) {
        s.display();
        cout << "-------------------";
    }
}

// Update student
void updateStudent(vector<Student> &students) {
    int id;
    cout << "Enter ID to update: ";
    cin >> id;

    for (auto &s : students) {
        if (s.id == id) {
            cout << "Enter new details:\n";
            s.input();
            saveToFile(students);
            cout << "Updated successfully!\n";
            return;
        }
    }
    cout << "Student not found!\n";
}

// Delete student
void deleteStudent(vector<Student> &students) {
    int id;
    cout << "Enter ID to delete: ";
    cin >> id;

    for (int i = 0; i < students.size(); i++) {
        if (students[i].id == id) {
            students.erase(students.begin() + i);
            saveToFile(students);
            cout << "Deleted successfully!\n";
            return;
        }
    }
    cout << "Student not found!\n";
}

// Menu
int main() {
    vector<Student> students;
    loadFromFile(students);

    int choice;

    do {
        cout << "\n===== Student Management System =====\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Update Student\n";
        cout << "4. Delete Student\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(students); break;
            case 2: displayStudents(students); break;
            case 3: updateStudent(students); break;
            case 4: deleteStudent(students); break;
            case 5: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }

    } while (choice != 5);

    return 0;
}
