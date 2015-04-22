#ifndef DynamicDataIO_FileWriter_H_
#define DynamicDataIO_FileWriter_H_

#include <fstream>
#include <string>
#include <iostream>


using namespace std;
class FileWriter {
public:
	void writeFile(string path, string text) {
		ofstream out(path);
		out << text;
		out.close();
	}
};


#endif //DynamicDataIO_FileWriter_H_