#include <iostream>
#include "DynIntStack.h"
#include<string>
#include<fstream>
#include<sstream>

using namespace std;


void deleteStack(DynIntStack & stack){
	int a;
	while (stack.isEmpty()==false)
	{
		stack.pop(a);	

	}
	
	cout<<"Stack emptied and program ending. "<<endl;





}
int spaceNum(string& line){//to count number of spaces before the line

	int i=0;
	int count=0;
	while(i<line.length()){
		if (line[i]==' ')
		{
			count++;
		}
		else {
			break;}
		i++;
	}

	return count;

}
bool isKeyword(string word){//to check if the given word is a keyword


	if (word == "if")
		return true;
	else if (word == "elif")
		return true;
	else if (word == "while")
		return true;
	else if (word == "else")
		return true;
	else if (word == "for")
		return true;
	else 
		return false;
}
string keywordName(string word)//to understand the what is the given word
{

	if (word == "if")
		return word;
	else if (word == "elif")
		return word;
	else if (word == "while")
		return word;
	else if (word == "else")
		return word;
	else if (word == "for")
		return word;
	else 
		return word;



}

int main(){
	DynIntStack stack;
	string filename;
	fstream input;
	string option=" ";
	cout<<"Please enter a file name: "<<endl;
	cin >> filename;
	input.open(filename);
	while(!(input.is_open()))//INPUT CHECK FOR FILE 
	{
		cout<<"Unable to open file, please enter a different file name: "<<endl;
		cin>> filename;
		input.open(filename);
	}
	cout<<"Starting file analysis... \nInitial indentation level is pushed to the stack as 0. "<<endl;//
	cout<<endl;

	stack.push(0);//pushing initial 0

	bool check=true;
	int popped;
	int linenum=1;
	string line;
	string firstword;
	string tempword;


	/* Reading and chekcing the first line separately*/
	getline(input,line);
	istringstream reader (line);
	int spaces=spaceNum(line);
	stack.pop(popped);//popping 0 out of stack so we can add the actaul number of spaces and to compare popped one
	stack.push(spaces);//pushing number of spaces

	cout<<"Line: "<< line<<endl;
	cout<<"Line number: "<<linenum<<endl;

	cout << spaces <<" number of spaces observed before the start of the line. "<< endl;
	cout<< "Current Level = "<<popped<<" This Line = "<<spaces<<endl;//popped = current indententaion level // spaces = this line indention level

	reader>>firstword;

	//since this is the first line we do not need to check keywords
	if (popped>spaces)//if current level > this line level
	{
		cout<<"Current line must be greater than the Current indentation level.\nStopping file analysis... "<<endl;
		check=false;
		cout<<endl;
		deleteStack(stack);
		return 0;
	}
	else if (popped<spaces){
		cout<<"Incorrect file structure.\nCurrent line cannot be greater than the Current indentation level. "<<endl;
		cout<<"Stopping file analysis..."<<endl; 
		check=false;
		cout<<endl;
		deleteStack(stack);
		return 0;
	}
	else if( popped==spaces)//only appropriate form
	{
		cout<<"Line belongs to current block."<<endl;
	}	
	if(isKeyword(firstword)==true){// if there is keyword observed in this line
		cout<< "Keyword " << keywordName(firstword)<< " found on this line."<<endl;
	}



	if (check==true){
		while(getline(input,line)){//reading the rest of the file doing necessary checks

			tempword=firstword;//temporary word for holding the previous line's first word

			istringstream reader (line);
			linenum++;
			reader>>firstword;

			cout<<endl;
			cout<<"Line number: "<<linenum<<endl;
			cout<<"Line: "<< line<<endl;

			spaces=spaceNum(line);
			cout << spaces <<" number of spaces observed before the start of the line. "<< endl;		


			stack.pop(popped);//popped = current indentation level

			if(isKeyword(tempword)==true){
				cout<<"This line proceeds a keyword containing line. "<<endl;
			}

			cout<< "Current Level = "<<popped<<" This Line = "<<spaces<<endl;
			//CHECKS//

			stack.push(popped);//to maintain current indentation level

			if (isKeyword(tempword)==true && popped<spaces)
			{
				cout<<"Line correct. "<< "Depth "<< spaces << " added to the stack. "<<endl;
				stack.push(spaces);
			}	
			else if (isKeyword(tempword)==true && popped>=spaces)//if there is keyword before this line and current ind level greater than this line level
			{
				cout<<"Current line must be greater than the Current indentation level.\nStopping file analysis... "<<endl;
				check=false;
				cout<<endl;
				deleteStack(stack);
				break;
			}
			else if(isKeyword(tempword)==false && popped>spaces)//if there is no keyword before this line and current current level is greater than this line level
			{
			
				stack.pop(popped);
				cout<<"Current line is smaller than Current indentation level; checking if line belongs to outer indentation. "<<endl;
				if(popped==spaces){//if this line equals any outer block indentation
						cout<<"Line belongs to outer block. "<<endl;
						stack.push(popped);
					}	
					else if (stack.isEmpty()==true&&popped!=spaces)//if stack is empty which means there is no indentation level equals to this line level
					{
						cout<<"Incorrect file structure.\nAn indentation level same as the Current line is not found in outer blocks.\nStopping file analysis... "<<endl;
						check=false;
						cout<<endl;
						deleteStack(stack);
						break;
					}

					else if(stack.isEmpty()==true&&popped==spaces){//if this line equals any outer block indentation
						cout<<"Line belongs to outer block. "<<endl;
						stack.push(popped);

					}
					
				while(popped!=spaces){//checking if the block belongs to another indentation level
					
					stack.pop(popped);
					
					
					cout<< "Current Level = "<<popped<<" This Line = "<<spaces<<endl;
					cout<<"Current line is smaller than Current indentation level; checking if line belongs to outer indentation. "<<endl;
					if(popped==spaces){//if this line equals any outer block indentation
						cout<<"Line belongs to outer block. "<<endl;
						stack.push(popped);
					}	
					else if (stack.isEmpty()==true&&popped!=spaces)//if stack is empty which means there is no indentation level equals to this line level
					{
						cout<<"Incorrect file structure.\nAn indentation level same as the Current line is not found in outer blocks.\nStopping file analysis... "<<endl;
						check=false;
						cout<<endl;
						deleteStack(stack);
						break;
					}

					else if(stack.isEmpty()==true&&popped==spaces){//if this line equals any outer block indentation
						cout<<"Line belongs to outer block. "<<endl;
						stack.push(popped);

					}
				
				}

			}


			else if (isKeyword(tempword)==false && popped<spaces){//if no keyword observed before this line and current level is less then this line
				cout<<"Incorrect file structure.\nCurrent line cannot be greater than the Current indentation level. "<<endl;
				cout<<"Stopping file analysis..."<<endl; 
				check=false;
				cout<<endl;
				deleteStack(stack);
				break;

			}
			else if(isKeyword(tempword)==false && popped==spaces)
			{
				cout<<"Line belongs to current block."<<endl;
			}	
			if(isKeyword(firstword)==true){// if there is keyword observed in this line
				cout<< "Keyword " << keywordName(firstword)<< " found on this line."<<endl;
			}
		}
	}

	if (check==true){
		cout<<endl;
		cout<<"Finished file analysis. File structure is correct! "<<endl;
		deleteStack(stack);
	}

	return 0;

}