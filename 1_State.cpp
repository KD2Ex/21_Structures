#include <iostream>
#include <fstream>

using namespace std;

struct state{
    string first_name;
    string last_name;
    string date;
    int cash = 0;
};

void add(ofstream& file, state& record) {
    file << record.first_name << " " << record.last_name << " " << record.date << " " << record.cash << endl;
}

void read(ifstream& file, state& record) {
    while(!(file.eof())) {
        file >> record.first_name >> record.last_name >> record.date >> record.cash;
        if (record.first_name.empty()) {
            break;
        } else {
            cout << record.first_name << " " << record.last_name << " "  << record.date << " " << record.cash
                 << " " << endl;
            record.first_name = "";
        }
    }
}

int main() {
    string operation;
    cout << "Enter a preferable operation:\n";
    cin >> operation;
    state record;
    if (operation == "add") {
        ofstream file("state.txt", ios::app);

        if (!file.is_open()) {
            cout << "Couldn't open the file\n";
            return 0;
        }

        cout << "Enter a record:\n";
        cin >> record.first_name >> record.last_name >> record.date >> record.cash;
        add(file, record);
        file.close();
    } else if (operation == "read") {
        ifstream file("state.txt");
        if (!file.is_open()) {
            cout << "Couldn't open the file\n";
            return 0;
        }
        read(file,record);
        file.close();
    } else {
        cout << "Wrong type of operation!";
    }
}