#ifndef HEADER_H
#define HEADER_H

//-------------------Structures-------------------
struct Jobs
{
	string job_name;
	int salary;
};

struct Staff
{
	string first_name;
	string last_name;
	string id;
	int age;
	struct Jobs staff_pos; //connecting Staff to Jobs
};

//-------------------Function Prototypes-------------------
int getInt(); //Making sure user does not input a non-integer value using “try check”
int maxLines(); //Maximum allowed records, to allow for array size determined by user
int countLines(); //Count number of pre-set  records in file
void itemAdd(Staff s[], int rupdate, int vupdate); //Adding Items
void itemDel(Staff s[]); //Deleting Items
void itemUpdate(Staff s[]); //Updating Items
void itemSearch(Staff s[]); //Searching for Item(s) – Asking user what to find
	void itemSearch(Staff s[], string c, string f, int i, int& found); //Actually searching for what the user wants
void itemSort(Staff s[]); //Sorting Items
	bool compareVariablesAsc(Staff a, Staff b); //Ascending Sort
	bool compareVariablesDes(Staff a, Staff b); //Descending Sort
void itemDisplay(Staff s[]); //Displaying Items
void printing(Staff s[], int i); //Printing (used for itemDisplay and itemSearch)
void itemSave(Staff s[]); //Saving Items
void statisticalReport(string change, int record, int count); //Statistical Report

//-------------------Global Variables-------------------
int lines = countLines(); //not counting header
int maxlines = maxLines(); //maximum allowed records in the file
int rupdate = -1; //to bypass itemUpdate condition in itemAdd
int vupdate = -1; //to bypass variable selection of itemUpdate in itemAdd
int sortchoice = 0; //sorting choice
bool printreport = 0; //flag for printing report
int ad=0, upd=0, del=0, srch=0, sor=0, disp=0, save=0; //counts for report
string savetoreport = ""; //string for report

#endif
