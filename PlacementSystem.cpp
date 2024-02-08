
/*  Online Placement management system  */



#include <bits/stdc++.h>
using namespace std;
 
class Candidate    // Candidate class 
{
private:
    string name;
    int rollNo;
    float cgpa;
    string branch;
    vector<pair<string, string>> myCompanies;
 
public:
    Candidate(string name, int rollNo, float cgpa, string branch)
    {
        this->name = name;
        this->rollNo = rollNo;
        this->cgpa = cgpa;
        this->branch = branch;
    }
    void registration();
    void displayCompanies();
    friend class coordinator;
    friend class Recruiter;
};
 
class Recruiter  // Recruiter class
{
private:
    string name;
    float MinCGPA;
    string JobProfile;
    vector<Candidate *> Students;
 
public:
    Recruiter(string N, float C, string j)
    {
        this->name = N;
        this->MinCGPA = C;
        this->JobProfile = j;
    }
    void StudentsEngaged();
    void StudentsUpdation();
    friend class coordinator;
};
 
class coordinator  // Cordinator class
{
public:
    vector<Candidate *> students;
    vector<Recruiter *> companies;
    bool checkEligibility(Candidate *c, Recruiter *r);
    void companiesList();
    void studentsList();
    void updation(Candidate *c, char status, string n);
    Recruiter *pointerToCompany(string nam);
    Candidate *findCand(string str);
    friend class Recruiter;
    friend class Candidate;
};
 
coordinator coord;
 
void Candidate ::registration()    //Candidate regestering for company
{
    coord.companiesList();
    cout << "Enter company's index to register: " << endl;
    Candidate *ptr = this;
    int a;
    cin >> a;
    while (a != -1)
    {
        bool b = coord.checkEligibility(ptr, coord.companies[a - 1]);   //Checking eligibility, if eligible->accepted
                                                                        // else rejected to register
        if (b)
        {
            cout << "Registered!" << endl;
        }
        else
        {
            cout << "Not Eligible!" << endl;
        }
 
        cout << "Press -1 is you don't want to register for anymore companies" << endl;
        cin >> a;
    }
}
 
void Candidate ::displayCompanies()    // Display candidates name and his applied company.
{
    for (auto it : myCompanies)
    {
        cout << it.first << " -> " << it.second << endl;
    }
}
 
void Recruiter ::StudentsEngaged()   //Showing Students name to the company
{
    cout << endl;
    for (int i = 0; i < Students.size(); i++)
    {
        cout << Students[i]->name << endl;
    }
    cout << endl;
}
 
void Recruiter ::StudentsUpdation()     //Updating Student application by recruter
{
    // call function from coordinator
    int n = Students.size();
    for (int i = 0; i < n; i++)
    {
        cout << "Name of Candidate : " << Students[i]->name << endl;
        char status;
        cout << "press R for 'Rejected' and S for 'Selected for next round' :";
        cin >> status;
        cout << endl;
        vector<Candidate *>::iterator it1;
        it1 = Students.begin() + i;        //If rejected erase that students detail.
        if (status == 'R')
            Students.erase(it1);
        coord.updation(Students[i], status, name);
    }
}
 
bool coordinator ::checkEligibility(Candidate *c, Recruiter *r)   //Checking if a candidate eligible for applying that job
{
    if (c->cgpa >= r->MinCGPA)
    {
        r->Students.push_back(c);
        c->myCompanies.push_back(make_pair(r->name, "Registered"));
        return true;
    }
    return false;
}
 
void coordinator ::companiesList()   // Co-ordinator seeing copany list that registered
{
    int count = 1;
    for (auto x : companies)
    {
        cout << "Index: " << count << " ";
        cout << x->name << endl;
        cout << "Min CGPA required : " << x->MinCGPA << endl;
        cout << "Job Profile: " << x->JobProfile << endl;
        cout << endl;
        count++;
    }
}
 
void coordinator::studentsList()    // Co-ordinator seeing Student list that registered
{
    for (auto a : students)
    {
        cout << "Name : " << a->name << "\n";
        cout << "Roll No.: " <<a->rollNo << "\n";
        cout << "CGPA: " << a->cgpa << "\n";
        cout << "Branch : " <<a->branch << "\n";
        cout << endl;
    }
}

void coordinator ::updation(Candidate *c, char status, string n)  // Updating Student status by co-ordinator
{
    int ind = 0;
    for (int i = 0; i < c->myCompanies.size(); i++)
    {
        if (c->myCompanies[i].first == n)
        {
            ind = i;
        }
    }
    if (status == 'R')
    {
        c->myCompanies[ind].second = "Rejected";
    }
    else if (status == 'S')
    {
        c->myCompanies[ind].second = "Selected";
    }
}
 
Recruiter *coordinator::pointerToCompany(string nam)    // Finding company name in the list
{
    Recruiter *pt = NULL;
    for (auto it : companies)
    {
        if (nam == it->name)
        {
            pt = it;
            break;
        }
    }
    return pt;
}
 
Candidate *coordinator::findCand(string str)    // Finding candidates name in the list
{
    Candidate* pt=NULL;
    for (auto it : students)
    {
        if (str == it->name)
        {
            pt = it;
            break;
        }
    }
    return pt;
} 
 
void comenu()    // Co-ordinator section, seeing candidate and recruiter list
{
    int choice;
    do
    {
        cout << "Welcome to Coordinator Menu" << endl;
        cout << "Enter 1 for displaying companies lists: " << endl;
        cout << "Enter 2 for displaying students lists: " << endl;
        cout << "Enter 0 to exit." << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            coord.companiesList();
            break;
        case 2:
            coord.studentsList();
            break;
        case 0:
            return;
        }
    } while (choice);
}
 
void recmenu(Recruiter *pt)    //After signing out , seeing candidates and updating application
{
    int ch;
    do
    {
        cout << "Welcome to Recruiter Menu" << endl;
        cout << "Enter 1 for Updating Candidate: " << endl;
        cout << "Enter 2 for Displaying Candidate List: " << endl;
        cout << "Enter 0 for Exit: " << endl;
        cin >> ch;
        switch (ch)
        {
        case 1:
            pt->StudentsUpdation();   // Updating application, selected / rejected.
            break;
 
        case 2:
            pt->StudentsEngaged();    // view Candidates and their details.
            break;
 
        case 0:
            return;
 
        default:
            cout << "Invalid List!" << endl;
            break;
        }
    } while (ch);
}

Recruiter *makeRecruiter()    // Recruiter's Signing out and filling details
{
    cout<<"Enter company name : ";
    string n;
    cin >> n;
    cout<<"Enter minimum CGPA : ";
    float cg;
    cin >> cg;
    cout<<"Enter Job Title : ";
    string jb;
    cin >> jb;
    Recruiter *ptr = new Recruiter(n, cg, jb);
    coord.companies.push_back(ptr);
    return ptr;
}

void recmenuStarting()   // Recruter sign in/ out
{
    int ch;
    Recruiter *pt;
    string inputname;
    do
    {
        cout << "Enter 1 for Signing In: " << endl;
        cout << "Enter 2 for Signing Up: " << endl;
        cout << "Enter 3 to exit." << endl;
 
        cin >> ch;
        switch (ch)
        {
        case 1:
            cout << "Enter your name: " << endl;   // Find the name and if exists -> show else break
            cin>>inputname;
            pt = coord.pointerToCompany(inputname);
            if (pt)
                recmenu(pt);
            else
                cout << "Not Found"<<endl;
            break;
 
        case 2:
            pt = makeRecruiter();     //Go to Signing out details section
            recmenu(pt);
            break;
 
        case 3:
            return;
 
        default:
            cout << "Invalid Choice!" << endl;
            break;
        }
    } while (ch);
}
 
Candidate *getDetails(void)     //  Candidates Signing out and filling details
{
    string name, branch;
    int rollNo;
    float cgpa;
    cout << "Enter name of a Candidate: ";
    cin >> name;
    cout << "Enter roll number of Candidate: ";
    cin >> rollNo;
    cout << "Enter cgpa of Candidate: ";
    cin >> cgpa;
    cout << "Enter branch of Candidate: ";
    cin >> branch;
    Candidate *p = new Candidate(name, rollNo, cgpa, branch);
    coord.students.push_back(p);
    return p;
}

void candidatemenu(Candidate *pt)    //After candidate's signing in/out section 
{
    int ch;
    do
    {
        cout << "Welcome to the candidate dashboard" << endl;
        cout << "Enter 1 for viewing your present status with the various companies: " << endl;  
        cout << "Enter 2 for registering for a new company:" << endl;   
        cout << "Enter 0 for Exit: " << endl;
        cin >> ch;
        switch (ch)
        {
        case 1:
            pt->displayCompanies();    // Status in applied company
            break;
 
        case 2:
            pt->registration();   // Apply in new company
            break;
        case 0:
            return;
        }
 
    } while (ch);
}
 
void candMenuStarting()  // Candidates sign in/ out
{
    int ch;
    Candidate *ptrC;
    string st;
    do
    {
        cout << "Enter 1 for Signing In: " << endl;
        cout << "Enter 2 for Signing Up: " << endl;
        cout << "Enter 3 to exit." << endl;
        cin >> ch;
        switch (ch)
        {
        case 1:
            cout << "Enter your name: " << endl;   // Find the name and if exists -> show else break
            cin>>st;
            ptrC = coord.findCand(st);
            if (ptrC)
                candidatemenu(ptrC);
            else {
                cout << "Not Found"<<endl;
                break;
            }
                
        case 2:
            ptrC = getDetails();    //Go to Signing in details section
            candidatemenu(ptrC);
            break;
 
        case 3:
            return;
 
        default:
            cout << "Invalid Choice!" << endl;
            break;
        }
    } while (ch);
}
 
int main()
{
    int ch;
    do
    {
        cout << "Placement Management Program" << endl;
        
        cout << "Enter 1 for Candidate" << endl;
        cout << "Enter 2 for Recruiter" << endl;
        cout << "Enter 3 for Coordinator" << endl;
        cout << "Enter 0 to exit" << endl;
        cin >> ch;
        switch (ch)
        {
        case 1:
            candMenuStarting();   // Candidate section
            break;
 
        case 2:
            recmenuStarting();    // Recruter section
            break;
 
        case 3:
            comenu();             // Coordinator section
            break;
        
        case 0:
            exit(0);
 
        default:
            cout << "Invalid Choice!" << endl;
        }
    } while (ch);
 
    return 0;
}

