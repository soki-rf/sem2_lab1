#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


class Student {
    string Name;
    string GroupId;
    vector<unsigned> Ratings;
    vector<string> Subjects;
public:
    void initialize(string Name, string GroupId, vector<unsigned> Ratings, vector<string> Subjects) {
        this->Name = Name;
        this->GroupId = GroupId;
        this->Ratings = Ratings;
        this->Subjects = Subjects;
    }
    string GetName() { return Name; }
    string GetGroupId() { return GroupId; }
    unsigned GetRatingSize() { return Ratings.size(); }
    vector<string> GetSubjects() { return Subjects; }
    vector<unsigned> GetRatings() { return Ratings; }
    unsigned GetSubjectsSize() { return Subjects.size(); }
    unsigned GetSum(){
        unsigned res = 0;
        for(unsigned i: Ratings)
            res += i;
        return res;
    }
};


class Group
{
    string Id;
    vector<Student> Students;
public:
    void SetId(string id) { Id = id; }
    void SetStudents(vector<Student> students) {Students = students;}
    void AddStudent(Student student) {
        Students.push_back(student);
    }
    void DeleteStudent(Student student) {
        for (int i=0; i < Students.size(); i++)
            if (student.GetName() == Students[i].GetName())
                Students.erase(Students.begin() + i);
    }
    Student FindStudent(string name) {
        for (int i=0; i < Students.size(); i++)
            if (Students[i].GetName() == name)
                return Students[i];
        cout << "No one found" << endl;
        return Student();
    }
    void show() {
        for (Student s : Students)
            cout << s.GetName() << ' ';
        cout << endl;
    }
    void SortByName(){
        for (int i = 0; i < (Students.size()); i++){
            for (int j = i; j < (Students.size()); j++){
                if (Students[i].GetName() > Students[j].GetName()){
                    Student x = Students[i];
                    Students[i] = Students[j];
                    Students[j] = x;
                }
            }
        }
    }
    void SortByRating(){
        for (int i = 0; i < (Students.size()); i++){
            for (int j = i; j < (Students.size()); j++){
                double rate_i = (double) (Students[i].GetSum()  / Students[i].GetRatingSize());
                double rate_j = (double) (Students[j].GetSum()  / Students[j].GetRatingSize());
                if (rate_i > rate_j){
                    Student x = Students[i];
                    Students[i] = Students[j];
                    Students[j] = x;
                }
            }
        }
    }
    vector<Student> VectorMathExcellent(){
        vector<Student> res;
        for (Student& student : Students){
            unsigned n = 0;
            for (; n < student.GetSubjectsSize(); n++)
                if (student.GetSubjects()[n] == "Math")
                    break;
            if (student.GetRatings()[n] == 5)
                res.push_back(student);
        }
        return res;
    }
    size_t CountTwoness(){
        size_t res = 0;
        for (Student & student : Students)
            for (unsigned j: student.GetRatings())
                if (j == 2){
                    res += 1;
                    break;
                }
        return res;
    }
    size_t CountExcellent(){
        size_t res = 0;
        for (Student & student : Students){
            int prom = 0;
            for (unsigned j: student.GetRatings())
                if (j == 5)
                    prom += 1;
            if (prom == student.GetRatingSize())
                res += 1;
        }
        return res;
    }
};


int main(){
    Student alex;
    alex.initialize("Alex", "IU8-24", {4, 5, 3, 3}, {"AYA", "Math", "Inzha", "History"});
    Student steve;
    steve.initialize("Steve", "IU8-24", {4, 4, 3, 5}, {"AYA", "Math", "Inzha", "History"});
    Student oleg;
    oleg.initialize("Oleg", "IU8-24", {2, 3, 4, 3}, {"AYA", "Math", "Inzha", "History"});
    vector<Student> students = {alex, steve, oleg};

    Group gr1;
    gr1.SetId("IU8-24");
    gr1.SetStudents(students);

    gr1.show();
    gr1.SortByName();
    gr1.show();
    gr1.SortByRating();
    gr1.show();
    cout << gr1.CountTwoness() << endl;
    cout << gr1.CountExcellent() << endl;

    vector<Student> exMath = gr1.VectorMathExcellent();
    for (Student s : exMath)
        cout << s.GetName() << ' ';
    cout << endl;

    Student bebrik;
    bebrik.initialize("Bebrik", "IU8-24", {2, 3, 2, 3}, {"AYA", "Math", "Inzha", "History"});

    gr1.AddStudent(bebrik);
    gr1.show();

    Student x = gr1.FindStudent("Bebrik");
    cout << x.GetName() << endl;

    gr1.DeleteStudent(x);
    gr1.show();
}
