 #include<stdio.h> // standerd inp out
 #include<stdlib.h> // file functions , atoi ,itoa
 #include<conio.h> // getch()
 #include<string.h> // string functions
 
//function declarations
void entry(); // atm banner -homepage
int read_acc();// details from file are loaded into global var + verification of existence of acc and acc type 
void rem_nl(char *p); // remove extra newline
void admin_options() ; //operations admin can perform
void user_options() ;//operations users can perform
void view_note_count(); // View the number of notes of each denomination
void deposit_notes(); // for Admin to enter notes into ATM machine
void view_acc_details(); //view details of acc
void withdraw(); //withdraw money from bank account
void update_note_count(int amount); // updating the note count present in the bank
void deposit(); // depositing money to atm machine
void change_pin(); //change the password
void read_notes_default(); //to set note counts in the gloabl var for user operations as note count is set only on initialising admin file
void save_details(); // re writting back to the file
  
//global variables - DETAILS
char acc_pass[50];
char acc_uname[50];
char acc_no[50];
char acc_bal[50];

//global variables - DENOMINATION	
int c_100 = 0;
int c_500 = 0;
int c_2000 = 0;

 int main()
 {
	system("cls");
	entry(); // home screen of atm machine
	fflush(stdout);
	
	if(read_acc()) // checks if account and password matches and if account exists + data entry to golabal var
	{
		printf(" Account Validation failed ...");
		exit(0); // terminating program
	}
	
	read_notes_default();//to set note counts in the gloabl var for user operations as note count is set only on initialising admin file
	system("cls");
	if(strcmp(acc_no,"admin") == 0)
	{
		admin_options();
	}
	else
	{
		user_options();
	}
	
	save_details();
	
	printf("\nDetails saved successfully\n");
	printf("Thank you \n");
	
 }
 
  void entry()
{
	char enter[20];
	printf("\n");printf("\n");printf("\n");
	puts("\t\t\t\t\t\t\tATM SIMULATOR"); // tabs are for layout design
	puts("\t\t\t\t\tpress enter to swipe card and start application");
	gets(enter);
	system("cls");
}

  int read_acc() // details from file are loaded into global var + verification of existence of acc and acc type 
 {
	 FILE *fh;
	 char account_number[50];
	 int cnt = 0;
	 int i = 0;
	 char str[50];
	 char c;
	 
	while(cnt<2) // allowing the person to enter details 2 times - on faliure program exits
	{
		cnt++;//updating statement of while loop 
		puts("Enter account number ");
		gets(account_number);
		strcat(account_number,".txt");
		puts("Enter password");
		while (i<4) // while entering password the stars instead of char produced by this code
		{
			str[i]=getch();
			c=str[i];
			if(c=='\0') break;
			else printf("*");
			i++;
		}
		str[i]='\0';//password is stored in str
		i=0;
		
		printf("\n");
		
		//reading the file
		
		if ((fh = fopen(account_number,"r")) == NULL) //checking if the account file exist
		{
		   printf("Error! ACCOUNT DOES NOT EXIST !! \n");	   // Program exits if the file pointer returns NULL.
		   continue;//returns control to while condition
		}
		
		fgets(acc_pass,100,(FILE*)fh); // first line of input file - password - common for user and admin file - writting to glabal var of password
		if(strcmp(account_number,"admin.txt") != 0) // if account type is not admin
		{
			//writing file contents onto global variables
			fgets(acc_no,100,(FILE*)fh);
			fgets(acc_uname,100,(FILE*)fh);
			fgets(acc_bal,100,(FILE*)fh);
			
			// removing extra newline which is entered while reading the data from file to variables
			
			rem_nl(acc_bal);
			rem_nl(acc_no);
			rem_nl(acc_uname);
		}
		else //admin file details entry
		{	
			//note details entry to global var done using common function in main
			strcpy(acc_no,"admin");
		}
		rem_nl(acc_pass); //removing extra newline of password
		//since password is common for both admin and user it is outside the if and else block
		
		//check function if username and pass valid

		if(strcmp(str,acc_pass) != 0)//str contains the password entered by the user
		{
			printf("PASSWORD MIS-MATCH !! \n");
			continue;//control back to while
		}
		else
		{
			cnt = 2;//exiting condition from while loop
			fclose(fh);
			return 0; //exiting function with successful validation
		}
	}
	fclose(fh);
	return 1;// validation of accno. and pass FAILED
 }
 
 void rem_nl(char *p) //removing the last charachter (\n)
{
	int a = strlen(p);
	strncpy(p,p,a-1);
	p[a-1]='\0';
}

 void read_notes_default() //in this function we are writing those amounts to our global variables of note count
{
	FILE *fh = fopen("admin.txt","r"); //admin file contains the number of notes in all denomination
	char s100[50],s500[50],s2000[50],pass[50]; // local string to hold note count from file as we read it as string
	fgets(pass,100,(FILE*)fh);
	fgets(s100,100,(FILE*)fh);
	fgets(s500,100,(FILE*)fh);
	fgets(s2000,100,(FILE*)fh);
	
	// removing extra newline which is entered while reading the data from file to variables
	
	rem_nl(s100);
	rem_nl(s500);
	rem_nl(s2000);
	
	//writing to global var of note count - converting string to int
	c_100 = atoi(s100);
	c_500 = atoi(s500);
	c_2000 = atoi(s2000);
	
	fclose(fh);
}

 void admin_options() //operations admin can perform
{
	int choice=0;
	do
	{
		printf("\n*******************************************************");
		printf("\nWelcome Admin !!\n");
		printf("\nSelect from the following options \n");
		printf("\n VIEW_DENOMINATION_COUNT:1 \n DEPOSIT_NOTES:2  \n QUIT:3 \n");
		printf("\nEnter option : ");
		scanf("%d",&choice);
		
		switch(choice)
		{
			case 1:
			view_note_count();// View the number of notes of each denomination 
			break;
			case 2:
			deposit_notes(); // for Admin to enter notes into ATM machine
			break;
		}
	
	}while(choice != 3);
}

void view_note_count()// View the number of notes of each denomination
{
	printf("\n Denomination count in the ATM \n");
	printf("2000 - %d \n",c_2000); // reading note count from global variables
	printf("500 - %d \n",c_500);
	printf("100 - %d \n",c_100);
}

void deposit_notes() // for Admin to enter notes into ATM machine
{
	//entering note count
	int nc2000,nc500,nc100;
	printf("Enter number of notes of denomination 2000 \n");
	scanf("%d",&nc2000);
	printf("Enter number of notes of denomination 500 \n");
	scanf("%d",&nc500);
	printf("Enter number of notes of denomination 100 \n");
	scanf("%d",&nc100);
	if(nc2000<0 || nc500<0 || nc100<0)
	{
		printf("Enter positive number of notes !");
		return;
	}
	
	//updatating note count of global note count
	c_100 += nc100;
	c_500 += nc500;
	c_2000 += nc2000;
	
	printf("Money loaded successfully !!\n");
	
	//view_note_count(); // display the note count present in the atm
}

void user_options() //operations users can perform
{
	int choice=0;
	do
	{
		printf("\n*******************************************************");
		printf("\nWelcome %s !!\n",acc_uname);
		printf("Your account number is: %s \n",acc_no);
		printf("\nSelect from the following options :\n");
		printf("\n VIEW_ACCOUNT_DETAILS:1 \n WITHDRAW:2 \n DEPOSIT:3 \n CHANGE PIN:4 \n QUIT:5 \n");
		printf("\nEnter option : ");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
			view_acc_details(); //view details of acc
			break;
			case 2:
			withdraw();// withdraw money from bank account
			break;
			case 3:
			deposit(); // depositing money to atm machine
			break;
			case 4:
			change_pin(); //change the password
			break;
			case 5:
			break;
			default :
			printf("Invalid choice !!");
		}
	
	}while(choice != 5);
	
}

void view_acc_details() //view details of acc
 {
	 printf("\nAccount details:\n");
	 printf("Account User Name : %s\n",acc_uname);
	 printf("Account number : %s\n",acc_no);
	 printf("Account Balance : %s\n",acc_bal);
 }

void withdraw() //withdraw money from bank account
 {
	int total = c_100*100+c_500*500+c_2000*2000; //total amount present in the bank
	int bal = atoi(acc_bal);// amount present in the users account
	
	printf("Enter amount to  withdraw :");
	int  amount;
	scanf("%d",&amount);
	
	if(amount%100 != 0)//since amount will be paid in denominations of 100,500,2000
		printf("Invalid amount - please enter amount that is a multiple of hundred \n");
	else if(amount>total)//requested amount greater then amount present in bank
		printf("Transaction unsuccessfull - Insufficient funds in the bank  \n");
	else if(amount>bal)//requested amount greater then amount present in users account
		printf("Transaction unsuccessfull - Insufficient account balance  \n");
	else
	{
		bal = bal - amount; //deducting money from account and updating to global var
		itoa(bal,acc_bal,10);//since acc_bal - global var is of char DT - Converting int to string - itoa(<int to be conv>,<storage str>,<base>)
		update_note_count(amount);// updating the note count present in the atm
		printf("Transaction successfull !! \n");
		//view_note_count(); // displaying the note count after updating
	}
 }
 
  void update_note_count(int amount) // updating the note count present in the atm
 {
	 int count2000,count500,count100; // number of notes required while withdrawing
	 count2000 = amount/2000; // number of 2000s notes will be required
	 if(count2000<=c_2000) //checking of number of notes req is < number of 2000 notes in atm
	 {
		 c_2000 -= count2000;//removing req number of notes from the atm and updating the global note count
		 amount = amount - count2000*2000; // remaing amount after getting 2000s
	 }
	 else // if number of 2000 notes req is less than that avaliable in the atm
	 {
		 count2000 = count2000 - c_2000; // decrementing avaliable note count required by the notes present in the atm 
		 c_2000 = 0;// making global note count of 2000 -> 0
		 amount = count2000*2000+(amount%2000); // total amount that is still required from atm
	 }
	 if(amount == 0) // checking if total amount recieved
		 return; // then empty return as amount notes updated for the required amount
	//similiarly done for 100 and 500
	 count500 = amount/500;
	 if(count500<=c_500)
	 {
		 c_500 -= count500;
		 amount = amount - count500*500;
	 }
	 else
	 {
		 count500 = count500 - c_500;
		 c_500 = 0;
		 amount = count500*500+(amount%500);
	 }
	 if(amount == 0)
		 return;
	 count100 = amount/100;
	 if(count100<=c_100)
	 {
		 c_100 -= count100;
		 amount = amount - count100*100;
	 }
	 else
	 {
		 count100 = count100 - c_100;
		 c_100 = 0;
		 amount = count100*100+(amount%100);
	 }
	 if(amount == 0)
		 return;
 }
 
  void deposit() // depositing money to atm machine
 {
	int nc2000,nc500,nc100;
	int total,bal = atoi(acc_bal);
	
	printf("Enter amount to deposit: \n");
	
	printf("Enter number of notes of denomination 2000 \n");
	scanf("%d",&nc2000);
	printf("Enter number of notes of denomination 500 \n");
	scanf("%d",&nc500);
	printf("Enter number of notes of denomination 100 \n");
	scanf("%d",&nc100);
	if(nc2000<0 || nc500<0 || nc100<0)
	{
		printf("Enter positive number of notes !");
		return;
	}
	
	total = nc100*100+nc500*500+nc2000*2000;//total value to be entered into user account
	
	//incrementing globlal variables of note count
	c_100 += nc100;
	c_500 += nc500;
	c_2000 += nc2000;
	
	//updating balance in users account
	bal = bal+total;
	itoa(bal,acc_bal,10);//writing to global var
	
	printf("Money successfully transfered to account !! \n");
 }
 
  void change_pin() //change the password
 {
	 char pass[50];
	 printf("Enter your current password\n");
	 scanf("%s",pass);
	 if(strcmp(acc_pass,pass)!=0)
	 {
		 printf("incorrect password\n");
	 }
	 else
	 {
		 char pass2[50],pass3[50];
		printf("enter new password\n");
		scanf("%s",pass2);
		printf("enter new password again \n");
		scanf("%s",pass3);
		if(strcmp(pass2,pass3)==0)
		{
			strcpy(acc_pass,pass2);
			printf("Password changed successfully \n");
		}
		else
		{
			printf("Password mis-match \n");
		}
	 }
 }
 
 void save_details() // writing back to file
 {
	 char account_number[50];
	 strcpy(account_number,acc_no);
	 strcat(account_number,".txt");
	 if(strcmp(account_number,"admin.txt")!=0)
	 {
		 FILE *fh = fopen(account_number,"w"); // users updated details
		 fprintf(fh,"%s\n",acc_pass);
		 fprintf(fh,"%s\n",acc_no);
		 fprintf(fh,"%s\n",acc_uname);
		 fprintf(fh,"%s\n",acc_bal);
		 fclose(fh);
	 }
	 
	 FILE *fh2 = fopen("admin.txt","r");
	 fscanf(fh2,"%s",acc_pass);
	 fclose(fh2);
	 
	 FILE *fh1 = fopen("admin.txt","w"); // notes denomination
	 fprintf(fh1,"%s\n",acc_pass);
	 fprintf(fh1,"%d\n",c_100);
	 fprintf(fh1,"%d\n",c_500);
	 fprintf(fh1,"%d\n",c_2000);
	 fclose(fh1);
 }
 

	 
 
 
 
 
 
 

 
 
 