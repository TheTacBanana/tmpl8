//#include <fstream>
//#include <stdio.h>
//#include <stdlib.h>
//#include <unistd.h>
#include <iostream>
#include <experimental/filesystem>
#include <string>
#include <algorithm>

using namespace std;
namespace fs = std::experimental::filesystem;

string storagePath = string(getenv("HOME")) + "/tmpl8";

void ListTemplates(){
    for (const auto & entry : fs::directory_iterator(storagePath)){
        fs::path path (entry);
		std::string filename = path.filename();
		std::cout << filename << std::endl;
    }
}

void MakeTemplateFromDir(string templateName){
    fs::copy(fs::current_path(), storagePath + "/" + templateName);
}

void RemoveTemplate(string templateName){
    fs::remove_all(storagePath + "/" + templateName);
}

void InitFromTemplate(string templateName, string newName){
	string path = storagePath + "/" + templateName;
    if (fs::exists(path)){
		string newDir = string(fs::current_path()) + "/" + newName;
		fs::create_directory(newDir);
        fs::copy(path, newDir);
    } else {
		std::cout << "Template not found" << std::endl;
    }
}

int main(int argc, char *argv[]){
    if (fs::exists(storagePath) == false) {
        fs::create_directory(storagePath);
        std::cout << "Created Template Directory" << std::endl;
    }

    if (argc >= 2){
        string command = argv[1];
		transform(command.begin(), command.end(), command.begin(), ::toupper);

		if (command == "LIST"){
            ListTemplates();
        }
		else if (command == "REMOVE"){
            if (argc >= 3)
            	RemoveTemplate(string(argv[2]));
			else
				std::cout << "Arguments not present" << std::endl;
        }
        else if (command == "NEW"){
			if (argc >= 3)
            	MakeTemplateFromDir(string(argv[2]));
			else
				std::cout << "Arguments not present" << std::endl;
        }        
        else if (command == "CREATE"){
			if (argc >= 4)
            	InitFromTemplate(string(argv[2]), string(argv[3]));
			else
				std::cout << "Arguments not present" << std::endl;
        }
    }
    return 0;
}