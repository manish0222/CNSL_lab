#include <iostream>
#include <cstdlib>
#include <string>
#include <algorithm>
using namespace std;
class hamming{
	public:
		string data; //it is the raw data received
		int m , r = 0; // n is the length of raw data and r is the number of redundant bits
		char * msg; // it will store the all bits (data + redundant). We made it dynamic because at compile time we dont know how much redundant bits will be there, we will initialize memory to it once we know the number of redundant bits.
		hamming(string data){
			this->data = data;
			//reversing the data received
			m = data.size();
			int power = 1;

			//finding the number of redundant bits and storing them in r
			while(power < (m + r + 1)){
				r++;
				power*=2;
			}
            cout<<"power is "<<power<<" redundant bits are "<<r<<endl;
			//Allocating memory to our dynamic msg array(Note we are using one based indexing).
			msg = new char[m+r+1];
			int curr = 0;

			//initializing the msg with data bits and for redundant bits, an initial value of n
			for(int i = 1 ; i <= m+r ; i++){
				if(i & (i-1)){
					msg[i] = data[curr++];
				}
				else msg[i] = 'n';
			}
            showmsg();
			//function call to set the redundant bits
			setRedundantBits();
		}
		//function to show the whole msg
		void showmsg(){
			cout << "the data packet to be sent is : ";
			for(int i = 1 ; i <=m+r ; i++){
				cout << msg[i] << " ";
			}
			cout << endl;
		}
        void showmsg1(string msg1){
			cout << "the data modified is ";
			for(int i = 1 ; i <=m+r ; i++){
				cout << msg1[i] << " ";
			}
			cout << endl;
		}
        int bin_to_int(string s){
            string num = s;
            int dec_value = 0;
        
            // Initializing base value to 1, i.e 2^0
            int base = 1;
        
            int len = m+r;
            for (int i = len - 1; i >= 0; i--) {
                if (num[i] == '1')
                    dec_value += base;
                base = base * 2;
            }
        
            return dec_value;
        }
		void setRedundantBits(){
			//for first redundant bit, check all those data bits at index where the first bit of index is set(1) similarly for second redundant bit, check all those data bits at index where the second bit of index is set(1), similarly for third redundant bit check all those data bits at index where the third bit of index is set to 1 and so on.
			int bit = 0;
			//outer loop runs for redundant bits (1 ,2 ,4 ,8 ....)
			for(int i = 1 ; i <= m+r ; i*=2){
				int count = 0;
				//inner loop runs for data bits
				for(int j = i+1 ; j<=m+r ; j++){
					// checking if the data bit corresponds to our redundant bit or not using bit manipulation
					if(j & (1 << bit)){
						if(msg[j] == '1') count++; // counting the number of ones in corresponding data bits
					}
				}
				//setting up redundant bits
				if(count & 1) msg[i] = '1';
				else msg[i] = '0';
				//increasing the bit position.
				bit++;
			}
			//showing up the message to be sent(data + redundant)
		}
		void receiver(){
			//this ans will store the redundant bits, if they were right then according to even parity they will store 0 else if some error was made in a bit it will store 1
			string ans = "";
			int bit = 0;
			//this loop corresponds to the logic used in set redundant bits function
			for(int i = 1 ; i <= m+r ; i*=2){
				int count = 0;
				for(int j = i+1 ; j<=m+r ; j++){
					if(j & (1 << bit)){
						if(msg[j] == '1') count++;
					}
				}
				//incrementing the ans variable with the parity of redundant bit
				// if it was right then add 0 else 1
				if(count & 1){
					if(msg[i] == '1') ans.push_back('0');
					else ans.push_back('1');
				}
				else{
					if(msg[i]=='0') ans.push_back('0');
					else ans.push_back('1');
				}
				bit++;
			}
            cout<<ans<<endl;
            char ch;
            cout<<"Do you want to change the bits Y/N -> ";cin>>ch;
			// if the ans had any occurrence of 1 then there is some fault
			if(ch=='y' || ch=='Y'){
                int k= (rand() % (m+r));
                cout<<"Pos Modified is "<<k<<endl;
                msg[k]-'0'==0 ? msg[k]='1':msg[k]='0';
                showmsg();
                //function call to set the redundant bits
                cout<<"\t\t Index is "<<k<<endl;
                msg[k]-'0'==0 ? msg[k]='1':msg[k]='0';
                showmsg();

                int val=bin_to_int(msg);
                cout<<"val is "<<val<<" "<<endl;
                // if(ans.find('1') != string::npos){
                //     int power = 1;
                //     int wrongbit = 0;
                //     //evaluating the binary expression of ans variable
                //     for(int i = 0 ; i < ans.size() ; i++){
                //         if(ans[i]=='1') wrongbit+=power;
                //         power*=2;
                //     }
                //     cout << "bit number " << (m+r-wrongbit) << " is wrong and having error " << endl;
			    // }
            }
			// if the ans dont have any occurrence of 1 then it is correct
			else{
				cout << "correct data packet received " << endl;
			}
		}
};
string ConvertToBinary(int n){
    string ans="";
    while(n){
        if(n%2==0)ans.push_back('0');
        else{
            ans.push_back('1');
        }
        n=n/2;
    }
    reverse(ans.begin(),ans.end());
    return ans;
}
int main(){
	string data;
    cout<<"Enter the data string ";cin>>data;
	for (int i = 0; i < data.length(); i++)
    {
        if(data[i]!=' '){
            cout<<"\t"<<i+1<<" "<<data[i]<<" "<<"Ascii "<<int(data[i])<<endl;
            string val=ConvertToBinary(data[i]);
            cout<<"Binary of "<<data[i]<<" is "<<val<<endl;
            hamming h(val);
            // manipulating any ith data bit to check if receiver is detecting a error in that bit. If you eliminate the following line then correct code will be sent to receiver following that no error is received
            
            //h.msg[i] == '0' ? h.msg[i] = '1' : h.msg[i] = '0';

            h.receiver();
            cout<<endl;
        }
    }
    
	return 0;
}

//time complexity = O(nlogn) where , n = databits + redundant bits
/*
Enter the data string Hello
        1 H Ascii 72
Binary of H is 1001000
power is 16 r is 4
the data packet to be sent is : n n 1 n 0 0 1 n 0 0 0 
the data packet to be sent is : 0 0 1 1 0 0 1 0 0 0 0 
Do you want to change the bits Y/N -> y
bit number 3 is wrong and having error 

        2 e Ascii 101
Binary of e is 1100101
power is 16 r is 4
the data packet to be sent is : n n 1 n 1 0 0 n 1 0 1 
the data packet to be sent is : 0 0 1 1 1 0 0 0 1 0 1 
Do you want to change the bits Y/N -> n
correct data packet received 

        3 l Ascii 108
Binary of l is 1101100
power is 16 r is 4
the data packet to be sent is : n n 1 n 1 0 1 n 1 0 0 
the data packet to be sent is : 0 0 1 0 1 0 1 1 1 0 0 
Do you want to change the bits Y/N -> n
correct data packet received 

        4 l Ascii 108
Binary of l is 1101100
power is 16 r is 4
the data packet to be sent is : n n 1 n 1 0 1 n 1 0 0 
the data packet to be sent is : 0 0 1 0 1 0 1 1 1 0 0 
Do you want to change the bits Y/N -> n
correct data packet received 

        5 o Ascii 111
Binary of o is 1101111
power is 16 r is 4
the data packet to be sent is : n n 1 n 1 0 1 n 1 1 1 
the data packet to be sent is : 1 0 1 0 1 0 1 1 1 1 1 
Do you want to change the bits Y/N -> n
correct data packet received 
*/
