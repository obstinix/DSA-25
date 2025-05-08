#include<iostream>
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
	int r;
	int HT[10];
	seq(){
		r = 1;
		for(int i = 0; i<10; i++)
			HT[i] = -1;
	}
	
	void search();
	void insert();
	void print();
	void modify();
};

fstream master, temp;
int main()
{
	int op, rollno;
	student x;
	seq s;
	master.open("StudInfo.txt", ios::out);
	master.close();
	do{
		cout<<"\n 1. Insert a record";
		cout<<"\n 2. Modify a record";
		cout<<"\n 3. Search a record";
		cout<<"\n 4. Print a record";
		cout<<"\n 5. Quit";

		cout<<"\n\n Enter your choice : ";
		cin>>op;

		switch(op)
		{
			case 1:
				s.insert();
				break;
			case 2:
				s.modify();
				break;
			case 3:
				s.search();
				break;
			case 4:
				s.print();
				break;
		}
	}while(op != 5);
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
	
	//Prepare index of hash table
	int index = st.rollno%10;
	HT[index] = r++;

	//Now write a record into file
	master.write((char *)&st, sizeof st);

	master.close();
}
void seq :: print()
{
	student st;
	master.open("StudInfo.txt", ios::in);
	cout<<"\n Hash Index : Roll No. : Name : Class : Division : Address\n";
	for(int i = 0; i<10 ; i++)
	{
		if(HT[i]!=-1)
		{
			int rec_no = HT[i];
			//cout<<rec_no<<endl;
			int loc = (rec_no-1)*sizeof(st);
			master.seekp(loc);
			master.read((char *)&st, sizeof st);
			cout<<i<<" "<<st.rollno<<" "<<st.name<<" "<< st.cls<<" "<<st.div<<" "<<st.add<<endl;
		}
	}
	master.close();
}
void seq :: modify()
{
	student st;
	int rec_no, roll_no;
	master.open("StudInfo.txt", ios::in|ios::out);	//original file

	cout<<"\n Enter the roll no to be modified : ";
	cin>>roll_no;
	
	rec_no = HT[roll_no%10];

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
	int roll_no, rec_no;

	master.open("StudInfo.txt", ios::in);

	cout<<"\n Enter the roll no to be searched : ";
	cin>>roll_no;
	
	rec_no = HT[roll_no%10];
	//cout<<rec_no<<endl;
	if(rec_no != -1)
	{
		int loc = (rec_no-1)*sizeof(st);
		master.seekp(loc);
		master.read((char *)&st, sizeof st);
		cout<<"\n record found \n ";
		cout<<st.rollno<<" "<<st.name<<" "<< st.cls<<" "<<st.div<<" "<<st.add<<endl;
	}
	else
		cout<<"\n Record does not exist \n";
	cout<<"\n";
	master.close();
}