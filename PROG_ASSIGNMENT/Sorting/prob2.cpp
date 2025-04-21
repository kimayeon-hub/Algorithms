#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

class Person {
private:
	string name, company, address, zipcode, phones, email;

public:
	Person() = default;
	Person(string n, string c, string a, string z, string p, string e): name(n), company(c), address(a), zipcode(z), phones(p), email(e) {}
	
	void print() {
		cout << name << endl;
		cout << "\tCompany: " << company << endl;
		cout << "\tAddress: " << address << endl;
		cout << "\tZIpcode: " << zipcode << endl;
		cout << "\tPhones: " << phones << endl;
		cout << "\tEmail: " << email << endl;
	}

	string get_name() { return name; }
	string get_company() { return company; }
	string get_address() { return address; }
	string get_zipcode() { return zipcode; }
	string get_phones() { return phones; }
	string get_email() { return email; }
};

string trim(string str) {
	int s = 0, t = str.length() - 1;
	while (s < str.length() && isspace(str[s]))
		s++;
	while (t >= 0 && isspace(str[t]))
		t--;
	
	if (s <= t)
		return str.substr(s, t - s + 1);
	return "";
}

vector<string> split_line(string line, char delimiter) {
	vector<string> tokens;
	stringstream sstream(line);
	string str;
	while (getline(sstream, str, delimiter))
		tokens.push_back(trim(str));
	return tokens;
}

void read_file(string filename, vector<Person> &vec) {
	ifstream infile(filename);
	string line;
	while (getline(infile, line)) {
		vector<string> tokens = split_line(line, '|');
		Person p(tokens[0], tokens[1], tokens[2], tokens[3], tokens[4], tokens[5]);
		vec.push_back(p);
	}
	infile.close();
}

void sort_by_name(vector<Person> &vec) {
	sort(vec.begin(), vec.end(), [](Person a, Person b) {return a.get_name() < b.get_name(); });
}

void sort_by_company(vector<Person>& vec) {
	sort(vec.begin(), vec.end(), [](Person a, Person b) {return a.get_company() < b.get_company(); });
}

void sort_by_address(vector<Person>& vec) {
	sort(vec.begin(), vec.end(), [](Person a, Person b) {return a.get_address() < b.get_address(); });
}

void sort_by_zipcode(vector<Person>& vec) {
	sort(vec.begin(), vec.end(), [](Person a, Person b) {return a.get_zipcode() < b.get_zipcode(); });
}

void sort_by_phones(vector<Person>& vec) {
	sort(vec.begin(), vec.end(), [](Person a, Person b) {return a.get_phones() < b.get_phones(); });
}

void sort_by_email(vector<Person>& vec) {
	sort(vec.begin(), vec.end(), [](Person a, Person b) {return a.get_email() < b.get_email(); });
}

void print(vector<Person>& vec) {
	for (Person p : vec)
		p.print();
	cout << endl;
}

void process_command() {
	vector<Person> address_book;
	string command;
	while (true) {
		cout << "$ ";
		getline(cin, command);
		vector<string> commands = split_line(command, ' ');

		if (commands.size() == 2 && commands[0] == "read")
			read_file(commands[1], address_book);
		else if (commands.size() == 2 && commands[0] == "sort") {
			if (commands[1] == "-name")
				sort_by_name(address_book);
			else if (commands[1] == "-company")
				sort_by_company(address_book);
			else if (commands[1] == "-address")
				sort_by_address(address_book);
			else if (commands[1] == "-zipcode")
				sort_by_zipcode(address_book);
			else if (commands[1] == "-phones")
				sort_by_phones(address_book);
			else if (commands[1] == "-email")
				sort_by_email(address_book);
		}
		else if (commands.size() == 1 && commands[0] == "print")
			print(address_book);
		else if (commands.size() == 1 && commands[0] == "exit")
			return;
	}
}

int main() {
	process_command();
	return 0;
}