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
unsigned long long modInverse(unsigned long long a, unsigned long long m);
void breakRSA(unsigned long long  N, unsigned long long  E, string C);

int main(void){

    unsigned long long N, E, P, Q;
    string C;

    cin >> N >> E >> C;
    //cout << N << endl << E;
    //cout << C;
    breakRSA(N, E, C);
    return 0;
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
    {   //When odd
        if (E % 2 == 1) r = mod(longMult(r, M),N); 
        //Even powers
        E = E/2; 
        M = mod(longMult(M, M), N);
    } 
    return r; 
} 


unsigned long long phi(unsigned long long n) 
{ 
    unsigned long long fy = n; 
    //We just need to calculate until the square root
    for (unsigned long long i=2;i*i<=n;i++) { 
          
        if (n%i == 0) {  
            while (n % i == 0) n /= i; //Looping for finding primes
            fy *= (1 - (1/(long double)i)); 
        } 
    } 
    //The only number that can be included that is greater than its square root is himself
    if (n > 1) fy *= (1 - (1 / (long double)n)); 

    return (unsigned long long)fy; 
} 




void breakRSA(unsigned long long  N, unsigned long long  E, string C){

    unsigned long long d = modInverse(E, phi(N)); 
    //cout << endl << "phi" <<phi(N) <<endl;
    //cout << "\nd=" << d;
   // d = E;
    string po = "";

    for(int k = 0; k<C.length(); k++){
        //po = to_string((int)M[k]);
        while(C[k]!=',' && k!=C.length()){ po+=C[k]; k++;}
        //cout<<"\n" << po << endl;
        po = modMult(po, d, N);
        //cout <<  "po=" << po;
        cout << (char)stoi(po);
        po = "";
        }
}

unsigned long long modInverse(unsigned long long a, unsigned long long b) 
{
    unsigned long long b_original = b, temp, quotient;
	long long c0 = 1, c1 = 0;  //a(c0) + b(c1) = 1


	while (a > 1) {
		quotient = a / b;

		temp = b; 
        b = a%b;
        a = temp;

		temp = c1; 
        c1 = c0 - quotient*c1; 
        c0 = temp;
	}
	if (c0 < 0) c0 = b_original + c0;
	return c0;
}

