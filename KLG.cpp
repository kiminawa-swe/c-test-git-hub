#include <iostream>
#include <iomanip> //to use endl
#include <vector>
#include <cctype> // to use isdigit
#include <string>
#include <conio.h> //to use _get() to make it interactive
#include <fstream> //to save and load file from txt. file
#include <cctype> //to use toupper tolower
#include <ctime> //to use time 
using namespace std;
// i created a class called guest so it can compute price according to days staying at the hotel

class guest
{
//private:----->only this class can acces this info (guest class only)
protected: //----->this class and its children can access it
     // initialize the attributes needed
     string name;
     int price; // pernight
     int days;  // days to stay
     string room;
     time_t CheckIn; //assing this the get the date

     static const int PRICE = 100;

public:
     // now use constructor //in order for it can construct the user data in main function
     guest(string n, int d, string r)
     {
          name = n;

          days = d;

          room = r;

          CheckIn=time(0); //set the check in time to start
     }
     int getDay() const
     {
          return days;
     }
     string getName() const
     { // dont forget to put const ,so it compatible with void saveFile function
          return name;
     }

     int getPrice() const
     {

          return getDay() * PRICE;
     }
     string getRoom() const
     {
          return room;
     }
     // void is called upon mention in main function
     void display_info() const
     {
          
          // cout<<right<<setw(30)<<"KLG management hotel"<<setw(10)<<endl;
          cout << setfill('-') << setw(40) << "-" << setfill(' ') << endl;
          cout << "guest's name: " << name << endl;
          cout << "room no:" << room << endl;
          cout << "total price: " << "RM" << getPrice() << endl;
     

          cout << setfill('-') << setw(40) << "-" << setfill(' ') << endl;
     }
};

//inherit from guest class
class VIP :public guest{
     public:
     VIP(string n,int d,string r) :guest(n,d,r){}

          //here constructor in guest will handle the rest

          //lets redefined the code in guest class for VIP class

          int getPrice()const{
               return (getDay()*PRICE)*0.2; //discout 80%

          };
          void display_info();

     

};
///////////////////////////////////////////////////////
// for the data to be save

void SaveFile(const vector<guest> &user_data)
{
     // use ofstream ---> ouput file stream
     ofstream outFile("KLG_db.txt"); // saved the file name tool:outFile

     // for a good practice.. use outFile.is_open()
     if (outFile.is_open())
     {
          for (int i = 0; i < user_data.size(); i++)
          {
               outFile << user_data[i].getName() << "|" << user_data[i].getDay() << "|" << user_data[i].getRoom() << endl;
          }

          outFile.close(); // close the tool after used
     }
}

void loadFile(vector<guest> &user_data)
{

     // use ifstream ,input file stream
     ifstream inFile("KLG_db.txt"); // read the txt,or aka database

     if (!inFile)
     {
          cout << "no record found" << endl;
          return;
     }
     // 1.creating a temporary variable ,because c++ cant read whole user_data[i] at once
     string tempName, tempRoom;
     // int tempDay;
     string tempDayStr;

     // 2.catch the pieces from the file(txt)

     // while(inFile >>tempName>>tempDay>>tempRoom){
     while (getline(inFile, tempName, '|'))
     { // remember getline only search char as delimiter, not string
          getline(inFile, tempDayStr, '|');
          getline(inFile, tempRoom);
          // 3.assemble the pieces into a guest object
          // its to call the constructor with the variable in it

          // check whether tempDayStr is empty or not, if empty, stoi will not work

          if (tempDayStr.empty())
          {
               continue; // continue will return back to the first loop ,
          }
          // convert back string to int
          int tempDay = stoi(tempDayStr);
          guest newguest_file(tempName, tempDay, tempRoom);

          // 4.put the finished object into the vector

          user_data.push_back(newguest_file);
     }
}

// displaying menu
void displayMenu(int choice)
{
     system("cls"); // to clear the screen to redraw menu
     system("color 0B");
     cout << endl;
     cout << endl;
     cout << endl;
     cout << endl;

     
     cout << setw(20) << "KLG management System" << setw(20) << endl;
     cout << setfill('-') << setw(40) << "-" << setfill(' ') << endl;
     cout << (choice == 1 ? ">" : " ") << "1.guest info " << endl;
     cout << (choice == 2 ? ">" : " ") << "2.display guest list" << endl;
     cout << (choice == 3 ? ">" : " ") << "3.Guest check out" << endl;
     cout << (choice == 4 ? ">" : " ") << "4.search user: " << endl;
     cout << (choice == 5 ? ">" : " ") << "exit(press 5): " << endl;
     cout << setfill('-') << setw(40) << "-" << setfill(' ') << endl;
}

string getName()
{
     string name; // declared locally
     bool valid = false;
     cout << "Enter your name: " << endl;

     while (!valid)
     {

          getline(cin, name);
          valid = true;

          for (int i = 0; i < name.size(); i++)
          {
               if (isdigit(name[i]))
               {
                    cout << "incorrect input!" << endl;
                    valid = false;
                    break; // stop the loop
               }
          }
     }
     return name;
}

////////////////////////room////////////
bool validRoom(string room)
{

     return room.size() == 4;
}

bool isTaken(const vector<guest> &user_data, string room)
{
     for (int i = 0; i < user_data.size(); i++)
     {
          if (user_data[i].getRoom() == room)
          {
               cout << "this room already occupied! " << endl;
               return true;
               // break;
          }
     }
     return false;
}

string addguestRoom(const vector<guest> &user_data)
{
     string room;
     do
     {
          cout << "enter room number: \n";
          cin >> room;
     } while (!validRoom(room) || isTaken(user_data, room));

     return room;
}

//////////check out feature////////////
void checkoutGuest(vector<guest> &user_data)
{

     int selector = 0;
     bool run = true;
     char kunci;

     while (run)
     {
          system("cls");
          cout << "GUEST CHECKOUT" << endl;
          cout << "press ESC to exit" << endl;

          // display
          for (int i = 0; i < user_data.size(); i++)
          {
               cout << (selector == i ? ">" : " ") << "NAME:" << user_data[i].getName() << " " << "ROOM:" << user_data[i].getRoom() << endl;
          }
          kunci = _getch(); // wait any kunci to be press

          if (kunci == -32 || kunci == 0)
          {
               kunci = getch(); // scrolling begun

               if (kunci == 72)
               {
                    if (selector > 0)
                         selector--;
               }
               else if (kunci == 80)
               {
                    if (selector < (user_data.size() - 1))
                         selector++;
               }
          }

          else if (kunci == 13)
          {
               if (user_data.empty())
               {
                    break;
               }
               char proceed;
               cout << "proceed?(Y/N)";
               cin >> proceed;
               if (towupper(proceed) == 'Y')
               {
                    cout << "checkout :" << user_data[selector].getName() << endl;
                    user_data.erase(user_data.begin() + selector);
                    SaveFile(user_data);
                    system("pause");
               }
               else if (towupper(proceed) == 'N')
               {
                    return;
               }
          }
          else if (kunci == 27)
          {
               run = false; // key=24 is ESC key
          }
     }

     /*for(int i=0;i<user_data.size();i++){
          user_data[i].display_info();
     }

     string room;
     cout<<"Enter room to checkout: "<<endl;
     cin>>room;
     for(int i=0;i<user_data.size();i++){
          //user_data[i].display_info(); //
          if(user_data[i].getRoom()==room){
               user_data.erase(user_data.begin()+i);

               SaveFile(user_data);
               cout<<"check out done!.."<<endl;
               system("pause");
               return;

          }

     }
     cout<<"room not found!"<<endl;

     system("pause");

     */
}

void searchGuest(const vector<guest> &user_data)
{

     for (int i = 0; i < user_data.size(); i++)
     {
          user_data[i].display_info();
     }

     string room;

     bool found = false;
     while (!found)
     {
          cout << "enter room to find" << endl;
          cin >> room;

          for (int i = 0; i < user_data.size(); i++)
          {
               if (user_data[i].getRoom() == room)
               {
                    cout << "found the room!" << endl;
                    user_data[i].display_info();
                    // cout<<"name: "<<user_data[i].getName()<<endl;
                    // cout<<"Day stay: "<<user_data[i].getDay()<<endl;
                    // cout<<"price to pay:"<<user_data[i].getPrice()<<endl;

                    found = true;
                    break;
               }
          }
          if (!found)
          {
               cout << "room not found..." << endl;
               break;
          }
     }

     system("pause");
}



int main()
{
     string name;
     int days;
     string room;
     // int choice=0;
     vector<guest> user_data; // store user data in vector

     // before the program start we should load the data first from the file

     loadFile(user_data);

     // implemeting the scrolling effect

     int choice = 1;
     bool running = true;
     char key;

     while (running)
     {
          
          // we use function to replace the menu
          displayMenu(choice);

          key = _getch(); // wait any key to be pressed

          // 224 refer to special key
          if (key == -32 || key == 0)
          {

               key = _getch();

               // scrolling logic //
               // if (key == 72 && choice > 1) choice--; // Up Arrow
               // else if (key == 80 && choice < 5) choice++; // Down Arrow

               if (key == 72)
               { // up
                    if (choice > 1)
                         choice--;
               }
               else if (key == 80)
               { // down
                    if (choice < 5)
                         choice++;
               }
          }
          else if (key >= '1' && key <= '5')
          {
               choice = key - '0'; // to convert from '1' to 1
          }
          else if (key == '1')
               choice = 1;
          else if (key == '2')
               choice = 2;
          else if (key == '3')
               choice = 3;
          else if (key == '4')
               choice = 4;
          else if (key == '5')
               choice = 5;

          // if user hit enter ,enter =13

          if (key == 13)
          {
               // remember to put one at here too
               system("cls"); // its to clear the display menu in order to show workspace only

               if (choice == 1)
               {
                    ///////////get name///////////////
                    name = getName();

                    /// entering room number///////////

                    validRoom(room);

                    room = addguestRoom(user_data);
                    isTaken(user_data, room);

                    ////////////get day/////////////

                    cout << "enter how many days to stay: \n";
                    while (!(cin >> days))
                    {
                         cin.clear();
                         cin.ignore(1000, '\n');
                         cout << "invalid input" << endl;

                         // break;
                    }
                    cin.clear();
                    cin.ignore(1000, '\n'); // clear the enter buffer

                    

                    // cin.ignore();

                    ///VIP/////
                    /* char VIP;
                    cout<<"VIP GUEST (Y/N): ?"<<endl;
                    cin>>VIP;
                    toupper(VIP);
                    if(VIP=='Y'){
                         VIP vipguest(name,days,room);
                         user_data.push_back(vipguest);
                         //SaveFile(user_data);

                    }
                    else if(VIP=='N'){
                         guest newguest(name, days, room);
                    // newguest.display_info();

                    user_data.push_back(newguest); // we stored name,days,room in vector
                    //SaveFile(user_data);
                    }*/
                   

                    
                    guest newguest(name,days,room);
                    user_data.push_back(newguest);

                    ///////////////////
                    // saving the data in the data base
                    SaveFile(user_data);
               }
               else if (choice == 2) //guest list
               {
                    cout << endl;
                    cout << endl;
                    cout << endl;
                    cout << endl;
               
                    cout << right << setw(30) << "KLG management hotel List" << setw(10) << endl;
                    for (int i = 0; i < user_data.size(); i++)
                    {
                         user_data[i].display_info();
                    }

                    system("pause"); // to make the list pause
               }
               else if (choice == 3)
               {

                    checkoutGuest(user_data);
               
               }
               else if (choice == 4)
               {

                    searchGuest(user_data);
               }
               else if (choice == 5)
               {
                    running = false;
               }
          }
     }
     cout << "alright thank you for coming!";
}
