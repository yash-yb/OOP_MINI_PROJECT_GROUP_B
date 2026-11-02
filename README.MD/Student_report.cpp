#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>
using namespace std;

class person{
    protected:
    string name;
    int age;
};

class student_details:public person{
    protected:
    string rollno;
    vector<int> marks;
    vector<string> sub_name;

    public:
    void input(){
        int n;

        cout<<"Enter Roll Number: ";
        getline(cin,rollno);

        cout<<"Enter Name: ";
        getline(cin,name);

        cout<<"Enter Age: ";
        if(!(cin>>age) || age<=0)
            throw "Invalid Age";

        cout<<"Enter Number of Subjects: ";
        if(!(cin>>n) || n<=0)
            throw "Invalid Number of Subjects";

        cin.ignore(numeric_limits<streamsize>::max(),'\n');

        marks.clear();
        sub_name.clear();

        for(int i=0;i<n;i++){
            string sub;
            int mark;

            cout<<"Enter Subject Name: ";
            getline(cin,sub);

            cout<<"Enter Marks: ";
            if(!(cin>>mark) || mark<0 || mark>100)
                throw "Invalid Marks";

            cin.ignore(numeric_limits<streamsize>::max(),'\n');

            sub_name.push_back(sub);
            marks.push_back(mark);
        }
    }

    float average(){
        int total=0;

        for(int i=0;i<marks.size();i++)
            total+=marks[i];

        if(marks.size()==0)
            throw "Division by zero";

        return (float)total/marks.size();
    }

    void display(){
        cout<<"\nName: "<<name;
        cout<<"\nRoll Number: "<<rollno;
        cout<<"\nAge: "<<age;
        cout<<"\n\nSubjects:\n";

        for(int i=0;i<marks.size();i++)
            cout<<sub_name[i]<<" : "<<marks[i]<<endl;

        cout<<"Average: "<<average()<<endl;
    }

    void edit(){
        int choice;

        cout<<"\n1. Change Name";
        cout<<"\n2. Change Age";
        cout<<"\n3. Change Subject Name";
        cout<<"\n4. Change Marks";
        cout<<"\nEnter Choice: ";
        cin>>choice;

        cin.ignore(numeric_limits<streamsize>::max(),'\n');

        switch(choice){
            case 1:
                cout<<"Enter New Name: ";
                getline(cin,name);
                break;

            case 2:
                cout<<"Enter New Age: ";
                if(!(cin>>age) || age<=0)
                    throw "Invalid Age";
                break;

            case 3:{
                int pos;
                cout<<"Enter Subject Number: ";
                cin>>pos;

                if(pos<1 || pos>sub_name.size())
                    throw "Invalid Subject Number";

                cin.ignore(numeric_limits<streamsize>::max(),'\n');

                cout<<"Enter New Subject Name: ";
                getline(cin,sub_name[pos-1]);
                break;
            }

            case 4:{
                int pos;
                cout<<"Enter Subject Number: ";
                cin>>pos;

                if(pos<1 || pos>marks.size())
                    throw "Invalid Subject Number";

                cout<<"Enter New Marks: ";
                cin>>marks[pos-1];

                if(marks[pos-1]<0 || marks[pos-1]>100)
                    throw "Invalid Marks";
                break;
            }

            default:
                throw "Invalid Choice";
        }
    }

    static vector<student_details> readAll(){
        vector<student_details> students;
        ifstream fin("students.csv");
        string line;

        while(getline(fin,line)){
            stringstream ss(line);
            student_details s;
            string temp;
            int n;

            getline(ss,s.rollno,',');
            getline(ss,s.name,',');
            getline(ss,temp,',');
            s.age=stoi(temp);

            getline(ss,temp,',');
            n=stoi(temp);

            for(int i=0;i<n;i++){
                string sub;
                int mark;

                getline(ss,sub,',');
                getline(ss,temp,',');

                mark=stoi(temp);

                s.sub_name.push_back(sub);
                s.marks.push_back(mark);
            }

            students.push_back(s);
        }

        return students;
    }

    static void saveAll(vector<student_details> students){
        ofstream fout("students.csv");

        if(!fout)
            throw "Unable to open CSV file";

        for(int i=0;i<students.size();i++){
            fout<<students[i].rollno<<",";
            fout<<students[i].name<<",";
            fout<<students[i].age<<",";
            fout<<students[i].marks.size();

            for(int j=0;j<students[i].marks.size();j++)
                fout<<","<<students[i].sub_name[j]<<","<<students[i].marks[j];

            fout<<endl;
        }

        fout.close();
    }

    static void addStudent(){
        vector<student_details> students=readAll();

        student_details s;
        s.input();

        for(int i=0;i<students.size();i++){
            if(students[i].rollno==s.rollno)
                throw "Roll Number Already Exists";
        }

        students.push_back(s);
        saveAll(students);

        cout<<"\nStudent Added Successfully!\n";
    }

    static void searchStudent(){
        vector<student_details> students=readAll();
        string roll;
        int found=-1;

        cout<<"Enter Roll Number: ";
        getline(cin,roll);

        for(int i=0;i<students.size();i++){
            if(students[i].rollno==roll){
                found=i;
                break;
            }
        }

        if(found==-1)
            throw "Student Not Found";

        students[found].display();

        int choice;
        cout<<"\n1. Edit Student";
        cout<<"\n2. Delete Student";
        cout<<"\n3. Back";
        cout<<"\nEnter Choice: ";
        cin>>choice;

        cin.ignore(numeric_limits<streamsize>::max(),'\n');

        if(choice==1){
            students[found].edit();
            saveAll(students);
            cout<<"Student Updated Successfully!\n";
        }
        else if(choice==2){
            students.erase(students.begin()+found);
            saveAll(students);
            cout<<"Student Deleted Successfully!\n";
        }
        else if(choice!=3)
            throw "Invalid Choice";
    }

    static void getAllStudents(){
        vector<student_details> students=readAll();

        if(students.size()==0){
            cout<<"No Student Records Found.\n";
            return;
        }

        cout<<"\nRoll No\tName\t\tAverage\n";

        for(int i=0;i<students.size();i++){
            cout<<students[i].rollno<<"\t";
            cout<<students[i].name<<"\t\t";
            cout<<students[i].average()<<endl;
        }
    }
    static void clear_buffer(){
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }
};

int main(){
    int choice;

    do{
        cout<<"\nSTUDENT REPORT CARD SYSTEM";
        cout<<"\n1. Add Student";
        cout<<"\n2. Search Student Details";
        cout<<"\n3. Get All Students";
        cout<<"\n4. Exit";
        cout<<"\nEnter Choice: ";

        try{
            if(!(cin>>choice))
                throw "Invalid Input";

            cin.ignore(numeric_limits<streamsize>::max(),'\n');

            switch(choice){
                case 1:
                    student_details::addStudent();
                    break;

                case 2:
                    student_details::searchStudent();
                    break;

                case 3:
                    student_details::getAllStudents();
                    break;

                case 4:
                    cout<<"Exiting Program...";
                    break;

                default:
                    throw "Invalid Choice";
            }
        }
        catch(const char* error){
            cout<<"\nError: "<<error<<endl;

            if(cin.fail()){
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
            }
        }
        catch(...){
            cout<<"\nError: Invalid or corrupted data.\n";
        }

    }while(choice!=4);

    return 0;
}
