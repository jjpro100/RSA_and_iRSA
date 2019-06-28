#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string> 
#include <sstream>
#include <cstring>
#include <fstream>
#include <time.h>
#include <algorithm>
#include <vector>

using namespace std;
string modMult(string M, unsigned long long  E, unsigned long long  N);
void RSA(unsigned long long  N, unsigned long long  E, string M);

int main(void){

unsigned long long N, E, P, Q;


string M;

cin >> N >> E >> M;
//sqrtl(N);
RSA(N, E, M);

    return 0;
}

void RSA(unsigned long long  N, unsigned long long  E, string M){

    //unsigned long long po;
    string po;
    for(int k = 0; k<M.length(); k++){
        po = to_string((int)M[k]);
    /*
    for(long long int i = 0; i<E-1; i++){
        po*=M[k];
    }*/

    po = modMult(po, E, N);
    if(k != M.length()-1) cout << po << ",";
    else cout << po;
    }

    //cout << power(po, 1, N);
    //cout << power(po, 1, N);
    //out << power(po, 1, N);

}

  string sumy(string N1, string N2){
		string result;

    if(N1.length()>N2.length()) while(N1.length()!=N2.length()) N2="0"+N2;
    else while(N2.length()!=N1.length()) N1="0"+N1;
	
	int  digit, carry=0;
    for (int i = N1.length()-1; i >= 0; i--) {
      digit = (N1[i]-48)+(N2[i]-48)+carry;
      if(digit>=10){carry=1; digit -=10;}
      else carry=0;
      result = to_string(digit) + result;
    }
    if (carry!=0) result = to_string(carry) + result; 
    return result;
  }

  string longMult(string a, string b){
  	int carry=0, zeros2add=0, digit;
  	string  result;
  	string Small, Large, partial;
    if(a.length()>b.length()) {Large=a; Small=b;}
    else {Large=b; Small=a;}
     for (int i = Small.length()-1; i >= 0; i--){
     	for (int j = Large.length()-1; j >= 0; j--){
     	 digit = ((Small[i]-48)*(Large[j]-48))+carry;
     	 carry = digit/10;
     	 digit%=10;
     	 partial = to_string(digit)+partial;
     	 if(j==0  && carry) partial   =  to_string(carry) + partial;
		 }
		 for(int i =0;  i<zeros2add; i++) partial+="0";
        result = sumy(result, partial);
		 carry = 0;
		 partial.clear();
     	zeros2add++;
     }
		return result;

  }

string mod(string num, unsigned long long p) 
{ 
    unsigned long long r = 0; 
  
    for (unsigned long long i = 0; i < num.length(); i++) 
         r = ((int)num[i] - 48 + 10*r) %p; 
  
    return to_string(r); 
} 


string modMult(string M, unsigned long long  E, unsigned long long  N) 
{ 
      M = mod(M, N);
	//cout << "h2";
  	string r = "1";
    while (E > 0) 
    {   //when odd
        if (E % 2 == 1) r = mod(longMult(r, M),N);
        E = E/2; 
        M = mod(longMult(M, M), N);
    } 
    return r; 
} 
