#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;


void xorCrypt(vector<unsigned char>& data, const string& key) {
    for (size_t i = 0; i < data.size(); ++i) {
        data[i] ^= key[i % key.length()];
    }
}


bool readFile(const string& filename, vector<unsigned char>& buffer) {
    ifstream file(filename, ios::binary);
    if (!file) {
        cerr << "Error: Could not open file " << filename << endl;
        return false;
    }

  
    file.seekg(0, ios::end);
    streamsize size = file.tellg();
    file.seekg(0, ios::beg);

 
    buffer.resize(size);
    if (!file.read(reinterpret_cast<char*>(buffer.data()), size)) {
        cerr << "Error: Could not read file " << filename << endl;
        return false;
    }

    return true;
}


bool writeFile(const string& filename, const vector<unsigned char>& buffer) {
    ofstream file(filename, ios::binary);
    if (!file) {
        cerr << "Error: Could not create file " << filename << endl;
        return false;
    }

    if (!file.write(reinterpret_cast<const char*>(buffer.data()), buffer.size())) {
        cerr << "Error: Could not write to file " << filename << endl;
        return false;
    }

    return true;
}

int main() {
    cout << "Simple XOR Encryption Tool" << endl;
    cout << "-------------------------" << endl;

    int choice;
    cout << "1. Encrypt File\n2. Decrypt File\n3. Encrypt Message\n4. Decrypt Message\n";
    cout << "Enter your choice (1-4): ";
    cin >> choice;
    cin.ignore(); 

    if (choice < 1 || choice > 4) {
        cerr << "Invalid choice!" << endl;
        return 1;
    }

    string key;
    cout << "Enter encryption key: ";
    getline(cin, key);

    if (key.empty()) {
        cerr << "Error: Key cannot be empty!" << endl;
        return 1;
    }

    if (choice == 1 || choice == 2) {
        
        string inputFile, outputFile;
        cout << "Enter input filename: ";
        getline(cin, inputFile);
        cout << "Enter output filename: ";
        getline(cin, outputFile);

        vector<unsigned char> buffer;
        if (!readFile(inputFile, buffer)) {
            return 1;
        }

        xorCrypt(buffer, key);

        if (!writeFile(outputFile, buffer)) {
            return 1;
        }

        cout << "Operation completed successfully!" << endl;
    } else {
        
        string message;
        cout << "Enter message: ";
        getline(cin, message);

        vector<unsigned char> buffer(message.begin(), message.end());
        xorCrypt(buffer, key);

        if (choice == 3) {
            cout << "Encrypted message (hex): ";
            for (unsigned char c : buffer) {
                printf("%02x", c);
            }
            cout << endl;
        } else {
            string decrypted(buffer.begin(), buffer.end());
            cout << "Decrypted message: " << decrypted << endl;
        }
    }

    return 0;
}