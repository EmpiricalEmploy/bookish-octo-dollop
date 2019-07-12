#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
//#include <ctype.h>
//#include <stdio.h>

using namespace std;



string run_length_encode(string input){
    if (input.length()<=1){
        return input;
    }
    int i = 0;
    string encoded = "";
    int curRun=1;
    while (i<input.length()){
        encoded.append(string(1,input[i]));
        while (input[i]==input[i+1]){
            curRun++;
            i++;
        }
        if (curRun>1){
			ostringstream str1;
			str1 << curRun;
			string str2 = str1.str();
            encoded.append(str2);
        }
        curRun=1;
        i++;
    }
    return encoded;
}

string run_length_decode(string input){
    if (input.length()<=1){
        return input;
    }
    string decoded = "";
    string curRunStr = "";
    int curRunInt = 1;
    int saved = -1;
    int i = 0;
    while (i<input.length()){
        decoded.append(string(1,input[i]));
        while (isdigit(input[i+1])){
            if (saved == -1){
                saved=i;
            }
            curRunStr.append(string(1,input[i+1]));
            i++;
        }
        if (curRunStr != ""){
            stringstream str1(curRunStr);
            str1 >> curRunInt;
            curRunStr="";
        }
        while (curRunInt>1){
            decoded.append(string(1,input[saved]));
            curRunInt--;
        }
        saved = -1;
        i++;
    }
    return decoded;

}


int main(){
    cout << run_length_encode("A") << "\tExpected: \"A\"" << '\n';
    cout << run_length_encode("AA") << "\tExpected: \"A2\"" << '\n';
    cout << run_length_encode("AAA") << "\tExpected: \"A3\"" << '\n' << '\n';

    cout << run_length_decode("A3") << "\tExpected: \"AAA\"" << '\n';
    cout << run_length_decode("A2") << "\tExpected: \"AA\"" << '\n';
    cout << run_length_decode("A") << "\tExpected: \"A\"" << '\n' << '\n';

    cout << run_length_encode("WWWABC") << "\tExpected: \"W3ABC\"" << '\n';
    cout << run_length_decode("W3ABC") << "\tExpected: \"WWWABC\"" << '\n';
    cout << run_length_encode("WWWWBBWWWWW") << "\tExpected: \"W4B2W5\"" << '\n';
    cout << run_length_decode("W4B2W5") << "\tExpected: \"WWWWBBWWWWW\"" << '\n';
}
