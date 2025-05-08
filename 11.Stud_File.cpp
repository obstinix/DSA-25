#include <iostream>
#include <fstream>
using namespace std;

typedef struct student
{
	int rollno;
	char name[20];
	char cls[10];
	char div[10];
	char add[50];
}student;

class seq
{
public:
	void search();
	void insert();
	void del();
	void print();
	void modify();
};

fstream master, temp;
int main()
{
	int op, rollno;
	student x;
	seq s;

	do{
		cout<<"\n 1. Insert a record";
		cout<<"\n 2. Delete a record";
		cout<<"\n 3. Modify a record";
		cout<<"\n 4. Search a record";
		cout<<"\n 5. Print a record";
		cout<<"\n 6. Quit";

		cout<<"\n\n Enter your choice : ";
		cin>>op;

		switch(op)
		{
			case 1:
				s.insert();
				break;
			case 2:
				s.del();
				break;
			case 3:
				s.modify();
				break;
			case 4:
				s.search();
				break;
			case 5:
				s.print();
				break;
		}
	}while(op != 6);
	return 0;
}
void seq :: insert()
{
	student st;
	master.open("StudInfo.txt", ios::app|ios::in|ios::out);
	master.clear();

	cout<<"\n Enter the record : \n";
	cout<<"\n Roll No. : Name : Class : Division : Address\n";
	cin>>st.rollno>>st.name>>st.cls>>st.div>>st.add;

	//Now write a record into file
	master.write((char *)&st, sizeof st);

	master.close();
}
void seq :: print()
{
	student st;
	master.open("StudInfo.txt", ios::in);

	while(master.read((char *)&st, sizeof st))
		cout<<st.rollno<<" "<<st.name<<" "<< st.cls<<" "<<st.div<<" "<<st.add<<endl;
	cout<<endl;
	master.close();
}
void seq :: modify()
{
	student st;
	int rec_no;
	master.open("StudInfo.txt", ios::in|ios::out);	//original file

	cout<<"\n Enter the record no to be modified : ";
	cin>>rec_no;

	int loc = (rec_no-1)*sizeof(st);

	master.seekp(loc);

	cout<<"\n Enter the record : \n";
	cout<<"\n Roll No. : Name : Class : Division : Address\n";
	cin>>st.rollno>>st.name>>st.cls>>st.div>>st.add;


	master.write((char *)&st, sizeof st);

	master.close();
	cout<<"\n";
}
void seq :: search()
{
	student st;
	int rollno, flag = 0;

	master.open("StudInfo.txt", ios::in);

	cout<<"\n Enter the roll no to be searched : ";
	cin>>rollno;

	while(master)
	{
		master.read((char *)&st, sizeof st);
		if(st.rollno == rollno)
		{
			flag = 1;
			cout<<"\n record found \n ";
			cout<<st.rollno<<" "<<st.name<<" "<< st.cls<<" "<<st.div<<" "<<st.add<<endl;
			break;
		}
	}
	if(flag == 0)
		cout<<"\n Record does not exist \n";
	cout<<"\n";
	master.close();
}
void seq :: del()
{
	student st;
	int rec_no;
	master.open("StudInfo.txt", ios::in|ios::out);	//original file
	temp.open("temp", ios::out);	                //temp file

	cout<<"\n Enter the record no to be deleted : ";
	cin>>rec_no;

	int count = 0;
	while(master.read((char *)&st, sizeof st))
	{
		count++;
		if(rec_no == count)
			break;
		else
			temp.write((char *)&st, sizeof st);
	}
	while(master.read((char *)&st, sizeof st))
		temp.write((char *)&st, sizeof st);

	master.close();
	temp.close();

	master.open("StudInfo.txt",ios::out);
	temp.open("temp",ios::in);

	while(temp.read((char *)&st, sizeof st))
		master.write((char *)&st, sizeof st);

	master.close();
	temp.close();

	cout<<"\n";
}
