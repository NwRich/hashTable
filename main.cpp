#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <ctime>

using namespace std;
struct student {
  char* fName = new char[64];
  char* lName = new char[64];
  int id = -1;
  float gpa = -1;
  student* next;
  student* prev;
};

void print(student* table[], int size);
bool hashT(student* table[], int &size, student* news);

int main() {
  student* *table = new student*[100];
  int size = 100;
  for (int i = 0; i < 100; i++) {
    table[i] = NULL;
  }
  char* input = new char[16];
  bool working = true;
  bool rehash = false;
  while (working == true) {
    cout << "add, remove, print, random student, or quit?" << endl;
    cin.getline(input, 16);
    if (strcmp(input, "quit") == 0) {
      working = false;
    }
    if (strcmp(input, "add") == 0) {
      student* news = new student();//news stands for newStudent and I am to lazy to go back and change it
      cout << "what is the first name?" << endl;
      cin >> news->fName;
      cout << "what is the students last name?" << endl;
      cin >> news->lName;
      cout << "what is the students id?" << endl;
      cin >> news->id;
      cout << "what is the students gpa?" << endl;
      cin >> news->gpa;
      rehash = hashT(table, size, news);
    }
    if (strcmp(input, "remove") == 0) {
      cout << "what is the id of the student that you want to terminate?" << endl;
      int id = -1;
      cin >> id;
      int index = id%size;
      delete table[index];
      table[index] = NULL;
    }
    if (strcmp(input, "random") == 0) {
      int numS = -1;//number of students to add
      char* fNames[256];
      char* lNames[256];
      char* temp = new char[256];
      bool empty = false;
      int index;
      cout << "how many students do you want to add?" << endl;
      cin >> numS;
      cin.get();
      for (int i = 0; i < numS; i++) {
	ifstream file;
	file.open("fName.txt");
	if (file.is_open()) {
	  for (int i = 0; i < file.eof() == false; i++) {
	    file.getline(temp,256);
	    fNames[i] = new char[256];
	    strcpy(fNames[i], input);
	  }
	}
	else {
	  cout << "file not found" << endl;
	}
	ifstream file2;
	file2.open("lName.txt");
	if (file.is_open()) {
	  for (int i = 0; i < file.eof() == false; i++) {
	    file2.getline(temp,256);
	    lNames[i] = new char[256];
	    strcpy(lNames[i], input);
	  }
	}
	else {
	  cout << "file not found" << endl;
	}
	student* news = new student();
	srand(time(NULL)/(i+1));
	index = rand()%100;
	news->fName = fNames[index];
	srand(time(NULL)/(i+1));
	index = rand()%100;
	news->lName = lNames[index];
	index = rand();
	news->id = index%1000000;
	news->gpa = index%4;
	rehash = hashT(table, size, news);
      }
    }
    if (strcmp(input, "print") == 0) {
      print(table, size);
    }
  }
  cout << "ending..." << endl;
  return 0;
}

bool hashT(student* table[], int &size, student* news) {
  int index;
  index = news->id%size;
  if (table[index] == NULL) {
    table[index] = news;
  }
  else {
    if (table[index]->next == NULL) {
      table[index] = news;
      news->prev = table[index]->next;
    }
    else if (table[index]->next->next == NULL) {
      table[index]->next->next = news;
      news->prev = table[index]->next->next;
    }
    else {
      table[index]->next->next->next = news;
      return true;
    }
  }
  int num = 0;
  for (int i = 0; i < size; i++) {
    if (table[i] != NULL) {
      num++;
    }
  }
  if (num >= size/2) {
    return true;
  }
}

void print(student* table[], int size) {
  cout << endl;
  for (int i = 0; i < size; i++) {
    if (table[i] != NULL) {
      cout << table[i]->fName << " ";
      cout << table[i]->lName << " ";
      cout << table[i]->id << " ";
      cout << table[i]->gpa << endl;
      if (table[i]->next != NULL) {
	cout << table[i]->fName << " ";
	cout << table[i]->lName << " ";
	cout << table[i]->id << " ";
	cout << table[i]->gpa << endl;
	if ( table[i]->next->next != NULL) {
	  cout << table[i]->fName << " ";
	  cout << table[i]->lName << " ";
	  cout << table[i]->id << " ";
	  cout << table[i]->gpa << endl;
	}
      }
    }
  }
  cout << endl;
}
