/* Personal Digital Assistant version 2.0
(Beta version->Work in progress)
by Raghav Singh.
*/

#include<fstream>
#include<dos>
#include<iomanip>
#include<process>
#include<math>
#include<string>
#include<ctype>
#include<stdio>

using namespace std;

 //Contacts
 class contacts {
     char name[35] , eid[30] , country[20],num[15] ;
  public:
     void view();
     void add();
     void update();
     char *retnum();
     char *retname();
     };

 void contacts::add()
   {
   cout << "Enter contact name :";
    gets(name) ;
   cout << "Enter the number :";
    cin >> num ;
   cout << "Enter the email id (if any,type NULL if none) :";
    gets(eid) ;
   cout << "Enter the country : ";
    gets(country) ;
   }

 void contacts::update()
   {
   cout << "Enter the new number : ";
   cin >> num ;
   }

 const int w = 20;

 void contacts::view() {
   cout <<name<<" "<< setw(w)<<num <<" "<<setw(w)<<eid<<" "<<setw(w)<<country<<" "<<endl;
 }

 char *contacts::retnum(){ return num;}

 char *contacts::retname(){ return name;}

 void listheader(){
 cout<<"________________________________________________________________________________"<<
 "Name                      Number                Email Id.                Country "<<
 "\n________________________________________________________________________________";
 }

 void conhead(){
 cout<<"\n"
   << "\t\t\t\t Contacts"<<endl<<"" ;
 }

 int contactlist(){
   lb:
   clrscr();
   char ch,numdel[15];
   int flag=0;
   contacts tempo;
   conhead();
   cout <<"A. Add new contact"<<endl<<"B. View contacts"
   <<endl<<"C. Delete contact"
   <<endl<<"D. Search contact name"<<endl
   <<"E. Search contact number"<<endl
   <<"F. Update existing contact"<<endl<<"G. Exit"
   <<endl<<"H. Back"
   <<endl<<"\n" << "Choice : ";
     cin >> ch ;
     ch = tolower(ch);
   clrscr();

   //Add new contact
   if(ch == 'a')
     {
     conhead();
     ofstream cFile("contacts.dat",ios::binary);
     contacts c ;
     do{
	c.add();
	cFile.write((char*)&c ,sizeof(c));
	cout << "Do you wish to continue (Y/N)?";
	  cin >> ch;
	  ch = tolower(ch);
	cout << endl;
       } while(ch == 'y');
     clrscr();
     cFile.close();

    //Display all contacts
    listheader();
    ifstream cfile("contacts.dat",ios::binary);
    while(cfile.read((char*)&c,sizeof(c)))
       {
       c.view();
       cfile.close();
	}
    cout<<"________________________________________________________________________________";
    cout<<endl << "Press B to go back."<<endl<<"Press E to exit."
    <<endl << "Choice : ";
    lb2:
    cin >> ch ;
    ch = tolower(ch);

    if (ch == 'b')
       { goto lb ;}
    else if ( ch == 'e')
       { exit(0);}
    else {
	 cout << "Invalid choice, enter again :";
	 goto lb2;
	}
   }

   //View contact
   else if(ch == 'b')  {
     conhead();
     ifstream cfile("contacts.dat",ios::binary);
     contacts c;
     listheader();

     while(cfile.read((char*)&c,sizeof(c)))
       {
       c.view();
       cfile.close();
       }
     cout<<"________________________________________________________________________________"
     << endl << "Press B to go back."<<endl << "Press E to exit."
     <<endl << "Choice : ";
     lb3:
     cin >> ch ;
     ch = tolower(ch);

     if (ch == 'b')
	{ goto lb ;}
     else if ( ch == 'e')
	{ exit(0);}
     else {
	cout << "Invalid choice,enter once again :";
       goto lb3;
      }
     }

  //Delete contact
  else if(ch == 'c'){
     int flag2 =0;
     conhead();
     listheader();
     ifstream cfile("contacts.dat",ios::binary);
     contacts c;

     while(cfile.read((char*)&c,sizeof(c))){
       c.view();
       cfile.close();
       }

     cout<<"________________________________________________________________________________";
     ifstream Cfile("contacts.dat",ios::binary);
     cout << "Enter the number to be deleted :";
       cin >> numdel;
     ofstream temp("temp.dat",ios::binary);
     while(Cfile.read((char*)&c,sizeof(c))){
	  if(strcmp(numdel,c.retnum())!=0)
 //Until and unless the numbers are not the same add it to temp.dat
	     temp.write((char*)&c,sizeof(c));
	  else {
 //Once the number to be deleted and no. in directory are equal.
	     flag2 = 1;
	     tempo = c;
	     }
	  }

      Cfile.close();
      temp.close();
      remove("contacts.dat");
      rename("temp.dat","contacts.dat");

      if(flag2){
	cout <<endl<< "The deleted contact is:"<<endl;
	listheader();
	tempo.view();
	cout<<"________________________________________________________________________________";
	}
      else if(!flag2)
	{ cout <<"The given contact number doesn't exists.";}

      cout <<endl<< "Press any key to go back.";
	 getch();
	 goto lb;
      }

 //Search contact no. when person name is known.
     if(ch == 'd'){
      char nm[20];
      conhead();
      cout << endl<<"Enter the name you want to search : ";
      gets(nm);
      ifstream file("contacts.dat",ios::binary);
      contacts rec;
      file.seekg(0,ios::beg);
      int found = 0;
      while(file.read((char *) &rec, sizeof(rec)))
	 {
	 if(strcmpi(nm,rec.retname())==0)
	    {
	     found=1;
	     listheader();
	     rec.view();
	    }
	 }
      cout<<"________________________________________________________________________________";
      file.close();
      if(found==0)  {
	cout<<"\n\n---Contact Not found---\n"<<endl<<"Press any key to go back.";
	getch();
	goto lb ;
	    }
      cout <<endl<< "Press any key to go back.";
       getch();
       goto lb ;
      }

//Search name on basis of contact no
      if(ch == 'e') {
      char telno[15];
      conhead();
      cout<<endl<<"Enter the number you want to search : ";
	cin >> telno;
      ifstream file("contacts.dat",ios::binary);
      contacts rec ;
      file.seekg(0,ios::beg);
      int found=0;
      while(file.read((char *) &rec, sizeof(rec)))
	 {
	    if(strcmp(telno,rec.retnum())==0)
	       {
		found=1;
		listheader();
		rec.view();
		}
	   }
      cout<<"________________________________________________________________________________";
      file.close();
      if(found==0){
	cout<<"\n\n---Contact Not found---\n"<<endl<<"Press any key to go back.";
	getch();
	goto lb ;
      }
      cout <<endl<< "Press any key to go back.";
	 getch();
	 goto lb;
     }

    //Update existing contact
    else if(ch == 'f'){
      contacts c;
      char nm[15];
      conhead();
      listheader();
      ifstream cfile("contacts.dat",ios::binary);
      while(cfile.read((char*)&c,sizeof(c))){
	c.view();
	cfile.close();
	}
      cout<<"________________________________________________________________________________";
      ifstream file("contacts.dat",ios::binary);
      cout << "Enter the contact number to be updated :";
	cin >> nm;
      ofstream temp("temp.dat",ios::binary);
      listheader();
      ifstream FILE("contacts.dat",ios::binary);
      while(FILE.read((char*)&c,sizeof(c))){
	if(strcmp(nm,c.retnum())==0){
	   c.view();
	   cout << endl;
	   c.update();
	   cout << endl;
	   flag = 1 ;
       }
      temp.write((char*)&c,sizeof(c));
   }
      cout<<"________________________________________________________________________________";
      file.close();
      temp.close();
      remove("contacts.dat");
      rename("temp.dat","contacts.dat");

      cout <<"Contact updated successfully!"<<endl;
      listheader();
      ifstream File("contacts.dat",ios::binary);
      while(File.read((char*)&c,sizeof(c))){
	  c.view();
	  File.close();
	  }
      cout<<"________________________________________________________________________________";
      File.close();
      if(!flag)
	 cout << "The given contact doesn't exists.";

    cout<<"Press any key to go back.";
    getch();
    goto lb;
    }

    else if(ch == 'g')
      {exit(0);}
    else if(ch == 'h')
       return 1;
    else        {
       cout << "Invalid choice , refreshing page...";
       goto lb;}
    return 0;   //Just for other functions.
 }

//Calendar
char week[7][10]={"Saturday","Sunday" ,"Monday","Tuesday","Wednesday","Thursday","Friday"}  ;
char weekacter[7][10]={"Saturday","Sunday" ,"Monday","Tuesday","Wednesday","Thursday","Friday"} ;

int isvalid(int d , char m[15], int y){
if ((strcmpi(m , "january")==0||strcmpi(m , "march")==0||strcmpi( m , "may")==0||strcmpi( m , "july")==0||strcmpi(m , "august")==0 ||strcmpi( m , "october")==0 ||strcmpi( m , "december")==0) && (d >= 1 && d <= 31 ))
       return 1 ;
else if ((strcmpi(m ,"april")==0 ||strcmpi( m , "june")==0 || strcmpi(m , "september")==0 || strcmpi( m , "november" )==0) && (d >= 1 && d <= 30))
       return 1 ;
else if ( (y % 4 == 0) && ( d >= 1 && d <= 29 ) && strcmpi(m , "february" )==0)
       return 1 ;
else if (d >=1 && d<=28 && strcmpi(m , "february")==0)
       return 1 ;
else
       return 0;
       }

char* day(int d, char m[],int y);

void shift(char week[7][10]){
//Shifting the week
int j ;
char temp[10];
strcpy(temp,week[0])       ;

 for(j = 0 ; j < 7 ; j++)   {
 strcpy(week[j],week[j+1]) ;
 }
 strcpy(week[6],temp);
}

void calendar(char m[],int y,int last){
int i ,j;
char Day[15]="";

strcpy(Day,day(1,m,y)); //Which day falls on the first day of the month.

//The week gets adjusted according to the first day.
for(i = 0 ; i < 7 ; i++){
  if(strcmpi(Day,week[i])==0)  {
    for( j = 0 ; j < i ; j ++ )
      shift(week);
    }
    }

//Displaying the week.
cout<<"____________________________________________________________________________"
<< "\n\t\t\t\t"<<strupr(m)<<' '<<y<<endl
 <<"____________________________________________________________________________"<<endl;
for(i = 0 ; i < 7 ; i++)
  cout << setw(10) << week[i];

  cout << endl ;

int dray[5][7] = { 1 , 2 , 3 ,4 ,5 , 6 , 7, 8 , 9 , 10 , 11 , 12 ,13 , 14,15 , 16 , 17 , 18 , 19 , 20 , 21 ,22, 23 , 24, 25, 26 , 27 , 28 ,29, 30 ,31} ;

for(i = 0 ; i < 5 ; i++){
  for(j = 0 ; j < 7 ; j ++){
     if(dray[i][j]<=last && dray[i][j]>0)
     cout << setw(10) << dray[i][j];
     }
  cout << endl ;
  }
cout<<"____________________________________________________________________________";

//Counter acting the effect of shifting the week:
for(i = 0 ; i < 7 ;++i){
  for(j = 0 ; j < 10 ; ++j)
     week[i][j]=weekacter[i][j];}
}


char * day(int d, char m[],int y){
int a1,a2 ;
a1  = y % 100 ;  //Last two digits of year
a2 = a1 ;
a1 = a1/4 ;  //remainder dropped while division with 4 .   3
a1 = a1 + d ;

if(strcmpi( m , "january")==0||strcmpi( m , "october")==0)
  a1 = a1 + 1 ;
else if(strcmpi(m , "february")==0||strcmpi( m , "march")==0||strcmpi( m , "november")==0)
  a1 = a1 + 4 ;
else if(strcmpi(m , "april")==0 ||strcmpi( m , "july")==0)
  a1 = a1 + 0 ;
else if(strcmpi(m , "may")==0)
  a1 = a1 + 2 ;
else if(strcmpi(m , "june")==0)
  a1 = a1 + 5 ;
else if(strcmpi(m , "august")==0)
  a1 = a1 + 3 ;
else if(strcmpi(m , "september")==0||strcmpi( m , "december")==0)
  a1 = a1 + 6 ;


if((y%4==0) && strcmpi(m , "january")==0||strcmpi( m , "february")==0)
  a1-- ;

while(y > 2100)
  y-=400;

if(y>=1700 && y<=1800)
  a1 = a1 + 4 ;
else if(y>=1800 && y<=1900)
  a1 = a1 + 2 ;
else if(y>=1900 && y<=2000)
  a1 = a1 + 0 ;
else if(y>=2000 && y<=2100)
  a1 = a1 + 6 ;

a1 = a1 + a2 ;
a1 = a1 % 7 ;

char *day;

for (int i= 0 ; i < 12 ; i ++ ){
if (a1 == i)
  strcpy(day,week[i]);
  }
  return day ;
}

int Calendar()
  {
  lb:
  clrscr();

  int d ,y;
  char m[15],ch, option;

  cout<<"\n"
  <<"\t\t\t\t Calendar"<<endl<<""
  <<"A. Day calculator"<<endl<<"B. Calendar"
  <<endl<<"C. Back"
  <<"\n"
  << "Choice : ";
    cin >> option;
    option = tolower(option);
  lb2:

  if (option == 'a') {
    clrscr();
    cout<<"\n"
    <<"\t\t\t\t Day Calculator"<<endl<<""
    <<endl<< "Enter the day in month : ";
      cin >> d ;
      if(d < 0 || d > 31)
      { cout << "You have entered an invalid value,enter a value between(0-31)"
	<<endl<<"Press any key to re-enter the values.";
	getch();
	goto lb2;
	}
    cout << "Enter the month : ";
      cin >> m ;
      if(strcmpi(m,"january")!=0 && strcmpi(m,"february")!=0 && strcmpi(m,"march")!=0 &&strcmpi(m,"april")!=0  &&strcmpi(m,"may")!=0 &&strcmpi(m,"june")!=0 &&strcmpi(m,"july")!=0  &&strcmpi(m,"august")!=0 &&strcmpi(m,"september")!=0 &&strcmpi(m,"october")!=0 && strcmpi(m,"november")!=0 && strcmpi(m,"december")!=0)
	 { cout << "Invalid value entered,you have to enter the month like:January,February etc..."
	 <<endl << "Press any key to re-enter the values." ;
	 getch();
	 goto lb2;
	 }

    cout << "Enter the year : ";
      cin >> y ;
      if(y < 1700)
	  { cout << "The year should be greater than or equal to 1700 for this program to run properly."; }

    if (isvalid(d,m,y)){
    char Day[10];
    strcpy(Day,day(d,m,y));
    cout <<"It's "<< Day << endl;
    }
  else if(isvalid(d,m,y)==0){
     cout << "Invalid date,refreshing...";
     goto lb2;
     }
  cout << endl << "Press any key to go back.";
     getch();
     goto lb;
}

else if(option == 'b'){
  lb3:
  clrscr();
  cout<<"\n"
  <<"\t\t\t\t Calendar"<<"\n"
  <<endl<< "Enter the month :" ;
    cin >> m ;
  if(strcmpi(m,"january")!=0 && strcmpi(m,"february")!=0 && strcmpi(m,"march")!=0 &&strcmpi(m,"april")!=0  &&strcmpi(m,"may")!=0 &&strcmpi(m,"june")!=0 &&strcmpi(m,"july")!=0  &&strcmpi(m,"august")!=0 &&strcmpi(m,"september")!=0 &&strcmpi(m,"october")!=0 && strcmpi(m,"november")!=0 && strcmpi(m,"december")!=0)
	 { cout << "Invalid value entered,you have to enter the month like:January,February etc..."
	 <<endl << "Press any key to re-enter the values." ;
	 getch();
	 goto lb3;
	 }

  cout << "Enter the year :";
    cin >> y ;
  if(y < 1700)
    { cout << "The year should be greater than or equal to 1700 for this program to run properly."; }


// Displaying the month calendar
if(isvalid(31,m,y)==1)  {
  calendar(m,y,31);
  getch();
  goto lb;    }

else if(isvalid(30,m,y)==1) {
  calendar(m,y,30);
  getch();
  goto lb;    }

else if(isvalid(29,m,y)==1) {
  calendar(m,y,29);
  getch();
  goto lb;    }

else if(isvalid(28,m,y)==1) {
  calendar(m,y,28);
  getch();
  goto lb;   }

else{
  cout<<"Invalid date , press any key to re-enter the values.";
  getch();
  goto lb3;
    }
}

else if (option == 'c')
  return 1;

return 0;
}

//Calculator
const float pi = 3.1416;
const double e = 2.718281828;

void operands(long double &x,long double &y){
 lb:
 cout<<endl<<"Enter a = ";
   cin >> x;
   if(isalpha(x)){
   cout << "You have entered an invalid value ,press any-key to re-enter.";
   getch();
   goto lb ;
   }
 cout<<"Enter b = ";
   cin >> y;
   if(isalpha(y)){
   cout << "You have entered an invalid value ,press any-key to re-enter.";
   getch();
   goto lb ;
   }
 }

void operands(long double &x) {
  lb:
  cout <<endl<< "Enter the number :";
    cin >> x ;
    if(isalpha(x)){
    cout << "You have entered an invalid value ,press any-key to re-enter.";
    getch();
    goto lb ;
    }
    }

int calculator()
{
lb :
clrscr();
 long double a,b;
 char ch;
 cout<<"\n"
 <<"\t\t\t\t Calculator"<<endl<<""
 <<endl
 <<"Press [+] -> Addition"<<endl
 <<"Press [-] -> Subtraction"<<endl
 << "Press [/] -> Division"<<endl
 <<"Press [*] -> Multiplication"<<endl
 <<"Press [P] -> Power"<<endl
 <<"Press [R] -> Square root"<<endl
 <<"Press [s] -> sin (rad) "<<endl
 <<"Press [c] -> cos (rad) "<< endl
 <<"Press [t] -> tan (rad)" <<endl
 <<"Press [n] -> ln "<<endl
 <<"Press [l] -> log"<<endl
 <<"Press [B] -> Back "<<endl
 <<"\nPi = "<<pi <<endl
 <<"e = "<<e<<endl
 <<"\nChoice : ";
   cin >> ch;
   clrscr();
  cout <<"\nPi = "<<pi <<endl
  <<"e = "<<e<<endl;

 switch (ch)
 {
 case '+' :
   cout << "You have chosen: Addition";
   operands(a,b);
   cout<<"Sum = "<< a+b;
   break;

 case '-' :
    cout << "You have chosen: Subtraction";
   operands(a,b);
   cout<<"Difference = "<<   a-b;
   break;

 case '/' :
    cout << "You have chosen: Division";
   operands(a,b);
   cout<<"Division = "<<   a/b;
   break;

 case '*' :
    cout << "You have chosen: Multiplication";
   operands(a,b);
   cout<<"Product = "<<    a*b;
   break;

 case 'P':case 'p':
    cout << "You have chosen: Power function";
   cout << "Enter the base = ";
     cin >> a ;
   cout << "Enter the exponent = ";
     cin >> b ;
   cout << "Power = "<<pow(a,b);
   break;

 case 'R' : case 'r' :
    cout << "You have chosen: Square root";
   operands(a);
   cout << "Square root = "<<sqrt(a);
   break;

 case 'S' : case 's' :
    cout << "You have chosen: sine function";
   operands(a);
   cout << "sin("<<a<<") = "<<sin(a);
   break;

 case 'C' : case 'c' :
   cout << "You have chosen: cosine function";
   operands(a);
   cout << "cos("<<a<<") = "<<cos(a);
   break;

 case 'T' : case 't' :
   cout << "You have chosen: tangent function";
   operands(a);
   cout << "tan("<<a<<") = "<<tan(a);
   break;

  case 'N' : case 'n' :
   cout << "You have chosen: Natural logarithm";
   operands(a);
   cout << "ln("<<a<<") = "<<log(a);
   break;

  case 'L' : case 'l' :
   cout << "You have chosen: Log (base 10)";
   operands(a);
   cout << "log("<<a<<") = "<<log(a)/log(10);
   break;

  case 'B' : case 'b' : return 1;

 default:
 cout<<"Invalid operation selected,press any key to refresh.";
 getch();
 goto lb ;
 }

 cout <<endl<< "Press B to go back / Press C to continue.";
   lb2:
   cin >> ch;
 ch = tolower(ch);
 if (ch == 'b')
    return 1;
 else if (ch == 'c')
    goto lb ;
 else {
    cout << "Invalid input, enter again...";
    goto lb2;
    }
}

void length(){
  char u,c;
  double v ;
  lb:
  clrscr();
  cout<<"\n"
  <<"\t\t\t\t Length"<<endl<<""
  << "metre (Press -> m)"<<endl <<"inch (Press -> i)"<<endl
  <<"foot (Press -> f)"<<endl << "yard (Press -> y)"<<endl
  <<"mile (Press -> o)"
  <<"\n"
  <<endl<<"Enter the current unit :";
    cin >> u ;
   if(!isalpha(u))
    {
    cout << "Invalid input, press any key to re-enter the value.";
    getch();
    goto lb ;
    }
  cout << "Enter the value of your current unit:";
    cin >> v ;
  cout << "Enter the unit you want to convert into :";
      cin >> c ;
  if(!isalpha(u))
    {
    cout << "Invalid input, press any key to re-enter the value.";
    getch();
    goto lb ;
    }
      u = tolower(u);
      c = tolower(c);

  if(u == 'm' && c == 'i')
     cout <<v<<" m "<<" = "<<v * 39.37 << "in ";
  else if(u == 'm' && c == 'f')
     cout <<v<<" m "<<" = "<<v * 3.28 << "ft ";
  else if(u == 'm' && c == 'y')
     cout <<v<<" m "<<" = "<<v * 1.0936 << "yd ";
  else if(u == 'm' && c == 'o')
     cout <<v<<" m "<<" = "<<v * 0.00062 << "mil ";

  else if(u == 'i' && c == 'm')
     cout <<v<<" in "<<" = "<<v * 0.0254 << " m ";
  else if(u == 'i' && c == 'f')
     cout <<v<<" in "<<" = "<<v * 0.083 << " ft ";
  else if(u == 'i' && c == 'y')
     cout <<v<<" in "<<" = "<<v * 0.027 << " yd ";
  else if(u == 'i' && c == 'o')
     cout <<v<<" in "<<" = "<<v * 0.000015 << " mil ";

 else if(u == 'f' && c == 'i')
     cout <<v<<" ft "<<" = "<<v * 12.0 << " in ";
  else if(u == 'f' && c == 'm')
     cout <<v<<" ft "<<" = "<<v * 0.3048 << " m ";
  else if(u == 'f' && c == 'y')
     cout <<v<<" ft "<<" = "<<v * 0.33 << " yd ";
  else if(u == 'f' && c == 'o')
     cout <<v<<" ft "<<" = "<<v * 12000.0 << " mil ";

  else if(u == 'y' && c == 'm')
     cout <<v<<" yd "<<" = "<<v * 0.9144 << " m ";
  else if(u == 'y' && c == 'f')
     cout <<v<<" yd "<<" = "<<v * 3.0 << " ft ";
  else if(u == 'y' && c == 'i')
     cout <<v<<" yd "<<" = "<<v * 36.0 << " in ";
  else if(u == 'y' && c == 'o')
     cout <<v<<" yd "<<" = "<<v * 0.00057<< " mil ";

  else if(u == 'o' && c == 'm')
     cout <<v<<" mil "<<" = "<<v * 0.0000254 << " m ";
  else if(u == 'o' && c == 'f')
     cout <<v<<" mil "<<" = "<<v * 0.000083 << " ft ";
  else if(u == 'o' && c == 'y')
     cout <<v<<" mil "<<" = "<<v * 0.000027 << " yd ";
  else if(u == 'o' && c == 'i')
     cout <<v<<" mil "<<" = "<<v * 0.001 << " in ";

cout <<endl<< "Press any key to go back.";
}

void temperature(){
  char u,c;
  double v ;
  lb:
  clrscr();
  cout<<"\n"
  <<"\t\t\t\t Temperature"<<endl<<""
  << "Celsius (Press -> C)"<<endl <<"Fahrenheit (Press -> F)"<<endl
  <<"Kelvin (Press -> K)"
  <<"\n"
  <<endl<<"Enter the current unit :";
    cin >> u ;
    if(!isalpha(u))
    {
    cout << "Invalid input, press any key to re-enter the value.";
    getch();
    goto lb ;
    }
  cout << "Enter the value of your current unit:";
    cin >> v ;
    if(!isalpha(u))
    {
    cout << "Invalid input, press any key to re-enter the value.";
    getch();
    goto lb ;
    }
  cout << "Enter the unit you want to convert into :";
      cin >> c ;
      u = tolower(u);
      c = tolower(c);

 if(u == 'c' && c == 'f')
   cout << v << " C "<<" = "<< (9.0/5.0) * v + 32.0 <<" F " ;
 else if(u == 'c' && c == 'k')
   cout << v << " C "<<" = "<< v+273.15<<" K ";

 if(u == 'f' && c == 'c')
   cout << v << " F "<<" = "<< (5.0*(v-32.0))/9.0 <<" C " ;
 else if(u == 'f' && c == 'k')
   cout << v << " F "<<" = "<< (v-32.0)*(5.0/9.0)+273.15<<" K ";

  if(u == 'k' && c == 'f')
   cout << v << " K "<<" = "<< 1.8*(v-273.0)+32.0 <<" F " ;
  else if(u == 'k' && c == 'c')
   cout << v << " K "<<" = "<< v-273.15<<" C ";

 cout <<endl<< "Press any key to go back.";
}

void mass(){
  char u,c;
  double v ;
  lb:
  clrscr();
  cout<<"\n"
  <<"\t\t\t\t Mass"<<endl<<""
  << "Kilogram (Press -> K)"<<endl <<"Pound (Press -> L)"<<endl
  <<"Ounce (Press -> o)"<<endl<<"Ton (Press -> t)"
  <<"\n"
  <<endl<<"Enter the current unit :";
    cin >> u ;
    if(!isalpha(u))
    {
    cout << "Invalid input, press any key to re-enter the value.";
    getch();
    goto lb ;
    }
  cout << "Enter the value of your current unit:";
    cin >> v ;
  cout << "Enter the unit you want to convert into :";
      cin >> c ;
  if(!isalpha(c))
    {
    cout << "Invalid input, press any key to re-enter the value.";
    getch();
    goto lb ;
    }
      u = tolower(u);
      c = tolower(c);

  if( u == 'k' && c == 'l')
    cout << v << " kg = "<< v * 2.2046 <<" lb ";
  else if( u == 'k' && c == 'o')
    cout << v << " kg = "<< v * 35.27 <<" oz ";
  else if( u == 'k' && c == 't')
    cout << v << " kg = "<< v * 0.001 <<" t ";

  else if( u == 'l' && c == 'k')
    cout << v << " lb = "<< v * 0.4535 <<" kg ";
  else if( u == 'l' && c == 'o')
    cout << v << " lb = "<< v * 16.0 <<" oz ";
  else if( u == 'l' && c == 't')
    cout << v << " lb = "<< v * 0.0004535 <<" t ";

  else if( u == 'o' && c == 'l')
    cout << v << " oz = "<< v * 0.0625 <<" lb ";
  else if( u == 'o' && c == 'k')
    cout << v << " oz = "<< v * 0.028 <<" kg ";
  else if( u == 'o' && c == 't')
    cout << v << " oz = "<< v * 0.000028 <<" t ";

  else if( u == 't' && c == 'l')
    cout << v << " t = "<< v * 2204.622 <<" lb ";
  else if( u == 't' && c == 'o')
    cout << v << " t = "<< v * 35273.96 <<" oz ";
  else if( u == 't' && c == 'k')
    cout << v << " t = "<< v * 1000.0 <<" kg ";

  cout <<endl<< "Press any key to go back.";
}

int convertor(){
lb:
char ch ;
clrscr();
cout<<"\n"
 <<"\t\t\t\t Convertor"<<endl<<""
  <<"A. Length"<<endl<<"B. Temperature"<<endl<<"C. Mass"<<endl<<"D. Back"<<endl
  <<""
  <<"Choice : ";
  cin >> ch ;
  ch = tolower(ch);
  if(ch == 'a')  {
    length();
    getch();
    goto lb;
    }
  else if(ch=='b'){
    temperature();
    getch();
    goto lb;
    }
  else if(ch=='c'){
    mass();
    getch();
    goto lb;
    }
  else if(ch == 'd'){
    return 1;
  }
  else   {
    cout << "Invalid input, press any key to refresh.";
    getch();
    goto lb ;
    }
}

 int timer(){
   clrscr();
   char ch ;
   int m,h,s,sec;
   lb:
   cout<<"\n"
   <<"\t\t\t\t Timer"<<endl<<""<<endl
   << "Enter the number of hours = " ;
     cin >> h ;
   cout << "Enter the number of minutes = ";
     cin >> m ;
   cout << "Enter the number of seconds = ";
     cin >> s ;
     sec = s+m*60+h*3600;
   clrscr();
   cout<<"\t\t\t\t Timer"<<endl<<"You have set the timer for:"<<endl
   <<h<<" H " <<m<< " M "<<s <<" S "<<endl <<"Press any key to start the timer";
   getch();

   while(sec){
   clrscr();
   cout<<"\t\t\t\t Timer"<<endl;
   sec--;
   if (s>0){
     s--; }
   if(s==0 && m>0 ){
     m-- ;
     s=60;}
   if(m==0 && h>0){
     h-- ;
     m=60;
     }
   if (sec==0)
     s=0;
   cout <<"Time left: "<< h<<" H "<<m<<" M "<<s<<"S";
   delay(1000);
   }
   sound(70);
   delay(1000);
   nosound();
   cout<<"\n\nTime up!"<<endl<<"Press B to start over"<<endl
   <<"Press E to exit."<<endl<<"Press M to go back"<<endl<<"Choice:";
     lb2:
     cin >> ch;
     ch = tolower(ch);
     clrscr();
     if (ch == 'b')
	goto lb;

     else if(ch == 'e')
	{exit(0);}

     else if(ch == 'm')
	return 1;

     else{
	cout << "Invalid choice, enter again : ";
	goto lb2;
	}
     return 0;
 }

  int f1=0,f2=0,f3=0,f4=0,f5=0;

 void main()
 {
  char mch, a[3] = { 'B','Y','E'};

 textbackground(BLACK);
 textcolor(GREEN);
 clrscr();
 //Welcome page
 cout << " WELCOME ";
 for(int i = 0 ; i < 3;i++){
    cout<<"  ";
     sound(70+i*100);
     delay(500);
     nosound();
    }
 clrscr();
cout<<"\n\n\n\n\n\n\n\n\n WW             WW EEEEE  LL      CCCCCC  OOOOOO  MM        MM  EEEEE"
 <<"\n  WW           WW  EE     LL      CC      OO  OO  MM MM  MM MM  EE"
  <<"\n   WW   WW    WW   EEEEE  LL      CC      OO  OO  MM   MM   MM  EEEEE"
   <<"\n    WW WW WW WW    EE     LL      CC      OO  OO  MM        MM  EE"
   <<"\n     WW     WW     EEEEE  LLLLLL  CCCCCC  OOOOOO  MM        MM  EEEEE";
delay(1000);
 //Options;

 choice:
 clrscr();
 sound(70);
 delay(500);
 nosound();

cout<<"\n" ;
cout <<"\t\t\t\tAPPLICATIONS" ;
 cout<<"\n";

cout<<"A. Contacts"<<endl<<"B. Calendar"
<<endl<<"C. Calculator"<<endl <<"D. Convertor"
<<endl<<"E. Timer"<<endl<<"F. Frequently Used";
oplb:
cout<<"\nG. Exit"
<<endl<<"";//<<"__________________________________________________________________________";

//Option chosen
cout << "\nEnter your choice:";
  cin >> mch;
  mch = tolower(mch);

  if (mch == 'a'){
     f1++;
     if(contactlist()==1)
       goto choice;}

  else if (mch == 'b'){
     f2++;
     if(Calendar()==1)
      goto choice;}

  else if (mch == 'c')  {
     f3++;
     if(calculator()==1)
      goto choice;}

  else if (mch == 'd') {
     f4++;
     if(convertor()==1)
      goto choice;}

  else if (mch == 'e'){
     f5++;
     if(timer()==1)
      goto choice;}

  else if (mch == 'g')
     {
   clrscr();
   cout<< "\n\n\n\n\n\n                   "
      << "\n                      "
      << "\n                   "
      << "\n                      "
      <<"\t\t" ;
   for(int i = 0 ; i < 3;i++){
    cout<<a[i];
     sound(70+i*100);
     delay(1000);
     nosound();
    }
     exit(0);
     }

  else if (mch == 'f'){
  clrscr();
  cout<<"\n" ;
  cout <<"\t\t\t\tFrequently Used" ;
  cout<<"\n";
   if(f1 ==0 && f2 == 0 && f3 == 0 && f4 == 0 && f5 == 0){
     cout << "No frequently used apps, press any key to go back.";
     getch();
     goto choice;
   }
   else{
       if(f1 > 0 ){
	 cout<<"\nA. Contacts";
	 }
       if(f2 > 0 ){
	 cout<<"\nB. Calendar";
	 }
       if(f3 > 0 ){
	 cout<<"\nC. Calculator";
	 }
       if(f4 > 0 ){
	 cout<<"\nD. Convertor";
	 }
       if(f5 > 0 ){
	 cout<<"\nE. Timer";
	 }
	 char ch;
	 cout << "\nQ. Back";
    goto oplb;
    }
    }

  else if(mch == 'q'){goto choice ;}
  else {
    cout <<endl<< "Your choice is invalid, refreshing main menu";
    for(int i = 0 ; i < 3;i++){
    cout<<" . ";
    delay(1000);
    }
    goto choice;
    }
 getch();
 }