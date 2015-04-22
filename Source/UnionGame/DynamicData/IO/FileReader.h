#ifndef DynamicDataIO_FileReader_H_
#define DynamicDataIO_FileReader_H_

#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>
#include <streambuf>


using namespace std;
class FileReader {
public:
	string readFile(string path) {
		ifstream t(path);
		string str;

		t.seekg(0, ios::end);
		str.reserve(t.tellg());
		t.seekg(0, ios::beg);

		str.assign((istreambuf_iterator<char>(t)),
			istreambuf_iterator<char>());

		return str;
	}
};
#endif //DynamicDataIO_FileReader_H_