#include <stdio.h>
#include <cs50.h>
#include <string.h> //Needed for 'strlen'
#include <ctype.h>
#include <unistd.h>
#include <crypt.h>
#define _XOPEN_SOURCE

void match(string pwd, string salt, string hash);

int main(int argc, string argv[])
{
    // If the program is run without exactly 1 argument, exit program with error
    if(argc != 2)
    {
        printf("Usage: ./crack [hash]\n");
        return 1;
    }
    else
    {
        // User inputs a hash at the cmd line
        string hash = argv[1];
        
        char salt[3]; // Took me an hour to figure out that you can't modify string literals because they point to read-only memory
        salt[0] = hash[0]; // Generate the salt based on the first 2 characters of the input hash
        salt[1] = hash[1];
        char pwd[]= "AAAA"; // Starting password
        
        // AAmVRJSUZ5juU hash for pwd='rofl' with salt='AA'
        // AAgCfzsl6NSeo hash for pwd='AAAB' with salt='AA'
        // AA1c0HA0ncGaY hash for pwd='COBB' with salt='AA'
        // AAr5Df55N2Tto hash for pwd='ZAZZ' with salt='AA'
        // AAHiifSbPPOKE hash for pwd='zyzz' with salt='AA'
        // 50BDJdBnHsHWA hash for pwd='zyzz' with salt='50'
        
        // 4 nested FOR loops to run through all 4-letter alphabetic passwords
        for (int i=0;i<58;i++) // Count 58 since there are 6 non-alphabetic characters sandwiched between ASCII upper and lower case
        {
            pwd[1]='A'; // Reset the 2nd character for the next iteration
            for (int n=0;n<58;n++)
            {
                pwd[2]='A'; // etc
                for (int j=0;j<58;j++)
                {
                    pwd[3]='A';
                    for (int p=0;p<58;p++)
                    {
                        if (!((p>25 && p<32)||(j>25 && j<32)||(n>25 && n<32)||(i>25 && i<32))) // Ignore special characters between ASCII upper and lower case 
                        {
                            match(pwd,salt,hash); // Call to our function 'match' that compares the user's hash with our own generated hash
                        }
                        pwd[3]++;
                    }
                    pwd[2]++;    
                }
                pwd[1]++;    
            }
            pwd[0]++;    
        }
        return 0;
    }
    
}

// This function compares the input hash given at the cmd prompt with the hash generated by the nested FOR loops above. If there is a match it prints the password and exits the program.
void match(string pwd, string salt, string hash)
{
    if(strcmp(crypt(pwd,salt),hash)==0)
        {
            printf("%s\n",pwd);
            return;
        }
}