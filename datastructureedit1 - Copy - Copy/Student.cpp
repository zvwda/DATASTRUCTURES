#include "Student.h"
using namespace std;

unordered_map<string, Course> Student::courses;
unordered_map<int, Student> Student::students;




Student::Student() {
    this->name = "";
    this->id = 000;
    this->password = "123";
}

Student::Student(string name, int id, string password, int max_hours_allowed, set<string>finished_courses, set<double> gradesfor_finished_courses, set<string>inprogress_courses, string academic_year) {
    //3ayz a4eel gpa w a7ot outo generated hina 
    this->name = name;
    this->id = id;
    this->password = password;
    this->max_hours_allowed = max_hours_allowed;
    this->finished_courses = finished_courses;
    this->gradesfor_finished_courses = gradesfor_finished_courses;
    this->inprogress_courses = inprogress_courses;
    this->academic_year = academic_year;
    studCount++;
    //write el student fel file
}
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
bool Student::login(string email,int id, string input_password)
{
    for (auto it = Student::students.begin(); it != Student::students.end(); ++it) {
        if (email == Student::students[id].email && input_password == Student::students[id].password) {
            cout << "Login successful. Welcome, " << this->name << "!" << endl;
            return true;
        }
    }
            cout << "Invalid login . Please try again." << endl;
            cout << "1- try again " << endl;
                cout << "2- break " << endl;

            return false;
        }
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
void Student::View_List_of_all_available_courses(Student s)
{
    Graph g;
    for (auto it = g.adjacency_list.begin(); it != g.adjacency_list.end(); ++it) {
        string name_of_course = it->first;

        bool found = false;
        for (int i = 0; i < it->second.size(); i++) {
            found = false;
            for (auto jt = finished_courses.begin(); jt != finished_courses.end(); ++jt) {
                if (*jt == it->second[i]) {
                    found = true;
                    break;
                }
            }
        }
        if (found) {
            //    is found in the set.
            cout << "- " << name_of_course << "  " << endl;
            s.checkprereq.push_back(name_of_course);

        }
        else {
            //  is not found in the set.
            continue;
        }
    }
}
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
void Student::filter_courses(Student s) {

    cout << "press 1 for showing your finished courses and 2 for in progress courses" << endl;
    int num;
    cin >> num;
    if (num == 1) {

        for (auto it = finished_courses.begin(); it != finished_courses.end(); ++it) {
            cout << *it << " ";
        }
        cout << endl;
    }
    else if (num == 2) {

        for (auto it = inprogress_courses.begin(); it != inprogress_courses.end(); ++it) {
            cout << *it << " ";
        }
        cout << endl;
    }

}


void Student::viewDetailsOfSpecificCourse(Course c) {
    cout << "Course name: " << c.name << endl;
    cout << "Course code: " << c.code << endl;
    if (c.requirement_or_elective) cout << "This course is a requirement" << endl;
    else cout << "This course is elective" << endl;
    cout << "Maximum number of students allowed to register for this course is: " << c.max_num_std << endl;
    cout << "Course hours: " << c.hours << endl;
    cout << "Course Instructor: " << c.instructor << endl;

}


void Student::edit_data(Student s) {
    string check_password;
    string new_password;
    cout << "enter your current password" << endl;
    cin >> check_password;

    if (check_password == s.password) {
        cout << "enter your new password";
        cin >> new_password;
        s.password = new_password;
    }
    else {
        cout << "wrong password..try again";
    }
    //overwrite el password fel file
}

void Student::viewAllCourses(Student s)
{
    cout << "Courses in Progress: " << endl;
    for (string x : inprogress_courses) {
        cout << x << " ";
    }
    cout << endl;
    cout << "finished courses: " << endl;
    for (string x : finished_courses) {
        cout << x << " ";
    }
    cout << endl;
}


void Student::registerCourse(Student s, Course c)
{
    bool finished = false;
    for (string x : s.finished_courses) {
        if (x == c.name) {
            finished = true;
        }
    }
    if (finished)
    {
        cout << "Course Already finished" << endl;
    }
    else
    {
        for (string x : checkprereq) {
            if (c.name == x) {
                // Add course to the in progress courses
                s.inprogress_courses.insert(c.name);
            }
            else {
                continue;
            }

        }
    }
}

/*float Student::get_course_credit_hours(string course_name) {

    unordered_map<string, Course>::const_iterator it;
    for (it = Student::courses.begin(); it != Student::courses.end(); it++) {
        if (it->second.name == course_name) {
            return it->second.hours;

    }
    // Course not found in map
    return -1.0;

}

// Calculate and return the cumulative GPA of the student
float Student::get_cumulative_gpa(){
    if (finished_courses.empty()) {
        return 0.0;
    }

    float total_grade_points = 0.0;
    float total_credit_hours = 0.0;

    set<string>::iterator course_it;
    set<double>::iterator grade_it;
    for (course_it = finished_courses.begin(), grade_it = gradesfor_finished_courses.begin();
        course_it != finished_courses.end() && grade_it != gradesfor_finished_courses.end();
        course_it++, grade_it++) {
        double grade = *grade_it;
        float credit_hours = get_course_credit_hours(*course_it);
        total_grade_points += grade * credit_hours;
        total_credit_hours += credit_hours;
    }

    if (total_credit_hours == 0.0) {
        return 0.0;
    }

    return total_grade_points / total_credit_hours;
}
// Print the grades of all finished courses for the student
void Student::print_finished_course_grades() {
    set<string>::iterator course_it;
    set<double>::iterator grade_it;
    for (course_it = finished_courses.begin(), grade_it = gradesfor_finished_courses.begin();
        course_it != finished_courses.end() && grade_it != gradesfor_finished_courses.end();
        course_it++, grade_it++) {
        cout << *course_it << ": " << *grade_it << endl;
    }
}
*/