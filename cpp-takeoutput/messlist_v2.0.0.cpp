// Updated Version mess_1.2

#include<iostream>
#include<cmath>
#include<cstdlib>
#include<cstring>
using namespace std;
#define memory1  ((struct node1 *) malloc(sizeof(struct node1)));
#define memory2  ((struct node2 *) malloc(sizeof(struct node2)));
#define memory3  ((struct node3 *) malloc(sizeof(struct node3)));
#define memory4  ((struct node4 *) malloc(sizeof(struct node4)));
#define memory5  ((struct node5 *) malloc(sizeof(struct node5)));

void help();
void about();
float round_off_amount(float number);
void Finding_last_date(struct node1 *aa);
int Numbers(char ch);

struct node1 *entry_node1(struct node1 *month);
struct node2 *entry_node2(struct node2 *border, int total_border);
struct node3 *entry_node3(struct node3 *expences, int expd_type);
struct node4 *entry_node4(struct node4 *daily, struct node1 *month, int total_day);
struct node5 *entry_node5(struct node5 *elect);
void show_node1(struct node1 *month);
void show_node2(struct node2 *border, int total_day, int expd_type);
void show_node3(struct node3 *expences);
void show_node4(struct node4 *daily, int total_border, int expd_type);
void show_node5(struct node5 *elect);
void show_all(struct node1 *month, struct node2 *border, struct node3 *expences, struct node4 *daily, struct node5 *elect, int total_day, int total_border, int expd_type);

void Daily_Entry_Data(struct node1 *month, struct node2 *border, struct node3 *expences, struct node4 *daily, int total_day, int total_border, int expd_type);
void Calculation(struct node1 *month, struct node2 *border, struct node3 *expences, struct node4 *daily, struct node5 *elect, int total_day, int total_border, int expd_type);

        struct node1 // monthly_sheet   [ONE SHEET]
        {
            char month_name[10], year_name[4]; 
            int month_pos, month_days;
            int total_meal;    // monthly total meal
            float per_meal_charge;
            float total_dipo;  // monthly total diposite
            float total_expd;  // monthly total expences
            
            float total_month_cash; //total cash to complete this month
            float total_hand_cash; // cash in my hand
            float total_due;   // monthly due
            float payment;
            struct node1 *next;   
        };
        struct node2   // border_sheet  [TOTAL_BORDER SHEET]
        {
            int id;
            char name[30];
            int total_meal;
            float total_dipo;  // candidate total diposite
            float total_expd;  // candidate total expences
            float total_due;   // candidate due
            struct node2 *next;
       //DIPOSITE DETAILS     
            int dipo_day[31];
            float dipo_amt[31];
       //EXPENCES DETAILS     
            char expd_name[20][30];
            float expd_amt[20];
        };
        struct node3 // Expenduture sheet    [ONE SHEET]
        {
            int id;
            char name[30];     //expenditure catagory name
            float total_expd;  // this type; monthly total expences
        //EXPENCES DETAILS         
            float per_expd_rate; // per head expences rate
            int meal_charge_id; //if it =1, then it is meal charge id
            float catagory_total; //monthly fixed cash (like MASSI/GAS bill/ELCT. bill/GURBAZE)
            float catagory_due;
            struct node3 *next;
        };
        struct node4 // daily entry sheet    [TOTAL_DAY SHEET]
        {
            int day; 
            char month_name[10], year_name[4];
            float total_dipo;  // daily total diposite
            float total_expd;  // daily total expences
            float total_due;   // daily due
            struct node4 *next;
        //DIPOSITE DETAILS         
            char dipo_name[20][30];
            float dipo_amt[20];
        //EXPENCES DETAILS         
            char expd_name[20][30];
            float expd_amt[20];
        };
        struct node5  // for electrict
        {
            int start_unit, end_unit;
            float per_unit, total_bill;
        };


    int main()
    {
while(1)
{        
char st[10];
cout<<"\n  continue\n  help\n  about\n  exit\n";
cout<<"enter your choice\t";    cin>>st;

if(strcmp(st,"help")==0)           help(); 
else if(strcmp(st,"about")==0)     about(); 
else if(strcmp(st,"exit")==0)      exit(0); 
else if(strcmp(st,"continue")==0)
    {  
        struct node1       *month=NULL;
        struct node2       *border=NULL;
        struct node3       *expences=NULL, *exps=NULL; 
        struct node4       *daily=NULL;       
        struct node5       *elect=NULL;   
        int total_day, total_border, expd_type;
        //total_day=total_border=expd_type=3;    
       month= entry_node1(month);    
       total_day= month->month_days;   
       cout<<"total days of '"<<month->month_name<<"::"<<month->year_name<<"' :\t"<<total_day<<"\n";  

       cout<<"\n\nenter total border of this Mess:\t"; cin>>total_border;
       border= entry_node2(border, total_border);  //border details
       cout<<"\n\nenter total Types Expenditure of this month:\t"; cin>>expd_type;           
       expences= entry_node3(expences, expd_type);  // Enpenditure Details           
       daily= entry_node4(daily, month, total_day);  // depend on above input
       // entry elect bill details
       exps= expences;
       while(exps!=NULL)
       {
            if(strcmp(exps->name,"elect")==0||strcmp(exps->name,"ELECT")==0||strcmp(exps->name,"electrict")==0||strcmp(exps->name,"ELECTRICT")==0)
                 elect= entry_node5(elect); // input elect bills
            exps= exps->next;
       }
       
       Daily_Entry_Data(month, border, expences, daily, total_day, total_border, expd_type);
       //show_all(month, border, expences, daily, total_day, total_border);
       Calculation(month, border, expences, daily, elect, total_day, total_border, expd_type);  
       
       int flag;
       cout<<"\n\n\n\nShow your result [Y=1/n=0]:\t"; cin>>flag;
       if(flag==1)     
        show_all(month, border, expences, daily, elect, total_day, total_border, expd_type);
        free(month); free(border); free(expences); free(daily);
    }    
else cout<<"Invalid Input\n"; 
}
    return 0;
    }


void Calculation(struct node1 *month, struct node2 *border, struct node3 *expences, struct node4 *daily, struct node5 *elect, int total_day, int total_border, int expd_type)
{
    struct node4 *rem_daily;
    struct node3 *rem_expences;
    struct node2 *rem_border;
    rem_daily=daily;    rem_expences=expences;  rem_border=border;
    
    //find total meal/ total hand cash / total_expd as total_month_cash;
    for(int i=1; i<=total_border; i++)
    {
        month->total_meal+=border->total_meal; 
        border=border->next;
    }   border=rem_border;
    month->total_hand_cash= (month->total_dipo - month->total_expd);
    month->total_month_cash+= month->total_expd;
        
        
    //per head expences details;
    char ch; int flag=0;
    while(expences != NULL)
    { 
        if(flag==0)
        {   cout<<expences->name<<"  .........Is it mess bazar? [Y/n]:\t"; cin>>ch;}
        if(flag==0 && (ch=='y' || ch=='Y'))
        {    
            month->per_meal_charge= (expences->total_expd/(float)month->total_meal);
            expences->per_expd_rate= month->per_meal_charge;
            expences->catagory_total= expences->total_expd;
            expences->meal_charge_id=1;     flag=1;
        }
        else{
            cout<<"(like MASSI/GAS bill/ELCT. bill/GURBAZE)"<<endl;
            expences->per_expd_rate= (expences->total_expd/(float)total_border);  
            cout<<expences->name<<" .....Is it fixed bill? [Y/n]:\t"; 
            cin>>ch;
            if(ch=='y' || ch=='Y') 
            {    
                if(strcmp(expences->name,"elect")==0||strcmp(expences->name,"ELECT")==0||strcmp(expences->name,"electrict")==0||strcmp(expences->name,"ELECTRICT")==0)
                {
                     expences->catagory_total= elect->total_bill;
                     cout<<"Total Electric Bill= "<<expences->catagory_total<<endl;
                }
                else {  cout<<"Insert its Total Monthly Cash:\t"; cin>>expences->catagory_total; }
                
                expences->per_expd_rate= expences->catagory_total/ (float) total_border;
                expences->catagory_due= (expences->catagory_total - expences->total_expd);
                cout<<"due cash of this catagory=\t"<<expences->catagory_due<<endl;
                month->total_month_cash+= expences->catagory_due;
            }
            else{
                expences->catagory_total= expences->total_expd;
                expences->per_expd_rate= expences->catagory_total/ (float) total_border;
            }
        }
        expences= expences->next;
    }   expences=rem_expences;
    
    month->total_due= (month->total_month_cash - month->total_dipo);   
        
   // cout<<"total month cash=\t"<<month->total_month_cash<<endl;
   // cout<<"total due in this month=\t"<<month->total_due<<endl;
  
    for(int i=1; i<=total_border; i++)
    {
     //   cout<<"\n"<<border->name<<"::............"<<endl;
        for(int j=1; j<=expd_type; j++)
        {
            strcpy(border->expd_name[j], expences->name);
            if(expences->meal_charge_id == 1)
            {    border->expd_amt[j]= (expences->per_expd_rate * (float)border->total_meal);    }
            else    
            {    border->expd_amt[j]=  expences->per_expd_rate;          }
          //  cout<<"border expences in catagory::::\t"<<border->expd_name[j]<<"\t::\t"<<border->expd_amt[j]<<endl;
            
            border->total_expd+=border->expd_amt[j];
            
            expences=expences->next; 
        }   expences=rem_expences;
        
        border->total_due= (border->total_expd - border->total_dipo);
        
         border=border->next;
    }   border=rem_border;
    
    month->payment=month->total_hand_cash + month->total_due; 
}


void Daily_Entry_Data(struct node1 *month, struct node2 *border, struct node3 *expences, struct node4 *daily, int total_day, int total_border, int expd_type)
{
cout<<"\n\n\nDAILY Data Entry>>>>>>>>>>>>>>>>>>>>>>>>>>>>.\n";
    struct node4 *rem_daily;
    struct node3 *rem_expences;
    struct node2 *rem_border;
    rem_daily=daily;    rem_expences=expences;  rem_border=border;
    
    for(int i=1; i<=total_day; i++)
    {
       float dipo=0, expd=0;
       if(daily->day != i) { cout<<"Error occure in date\n"; exit(0); }
       cout<<"\nToday DATE:\t"<<daily->year_name<<":"<<daily->month_name<<":"<<daily->day<<endl;
       
       // DIPOSITE DAILY
       char ch;
      cout<<"Any one diposite today [Y/n]:\t"; cin>>ch;
      for(int j=1; j<=total_border; j++)
      {
            if(ch=='y' || ch=='Y') 
            {    cout<<border->id<<".\t"<<border->name<<" ::\t Amt:\t";  cin>>dipo;     }
            else dipo=0;
            
            border->total_dipo+=dipo;
                    border->dipo_day[i]=daily->day;
                    border->dipo_amt[i]=dipo;
            
            daily->total_dipo+=dipo;
                    strcpy(daily->dipo_name[j], border->name);
                    daily->dipo_amt[j]=dipo;
                    
            border=border->next;
      }    
      // cout<<"Todays Total Diposite:\t"<<daily->total_dipo<<endl;       
       month->total_dipo+=daily->total_dipo;
       
       border=rem_border;
       
       
       
       //EXPENCES DAILY
       cout<<"\nEnter Expences Daily\n";
       cout<<"Any one diposite today [Y/n]:\t"; cin>>ch;
       for(int j=1; j<=expd_type; j++)
       {
            if(ch=='y' || ch=='Y') 
            {  cout<<expences->id<<".\t"<<expences->name<<" ::\t Amt:\t";    cin>>expd;   }
            else expd=0;
            
            expences->total_expd+=expd;
                    strcpy(daily->expd_name[j], expences->name);
                    daily->expd_amt[j]=expd;
            
            expences=expences->next;
            
            daily->total_expd+=expd;
       } 
      // cout<<"Todays Total Expences:\t"<<daily->total_expd<<endl;       
       month->total_expd+=daily->total_expd;
       
       expences=rem_expences;
       daily=daily->next;
    }
    daily=rem_daily;
    cout<<endl<<endl;
}


// complete.....entry node...............
struct node1 *entry_node1(struct node1 *month)
{
    month=memory1;
    cout<<"enter year:\t"; cin>>month->year_name;
    cout<<"enter month name(all CAPITAL letter):\t"; cin>>month->month_name;    
    Finding_last_date(month); 
    month->total_meal=0;
    month->per_meal_charge=0;
    month->total_dipo=0;
    month->total_expd=0;
    month->total_hand_cash=0; 
    month->total_month_cash=0; 
    month->total_due=0;
    month->payment=0;
    month->next=NULL;
    return month;
}
struct node2 *entry_node2(struct node2 *border, int total_border)
{
    cout<<"Total border of the Mess:\t"<<total_border<<endl;
    struct node2 *temp, *remember;
    for(int i=1; i<=total_border; i++)
    {
        temp=memory2;
        temp->id=i;
        cout<<"enter "<<i<<"-th border name::\t"; cin>>temp->name;
        cout<<"total meal=\t"; cin>>temp->total_meal;
        temp->total_dipo=0;
        temp->total_expd=0;
        temp->total_due=0;
        temp->next=NULL;
        
        if(border==NULL) { border=temp;  remember=border; }
        else{ border->next=temp;   border=border->next; }
    }
    return remember;
}
struct node3 *entry_node3(struct node3 *expences, int expd_type)
{
    cout<<"\n\nTotal expences Type of the Mess:\t"<<expd_type<<endl;
    struct node3 *temp, *remember;
    for(int i=1; i<=expd_type; i++)
    {
        temp=memory3;
        temp->id=i;
        cout<<"enter "<<i<<"-th Expences name::\t"; cin>>temp->name;
        temp->total_expd=0;
        temp->per_expd_rate=0;
        temp->meal_charge_id=0;
        temp->catagory_total=0;
        temp->catagory_due=0;
        temp->next=NULL;
        
        if(expences==NULL) { expences=temp;  remember=expences; }
        else{ expences->next=temp;   expences=expences->next; }
    }
    return remember;
}        
struct node4 *entry_node4(struct node4 *daily, struct node1 *month, int total_day)
{
//cout<<"Total Days of the Mess:\t"<<total_day<<endl;
    struct node4 *temp, *remember;
    for(int i=1; i<=total_day; i++)
    {
        temp=memory4;
        strcpy(temp->month_name, month->month_name);
        strcpy(temp->year_name, month->year_name);
        temp->day=i;
        temp->total_dipo=0;
        temp->total_expd=0;
        temp->total_due=0;
        temp->next=NULL;
        
        if(daily==NULL) { daily=temp;  remember=daily; }
        else{ daily->next=temp;   daily=daily->next; }
    }
    return remember;
}
struct node5 *entry_node5(struct node5 *elect)
{
   elect=memory5;
   cout<<"entery ELECTRICT Bill details.......\n";
   cout<<"Starting Unit :\t";   cin>>elect->start_unit;
   cout<<"Ending Unit :\t";      cin>> elect->end_unit;
   cout<<"Bill per Unit:\t";     cin>> elect->per_unit;
   elect->total_bill= (elect->end_unit - elect->start_unit) * elect->per_unit;
   return elect;
}

// complete.....display node................
void show_all(struct node1 *month, struct node2 *border, struct node3 *expences, struct node4 *daily, struct node5 *elect, int total_day, int total_border, int expd_type)
{
    cout<<"\n\n\n\n\nSHOW ALL DATA FINALLY\n"<<endl;
       show_node1(month);
       show_node5(elect);
       show_node2(border,total_day, expd_type); 
       show_node3(expences);
       show_node4(daily,total_border, expd_type);
}
void show_node1(struct node1 *month)
{
cout<<"\n\nshow Monthly Data\n"<<endl;
    cout<<month->month_name<<"\t::\t"<<month->year_name<<endl;
    cout<<"monthly total diposite:\t"<<month->total_dipo<<endl;
    cout<<"monthly total expences:\t"<<month->total_expd<<endl<<endl;
    cout<<"monthly total meal:\t"<<month->total_meal<<endl;
    cout<<"Per meal Charge:\t"<<month->per_meal_charge<<endl<<endl;
    cout<<"Cash in my hand:\t"<<month->total_hand_cash<<endl;
    cout<<"monthly due:\t"<<month->total_due<<endl<<endl;
    cout<<"So TOTAL DUE IN THIS MONTH=\t"<<month->payment<<" Rs/-"<<endl;
    cout<<endl;
}
void show_node2(struct node2 *border, int total_day, int expd_type)
{
float amt1=0, amt2=0,  no1;
cout<<endl<<"\n\nshow Border Details Data...............\n"<<endl;
    while(border != NULL)
    { 
        cout<<"\n\n------------------------------------------------"<<endl;
        cout<<"------------------"<<border->name<<"--------------------"<<endl;
        cout<<"------------------------------------------------"<<endl;
        cout<<"Total Meal:\t"<<border->total_meal<<endl;
        cout<<"Total Diposite:\t"<<border->total_dipo<<endl;
        no1=round_off_amount(border->total_expd);
        cout<<"Total Expenditure:\t"<<border->total_expd<<" Rs/-; that is: "<<no1<<" Rs/-"<<endl;
        no1= (no1 - border->total_dipo);
        cout<<"Total Due/Extra:\t"<<no1<<endl; 
        //cout<<"Total Due/Extra:\t"<<border->total_due<<endl;       
        amt1+=no1;      amt2+=border->total_due;
        
        cout<<"\nShow Diposite Details\n";
        for(int j=1; j<=total_day; j++)
            if(border->dipo_amt[j] != 0)
            cout<<j<<". Date= "<<border->dipo_day[j]<<"\t:\tAmt:\t"<<border->dipo_amt[j]<<endl;
            
        cout<<"\nExpences Details\n";
        for(int j=1; j<=expd_type; j++)
            cout<<j<<". "<<border->expd_name[j]<<" \t::\t"<<border->expd_amt[j]<<endl;
        
        border=border->next;
    }
    
    cout<<"\n\n**********************************************"<<endl;
    cout<<"TOTAL DUE FORM ALL BORDERS=\t"<<amt1<< " Rs/-\n";
    cout<<"Profit of Manager=\t"<<round_off_amount(amt2-amt1)<< " Rs/-"<<endl;
    cout<<"**********************************************"<<endl<<endl;
}
void show_node3(struct node3 *expences)
{
float amt=0;
cout<<"\n\nshow Expences Details Data...............\n"<<endl;
    while(expences != NULL)
    {
    cout<<"\n\n------------"<<expences->name<<"----------------------"<<endl;
      
        cout<<endl<<expences->id<<". TOTAL MONTHLY '"<<expences->name;
        cout<<"'\t::\tAmount=\t"<<expences->catagory_total<<" Rs/-"<<endl;
        if(expences->meal_charge_id==0)
            cout<<"expences rate=\t"<<expences->per_expd_rate<<" Rs/- per Border"<<endl;
        else
            cout<<"meal Charge=\t"<<expences->per_expd_rate<<" per MEAL in this month"<<endl;
        if(expences->catagory_due>0) 
        {
            cout<<"*******************************************"<<endl;
            cout<<"***\tDue Bill= \t"<<expences->catagory_due<<" Rs/-  ***"<<endl;
            cout<<"*******************************************"<<endl;
        }
        amt+=expences->catagory_due;
        expences=expences->next;
    }cout<<endl<<"TOTAL DUE BILL=\t"<<amt<<" In this month\n"<<endl<<endl;
}
void show_node4(struct node4 *daily, int total_border, int expd_type)
{
cout<<"\n\nshow Day to Day Details...............\n"<<endl;
    while(daily != NULL)
    {
    cout<<"\n\n------------"<<daily->year_name<<":"<<daily->month_name<<":"<<daily->day<<"----------------------"<<endl;
        cout<<"Total Diposite of this day:\t"<<daily->total_dipo<<endl;
        cout<<"Total Expenditure of this day:\t"<<daily->total_expd<<endl;
       // cout<<"Total Due/Extra:\t"<<daily->total_due<<endl;
       if(daily->total_dipo != 0)
       {
          cout<<"\nDiposite Details\n";
          for(int j=1; j<=total_border; j++)
            if(daily->dipo_amt[j] != 0)
                cout<<j<<". "<<daily->dipo_name[j]<<"\t::\t"<<daily->dipo_amt[j]<<endl;
       }
       if(daily->total_expd != 0)
       {     
          cout<<"\nExpences Details\n";
          for(int j=1; j<=expd_type; j++)
            if(daily->expd_amt[j] != 0)
                cout<<j<<". "<<daily->expd_name[j]<<"\t::\t"<<daily->expd_amt[j]<<endl;
       }
        daily=daily->next;
    }cout<<endl<<endl;
}
void show_node5(struct node5 *elect)
{
   cout<<"*******************************************"<<endl;
   cout<<"**********ELECTRICT BILL DETAILS***********"<<endl;
   cout<<"Starting Unit :\t"<<elect->start_unit<<endl;
   cout<<"Ending Unit :\t"<<elect->end_unit<<endl;
   cout<<"Total Unit :\t"<<(elect->end_unit-elect->start_unit)<<endl;
   cout<<"Bill per Unit:\t"<<elect->per_unit<<endl;
   cout<<"Total Cash:\t"<<elect->total_bill<<endl;
   cout<<"*******************************************"<<endl;
}
// ----------------Helping Function -------------


int Numbers(char ch)
{
   if(ch=='1') return 1;
   else if(ch=='2') return 2;
   else if(ch=='3') return 3;
   else if(ch=='4') return 4;
   else if(ch=='5') return 5;
   else if(ch=='6') return 6;
   else if(ch=='7') return 7;
   else if(ch=='8') return 8;
   else if(ch=='9') return 9;
   else if(ch=='0') return 0;
}
void Finding_last_date(struct node1 *aa)
{
      int mm=0,yyyy=0;
      
      for(int i=0; i<4; i++)
         yyyy=yyyy*10+Numbers(aa->year_name[i]);
     
    do{ 
      if(strcmp(aa->month_name,"JANUARY")==0)        aa->month_pos=1;     
      else if(strcmp(aa->month_name,"FEBRUARY")==0)  aa->month_pos=2;  
      else if(strcmp(aa->month_name,"MARCH")==0)     aa->month_pos=3;     
      else if(strcmp(aa->month_name,"APRIL")==0)     aa->month_pos=4;  
      else if(strcmp(aa->month_name,"MAY")==0)       aa->month_pos=5; 
      else if(strcmp(aa->month_name,"JUNE")==0)      aa->month_pos=6; 
      else if(strcmp(aa->month_name,"JULY")==0)      aa->month_pos=7; 
      else if(strcmp(aa->month_name,"AUGUST")==0)    aa->month_pos=8; 
      else if(strcmp(aa->month_name,"SEPTEMBER")==0) aa->month_pos=9; 
      else if(strcmp(aa->month_name,"OCTOBER")==0)   aa->month_pos=10; 
      else if(strcmp(aa->month_name,"NOVEMBER")==0)  aa->month_pos=11; 
      else if(strcmp(aa->month_name,"DECEMBER")==0)  aa->month_pos=12; 
      else{cout<<"invlid input/ input-format of month\n";  
      cout<<"please enter month name again (in small case letter)\t:\t"; 
      cin>>aa->month_name;     
      aa->month_pos=0; }         
   }while(aa->month_pos==0);   
      mm= aa->month_pos;
   
		if(yyyy>9999 || yyyy<1000)
	    	{cout<<"\n\nInvalid Input now....in YEAR.\n"; exit(0);}
	    	
		if(mm==1||mm==3||mm==5||mm==7||mm==8||mm==10||mm==12)  aa->month_days=31;
      else if(mm==4||mm==6||mm==9||mm==11)   aa->month_days=30;
      else if(mm==2)
      {   if((yyyy%4==0 && yyyy%100!=0) || (yyyy%400==0)) aa->month_days=29;
		    else       aa->month_days=28;
		}
	//	return aa->month_days;
}
float round_off_amount(float number)
{
    int a; float decimal_part, no;
    a=(int)number;
    decimal_part= fabs(number-(float)a);
    if(decimal_part >= 0.50)  no=(float) (a+1);
    else no=(float) a;
    return no;
}
void about()
{
    cout<<"\n\n\n\n*******************************\nAbout this programming\n******************************************\n";
    cout<<"BIWASINDHU MANDAL\nWhatapps NO.: 847997339\n*************************************************\n\n\n\n\n";
}
void help()
{
    cout<<"\n\n\n\n-------------------------\nHelping to You\n-----------------------------------";
    cout<<"\n\n...........................Updated Version mess_1.2..............................\n\n";
    cout<<"\n\nFirst you enter YEAR & MONTH.\n\nafter enter 'total days of your english month take automatically'.\n\nnext enter 'total border in your Hostel'.\n\nenter 'all Border name' and 'Total meal of your Hostel'.\n\nnext enter 'total EXPENCES Types in your mess'. [like Hostel_Bazar, EST charge, Massi Bill, Gurbaze Bill, Gas Bill, Bonus, Elct. Bill etc.] -- enter total type.\n\nnext enter 'all EXPENCES CATAGORY NAME. [like Hostel_Bazar, EST charge, Massi Bill, Gurbaze Bill, Gas Bill, Bonus, Elct. Bill etc.] --- enter only name of its.\n\nenter DAY BY DAY 'DIPOSITES' & 'EXPENCES'::::\nif at that day you diposite\tthen enter Y/y for 'YES',\totherwise enter N/n for 'NO'.\n\nif(yes): then enter 'diposite of total amount by this person at that day' one-by-one.\n-------***choose same critariya in the case of 'EXPENCES'.\n\nAfter input of all 'DIPOSITES' & 'EXPENCES' day by day of this month. Now this screen show you 'Is it mess bazar?[Y/n]'This means that\n\t if catogory is 'mess bazar' then enter Y/y for YES\n\telse enter N/n for NO.\n\twhen you enter 'n' for 'no' the scree show you 'Is it fixed bill?[Y/n]'\n\nThis means [like EST charge, Massi Bill, Gurbaze Bill, Gas Bill, Bonus, Elct. Bill etc.] which are divisible by all Hostel Border. So it may have a monthly Round of Bill [as example: Est_Charge/Unsource Bill(Puja Chada etc) have no Round-off figure, But, GAS_Ch., Massi_Ch., Elct._Ch. ect. have a Fixed monthly figure].\n\n\nIf the Other bill is 'Electric Bill'(In case of input please enter 'elect'/'Elect'/'ELECT') then enter unit details and value per unit.\n\n  So, if this expences have any Round-off Monthly Figure\n\t then enter Y/y for 'YES'(then enter its Round-off Monthly Bill)\n\t else enter N/n for 'NO'.\n\n\nIf you want to see your Full Result then enter 1 for 'YES' else enter 0 for 'NO'.\n\n\n\n\n\nIthink you satisfied to see my help............\nCheck please .......\nIf any quory goto 'About Portion' get help or take help.\n "<<endl;
    cout<<"Thank You to see it\n==============================================================================================\n\n\n"<<endl;
}       




