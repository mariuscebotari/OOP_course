#include <iostream>
#include <vector>
#include <limits>

class Student {
public:
    std::string name;
    std::string faculty;
    std::string specialty;
    double grade;
    bool isGraduated;

    Student(std::string name, std::string faculty, std::string specialty, double grade, bool isGraduated = false)
            : name(name), faculty(faculty), specialty(specialty), grade(grade), isGraduated(isGraduated) {}
};

Student CreateFromConsole() {
    std::cout << "Enter student name: ";
    std::string name;
    std::cin.ignore();
    std::getline(std::cin, name);

    std::cout << "Enter faculty: ";
    std::string faculty;
    std::getline(std::cin, faculty);

    std::cout << "Enter specialty: ";
    std::string specialty;
    std::getline(std::cin, specialty);

    std::cout << "Enter student grade: ";
    double grade;
    std::cin >> grade;

    std::cout << std::endl;
    return Student(name, faculty, specialty, grade);
}

void GraduateStudent(std::vector<Student>& students, const std::string& name) {
    for (Student& student : students) {
        if (student.name == name && !student.isGraduated) {
            student.isGraduated = true;
            std::cout << student.name << " has graduated.\n";
            return;
        }
    }
    std::cout << "Student not found or already graduated.\n";
}

void DisplayEnrolledStudents(const std::vector<Student>& students) {
    std::cout << "Enrolled students:\n";
    for (const Student& student : students) {
        if (!student.isGraduated) {
            std::cout << "Name: " << student.name << ", Faculty: " << student.faculty << ", Specialty: " << student.specialty
                      << ", Grade: " << student.grade << "\n";
        }
    }
}

void DisplayGraduates(const std::vector<Student>& students) {
    std::cout << "Graduates:\n";
    bool found = false;
    for (const Student& student : students) {
        if (student.isGraduated) {
            std::cout << "Name: " << student.name << ", Faculty: " << student.faculty << ", Specialty: " << student.specialty
                      << ", Grade: " << student.grade << "\n";
            found = true;
        }
    }
    if (!found) {
        std::cout << "No graduates found.\n";
    }
}

void CheckStudentFaculty(const std::vector<Student>& students, const std::string& name, const std::string& faculty) {
    for (const Student& student : students) {
        if (student.name == name) {
            if (student.faculty == faculty) {
                std::cout << student.name << " is enrolled in the faculty " << student.faculty << "\n";
            } else {
                std::cout << student.name << " is not enrolled in the faculty " << student.faculty << "\n";
            }
            return;
        }
    }
    std::cout << "Student not found.\n";
}

void ShowMenu() {
    std::cout << "1. Add student.\n";
    std::cout << "2. Graduate student.\n";
    std::cout << "3. Display enrolled students.\n";
    std::cout << "4. Display graduates.\n";
    std::cout << "5. Check student faculty.\n";
    std::cout << "6. Exit\n";
}

int main() {
    std::vector<Student> students;
    int option;

    do {
        ShowMenu();
        std::cout << "Choose an option: ";

        if (!(std::cin >> option)) {
            std::cin.clear(); // Curățăm flag-ul de eroare
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Golim buffer-ul
            std::cout << "Invalid input! Please enter a number.\n";
            continue;
        }

        switch (option) {
            case 1: {
                Student student = CreateFromConsole();
                students.push_back(student);
                std::cout << "Added student!\n";
                break;
            }
            case 2: {
                std::string name;
                std::cin.ignore(); // Ignorăm newline-ul lăsat de std::cin înainte
                std::cout << "Enter the name of the student to graduate (with spaces): ";
                std::getline(std::cin, name);

                GraduateStudent(students, name);
                break;
            }
            case 3: {
                DisplayEnrolledStudents(students);
                break;
            }
            case 4: {
                DisplayGraduates(students);
                break;
            }
            case 5: {
                std::string name, faculty;
                std::cin.ignore(); // Ignorăm newline-ul rămas
                std::cout << "Enter the student name: ";
                std::getline(std::cin, name);
                std::cout << "Enter the faculty: ";
                std::getline(std::cin, faculty);
                CheckStudentFaculty(students, name, faculty);
                break;
            }
            case 6:
                std::cout << "Exit the program.\n";
                break;
            default:
                std::cout << "Invalid option! Please enter a number between 1 and 6.\n";
        }
        std::cout << std::endl;
    } while (option != 6);

    return 0;
}