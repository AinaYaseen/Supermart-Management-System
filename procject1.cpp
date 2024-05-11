#include<iostream>
#include<cstring>
#include<fstream>
#include <iomanip>
#include<ctime>
using namespace std;

void Welcome();
void login();
void reg();
void mainmenu(string);
void Products(string username);
void create_userhistory(string [],double,int,string);
void show_history(string);
int get_num_of_purchases(string);
void billing(double , string ); 

int main(){
   Welcome();
}

void Welcome(){
	system("cls");
	int choice;


cout<<"\t---------------- Welcome To Aina Mart ----------------"<<endl<<endl;

cout<<" Press 1 for Login"<<endl;
cout<<" press 2 for Registraion"<<endl;
cout<<" Press 3 to Quit App"<<endl;
cout<<endl;

cout<<"Enter Number of Your choice : ";
	cin>>choice;
if(choice == 1){
	login();
}else if(choice == 2){
	reg();
}
else if(choice == 3){
	cout<<"Visit Again!";
}
}


void login(){
	system("cls");
	cout << "\n ********** **********  ****      ***   **********      **********  *************  ***********  **********  **********       "  
                "\n ********** **********  ****      ***   **********      ****        *************  ***********  **********  **********       "
                "\n ***    ***    ****     ******    ***   ***    ***      ****        *************  ***     ***  ***    ***  ****             "
                "\n ***    ***    ****     *** ***   ***   ***    ***      **********       ****      ***     ***  ***    ***  ****             "
                "\n **********    ****     ***  ***  ***   **********      **********       ****      ***     ***  **********  ********         "
                "\n **********    ****     ***   *** ***   **********            ****       ****      ***     ***  ******	   **** 		    "
                "\n ***    *** **********  ***    ******   ***    ***            ****       ****      ***********  *** ****    **********             "
                "\n ***    *** **********  ***     *****   ***    ***      **********       ****      ***********  ***   ****  **********       ";
               cout<<endl<<endl;
    string username,password,un,pw;
    int ch;
    bool isfound = false;
     
    cout<<"\t---------------- Login TO Continue ----------------"<<endl<<endl;
    cout<<" Enter username : ";
    cin>>username;
    cout<<" Enter Password : ";
 cin>>password;
    ifstream file("record.txt");
    while(file>>un>>pw){ 
        if(un == username && pw == password){
            isfound = true;
            break;
        }
    }
    file.close();

    if(isfound){
        cout<<endl<<"Successfully Login";
        
        mainmenu(username); 
    }else{
       int c;
        cout<<endl<<"\tWrong Username Or Password try Again"<<endl;
		cout<<" Register Screen press 1 : "<<endl;
		cin>>c;	
		
if(c==1){
	reg();
		}
}
}


void reg() {
    string username, password, un, pw;
    bool isfound = false;
    int c, ch;
    system("cls");
    cout << "\t---------------- Welcome To User Registration Page ----------------" << endl
         << endl;

    cout << " Enter username : ";
    cin >> username;
    cout << " Enter Password : ";
   cin>>password;
  

 
        ofstream files("record.txt", ios::app);
        files << username << " " << password << endl;
        files.close();
        cout << endl;
        cout << "\tRegistration Successful! Now you can login and enjoy our services." << endl;
        cout << endl << "Press 1 for Login Screen: ";
        cin >> c;
        if (c == 1) {
            login();  
    }
}



void mainmenu(string username){
		system("cls");
	int c;
	cout<<"\t---------------- Welcome To Home Screen ----------------"<<endl<<endl;

    cout<<" 1) View Product "<<endl;
	cout<<" 2) View History"<<endl;
	cout<<" 3) Logout"<<endl;
 
	 cout<<endl<<"Enter The Number of Your choice : ";
 	cin>>c;
 	if(c==1){
 	 Products(username);
	 }else if(c==2){
	 	show_history(username);
	 }else if(c==3){
	 	Welcome();
	 }
}

void Products(string username) {
    system("cls");
    string pname, item_name,pquantity;
    int count = 0;
    int cnt = 0;
    bool isfound = false;
    double pprice = 0;
    double tprice = 0;
    cout << "\t---------------- Product Page ----------------" << endl << endl;
    ifstream file("Product.txt");
    cout << "No.\t Name" << setw(30) << "Quantity" <<setw(20) <<"Price" << endl;
    cout<<endl<<endl;
    while (file >> pname >>pquantity>> pprice) {
        cout << count + 1 << "\t" << setw(30) << left << pname << right << setw(5) <<pquantity << setw(20)<< pprice <<endl;
        count++;
    }
    string item[count]; 
    cout << endl << " Input 0 if you are done shopping" << endl;
    while (true) {
        int item_index; // declare item_index variable
        cout << endl << " Enter the index of the item you want to buy (1-" << count << ") : ";
        cin >> item_index;

        if (item_index == 0){
            create_userhistory(item, tprice, cnt, username); 
            billing(tprice, username);
            break;
        } else if (item_index < 1 || item_index > count) {
            cout << "Invalid item index. Please try again." << endl;
            continue;
        }
        item_index--;
        ifstream infile("Product.txt");
        int current_index = 0;
        while (infile >> pname >>pquantity>> pprice) {
            if (current_index == item_index) {
                isfound = true;
                int quantity;
                cout << "Enter the quantity of the item you want to buy: ";
                cin >> quantity;
                tprice += pprice * quantity;
                item[cnt] = pname;
                cnt++;
                break; 
            }
            current_index++;
        }
        if (isfound) {
            cout << "Total Amount is: " << tprice << endl;
        } else {
            cout << "Invalid item index. Please try again." << endl;
        }
    }
}

void create_userhistory(string item_name[], double price, int count,string username) {
    ofstream outfile("history.txt", ios::app);
    outfile<<username<<" ";
	for(int i =0;i<count;i++){
		outfile<<item_name[i]<<",";
}
       outfile<<" "<<price<<endl;
}

void billing(double price, string username) {
    system("cls");
    int c;
    string address;
    int num_of_purchases = get_num_of_purchases(username); // a function to get the number of purchases made by the user
    bool is_discount = false;

    cout << "\t---------------- Billing Page ----------------" << endl << endl;
    cout << "Total Payable Amount is " << price << endl;

    if (price == 0) {
        cout << endl << "\tYou did not purchase anything";
        Products(username);
    }
    
    if (num_of_purchases > 5) {
    double discount = 0.25 * price;
    price -= discount;
    is_discount = true;
    cout << "Congratulations! You are eligible for a 25% discount on this purchase." << endl;
    cout << "Your discounted price is " << price << endl;
}

    cout << endl << " Select payment method" << endl;
    cout << " press 1 Pay With Cash" << endl;
    cout << " press 2 Pay With Card" << endl;
    cout << endl << "Enter your choice : ";
    cin >> c;

    if (c == 1) {
        cout << "Thanks for purchase! Your package will be delivered to you as soon as possible." << endl;
        int ch;
       cout<<"Press 0 to return : ";
       cin>>ch;
    if(ch==0){
   mainmenu(username);

	}
    }
    else if (c == 2) {
        unsigned short cvv;
        cout << "\tEnter the CVV number : ";
        cin >> cvv;
        cout << "Thanks for purchase!"<< endl<<endl;
          int ch;
       cout<<"Press 0 to return : ";
       cin>>ch;
    if(ch==0){
    	Products(username);
	}
    }
}

int get_num_of_purchases(string username) {
    ifstream infile("history.txt");
    string search_string = username;
	string line;
    int num_of_purchases = 0;
while (getline(infile, line)) {
        if (line.find(search_string) != string::npos) {
         num_of_purchases++;
		}
    }
    infile.close();
    return num_of_purchases;
}

void show_history(string username) {
	system("cls");
    string search_string = username;
    ifstream file("history.txt");
    string line;
    bool isfound = false;
    cout<<"\t---------------- Purchase History ----------------"<<endl<<endl;
    while (getline(file, line)) {
        if (line.find(search_string) != string::npos) {
            cout <<" "<< line << endl;
         isfound = true; 
		}
    }    
    if(isfound != true){
    	cout<<"No Purcahase History found "<<endl;
	}
    file.close();
 int c;
 cout<<"Press 0 to go back : ";
 cin>>c;
 if(c==0){
 	mainmenu(username);
 }
}


