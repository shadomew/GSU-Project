#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <map>
#include <ctime>
#include <iterator>

using namespace std;

class directory{
public:
	string title;
	time_t created;
	map <string, directory> children; 
	string files[50];
	time_t fcreated[50];
	int numfiles = 0;
	directory *parent;
	
	directory(string a){
	    title = a;
	}

	directory(string a, directory *b){
		title = a;
		parent = b;
	} 
	
	void clear(){
	this->children.clear();
	}

};

//this is is you just cd, goes to parent unless in root
/*void cd(directory root, directory *curr, directory **curr){
	if(curr = &root){
	return;
	}
	else{
	*curr = *curr->parent;
	}
}
//cd  taking parameter to children or parent specifically
void cd(directory root, directory *curr, directory newdir){
	if(curr = &root){
	return;
	}
	else{
		if(newdir.title = curr->parent->title){
		
		}
	}
}*/



void mkfs(directory dir){
    	//map<string,directory>root;
	dir.clear();
	//directory ("root");
	//root.insert(pair<string,directory>("root",a));
	
	cout<<"System has been formatted"<<endl;
}
void ls(directory *curr){
	
	//curr->files[curr->numfiles] = name;
	map<string, directory >::iterator i; //part of the map class
	for (i = curr->children.begin();i != curr->children.end(); ++i){
		
	cout<<"["<<i->first<<"]"<<"  ";
	}
	
	for(int k = 0; k<curr->numfiles;k++){
	cout<<curr->files[k]<<" ";
	}
	cout<<endl; 
}

void rmdir(string name, directory *curr){
	bool found = false;
	map<string, directory >::iterator i;
	for (i = curr->children.begin();i != curr->children.end(); ++i){
	if(i->first == name){	
	curr->children.erase(i);
	found =true;
		}
	}
	if(found ==false){
	cout<<"directory: "<<name<<" not found"<<endl;	
	}
}

void rmfl(string name, directory *curr){
	bool found = false;
	for(int i = 0; i < curr->numfiles; i++){
		if(curr->files[i] ==name){
		curr->files[i] = "\0";
		found =true;
		
		}
	}
	
	if(found ==false){
	cout<<"file: "<<name<<" not found"<<endl;
	}

}


void mkfl(string name, directory *curr){

    curr->files[curr->numfiles] = name;
    cout<<"file "<<name<<" added to directory "<<curr->title<<endl;
    curr->numfiles++;
}

void mkdir(string name, directory *curr){
string temp = name;

//constructor taking name and pointer to parent directory
directory b(temp, curr);

cout<< "directory " << temp << " created in " << curr->title << endl;

curr->children.insert(pair<string,directory>(name,b));

}

bool exit(){
return false;
}

void shell_loop(directory root, directory *curr, bool format){
bool status =1;
string input;
string command;
string parameter = "";

	do{
	cout<< "My_shell_3232: ";
	getline(cin, input);
	for(int i = 0; i<input.length();i++){
	//looks for space in command line, assigns command and parameter
	if(input[i] ==' '){
	command = input.substr(0,i);
	parameter = input.substr(i+1,input.length()-1);
	break;
	}else{
	//no space, no parameter entered
	command = input;
	}
}
	if (command=="exit"){
	
	status = exit();
	}
	if (command=="mkfs"){
		mkfs(root);
	}
	if(command =="mkfl"){
		if(parameter == ""){
		cout<<"command requires parameter"<<endl;
		}else{
		mkfl(parameter, curr);
		}
	}
	if(command =="mkdir"){
		if(parameter == ""){
		cout<<"command requires parameter"<<endl;
		}else{
		mkdir(parameter, curr);
		}
	}
		if(command =="ls"){
		ls(curr);
	}
	if(command == "rmdir"){
		if(parameter == ""){
		cout<<"command requires parameter"<<endl;
		}else{
		rmdir(parameter, curr);
		}
	}
	if(command == "rmfl"){
		if(parameter == ""){
		cout<<"command requires parameter"<<endl;
		}else{
		rmfl(parameter, curr);
		}
	}
	//if(command =="cd"){
	//	if(parameter==""){cd(root, curr, *curr);}

	//}
	}while(status ==  1);
}





int main(){

bool format = 0;

directory rootdir("root");
directory *curr = &rootdir;

//initializes the shell loop 
cout<<"Welcome to CSCI 3232 shell file system!\n";

shell_loop(rootdir, curr, format);



cout<<"bye"<<endl;

return EXIT_SUCCESS;
}
