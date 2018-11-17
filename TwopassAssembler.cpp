/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TwopassAssembler.cpp
 * Author: Rojen
 *
 * Created on November 9, 2018, 9:18 PM
 */

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <sstream>
using namespace std;
int address[100]; 
string opcode2[]={"JNS,""LOAD","STORE","ADD","SUBT","INPUT","OUTPUT","HALT","SKIPCOND","JUMP","CLEAR","ADDL","JUMPI","LOADI","STOREL"};
map <string, string> OP;
multimap<string, int> Symboltable;
int code [100];
int sizeofsymbol =0;
 string symbol[100];
    int add[100]; 
    bool isOpcode2(string op){
         for (int i= 0; i<15;i++){
        if(opcode2[i]==op){
        return true;
         cout << "done";
        }
    }
    }

int search( string a){
    if (a=="a"){return 0;}
    for (int i = 0;i< sizeof(symbol);i++){
        if(symbol[i]==a) 
       return i;
    }
    return 0 ;
}

int main(int argc, char** argv) {
  OP.insert(pair <string, string> ("JNS", "0"));
  OP.insert(pair <string, string> ("LOAD", "1"));
  OP.insert(pair <string, string> ("STORE", "2"));
  OP.insert(pair <string, string> ("ADD", "3"));
  OP.insert(pair <string, string> ("SUBT", "4"));
  OP.insert(pair <string, string> ("INPUT", "5"));
  OP.insert(pair <string, string> ("OUTPUT", "6"));
  OP.insert(pair <string, string> ("HALT", "7"));
  OP.insert(pair <string, string> ("SKIPCOND", "8"));
  OP.insert(pair <string, string> ("JUMP", "9"));
  OP.insert(pair <string, string> ("CLEAR", "A"));
  OP.insert(pair <string, string> ("ADDI", "B"));
  OP.insert(pair <string, string> ("JUMPI", "C"));
  OP.insert(pair <string, string> ("LOADI", "D"));
  OP.insert(pair <string, string> ("unused", "F"));
    ifstream in ;
    string file;
    string read;
    string label;
    string value;
    list<string> Opcode;
    list<string> Label;
    list<string> Val;
    int counter=000,i=0;
    cout << "Enter the file name:";
    cin >> file;
    in.open(file);
     int r=0;
        while(!in.eof()){
              in>> read;
                 if (read.find('#')!=std::string::npos) {
                in.ignore(256,'\n');
                counter -=1;
                    }
                 else if (read!="#") {
                        if (read.find(',')!=std::string::npos){
                            symbol[r]=read[0];
                            add[r]=counter;
                            r++;
                            Label.push_back(read);
                            in>> read;
                            if(read=="HALT"|| read=="OUTPUT" ||read=="INPUT"|| read=="CLEAR"){
                                       Opcode.push_back(read);
                                        Val.push_back("a");}
                             else {Opcode.push_back(read);
                                     if(read=="ORG"){
                                        in>> read;
                                        counter = std::stoi(read); 
                                         Val.push_back(read); 
                                        }
                                     else{ in >> read;
                                         Val.push_back(read);
                                         }
                                        }

                            }
                     else {
                         if(read=="HALT"|| read=="OUTPUT" ||read=="INPUT"|| read=="CLEAR"){
                                Opcode.push_back(read);
                                 Val.push_back("a");
                                 }
                        else {Opcode.push_back(read);
                            if(read=="ORG"){
                                 in>> read;
                                counter = std::stoi(read); 
                                 Val.push_back(read); }
                                else{ 
                                    in >> read;
                                     Val.push_back(read);}
                                    }           
                            }  
                    }
                i++;
                address[i]=counter;
                counter++;
            }
           sizeofsymbol=r;
           in.close();
    // First pass of Two pass Assembler
   string comma =",";
    cout << "-------SYMBOL TABLE-------"<< endl;
    cout << "Symbol---------------Value"<< endl;
    for ( int i =0 ; i< sizeofsymbol; i++ ){
    cout << symbol[i]<<"--------------------"<< add[i]<< endl;
    }

    int b=0;
    string Value[100];
    for (string j :Val){
    Value[b]=j;
    b++;
    }
    // Second pass of two pass assembler
    std::map<string,string>::iterator it;
    int k=0;
    int loc=0;
    int c=0;
    std::list<string>::iterator i2=Val.begin();
    cout << "--ASSEMBLER PASS TWO---"<< endl;
    cout <<"Location------------Code"<< endl;
            for (string i :Opcode ){
                    cout << "0"<<address[k];
                                     if (i=="DEC"){ 
                                             int num=std:: stoi (Value[k]);
                                             std ::stringstream ss; 
                                            ss << hex << num; 
                                            string res = ss.str(); 
                                            cout <<"---------------"<<"0x" << res <<"----"<<symbol[c]<< " " <<i<< "---"<< Value[k]<<endl;
                                            c++;
                                            }
                                    else if( i=="HEX"){cout <<"---------------";
                                             int num =std:: stoi(Value[k]);
                                                if(num < 10)cout <<"000"<<Value[k] <<"----"<<symbol[c]<<"----"<< i<<"---"<< Value[k]<<endl;
                                                else if(num > 10)cout <<"00"<<Value[k] <<"----"<<symbol[c]<<"----"<<i<<"---"<< Value[k]<<endl;
                                                else if(num> 100)cout <<"0"<<Value[k] <<"----"<<symbol[c]<<"----"<< i<<"---"<<Value[k]<<endl;
                                                c++;
                                             }
                                    else if (i== "ORG"){
                                            cout <<"00---------------" "0000"<<"----"<< i<< "---"<< Value[k]<<endl;
                                            }
                                    else if(i=="HALT"|| i=="OUTPUT" ||i=="INPUT"|| i=="CLEAR"){ 
                                            if (i=="HALT")cout<<"---------------" << "7000"<< "----"<< i << endl;
                                            if (i=="OUTPUT")cout<<"---------------" << "6000"<<"----"<< i <<endl;
                                            if (i=="INPUT")cout<<"---------------" << "5000"<< "----"<<i <<endl;
                                            if (i=="CLEAR")cout<<"---------------" << "A000"<<"----"<<i <<endl;
                                            }
                                     else {
                                    loc=search(Value[k]);
                                       it = OP.find(i);
                                        cout <<"---------------"<< it->second<<add[loc]<<"----"<< i<<"---"<< Value[k]<<endl;
                                        loc=0;
                                            }
                     ++i2;
                     k++;
                }
  
}

 

