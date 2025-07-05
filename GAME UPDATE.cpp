#include<iostream>
#include <windows.h>
#include<conio.h>
#include<cstdlib>
#include<ctime>
#include<fstream>
using namespace std;
void track(); // track display
void header();// header display 
int choices();// display and store choices
void gotoxy(int x, int y);// x,y coordinates defination
void car();// display car design on console
void position();// game logic
void instructions();// display game rule
void hurdles();// display hurdles
int signup();// signup function get the user name and password
int signin();// check if the user exist in the file or not 
void signinheader();// signin headre
void signupheader();// signup header 
void setGameBackgroundColor();//control game color
const int NUM_HURDLES=3;
const int SCREEN_WIDTH = 80;
const int SCREEN_HEIGHT = 40;
int main()
{
	system("color 70");

	srand(time(0));// randomly seed generator
	while(true)
	{
		header();
	int n=choices();
	if(n==1)
	{
		cout<<"STARTING THE GAME..."<<endl;
		position();
	}

	else if(n==2)
	{
		instructions();
	}
	else if(n==3)
	{
		system("cls");
		signup();
	}
	else if(n==4)
	{
		system("cls");
		signin(); //calling sign in function	
	}
	else if(n==5)
	{
		system("cls");
		cout<<"QUITING..."<<endl;
		cout<<"GOODBYE!"<<endl;
		exit(0);
	}
	else
	{
		cout<<"PLEASE ENTER RIGHT CHOICE..."<<endl;
	}
	}
	
}
void track() { //print track
	for(int i=0;i<40;i++){
		cout<<"  ||										||"<<endl;
	}
}
void header() //print header
{
   cout<<"					########################################    	    "<<endl;
   cout<<"					#   WELCOME TO RACING EDGE CAR GAME    #            "<<endl;
   cout<<"					########################################    	    "<<endl;
}
int choices() // get the user choice.
{
	int x;
	cout<<"1-START GAME"<<endl;
	cout<<"2-INSTRUCTION"<<endl;
	cout<<"3-SIGNUP"<<endl;
	cout<<"4-SIGNIN"<<endl;
	cout<<"5-QUIT"<<endl;
	cout<<"SELECT AN OPTION:";
	cin>>x;
	return x;
 }
void gotoxy(int x, int y) { //control the x,y coordinates of cars and hurdles
    COORD coord; 
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void car(int x,int y){ //to print car on its x,y position of console
	gotoxy(x,y);
	cout<<" ||"<<endl;
	gotoxy(x,y+1);
	cout<<"||||"<<endl;
	gotoxy(x,y+2);
	cout<<" ||"<<endl;
	gotoxy(x,y+3);
	cout<<"||||"<<endl;
}
void hurdles(int x, int y) // to print hurdles on its x,y position of console
{
	gotoxy(x, y);
	cout<<"||||"<<endl;
	gotoxy(x,y+1);
	cout<<" || "<<endl;
	gotoxy(x,y+2);
	cout<<"||||"<<endl;
	gotoxy(x,y+3);
	cout<<" || "<<endl;
	
}
void instructions() // a function to display rules of games
{
		system("cls");
		cout<<"INSTRUCTIONS..."<<endl;
		cout<<"1- USE ARROW KEYS TO MOVE THE CAR"<<endl;
		cout<<"2- AVOID OBSTACLES TO INCREASE THE SCORE"<<endl;
		cout<<"3- AS LONG YOU PLAY GAME WILL BE MORE HARDER "<<endl;
		cout << "Press any key to return to the main menu...";
    	_getch();
    	system("cls");
}
void position() { // game logic
    int carX = 65;
    const int carY = 36;
    int hurdlesX[NUM_HURDLES];
    int hurdlesY[NUM_HURDLES];
    int hurdlesSpeed[NUM_HURDLES];
    int score = 0;
    int highScore = 0;
    int gameSpeed = 100;

    ifstream inFile("highscore.txt");
    if (inFile.is_open()) {
        inFile >> highScore;
        inFile.close();
    }

    for (int i = 0; i < NUM_HURDLES; i++) {
        hurdlesX[i] = rand() % (SCREEN_WIDTH - 10) + 5;
        hurdlesY[i] = rand() % 10;
        hurdlesSpeed[i] = rand() % 3 + 1;
    }

    while (true) {
        system("cls");
        gotoxy(90, 0);
        cout << "Score: " << score << "   High Score: " << highScore;
        track();
        car(carX, carY);

        for (int i = 0; i < NUM_HURDLES; i++) {
            hurdles(hurdlesX[i], hurdlesY[i]);
            hurdlesY[i] += hurdlesSpeed[i];

            if (hurdlesY[i] >= carY && abs(hurdlesX[i] - carX) < 5) {
                system("cls");
                cout << "GAME OVER! You hit an obstacle." << endl;
                cout << "YOUR SCORE IS: " << score << endl;
                if (score > highScore) {
                    ofstream outFile("highscore.txt");
                    if (outFile.is_open()) {
                        outFile << score;
                        outFile.close();
                    }
                    cout << "NEW HIGH SCORE!" << endl;
                }

                cout << "PRESS ANY KEY TO RETURN TO THE MAIN MENU..." << endl;
                _getch();
                system("cls");
                return;
            }

            if (hurdlesY[i] > SCREEN_HEIGHT) {
                hurdlesY[i] = 0;
                hurdlesX[i] = rand() % (SCREEN_WIDTH - 10) + 5;
                hurdlesSpeed[i] = rand() % 3 + 1;
                score++;

                if (score > 20 && gameSpeed > 50) {
                    gameSpeed -= 5; 
                }
            }
        }
		// get the control keys from user and move car left and right
        if (_kbhit()) {
            char ch = _getch();
            if (ch == -32) {
                ch = _getch();
                if (ch == 75 && carX > 5) {
                    carX -= 3;
                } else if (ch == 77 && carX < SCREEN_WIDTH - 10) {
                    carX += 3;
                }
            }
        }

        Sleep(gameSpeed);
    }
}

int signup() {
    signupheader();
    string username, password;
    cout << "Enter Username:" << endl;
    cin >> username;
    cout << "Enter Password:" << endl;
    cin >> password;
    
	ofstream out("signup_users.txt", ios::app);
    if (out.is_open()) {
        out << username <<endl<< password << endl;
        out.close();
        cout << "SIGNUP SUCCESSFUL!" << endl;
        cout<<endl;
		cout<<"PRESS ANY KEY TO EXIT MAIN MENU.."<<endl;
		_getch();
		system("cls");
		return 0;
    }
	
	else {
        cout << "Error: Could not open the file!" << endl;
        return -1;
    }
}

int signin() {
    signinheader();
    string name, pass;
    cout << "ENTER NAME: ";
    cin >> name;
    cout << "ENTER PASSWORD: ";
    cin >> pass;
    ifstream in("signup_users.txt", ios::in);
    if (!in.is_open()) {
        cout << "Error: Could not open the file! Please ensure users have signed up." << endl;
        return -1;
    }
    
    string storedUsername, storedPassword;
    bool found = false;
    while (in >> storedUsername >> storedPassword) {
        if (name == storedUsername && pass == storedPassword) {
            found = true;
            break;
        }
    }

    in.close();

    if (found) {
        cout << "LOGIN SUCCESSFULLY!" << endl;
        return 1; 
    } else {
        cout << "LOGIN FAILED: Incorrect username or password!" << endl;
        cout << "PRESS ANY KEY TO RETURN TO THE MAIN MENU..." << endl;
        _getch();  
        system("cls");  
        return 0;
    }
}

void signinheader()
{
	cout<<"					########################################    	    "<<endl;
    cout<<"					#    SIGN IN TO RACING CAR EDGE GAME   #            "<<endl;
    cout<<"					########################################    	    "<<endl;
}
void signupheader()
{
	cout<<"					########################################    	    "<<endl;
    cout<<"					#    SIGN UP TO RACING CAR EDGE GAME   #            "<<endl;
    cout<<"					########################################    	    "<<endl;
}
void setConsoleColor(int foreground, int background) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (background << 4) | foreground);
}