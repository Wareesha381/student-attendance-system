#include<iostream>
#include<fstream>

//Creating Functions 
void SignUp();
void SignIn();
void markAttendence();
void individiualReport();
void classReport();
void defaultersStudents();
void individualAttendanceReport();
void changePassword();

//Declaring Globle Variables
char* firstName = new char[20];
char* lastName = new char[20];
char* userName = new char[10];
char* password = new char[20];
char* confirmPassword = new char[20];
const int  maxStudents = 30, maxDays = 30;


using namespace std;
int main()
{
    //Options
    int choice;

    cout << endl << "========================================================================================================================" << endl;
    cout << "\t\t\t\t\t Welcome to Attendance Recorder System" << endl;
    cout << endl << "========================================================================================================================" << endl;
    cout << "1. Sign Up" << endl;
    cout << "2. Sign In" << endl;
    cout << "3. Exit" << endl;
    cout << "=====================================\n";

    do
    {
        //Making Selection
        cout << endl;
        cout << "Select an option (1-3): ";
        cin >> choice;
        cin.ignore();

        if (choice == 1)
        {
            SignUp();
        }
        else if (choice == 2)
        {
            SignIn();
        }

        else if (choice == 3)
        {
            cout << "Exit Menu!" << endl;
            break;
        }
    } 
    while (true);
    return 0;
}


void SignUp()
{
    bool unique = true;

    //Entring data of user
    cout << endl << "\t\t\t\t=========SignUp Form==========" << endl;

    cout << "Enter First Name: ";
    cin.ignore();
    cin.getline(firstName, 20);

    cout << "Enter Last Name: ";
    cin.getline(lastName, 20);

    cout << "Enter Username: ";
    cin.getline(userName, 20);

    ifstream user("users.txt");

    if (!user.is_open())
    {
        cout << "Error in Opening User File! ";
    }
    char line[50];

    while (user.getline(line, 50))
    {
        char existingUsername[50];
        int j = 0, i = 0;

        while (line[i] != ',' && line[i] != '\0')
        {
            existingUsername[j++] = line[i++];
        }
        existingUsername[j] = '\0';

        int found = 1, k = 0;

        while (userName[k] != '\0' || existingUsername[k] != '\0')
        {
            if (userName[k] != existingUsername[k])
            {
                found = 0;
                break;
            }
            k++;
        }

        if (found == 1)
        {
            unique = false;
            break;
        }
    }
    user.close();

    if (!unique)
    {
        cout << "Username Already Exists!Choose another Username";
        return;
    }

    cout << "Enter Password: ";
    cin.getline(password, 20);

    cout << "Confirm Password: ";
    cin.getline(confirmPassword, 20);

    bool correct = true;

    for (int i = 0; i < 20; i++)
    {
        if (password[i] != confirmPassword[i])
        {
            correct = false;
            break;
        }
        else
        {
            if (password[i] == '\0' && confirmPassword[i] == '\0')
            {
                break;
            }
        }

    }
    if (!correct)
    {
        cout << "Wrong Password...Try Again! ";
        return;
    }

    ofstream signupdata("users.txt", ios::app);//writing the user detail

    if (!signupdata.is_open())
    {
        cout << "Error in opening Users file!...Try Again!" << endl;
    }
  
    //Entring new user to file
    signupdata << userName << "," << password << endl;
    signupdata.close();

    cout << "===============================" << endl;
    cout << "Account Created Successfully!" << endl;
  

}

void SignIn()
{
    bool signin = false;
    int choice;

    ifstream user("users.txt");

    if (!user.is_open())
    {
        cout << "Error in opening User File!";
        return;
    }

    char* signInusername = new char[20];
    char* signInpassword = new char[20];

    cout << endl << "\t\t\t\t=========SignIn Form==========" << endl;

    cout << "Enter Username: ";
    cin.getline(signInusername, 20);

    cout << "Enter Password: ";
    cin.getline(signInpassword, 20);

    char fileLine[50];

    while (user.getline(fileLine, 50))
    {
        char fileUsername[20];
        char filePassword[20];

        int i = 0, j = 0;

        //Stroring All the data from file

        while (fileLine[i] != ',' && fileLine[i] != '\0')
        {
            fileUsername[j++] = fileLine[i++];
        }
        fileUsername[j] = '\0';

        if (fileLine[i] == ',')
        {
            i++;
        }
        j = 0;

        while (fileLine[i] != '\0' && fileLine[i] != '\n')
        {
            filePassword[j++] = fileLine[i++];
        }
        filePassword[j] = '\0';

        //Checking Username
        bool userNameMatch = true;
        int k = 0;

        while (fileUsername[k] != '\0' && signInusername[k] != '\0')
        {
            if (fileUsername[k] != signInusername[k])
            {
                userNameMatch = false;
                break;
            }
            k++;
        }

        //Cahecking Password
        
        bool passwordMatch = true;
        k = 0;

        while (filePassword[k] != '\0' && signInpassword[k] != '\0')
        {
            if (filePassword[k] != signInpassword[k])
            {
                passwordMatch = false;
                break;
            }
            k++;
        }

        //Signing in
        if (passwordMatch && userNameMatch)
        {
            signin = true;
            break;
        }
    }
    user.close();



    if (signin)
    {

        cout << "===============================" << endl;
        cout << "Sign-In Successfully!...Congratulations..." << endl;

        //Diging into Attendence Dashboard
        cout << endl << "========================================================================================================================" << endl;
        cout << endl << "\t\t\t\t\t---- Attendance Dashboard---- " << endl;
        cout << endl << "========================================================================================================================" << endl;

        cout << "1. Mark Daily Attendance " << endl;
        cout << "2. View Individual Report" << endl;
        cout << "3. View Class Report" << endl;
        cout << "4. View Defaulters" << endl;
        cout << "5. Search Student Attendance" << endl;
        cout << " 6. Change Password" << endl;
        cout << " 7. Sign Out" << endl;

        do
        {
            //Making Choices

            cout << "Enter option(1-7): ";
            cin >> choice;

            if (choice == 1)
            {
                markAttendence();
            }

            else if (choice == 2)
            {
                individiualReport();
            }

            else if (choice == 3)
            {
                classReport();
            }

            else if (choice == 4)
            {
                defaultersStudents();
            }

            else if (choice == 5)
            {
                individualAttendanceReport();
            }

            else if (choice == 6)
            {
                changePassword();
            }

            else if (choice == 7)
            {
                cout << "You Sign Out!" << endl;
                cout << "======================================================================================================" << endl;
                break;
            }
        } 
        while (true);
    }
    else
    {
        cout << "Incorrect UserName and Password!";
    }

    //Clearing the memory
    delete[]firstName;
    delete[]lastName;
    delete[]userName;
    delete[]password;
    delete[]confirmPassword;

}

void markAttendence()
{

    cout << "-----------------------------------------------" << endl;
    cout << " \t\tDaily Attendance Entry" << endl;
    cout << "-----------------------------------------------" << endl;

    int dayNumber;
    char**studentsName = new char*[maxStudents];
    char**studentsId = new char*[maxStudents];
    const int maxNameLength = 50;
    const int maxIdLength = 20;
    int totalStudents = 0;

    for (int i = 0; i < maxStudents; i++)
    {
        studentsName[i] = new char[maxNameLength];
        studentsId[i] = new char[maxNameLength];
    }

    char lineread[100];

    ifstream studentsdata("students.txt");//reading Students from file

    if (!studentsdata.is_open())
    {
        cout << "Error in opening Student data!...Try Again...!";
        return;
    }

    while (studentsdata.getline(lineread, 100) && totalStudents < maxStudents)
    {
        int i = 0, j = 0;

        while (lineread[i] != ',' && lineread[i] != '\0')
        {
            studentsId[totalStudents][j++] = lineread[i++];
        }
        studentsId[totalStudents][j] = '\0';

        if (lineread[i] == ',')
        {
            i++;//skip comma
        }
        j = 0;

        while (lineread[i] != '\0')
        {
            studentsName[totalStudents][j++] = lineread[i++];
        }
        studentsName[totalStudents][j] = '\0';
        totalStudents++;
    }
    studentsdata.close();

    int** attendance = new int* [maxStudents];//decleration of 2D-dynamic array

    for (int i = 0; i < maxStudents; i++)
    {
        attendance[i] = new int[maxDays];

        for (int j = 0; j < maxDays; j++)
        {
            attendance[i][j] = -1;
        }
    }

    //Read existing attendance record
    ifstream readfile("attendence.txt");

    if (!readfile.is_open())
    {
        cout << "Error in opening attendance file!...Try Again!....!" << endl;
    }
    int i = 0;

    while (readfile.getline(lineread, 100) && i < totalStudents)
    {
        int index = 0;
        int j = 0, col = 0;
        char temp[50] = {};
        int s = 0;

        while (lineread[index] != '\0')
        {
            if (lineread[index] == ',' || lineread[index + 1] == '\0')
            {
                if (lineread[index] != ',' && lineread[index + 1] == '\0')
                {
                    temp[s++] = lineread[index];
                }
                temp[s] = '\0';
          
                if (col == 0)
                {
                    if (studentsId[i][0] == '\0')
                    {
                        for (int k = 0; k < maxIdLength; k++)
                        {
                            studentsId[i][k] = temp[k];
                        }
                    }
                }
                else
                {
                    int val = 0, k = 0;

                    bool neg = false;

                    if (temp[k] == '-')
                    {
                        neg = true;
                        k++;
                    }
                    val = 0;

                    while (temp[k] >= '0' && temp[k] <= '9')
                    {
                        val = val * 10 + (temp[k] - '0');
                        k++;
                    }
                    if (neg)
                    {
                        val = -val;
                    }
                    attendance[i][col - 1] = val;
                }
                s = 0;
                col++;
            }
            else
            {
                temp[s++] = lineread[index];
            }
            index++;
        }
        i++;
    }
    readfile.close();

    cout << "Enter Day Number(1-30): ";
    cin >> dayNumber;

    if (dayNumber < 1 || dayNumber>30)
    {
        cout << "Invalid Day!...Try Again! ";
        return;
    }

    cout << "Marking attendance for all students on Day " << dayNumber << ": " << endl;
    cout << endl;

    for (int i = 0; i < totalStudents; i++)
    {
        int state = -1;

        cout << "Student " << i + 1 << ": " << studentsId[i] << "- " << studentsName[i] << endl;
        cout << "Present (1)/ absent(0): ";
        cin >> state;
        cout << endl;

        if (state != 0 && state != 1)
        {
            cout << "Invalid State! ";
            i--;
            continue;
        }
        attendance[i][dayNumber - 1] = state;
        cout << endl;
    }

    ofstream studentAttendence("attendence.txt");//marking attendence of students   

    if (!studentAttendence.is_open())
    {
        cout << "Error in opening Student attendance!...Try Again...!";
        return;
    }

    for (int i = 0; i < totalStudents; i++)
    {
            studentAttendence << studentsId[i];

            for (int j = 0; j < maxDays; j++)
            {
                if (attendance[i][j] != -1)
                {
                    studentAttendence << "," << attendance[i][j];
                }
            }
            studentAttendence << endl;
    }
    studentAttendence.close();

    cout << endl;
    cout << "Attendence of day" << dayNumber << "has been recorded successfully!";
    cout << endl;

    for (int i = 0; i < maxStudents; i++)
    {
        delete[]attendance[i];
        delete[]studentsId[i];
        delete[]studentsName[i];
    }

    delete[]attendance;
    delete[]studentsId;
    delete[]studentsName;
}

void individiualReport()
{
    cout << "-----------------------------------------------" << endl;
    cout << " \t\tView Individual Report" << endl;
    cout << "-----------------------------------------------" << endl;

    ifstream studentfind("students.txt");

    if (!studentfind.is_open())
    {
        cout << "Error in Opening Students file! ";
        return;
    }


    const int  maxLineLength=200;
    const int maxNameLength = 50;
    const int maxIdLength = 20;
    
    char** studentid = new char*[maxStudents];
    char** studentName = new char*[maxStudents];
    bool StudentFound = false;
   

    for (int i = 0; i < maxStudents; i++)
    {
        studentid[i] = new char[maxIdLength];
        studentName[i] = new char[maxNameLength];
    }

    char searchId[maxIdLength];
    int totalstudent = 0;
    char line[maxLineLength];
    
    cout << "Enter the search id: ";
    cin >> searchId;

    while (studentfind.getline(line, maxLineLength) && totalstudent < maxStudents)
    {
        int i = 0, j = 0;
        bool studentFound = false;

        while (line[i] != ',' && line[i] != '\0')
        {
            studentid[totalstudent][j++] = line[i++];
        }
        studentid[totalstudent][j] = '\0';

        if (line[i] == ',')
        {
            i++;
        }
        j = 0;

        while (line[i] != '\0')
        {
            studentName[totalstudent][j++] = line[i++];
        }
        studentName[totalstudent][j] = '\0';
        totalstudent++;
    }
    studentfind.close();

    int indexing = -1;//if student not found
    for (int i = 0; i < totalstudent; i++)
    {
        bool match = true;
        for (int j = 0; j < maxIdLength; j++)
        {
            if (searchId[j] != studentid[i][j])
            {
                match = false;
                break;
            }
            if (searchId[j] == '\0' && studentid[i][j] == '\0')
            {
                break;
            }
        }

        if (match)
        {
            indexing = i;
            StudentFound = true;
            break;
        }
    }

    if (!StudentFound)
    {
        cout << "Oops!Student not Found! " << endl;

        for (int i = 0; i < maxStudents; i++)
        {
            delete[]studentName[i];
            delete[]studentid[i];
        }
        delete[]studentName;
        delete[]studentid;
        return;
    }

    ifstream attendencedind("attendence.txt");//Now reading attendence file

    if (!attendencedind.is_open())
    {
        cout << "Error opening Attendence file!";
        return;
    }

    
    bool Found = false;

    while (attendencedind.getline(line,maxLineLength))
    {
        int i = 0, j = 0;
        char currentId[maxIdLength] = {};

        while (line[i] != ',' && line[i] != '\0')
        {
            currentId[j++] = line[i++];
        }
        currentId[j] = '\0';

        bool match = true;

        for (int k = 0; k < maxIdLength; k++)
        {
            if (currentId[k] != studentid[indexing][k])
            {
                match = false;
                break;
            }
            if (currentId[k] == '\0' && studentid[indexing][k] == '\0')
            {
                break;
            }
        }
      

        if(match)
        { 
            Found = true;

            float presentDaysCount = 0.00, absentDaysCount = 0.00, totalDaysCount = 0.00;
            i++; //comma skip

            while (line[i]!='\0')
            {
                if (line[i] == '1')
                {
                    totalDaysCount++;
                    presentDaysCount++;
                }
                else if (line[i] == '0')
                {
                    absentDaysCount++;
                    totalDaysCount++;

                }
                i++;
            }

            float percentage = 0.00;

            percentage = (presentDaysCount / totalDaysCount) * 100;

            if (percentage >= 75)
            {
                cout << "Status:\tGood" << endl;
            }
            else
            {
                cout << "Status: \tDefaulter" << endl;
            }
            cout << "Report for: " << studentid[indexing] << "- " << studentName[indexing] << endl;
            cout << "Present Days: \t" << presentDaysCount << endl;
            cout << "Absent Days: \t" << absentDaysCount << endl;
            cout << "Attendence Precentage: " << percentage << endl;
            cout << "Total Days: " << totalDaysCount << endl;
            cout << "-------------------------------------------------------------------" << endl;
            break;

        }
    }
    if (!Found)
    {
        cout << "Attendence not Found! ";
    }
    attendencedind.close();

    for (int i = 0; i < maxStudents; i++)
    {
        delete[]studentid[i];
        delete[]studentName[i];
    }
    delete[]studentid;
    delete[]studentName;
}

void classReport()
{
    cout << endl << "---------------------------------------------" << endl;
    cout << " ID\tName\t\tAttendance %" << endl;
    cout << "---------------------------------------------" << endl;

    const int maxStudents = 30;
    const int maxNameLength = 50;
    char studentIds[maxStudents][10] = {};
    char studentNames[maxStudents][maxNameLength] = {};
    int presentCount[maxStudents] = {};
    int totalCount[maxStudents] = {};
    int totalStudents = 0;

    ifstream studentFileread("students.txt");

    if (!studentFileread.is_open()) {
        cout << "Error opening students.txt!" << endl;
        return;
    }

    char linename[100];

    while (studentFileread.getline(linename, 100) && totalStudents < maxStudents)
    {
        int i = 0, j = 0;

        while (linename[i] != ',' && linename[i] != '\0' && linename[i] != '\n')
        {
            studentIds[totalStudents][j++] = linename[i++];
        }
        studentIds[totalStudents][j] = '\0';

        i++; // skiping comma
        j = 0;

        while (linename[i] != '\0' && linename[i] != '\n' && linename[i] != '\r')
        {
            studentNames[totalStudents][j++] = linename[i++];
        }
        studentNames[totalStudents][j] = '\0';

        totalStudents++;
    }
    studentFileread.close();

    ifstream attendanceFile("attendence.txt");

    if (!attendanceFile.is_open())
    {
        cout << "Error opening attendence.txt!" << endl;
        return;
    }

    char attLine[150];

    while (attendanceFile.getline(attLine, 150))
    {
        int i = 0;

        // Skiping leading spaces
        while (attLine[i] == ' ') i++;

        // Read ID
        char idlimit[10];
        int j = 0;
        while (attLine[i] != ',' && attLine[i] != '\0' && attLine[i] != '\n')
        {
            idlimit[j++] = attLine[i++];
        }
        idlimit[j] = '\0';

        if (attLine[i] == ',') i++; // skip comma

        // Match student index
        int index = -1;
        for (int s = 0; s < totalStudents; s++)
        {
            int k = 0;
            while (studentIds[s][k] == idlimit[k] && studentIds[s][k] != '\0' && idlimit[k] != '\0') k++;
            if (studentIds[s][k] == '\0' && idlimit[k] == '\0')
            {
                index = s;
                break;
            }
        }

        // Count for 1s and 0s

        if (index != -1)
        {
            while (attLine[i] != '\0')
            {
                if (attLine[i] == '1')
                {
                    presentCount[index]++;
                    totalCount[index]++;
                }
                else if (attLine[i] == '0')
                {
                    totalCount[index]++;
                }
                i++;
            }
        }
    }
    attendanceFile.close();

    //Maintanig Report 
    for (int i = 0; i < totalStudents; i++)
    {
        cout << studentIds[i] << "\t" << studentNames[i];

        // Align columns
        int length = 0;
        while (studentNames[i][length] != '\0')
        {
            length++;
        }
        for (int s = 0; s < 16 - length; s++) cout << " ";

        float percentage = 0.0f;

        if (totalCount[i] > 0)
        {
            percentage = (presentCount[i] * 100.0f) / totalCount[i];

        }
        cout << percentage << "%" << endl;
    }
}

void defaultersStudents()
{
    cout << endl << "---------------------------------------------" << endl;
    cout << "\t\tDefaulter Students " << endl;
    cout << "---------------------------------------------" << endl;

    const int maxStudents = 30;
    const int maxNameLength = 50;
    char studentIds[maxStudents][10] = {};
    char studentNames[maxStudents][maxNameLength] = {};
    int presentCount[maxStudents] = {};
    int totalCount[maxStudents] = {};
    int totalStudents = 0;

    ifstream studentFileread("students.txt");

    if (!studentFileread.is_open()) {
        cout << "Error opening students.txt!" << endl;
        return;
    }

    char linename[100];
    while (studentFileread.getline(linename, 100) && totalStudents < maxStudents) {
        int i = 0, j = 0;

        while (linename[i] != ',' && linename[i] != '\0' && linename[i] != '\n') {
            studentIds[totalStudents][j++] = linename[i++];
        }
        studentIds[totalStudents][j] = '\0';

        i++; // skiping comma
        j = 0;

        while (linename[i] != '\0' && linename[i] != '\n' && linename[i] != '\r') {
            studentNames[totalStudents][j++] = linename[i++];
        }
        studentNames[totalStudents][j] = '\0';

        totalStudents++;
    }
    studentFileread.close();

    ifstream attendanceFile("attendence.txt");

    if (!attendanceFile.is_open()) {
        cout << "Error opening attendence.txt!" << endl;
        return;
    }

    char attLine[150];

    while (attendanceFile.getline(attLine, 150))
    {
        int i = 0;

        // Skiping leading spaces
        while (attLine[i] == ' ') i++;

        // Read ID
        char idlimit[10];
        int j = 0;
        while (attLine[i] != ',' && attLine[i] != '\0' && attLine[i] != '\n')
        {
            idlimit[j++] = attLine[i++];
        }
        idlimit[j] = '\0';

        if (attLine[i] == ',')
        {
            i++;// skiping comma
        }

        // Match student index
        int index = -1;
        for (int s = 0; s < totalStudents; s++) {
            int k = 0;
            while (studentIds[s][k] == idlimit[k] && studentIds[s][k] != '\0' && idlimit[k] != '\0') k++;
            if (studentIds[s][k] == '\0' && idlimit[k] == '\0') {
                index = s;
                break;
            }
        }

        // Count for 1s and 0s

        if (index != -1)
        {
            while (attLine[i] != '\0')
            {
                if (attLine[i] == '1')
                {
                    presentCount[index]++;
                    totalCount[index]++;
                }
                else if (attLine[i] == '0')
                {
                    totalCount[index]++;
                }
                i++;
            }
        }
    }
    attendanceFile.close();

    //Maintanig Report 
    cout << endl << " ID\tName\t\tAttendance %" << endl;

    for (int i = 0; i < totalStudents; i++)
    {

        // Align columns
        int length = 0;
        while (studentNames[i][length] != '\0')
        {
            length++;
        }
        for (int s = 0; s < 16 - length; s++);

        float percentage = 0.0f;

        if (totalCount[i] > 0)
        {
            percentage = (presentCount[i] * 100.0f) / totalCount[i];

        }
        if (percentage < 75)
        {
            cout << studentIds[i] << "\t" << studentNames[i];
            cout << "\t" << percentage << "%" << endl;
        }


    }

}

void individualAttendanceReport()
{
    cout << endl << "---------------------------------------------" << endl;
    cout << "\t\tIndividual Attendence Report " << endl;
    cout << "---------------------------------------------" << endl;
    const int maxStudents = 30;
    const int maxNameLength = 50;
    char studentIds[maxStudents][10] = {};
    char studentNames[maxStudents][maxNameLength] = {};
    int totalStudents = 0;

    // Step 1: Read students.txt
    ifstream studentFileread("students.txt");
    if (!studentFileread.is_open())
    {
        cout << "Error opening students.txt!" << endl;
        return;
    }

    char linename[100];

    while (studentFileread.getline(linename, 100) && totalStudents < maxStudents)
    {
        int i = 0, j = 0;

        // id
        while (linename[i] != ',' && linename[i] != '\0' && linename[i] != '\n')
        {
            studentIds[totalStudents][j++] = linename[i++];
        }
        studentIds[totalStudents][j] = '\0';

        i++; j = 0;

        //name
        while (linename[i] != '\0' && linename[i] != '\n' && linename[i] != '\r')
        {
            studentNames[totalStudents][j++] = linename[i++];
        }
        studentNames[totalStudents][j] = '\0';

        totalStudents++;
    }
    studentFileread.close();

   
    char search[50];

    cout << "\nSearch Student Attendance:\n";
    cout << "Enter ID or Name: ";
    cin.ignore();  
    cin.getline(search, 50);

//student found
   int foundIndex = -1;

    for (int i = 0; i < totalStudents; i++)
    {
         //id check
        int match = 1;
        int j = 0;
        while (search[j] != '\0' || studentIds[i][j] != '\0')
        {
            if (search[j] != studentIds[i][j])
            {
                match = 0;
                break;
            }
            j++;
        }
        if (match == 1)
        {
            foundIndex = i;
            break;
        }

        //name check
        match = 1;
        j = 0;
        while (search[j] != '\0' || studentNames[i][j] != '\0')
        {
            if (search[j] != studentNames[i][j])
            {
                match = 0;
                break;
            }
            j++;
        }
        if (match == 1)
        {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1)
    {
        cout << "Student not found!" << endl;
        return;
    }

    ifstream attendanceFile("attendence.txt");

    if (!attendanceFile.is_open())
    {
        cout << "Error opening attendence.txt!" << endl;
        return;
    }

    char targetID[10];
    int t = 0;
    while (studentIds[foundIndex][t] != '\0')
    {
        targetID[t] = studentIds[foundIndex][t];
        t++;
    }
    targetID[t] = '\0';

    bool found = false;
    char attLine[150];

    while (attendanceFile.getline(attLine, 150))
    {
        int i = 0, j = 0;

        while (attLine[i] == ' ')
        {
            i++;
        }

        char fileID[10];

        while (attLine[i] != ',' && attLine[i] != '\0')
        {
            fileID[j++] = attLine[i++];
        }
        fileID[j] = '\0';

        int match = 1;
        int a = 0;
        while (fileID[a] != '\0' || targetID[a] != '\0')
        {
            if (fileID[a] != targetID[a])
            {
                match = 0;
                break;
            }
            a++;
        }

        if (match == 1)
        {
            found = true;

            cout << "\n---------------------------------------------\n";
            cout << "ID: " << studentIds[foundIndex] << endl;
            cout << "Name: " << studentNames[foundIndex] << endl;
            cout << "Attendance: ";

            // Print attendance (after ID)
            while (attLine[i] != '\0')
            {
                if (attLine[i] == ',')
                {
                    i++;
                    if (attLine[i] == '0' || attLine[i] == '1')
                    {
                        cout << attLine[i] << " ";
                    }
                }
                else
                {
                    i++;
                }
            }

            cout << "\n---------------------------------------------\n";
            break;
        }
    }

    if (!found)
    {
        cout << "Attendance record not found for the student." << endl;
    }

    attendanceFile.close();
}

void changePassword()
{
    cout << endl << "---------------------------------------------" << endl;
    cout << "\t\tChange Password " << endl;
    cout << "---------------------------------------------" << endl;

    char userName[20];
    char oldPassword[20];
    char newconfirmPassword[20];
    char newPassword[20];

    cin.ignore(); 
    cout << "Enter Username: ";
    cin.getline(userName, 20);

    cout << "Enter Old Password: ";
    cin.getline(oldPassword, 20);

    cout << "Enter New Password: ";
    cin.getline(newPassword, 20);

    cout << "Confirm New Password: ";
    cin.getline(newconfirmPassword, 20);

    bool match = true;

    //checking if the new and pervious password matches
    for (int i = 0; i < 20; i++)
    {
        if (newconfirmPassword[i] != newPassword[i])
        {
            match = false;
            break;
        }
        if (newconfirmPassword[i] == '\0' && newPassword[i] == '\0')
            break;
    }
    if (!match)
    {
        cout << "Passwords do not match...Try Again!" << endl;
        return;
    }

    ifstream user("users.txt");//read user file
    ofstream temp("temp.txt");// write in temperory file

    if (!user.is_open() || !temp.is_open())
    {
        cout << "Error in Opening files...Try Again!" << endl;
        return;
    }

    char line[100] = {};
    bool passwordChange = false;

    while (user.getline(line, 100))
    {
        int i = 0, j = 0;
        char fileUserName[20] = {};
        char filePassword[20] = {};

        //username
        while (line[i] != ',' && line[i] != '\0')
        {
            fileUserName[j++] = line[i++];
        }
        fileUserName[j] = '\0';

        if (line[i] == ',')
        {
            i++; // Skip comma
        }

        j = 0;
        //password
        while (line[i] != '\0' && line[i] != '\n')
        {
            filePassword[j++] = line[i++];
        }
        filePassword[j] = '\0';

        bool userNameMatch = true, oldPasswordMatch = true;

        //check if uername name matches with users file
        for (int k = 0; k < 20; k++)
        {
            if (userName[k] != fileUserName[k])
            {
                userNameMatch = false;
                break;
            }

            if (userName[k] == '\0' && fileUserName[k] == '\0')
                break;
        }

        for (int k = 0; k < 20; k++)
        {
            if (oldPassword[k] != filePassword[k])
            {
                oldPasswordMatch = false;
                break;
            }
            if (oldPassword[k] == '\0' && filePassword[k] == '\0')
                break;
        }

        //feeding into temperory file
        if (userNameMatch && oldPasswordMatch)
        {
            temp << userName << "," << newPassword << endl;
            passwordChange = true;
        }
        else
        {
            temp << fileUserName << "," << filePassword << endl;
        }
    }

    user.close();
    temp.close();

    if (passwordChange)
    {
        remove("users.txt");
        if(rename("temp.txt", "users.txt")==0)
        {
            cout << "Password changed successfully!" << endl;
        }
        else
        {
            cout << "Error renaming file! Password not updated." << endl;
        }
    }
    else
    {
        remove("temp.txt");
        cout << "Incorrect Password or Username" << endl;
    }
}