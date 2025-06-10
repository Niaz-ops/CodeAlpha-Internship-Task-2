#include <iostream>
#include <vector>
#include <string>
using namespace std;

float GradeToGradePoints(string grade);

class course {
public:
    string name;
    int creditHours;
    float gradePoints;
};
class Practical {
    public:
    string p_name;
    string p_grade;
    int p_creditHours;
};
class Student {
    public:
    string name;
    string rollNo;
    string address;
    int age;
    vector<course> courses;
    vector<Practical> practicals;
};

int main(){
    
    vector<Student>students;
    int noOfStudents;

    cout<<"Enter number of students : ";
    cin>>noOfStudents;
    
    for(int i = 1; i <= noOfStudents; i++){
        Student stud;
        
        cout<<"Enter name of student "<<i<<" : ";
        cin>>stud.name;

        cout<<"Enter roll number of student "<<i<<" : ";
        cin>>stud.rollNo;

        cout<<"Enter address of student "<<i<<" : ";
        cin>>stud.address;

        cout<<"Enter age of student "<<i<<" : ";
        cin>>stud.age;

        int NoOfCourses;
        cout << "Enter number of courses : ";
        cin >> NoOfCourses;

        int TotalCreditHours = 0;
        float TotalGradePoints = 0;

        for (int j = 1; j <= NoOfCourses; j++) {
            course c;
            
            cout<<"\nEnter name of course: ";
            cin>>c.name;

            cout<<"Enter credit hours for course : ";
            cin>>c.creditHours;
        
            string grade;
            cout << "Enter grade: ";
            cin >> grade;

            float pointPerGrade = GradeToGradePoints( grade);
            c.gradePoints = pointPerGrade * c.creditHours;

            TotalCreditHours += c.creditHours;
            TotalGradePoints += c.gradePoints;

            stud.courses.push_back(c);
        }

        int noOfPracticals;
        cout<<"Enter number of practicals : ";
        cin>>noOfPracticals;
        float totalPracticalGradePoints = 0;

        for(int k = 1; k <= noOfPracticals; k++){
            Practical p;
            cout<<"\nEnter name of practical : ";
            cin>>p.p_name;

            cout<<"\nEnter credit hours for practical : ";
            cin>>p.p_creditHours;

            cout<<"\nEnter grade for practical : ";
            cin>>p.p_grade;

            float pointsPerPractical = GradeToGradePoints(p.p_grade);
            totalPracticalGradePoints += pointsPerPractical;

            stud.practicals.push_back(p);
        }
        students.push_back(stud);
    }

    // Display results
    for(const Student& stud : students){
        cout<<"\n\n============= Mark Sheet =============\n\n";
        cout <<"\nName: " << stud.name<<endl;
        cout<<"Roll No: " << stud.rollNo<<endl;
        cout<<"Address: " << stud.address<<endl;
        cout<<"Age: " << stud.age << endl<<endl;

        cout << "\nCourse\t\tCredit Hours\tGrade Points\n";
        float totalCreditHours = 0, totalGradePoints = 0;

        for (const course& c : stud.courses) {
            cout<<c.name <<"\t\t"<<c.creditHours<<"\t\t"<<c.gradePoints<<endl;
            totalCreditHours += c.creditHours;
            totalGradePoints += c.gradePoints;
        }
        
        float totalPracticalCreditHours = 0, totalPracticalGradePoints = 0;
        cout << "\nPractical\tCredit Hours\tGrade Points\n";
        for(const Practical& p : stud.practicals){
            
            float practicalPoints = GradeToGradePoints(p.p_grade) * p.p_creditHours;

            cout<<p.p_name<<"\t\t"<<p.p_creditHours<<"\t\t"<<p.p_grade<<endl;

            totalPracticalCreditHours += p.p_creditHours;
            totalPracticalGradePoints += practicalPoints;
        }
        float TotalQualityPoints = totalPracticalGradePoints+ totalGradePoints;
        float Totalcredithours = totalCreditHours + totalPracticalCreditHours;
        float GPA = TotalQualityPoints/ Totalcredithours;
        GPA = (int)(GPA * 100 + 0.5) / 100.0;
        cout<<"\n\nGPA = "<<GPA;
    }
    return 0;
}

float GradeToGradePoints(string grade){
    if(grade == "A+"){
        return 4.0;
    }else if(grade == "A"){
        return 3.5;
    }else if(grade == "B+"){
        return 3.0;
    }else if(grade == "B"){
        return 2.5;
    }else if(grade == "C+"){
        return 2.0;
    }else if(grade == "C"){
        return 1.5;
    }else if(grade == "C-"){
        return 1.0;
    }else{
        return 0.0;
    }
}