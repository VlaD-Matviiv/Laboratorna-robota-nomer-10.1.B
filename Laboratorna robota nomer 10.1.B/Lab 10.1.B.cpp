// Lab 10.1.B

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <Windows.h>

using namespace std;

enum Specialization 
{
    ComputerScience,
    Informatics,
    MathEconomics,
    PhysicsInformatics,
    LaborEducation
};

struct Student 
{
    string lastName;
    int course;
    Specialization spec;
    int physicsGrade;
    int mathGrade;
    union {
        int programmingGrade;
        int numericalMethodsGrade;
        int pedagogyGrade;
    };
};

double calculateAverage(const vector<Student>& students, int(Student::* subject)) 
{
    double sum = 0;
    int count = 0;
    for (const auto& student : students) 
    {
        sum += student.*subject;
        count++;
    }
    return count > 0 ? sum / count : 0;
}

int countHighPhysicsGrades(const vector<Student>& students) 
{
    int count = 0;
    for (const auto& student : students) 
    {
        if (student.physicsGrade == 4 || student.physicsGrade == 5) 
        {
            count++;
        }
    }
    return count;
}

string specializationToString(Specialization spec) 
{
    switch (spec) 
    {
    case ComputerScience: return "Комп'ютерні науки";
    case Informatics: return "Інформатика";
    case MathEconomics: return "Математика та економіка";
    case PhysicsInformatics: return "Фізика та інформатика";
    case LaborEducation: return "Трудове навчання";
    default: return "Невідома спеціальність";
    }
}

int main() 
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int numStudents;
    cout << "Введіть кількість студентів: ";
    cin >> numStudents;
    vector<Student> students(numStudents);

    for (int i = 0; i < numStudents; ++i) 
    {
        cout << "\nСтудент #" << (i + 1) << ":\n";
        cout << "Прізвище: ";
        cin >> students[i].lastName;
        cout << "Курс: ";
        cin >> students[i].course;
        int spec;
        cout << "Спеціальність (0 - Комп'ютерні науки, 1 - Інформатика, 2 - Математика та економіка, 3 - Фізика та інформатика, 4 - Трудове навчання): ";
        cin >> spec;
        students[i].spec = static_cast<Specialization>(spec);
        cout << "Оцінка з фізики: ";
        cin >> students[i].physicsGrade;
        cout << "Оцінка з математики: ";
        cin >> students[i].mathGrade;

        if (students[i].spec == ComputerScience) 
        {
            cout << "Оцінка з програмування: ";
            cin >> students[i].programmingGrade;
        }
        else if (students[i].spec == Informatics) 
        {
            cout << "Оцінка з чисельних методів: ";
            cin >> students[i].numericalMethodsGrade;
        }
        else 
        {
            cout << "Оцінка з педагогіки: ";
            cin >> students[i].pedagogyGrade;
        }
    }

    cout << "\nСписок студентів:\n";
    cout << setw(5) << "№" << setw(15) << "Прізвище" << setw(8) << "Курс" << setw(25) << "Спеціальність"
        << setw(10) << "Фізика" << setw(10) << "Математика" << setw(15) << "Програмування"
        << setw(15) << "Чисельні методи" << setw(15) << "Педагогіка" << endl;

    for (int i = 0; i < numStudents; ++i) 
    {
        cout << setw(5) << (i + 1)
            << setw(15) << students[i].lastName
            << setw(8) << students[i].course
            << setw(25) << specializationToString(students[i].spec)
            << setw(10) << students[i].physicsGrade
            << setw(10) << students[i].mathGrade;

        if (students[i].spec == ComputerScience) 
        {
            cout << setw(15) << students[i].programmingGrade << setw(15) << "-" << setw(15) << "-";
        }
        else if (students[i].spec == Informatics) 
        {
            cout << setw(15) << "-" << setw(15) << students[i].numericalMethodsGrade << setw(15) << "-";
        }
        else 
        {
            cout << setw(15) << "-" << setw(15) << "-" << setw(15) << students[i].pedagogyGrade;
        }
        cout << endl;
    }

    double avgPhysics = calculateAverage(students, &Student::physicsGrade);
    double avgMath = calculateAverage(students, &Student::mathGrade);

    cout << "\nСередній бал з фізики: " << avgPhysics;
    cout << "\nСередній бал з математики: " << avgMath;

    int highPhysicsGrades = countHighPhysicsGrades(students);
    cout << "\nКількість студентів з оцінкою '4' або '5' з фізики: " << highPhysicsGrades << endl;

    return 0;
}
