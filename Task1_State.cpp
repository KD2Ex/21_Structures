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
/*    do {
        file >> record.first_name >> record.last_name >> record.date >> record.cash;
        cout << record.first_name << " " << record.last_name << " "  << record.date << " " << record.cash
        << " " << endl;
    } while(!(file.eof() || record.first_name.empty()));*/
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
        cout << "Enter a record:\n";
        cin >> record.first_name >> record.last_name >> record.date >> record.cash;
        add(file, record);
        file.close();
    } else if (operation == "read") {
        ifstream file("state.txt");
        read(file,record);
        file.close();
    } else {
        cout << "Wrong type of operation!";
    }
}