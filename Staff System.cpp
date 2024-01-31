//CS221 Project Assignement 2021-2022 Term 2

#include <iostream> //user input output
#include <fstream> //file input output
#include <string> //strings
#include <bits/stdc++.h> //sort() function
#include <ctime> //report time
using namespace std;

#include "Header.h" //function prototypes and structs

//-------------------Main Function-------------------

//-------------------Main Function-------------------

int main () //creating and adding original data to the file
{
	string ignore; //string for ignoring lines
	string temp; //for non string inputs
	ifstream staff_file;
	bool staffcreated = 0; //for initial Staff List.txt created report
	ofstream log_file; //always generated as user goes through the program, appends all sessions.

	staff_file.open("Staff List.txt"); //opening staff file
	while (!staff_file.is_open()) //checking if file is available, if not then create
	{
		cout << "File was not previously created." << endl;
		ofstream staff_file("Staff List.txt"); //open the file
		staff_file << "ID, NAME, AGE, STAFF POSITION, SALARY" << endl; //adding file header
		cout << "File has now been created.\n";
		staffcreated = 1;
		lines++; //to account for header not originally being present
		break;
	} 
	staff_file.close();

	staff_file.open("Staff List.txt"); //opening staff file
	log_file.open("Log File.txt", ios::app);
	log_file << "\n============================================================================================================================\n\n"; //seperated between sessions, generate once each session
  	log_file.close();
	if (staffcreated == 1)
	{
		statisticalReport("Main - Staff List.txt Created", -1, -1);
	}

	getline(staff_file, ignore, '\n'); //get the first line (header) and ignore it
	Staff stafflist[maxlines]; //declare struct as array
	if (lines != 0) //if file isn't empty
	{
		for (int i = 0; i < lines; i++)
		{
			getline(staff_file, stafflist[i].id, ',');	//ID
			getline(staff_file, ignore, ' ');
			getline(staff_file, stafflist[i].first_name, ' '); //first name
			getline(staff_file, stafflist[i].last_name, ','); //last name
			getline(staff_file, ignore, ' '); 
			getline(staff_file, temp, ','); //age
			getline(staff_file, ignore, ' ');
			try //making sure the program doesn't input an incorrect datatype from the file
			{
				stafflist[i].age = stoi(temp);
			}
			catch (const std::exception&) //if it finds an incorrect datatype, set to 0 and ask user to update.
			{
				cout << "There is an invalid datatype in the file. Age, Record: " << i + 1 << endl;
				cout << "Datatype must be a positive integer. Please edit using option \"2 --> Update Item\"" << endl;
				cout << "Automatically set to value of 0" << endl;
				stafflist[i].age = 0;
			}
			getline(staff_file, stafflist[i].staff_pos.job_name, ','); //staff position
			getline(staff_file, ignore, ' ');
			getline(staff_file, temp, '\n'); //salary
			try //making sure the program doesn't input an incorrect datatype from the file
			{
				stafflist[i].staff_pos.salary = stoi(temp);
			}
			catch (const std::exception&) //if it finds an incorrect datatype, set to 0 and ask user to update.
			{
				cout << "There is an invalid datatype in the file. Salary, Record: " << i + 1 << endl;
				cout << "Data type must be an integer. Please edit using option \"2 --> Update Item\"" << endl;
				cout << "Automatically set to value of 0" << endl;
				stafflist[i].staff_pos.salary = 0;
			}
		}
	}
	statisticalReport("Main - " + to_string(lines) + " Records Imported From \"Staff List.txt\" Successfully\n\t\t\t--Maximum allowed records: " + to_string(maxlines), -1, -1);
	//Main Menu
	int choice;
	int f = -1; //tells program whether or not to generate the report
	while(true)
	{
		cout << "\n\nWhat would you like to preform?" << endl;
		cout << "1 --> Add New Item" << endl;
		cout << "2 --> Update Item" << endl;
		cout << "3 --> Delete Item" << endl;
		cout << "4 --> Search For Item" << endl;
		cout << "5 --> Sort List" << endl;
		cout << "6 --> Display List\n" << endl;
		cout << "0 --> Save Items Into File" << endl;
		cout << "-1 --> Exit Program\n" << endl << ">";

		choice = getInt();
		
		cout << "\n";
		switch(choice)
		{
			case -1: 	//exit program
				char genreport; //store user option for generating the report
				while(true)
				{
					cout << "Do you want to generate a statistical report of this session? (Y/N)\n" << ">";
					cin >> genreport;
					if (toupper(genreport) == 'Y') //if yes
					{
						statisticalReport("Statistical Report Generated", -1, -1);
						f = 0; //generate report
					}
					else if(toupper(genreport) != 'N') //if any other answer other than yes or no
					{
						cout << "That is not a correct option, please try again." << endl;
						continue;
					}
					break;
				}
				statisticalReport("Quiting Program", -1, f);
				cout << "\nExiting program...";
				return 0; //return 0 quits the program while in main
				break;
			case 0:	 	//save into file
				itemSave(stafflist);
				break;
			case 1:		//adding new record
				itemAdd(stafflist, rupdate, vupdate);
				break;
			case 2:		//update record
				itemUpdate(stafflist);
				break;
			case 3:		//delete record
				itemDel(stafflist);
				break;
			case 4:		//search record
				itemSearch(stafflist);
				break;
			case 5:		//sort record
				itemSort(stafflist);
				break;
			case 6:		//display record
				itemDisplay(stafflist);
				break;
			default: 	//if user input is not of the above choices.
				cout << "That's not a valid service. Please try again. " << endl;
				continue;	//return to main menu to try again
		}
	}
	return 0;
}

//-------------------Function Definitions-------------------

int getInt() //-------------------try catch, ensuring input is an int when needed.
{
	string input;
	int intinput;

	while(true)
	{
		try
		{
			cin >> input;
			intinput = stoi(input);
			break;
		}
		catch (const std::exception&)
		{
			cout << "This variable must be an integer. Please try again" << endl << ">";
			continue;
		}
	}
	return intinput;
}

int countLines() //-------------------count number of records already stored in file
{
	ifstream staff_file ("Staff List.txt");
	string i;

	while (getline(staff_file, i)) //loop while there is a line
  	{
		if ((i[0] == '\0')) //so it doesn't count a line that happens to be empty
		{
			lines--;
		}
		lines++;
	}
	lines--; //to ignore header (first line in the file)
	return lines;
}

int maxLines() //-------------------input and return number of maximum allowed records according to user
{	
	int max;
	while(true)
	{
		cout << "Enter maximum allowed number of records: " << endl << ">";
		max = getInt();
		if (max <= 0)
		{
			cout << "You can't have zero or less records." << endl;
			continue;
		}
		if (lines > max)
		{
			cout << "There are already " << lines << " records in the file." << endl;
			cout << "Please enter a max line value that is bigger or equal to " << lines << ".\n" << endl;
			continue;
		}
		break;
	}
	return max; //return answer then continue the code
}

//*------------------------------Editing Functions------------------------------*//

void itemAdd(Staff s[], int rupdate, int vupdate) //-------------------Adding Function
{
	string newid, newfirst, newlast, newjob;
	int newage, newsalary, returncheck = 0;

	if ((rupdate == -1) && (lines >= maxlines)) //checking if current number of lines has exceeded maximum allowed values or not
	{
		cout << "You have hit the maximum allowed records, please delete a record and try again.\n";
		statisticalReport("itemAdd - Maximum Allowed Records Hit", -1, -1);
		return;
	}

	if (vupdate == 1 || vupdate == -1)
	{
		while(true)
		{
			cout << "\nEnter staff's ID: " << endl;
			cin >> newid;
			for (int i = 0; i < lines; i++) //checking if ID already exists within the current lines
			{
				if (newid == s[i].id) //if it does exist, then user can not use this ID: Do what is inside the following if statement
				{
					if (newid != s[rupdate].id) //if inputed ID = same ID as record user wants to *update*, it is allowed, else do the following
					{
						cout << "\nYou've already used that ID for a different record." << endl;
						cout << "Please use a different ID";
						if (rupdate != -1) //only if user is updating
						{
							cout << ", or keep the ID this staff already has.";
						}
						cout << "\nUse option \"4 --> Search For Item\" to search for if the ID already exists.\n";
						returncheck = 1; //ensuring user only goes back to main if they input ID that already exists
						continue;
					}
				}
			}
			break;
		}
		if (returncheck == 1)
		{
			return; //return back to update
		}
	}

	if (vupdate == 2 || vupdate == -1)
	{
		cout << "Enter staff's first name: " << endl;
		cin >> newfirst;
	}
	if (vupdate == 3 || vupdate == -1)
	{
		cout << "Enter staff's second name: " << endl;
		cin >> newlast;		
	}
	if (vupdate == 4 || vupdate == -1)
	{
		while (true)
		{
			cout << "Enter staff's age: " << endl;
			newage = getInt();
			if (newage < 0)
			{
				cout << "Age can not be less than 0. Try again." << endl;
			}
			else
			{
				break;
			}
		}
	}
	cin.ignore(); //clear cin buffer
	if (vupdate == 5 || vupdate == -1)
	{
		cout << "Enter staff's job: " << endl;
		getline(cin, newjob);
	}
	if (vupdate == 6 || vupdate == -1)
	{
		cout << "Enter staff's salary: " << endl;
		newsalary = getInt();
	}

	if (rupdate != -1) //for itemUpdate only
	{
		if (vupdate == 1 || vupdate == -1){s[rupdate].id = newid;}
		if (vupdate == 2 || vupdate == -1){s[rupdate].first_name = newfirst;}
		if (vupdate == 3 || vupdate == -1){s[rupdate].last_name = newlast;}
		if (vupdate == 4 || vupdate == -1){s[rupdate].age = newage;}
		if (vupdate == 5 || vupdate == -1){s[rupdate].staff_pos.job_name = newjob;}
		if (vupdate == 6 || vupdate == -1){s[rupdate].staff_pos.salary = newsalary;}
		cout << "\nRecord Updated!";
		return; //returns to itemUpdate
	}
	
	s[lines].id = newid;
	s[lines].first_name = newfirst;
	s[lines].last_name = newlast;
	s[lines].age = newage;
	s[lines].staff_pos.job_name = newjob;
	s[lines].staff_pos.salary = newsalary;
	lines++; //add new line
	cout << "\nRecord added!";
	statisticalReport("itemAdd - Record Added Successfully", lines, 1);
}

void itemUpdate(Staff s[]) //-------------------Updating Function
{
	int rchoice, vchoice;

	if (lines <= 0) //checking if lines are already 0
	{
		cout << "There are no records to update. Please add a record.\n";
		statisticalReport("itemUpdate - No Records To Update", -1, -1);
		return;	//return to main menu
	}

	while(true)
	{
		cout << "What record number do you want to update? " << endl << ">";
		rchoice = getInt(); //which row to update?
		if (rchoice > lines) //ensuring user does not try to update a non existant record
		{
			cout << "This record does not exist yet, please try adding it first.\n" << endl;
			continue;
		}
		if (rchoice < 1) //ensuring user does not input a number under 1 (minimum record)
		{
			cout << "You can not update a record less than 1.\n" << endl;
			continue;
		}
		break;
	}

	rchoice--; //to match array index
	while(true)
	{
		cout << "What variable would you like to update?" << endl;
		cout << "1- ID, 2- First Name, 3- Second Name" << endl;
		cout << "4- Age, 5- Staff Position 6- Salary" << endl << ">";
		vchoice = getInt(); //which variable to update?
		if (vchoice == 1 || vchoice == 2 || vchoice == 3 || vchoice == 4 || vchoice == 5 || vchoice == 6)
		{
			itemAdd(s, rchoice, vchoice); //using the same code from itemAdd to save space
			statisticalReport("itemUpdate - Record Updated Successfully", rchoice + 1, 2);
			return; //return to main menu
		}
		else
		{	
			cout << "That isn't a valid variable. \n";
			continue;
		}
	}
}

void itemDel(Staff s[]) //-------------------Main Deleting Function
{
	int choice, j=0;

	if (lines <= 0) //checking if lines are already 0
	{
		cout << "There are no records to delete. Please add a record. \n";
		statisticalReport("itemDel - No Records To Delete", -1, -1);
		return;	//return to main menu
	}
	
	while(true)
	{
		cout << "Which record number do you want to delete?" << endl;
		choice = getInt();
		
		if (choice > lines || choice < 1) //ensuring user does not try to delete a nonexistant record
		{
			cout << "This record does not exist yet, try adding it first." << endl;
			continue;
		}
		break;
	}
	
	choice--; //to match array index
	for (int i = 0; i < lines; i++) //checking if ID already exists
	{
		if (i != choice) //allowing all to pass except the index we want to delete
		{
			s[j] = s[i];
			j++;
		}
	}
	lines--; //remove last line
	cout << "Record " << choice + 1 << " deleted!" << endl;
	statisticalReport("itemDel - Record Deleted Successfully", choice+1, 3);
}

//*------------------------------Seaching Functions------------------------------*//

void itemSearch(Staff s[]) 	//-------------------Searching Function
{
	int choice;
	string find;
	int found = 0;

	if (lines <= 0) //checking if lines are already 0
	{
		cout << "There are no records to search for. Please add a record. \n";
		statisticalReport("itemSearch - No Records To Search", -1, -1);
		return;	//return to main menu
	}


	while(true)
	{
		cout << "What variable do you want to search by?" << endl;
		cout << "1- ID, 2- First Name, 3- Second Name" << endl;
		cout << "4- Age, 5- Staff Position 6- Salary" << endl << ">";
		choice = getInt();
		cout << "What are you looking for? " << endl << ">" ;
		cin >> find;
		switch(choice)
		{
			case 1: //search in ID
				for (int i = 0; i < lines; i++)
				{
					itemSearch(s, s[i].id, find, i, found);
				}
				break;
			case 2: //search in First Name
			for (int i = 0; i < lines; i++)
				{
					itemSearch(s, s[i].first_name, find, i, found);
				}
			break;
			case 3: //search in Last Name
			for (int i = 0; i < lines; i++)
				{
					itemSearch(s, s[i].last_name, find, i, found);
				}
				break;
			case 4: //search in age
				for (int i = 0; i < lines; i++)
				{
					itemSearch(s, to_string(s[i].age), find, i, found);
				}
				break;
			case 5: //search in position
				for (int i = 0; i < lines; i++)
				{
					itemSearch(s, s[i].staff_pos.job_name, find, i, found);
				}
				break;
			case 6: //search in salary
				for (int i = 0; i < lines; i++)
				{
					itemSearch(s, to_string(s[i].staff_pos.salary), find, i, found);
				}
				break;
			default:
				cout << "That isn't a valid variable. \n";
				continue; //going back to start of function to try again
		}
		break;
	}

	if (found != 1)
	{
		cout << "\nUnable to find \"" << find << "\" in the records.\n";
		statisticalReport("itemSearch - Records Search Failed", -1, -1);
	}
}

void itemSearch(Staff s[], string c, string f, int i, int& found)
{
	//(unsigned data type to avoid compiler warning about comparing integers of different signedness)
	for (unsigned j = 0; j < (c.length()); j++) //lowercase string to search in
	{
		c[j] = tolower(c[j]);
	}
	for (unsigned j = 0; j < (f.length()); j++) //lowercase string to find
	{
		f[j] = tolower(f[j]);
	}
	
	if ((c.find(f)) == 0) //if found, print it/them
	{
		cout << "\nRecord found!" << endl;
		printing(s, i);
		found = 1;
		statisticalReport("itemSearch - Records Searched Successful", -1, 4);
	}
}

//*------------------------------Sorting Functions------------------------------*//

void itemSort(Staff s[]) //-------------------Sorting Function
{
	int direction;

	if (lines <= 1) //if empty or just one record, then no need to sort
	{
		cout << "There are less than 2 records. No need to sort.\n";
		statisticalReport("itemSort - No Records To Sort", -1, -1);
		return;
	}
	
	while(true)
	{
		cout << "What direction to sort by? " << endl;
		cout << "1- Ascending, 2- Decending"  << endl << ">";
		direction = getInt();
		cout << "What variable to sort by? " << endl;
		cout << "1- ID, 2- First Name, 3- Second Name" << endl;
		cout << "4- Age, 5- Staff Position 6- Salary" << endl << ">";
		sortchoice = getInt();
		if (sortchoice <= 0 || sortchoice > 6) //if user inputs 0 or below, or above 6, these aren't valid options
		{
			cout << "That\'s not a valid variable. Try again." << endl;
			continue;
		}
		if (direction == 1) //ascending
		{
			sort(s, s + lines, compareVariablesAsc);
			switch(sortchoice) //for report
			{
				case 1: //id
					statisticalReport("itemSort - Records Sorted Ascendingly by ID", -1, 5);
					break;
				case 2: //first name
					statisticalReport("itemSort - Records Sorted Ascendingly by First Name", -1, 5);
					break;
				case 3: //last name
					statisticalReport("itemSort - Records Sorted Ascendingly by Last Name", -1, 5);	
					break;		
				case 4: //age
					statisticalReport("itemSort - Records Sorted Ascendingly by Age", -1, 5);
					break;
				case 5: //job name
					statisticalReport("itemSort - Records Sorted Ascendingly by Staff Position", -1, 5);
					break;
				case 6: //salary
					statisticalReport("itemSort - Records Sorted Ascendingly by Salary", -1, 5);
					break;
			}
			break;	
		}
		else if (direction == 2) //descending
		{
			sort(s, s + lines, compareVariablesDes);
			switch(sortchoice) //for report
			{
				case 1: //id
					statisticalReport("itemSort - Records Sorted Descendingly by ID", -1, 5);	
					break;	
				case 2: //first name
					statisticalReport("itemSort - Records Sorted Descendingly by First Name", -1, 5);
					break;
				case 3: //last name
					statisticalReport("itemSort - Records Sorted Descendingly by Last Name", -1, 5);		
					break;
				case 4: //age
					statisticalReport("itemSort - Records Sorted Descendingly by Age", -1, 5);
					break;
				case 5: //job name
					statisticalReport("itemSort - Records Sorted Descendingly by Staff Position", -1, 5);
					break;
				case 6: //salary
					statisticalReport("itemSort - Records Sorted Descendingly by Salary", -1, 5);
					break;
			}
			break;		
		}
		else
		{
			cout << "That\'s not a valid direction. Try again." << endl;
			continue;
		}
	}
	cout << "\nRecords Sorted Succesfully!";
}

bool compareVariablesAsc(Staff a, Staff b) //Ascending sort
{
	switch(sortchoice)
	{
		case 1: //using id
			return (a.id < b.id);	
		case 2: //using first name
			return (a.first_name < b.first_name);
		case 3: //using last name
			return (a.last_name < b.last_name);				
		case 4: //using age
			return (a.age < b.age);
		case 5: //using job name
			return (a.staff_pos.job_name < b.staff_pos.job_name);
		case 6: //using salary
			return (a.staff_pos.salary < b.staff_pos.salary);
	}
	return 0;
}

bool compareVariablesDes(Staff a, Staff b) //Decending sort
{
	switch(sortchoice)
	{
		case 1: //using id
			return (a.id > b.id);
		case 2: //using first name
			return (a.first_name > b.first_name);
		case 3: //using last name
			return (a.last_name > b.last_name);				
		case 4: //using age
			return (a.age > b.age);
		case 5: //using job name
			return (a.staff_pos.job_name > b.staff_pos.job_name);
		case 6: //using salary
			return (a.staff_pos.salary > b.staff_pos.salary);
	}
	return 0;
}

//*------------------------------Printing/Saving Functions------------------------------*//

void itemDisplay(Staff s[]) //-------------------Display Function
{
	cout << "==================================================\n";
	cout << "No.  ID - Name, Age:\n\tPosition, Salary" << endl;
	if (lines == 0) //If there are no items to display
	{
		cout << "Empty \n";
	}
	for (int i = 0; i < lines; i++) //printing items
	{
		printing(s, i);
	}
	cout << "==================================================\n";
		statisticalReport("itemDisplay - Records Displayed Successfully", -1, 6);
}

void printing(Staff s[], int i) //-------------------Printing Function
{
	cout << "-------------------------------------------------\n";
	cout << i+1 << ".  " << s[i].id << " - " << s[i].first_name << " " << s[i].last_name << ", " << s[i].age << ":\n\t";
	cout << s[i].staff_pos.job_name << ", $" << s[i].staff_pos.salary << endl;
}

void itemSave(Staff s[]) //-------------------Saving Function
{
	ofstream staff_file ("Staff List.txt");
	staff_file << "ID, NAME, AGE, STAFF POSITION, SALARY " << endl;
	for (int i = 0; i < lines; i++) //printing items
	{
		staff_file << s[i].id << ", " << s[i].first_name << " " << s[i].last_name << ", " <<  s[i].age;
		staff_file << ", " << s[i].staff_pos.job_name << ", " << s[i].staff_pos.salary << endl;
	}
	cout << "Records saved succesfully!" << endl;
	statisticalReport("itemSave - " + to_string(lines) + " Records Exported to \"Staff List.txt\" Successfully", -1, 7);
}

void statisticalReport(string change, int record, int count) //-------------------Generate Report & Log Files Function
{
	//getting time
    time_t curr_time = time(0);
	tm * curr_tm;
	char timenow[80];
	char reporttime[80];
	string reportname="";
	curr_tm = localtime(&curr_time);
	strftime(timenow, 80, "[%d/%m/%Y | %I:%M:%S%p]", curr_tm);
	strftime(reporttime, 80, "%d-%m-%Y-%I-%M-%S%p", curr_tm);

	//logging time, changes and number of records
	ofstream report_file; //generated when user asks, includes log file for session + statistical details
	ofstream log_file;
	log_file.open("Log File.txt", ios::app); //appending
	for (int i = 0; i < 25; i++)
	{
		savetoreport += timenow[i]; //converting array of char to string
	}
	savetoreport += " " + change;

	log_file << timenow << " " << change;

	if (record != -1) //if a record has been altered
	{
		savetoreport += " - Record " + to_string(record) + " Altered";
		savetoreport += "\n\t\t\t--Current Number of Records: " + to_string(lines);

		log_file << " - Record " << record << " Altered";
		log_file << "\n\t\t\t--Current Number of Records: " << lines;
	}

	savetoreport += "\n\n"; //seperate different logs
	log_file << "\n\n";
	
	// Key Legend for int count:
	// 0 = Print Report
	// 1 = Item Added 		2 = Item Updated 	3 = Item Deleted
	// 4 = Item Searched 	5 = Item Sorted 	6 = Item Displayed
	// 7 - Items Saved
	if (count == 1){ad++;}
	else if (count == 2){upd++;}
	else if (count == 3){del++;}
	else if (count == 4){srch++;}
	else if (count == 5){sor++;}
	else if (count == 6){disp++;}
	else if (count == 7){save++;}

	if (count == 0) //only generated if user requests
	{

		for (int i = 0; i < 21; i++)
		{
			reportname += reporttime[i];
		}
		report_file.open("Statistical Report-" + reportname + ".txt"); //creating file with current time stamp
		
		report_file << "---Modifications to the File---" << endl;
		report_file << "Last Update: " << timenow << endl;
		report_file << "Number of records: " << lines << endl;
		report_file << ad << " File(s) Added." << endl << upd << " File(s) Updated." << endl << del << " File(s) Deleted." << endl;
		report_file << srch << " File(s) Searched." << endl << sor << " Time(s) Sorted." << endl << disp << " Time(s) Displayed." << endl;
		report_file << save << " Time(s) Saved.\n\n";
		report_file << "---File Log---" << endl;
		report_file << savetoreport;
		cout << "User Report Succesfully Generated at " << timenow << endl;
		report_file.close();
	}
	log_file.close();
}