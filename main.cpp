#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

struct Result{
    float moldIndex, averageInTemp, averageOutTemp, averageInHum, averageOutHum;
    string date;
}in, out, minTemp, maxTemp; //Objekt relataerade till struct Result
// Function prototypes
void swap(Result *xp, Result *yp);
void humidSorted(vector<Result>);
void tempSorted(vector<Result>);
void moldSorted(vector<Result>);
void printArr(int);
float searchIn(vector<Result>, string);
float searchOut(vector<Result>, string);
void moldIn(vector<Result>);
void moldOut(vector<Result>);
void autumnWinter();
//2st vector för alla beräknade värden ute/inne
struct vector<Result>inne; vector<Result>ute;

int main(int argc, const char * argv[]){
    string day, time, inOut, temperature, humid, currentDate ="", checkDate = "";
    int  i = 0, j = 0, k = 0;
    float sumOutTemp = 0.0,  sumInTemp = 0.0, sumInHumid = 0.0, sumOutHumid = 0.0;
    bool a = true;
    bool b = true;
    //Hämta textfil
    ifstream text("tempdata4.txt"); //Läs in värden från "tempdata4.txt"
    if(text.is_open()){ //Fortsätt läsa in värden tills det inte finns mer att läsa in och lagra tillfälligt i resp string-variabel.
        while (!text.eof()){
            getline(text, day, ' ');
            getline(text, time, ',');
            getline(text, inOut, ',');
            getline(text, temperature, ',');
            getline(text, humid);
            //Kontrollerar datum genom att jämföra strings. Om strings matchar true annars false
            if(day == checkDate){
                i++; //Räknare för totala antalet mätvärden.
                currentDate = day; //Sparar aktuell dag
                //Konverterar inläst string, sparar och adderar resp mätvärde
                if(inOut == "Inne"){
                    sumInTemp += stof(temperature);
                    sumInHumid += stoi(humid);
                    j++;    //Räknare för antal mätvärden inne
                }else{
                    sumOutTemp += stof(temperature);
                    sumOutHumid += stoi(humid);
                    k++;    //Räknare för antal mätvärden ute
                }
            }else{
                checkDate = day; //Checkdate byter värde. Används för att särskilja aktuell dag för mätvärden.
                if(i != 0){ //Gäller bara första inläsning. Ingen data lagras i det fall i == 0
                    /*  Beräknar medelvärde för inne/ute, läser in aktuell dag för mätvärden.   *
                     *  Lagar data i struct Result knutet till resp objekt in och ut            */
                    //Beräkning av medelvärden inne
                    in.averageInHum = sumInHumid/j;
                    in.averageInTemp = sumInTemp/j;
                    in.date = currentDate;
                    //Beräkning av medelvärden ute
                    out.averageOutTemp = sumOutTemp/k;
                    out.averageOutHum = sumOutHumid/k;
                    out.date = currentDate;
                    //Lagra alla värden för resp objekt i resp vector för inne/ute.
                    inne.push_back(in);
                    ute.push_back(out);
                    //Nollställer räknare och variabler för medelvärden. Ny beräkning för varje dag.
                    sumInTemp = 0; sumOutTemp = 0; sumInHumid = 0; sumOutHumid = 0;
                    j = 0; k = 0;
                }
            }
        }
    }
    // Printing welcome message and options
     do{
        cout << "\n\t\t****************************************************"
             << "\n\t\t*                                                  *"
             << "\n\t\t*                    Welcome to                    *"
             << "\n\t\t*         <<    GET * WEATHER * DATA    >>         *"
             << "\n\t\t*                                                  *"
             << "\n\t\t*               --------------------               *"
             << "\n\t\t*                    Main menu                     *"
             << "\n\t\t*               --------------------               *"
             << "\n\t\t*                     Options                      *"
             << "\n\t\t*                                                  *"
             << "\n\t\t*  1. Search for avarage temperature by date       *"
             << "\n\t\t*  2. Show avarage temperature data                *"
             << "\n\t\t*  3. Show avarage humidity data                   *"
             << "\n\t\t*  4. Show mold index (Risk of mold)               *"
             << "\n\t\t*  5. Show meterologic autmn/winter                *"
             << "\n\t\t*                                                  *"
             << "\n\t\t*\t\t\t> Enter 'q' to quit <                  *"
             << "\n\t\t*                                                  *"
             << "\n\t\t****************************************************"
             << "\n\t\t   << \t\t Please enter your choice \t\t >>"
             << "\n\n\t \t \t \t Enter here >> " << endl;
         
         int menyChoice = 0;
         string input;
         // in stream check // Only valid choice from menu accepted. 'q' to exit.
         do{
             cin >> input;
             if(input[0] == 113){
                 a = false;
                 break;
             }
             if(!(input[0] > 48 && input[0] < 54)){
                 cout << "\n\t\tInvalid input!\n\t\tPlease try again." << endl;
             }else{
                 b = false;
                 menyChoice = input[0] - 48;
                 break;
                }
         }while(true);
         
        // ****  Main meny switch e****//
        switch (menyChoice)
        {
        case 1:{
            cout << "\n\t\t----------------------------------------------------"
                 << "\n\t\tPlease enter date accordingly: xxxx-xx-xx\t\t       "
                 << "\n\t\t----------------------------------------------------" << endl;
            string input;
            cout << "\n\t \t \t Enter here >> "; cin >> input; // Input from user
            cout << endl;
        // ****  Sub meny ****//
            cout << "\n\t\t*****************************************************"
                 << "\n\t\t*                                                   *"
                 << "\n\t\t*     1. Show average indoor temperature            *"
                 << "\n\t\t*     2. Show average outdoor temperature           *"
                 << "\n\t\t*                                                   *"
                 << "\n\t\t*****************************************************"
                 << "\n\n\t\t   << \t\t Please enter your choice \t\t >>" << endl;
        int averageTempChoice;
        cout << "\t \t \t \t Enter here >> "; cin >> averageTempChoice;
        // Sub meny
          switch(averageTempChoice)
                {
             case 1:{
             float search = searchIn(inne, input);
                if (search == -1){
                    cout << "\t\t----------------------------------------------------" << endl
                         << "\t\t\t Insufficient data                                " << endl
                         << "\t\t----------------------------------------------------" << endl << endl;
                }else{
                    cout << "\t\t----------------------------------------------------" << endl;
                    printf( "\n\t\t AVERAGE INDOOR TEMPERATURE C\u00B0: %.1f", search);
                    cout << "\n\t\t----------------------------------------------------" << endl << endl;
                    }
                        break;
                    }
               case 2:{
               float search = searchOut(ute, input);
                if (search == -1){
                    cout << "\t\t----------------------------------------------------" << endl
                         << "\t\t\t Insufficient data                                " << endl
                         << "\t\t----------------------------------------------------" << endl << endl;
                }else{
                    cout << "\t\t----------------------------------------------------" << endl;
                    printf( "\t\t AVERAGE OUTDOOR TEMPERATURE C\u00B0: %.1f\n", search);
                    cout << "\t\t----------------------------------------------------" << endl << endl;
                    }
                        break;
                    }
                }
              break;
        }
        case 2:{
            tempSorted(inne);
            tempSorted(ute);
            int choice = 1;
            printArr(choice);
                    break;
                }
        case 3:{
            humidSorted(inne);
            humidSorted(ute);
            int choice = 2;
            printArr(choice);
            break;
            }
        case 4:
            {
            moldIn(inne);
            moldOut(ute);
            int choice = 3;
            printArr(choice);
            break;
            }
            case 5:{
            tempSorted(inne);
            tempSorted(ute);
            autumnWinter();
            break;
            }
        }
    }while(a);
    
    cout << "Exiting..." << endl;
}
// Print funtion. Use of int choice determent which data is printed.
// Use of printf also perform "banking round off" to nearest decimal number.
void printArr(int choice){
    //    string inTemp = subChoice;
    int i;
    if(choice == 1){
        for (i = 0; i != 5; i++){
            if(i == 0)
            cout << "\t\t5 HIGHEST AVERAGE TEMPERATURES C\u00B0:" << "\n\t\tIndoor \t\tOutdoor \t\tDate \n";
            
            printf("\t\t%4.1f \t\t%4.1f \t\t\t%s\n",
            inne[i].averageInTemp, ute[i].averageOutTemp, inne[i].date.c_str());
        }
        for (int j = (int)inne.size()-5; j < inne.size(); j++) {
            if(j== (int)inne.size()-5)
            cout << "\n\t\t5 LOWEST AVERAGE TEMPERATURES C\u00B0:" << "\n\t\tIndoor \t\tOutdoor \t\tDate \n";
            
            printf("\t\t%4.1f \t\t%4.1f \t\t\t%s\n",
            inne[j].averageInTemp, ute[j].averageOutTemp, ute[j].date.c_str());
        }
    }
    if(choice == 2){
        for (int i = (int)inne.size()-5; i < inne.size(); i++){
            if(i == (int)inne.size()-5)
            cout << "\t\t5 HIGHEST AVERAGE HUMIDITY %:" << "\n\t\tIndoor \t\tOutdoor \t\tDate \n";
            
            printf("\t\t%4.1f \t\t%4.1f \t\t\t%s\n",
            inne[i].averageInHum, ute[i].averageOutHum, inne[i].date.c_str());
        }
        for (int j = 1; j != 6; j++){
            if(j==1)
            cout << "\n\t\t5 LOWEST AVERAGE HUMIDITY %" << "\n\t\tIndoor \t\tOutdoor \t\tDate\n";
            
            printf("\t\t%4.1f \t\t%4.1f \t\t\t%s\n",
            inne[j].averageInHum, ute[j].averageOutHum, ute[j].date.c_str());
        }
    }
    if(choice == 3){
        int minMax = 0;
        for (int j = (int)inne.size()-5; j < inne.size(); j++) {
            if(j== (int)inne.size()-5)
                cout << "\t\t5 DATES WITH HIGHEST RISK OF MOLD (0 < 6):" << "\n\t\tIndoor \t\tOutdoor \t\tDate \n";
            
            printf("\t\t%4.1f \t\t%4.1f \t\t\t%s\n",
                   inne[j].moldIndex, ute[j].moldIndex, ute[j].date.c_str());
            }
        for (i = 0; i != ute.size(); i++){
            if(i == 0)
                cout << "\n\t\t5 DATES WITH LOWEST RISK OF MOLD:" << "\n\t\tIndoor \t\tOutdoor \t\tDate \n";
            
            if(inne[i].moldIndex > 0.1 || ute[i].moldIndex > 0.1){
                minMax++;
            printf("\t\t%4.1f \t\t%4.1f \t\t\t%s\n",
                   inne[i].moldIndex, ute[i].moldIndex, inne[i].date.c_str());
            }
                if(minMax == 5)
                    i = (int)ute.size()-1;
            }
        }
    }
// Linear search functions for average indoor/outdoor temp by date
float searchIn(vector<Result>, string s){
    for (int i = 0; i < inne.size(); i++){
        if(inne[i].date == s){
            return inne[i].averageInTemp;
        }
    }
    return -1;
}
float searchOut(vector<Result>, string s){
    for (int i = 0; i < ute.size(); i++){
        if(ute[i].date == s){
            return ute[i].averageOutTemp;
        }
    }
    return -1;
}
// Swap function
void swap(Result* xp, Result* yp){
    Result temp = *xp;
    *xp = *yp;
    *yp = temp;
}// Sorting functions // Bubblesort
void tempSorted(vector<Result>){
    for (int i = 0; i < inne.size(); i++){
        for (size_t j = inne.size(); j > 0 + i; j--)
            if (inne[j].averageInTemp > inne[j-1].averageInTemp) // Compare value at index [i] with index [i+1]
                swap(&inne[j], &inne[j-1]);                      // If if-statement == true then call swap function
    }
    for (int i = 0; i < ute.size(); i++){
        for (size_t j = ute.size(); j > 0 + i; j--)
            if(ute[j].averageOutTemp > ute[j-1].averageOutTemp) // Compare value
                swap(&ute[j], &ute[j-1]);                       // Call swap function
    }
}
void humidSorted(vector<Result>){
    for (int i = 0; i < inne.size(); i++){
        for (int j = 0; j < inne.size() - i; j++)
            if (inne[j].averageInHum > inne[j+1].averageInHum)   // Compare value
                swap(&inne[j], &inne[j+1]);                      // Call swap function
    }
    for (int i = 0; i < ute.size(); i++){
        for (int j = 0; j < ute.size() - i; j++)
            if(ute[j].averageOutHum > ute[j+1].averageOutHum)   // Compare value
                swap(&ute[j], &ute[j+1]);                       // Call swap function
    }
}
void moldSorted(vector<Result>){
    for (int i = 0; i < inne.size(); i++){
        for (int j = 0; j < inne.size() - i; j++)
            if (inne[j].moldIndex > inne[j+1].moldIndex)        // Compare value
                swap(&inne[j], &inne[j+1]);                     // Call swap function
    }
    for (int i = 0; i < ute.size(); i++){
        for (int j = 0; j < ute.size() - i; j++)
            if(ute[j].moldIndex > ute[j+1].moldIndex)           // Compare value
                swap(&ute[j], &ute[j+1]);                       // Call swap function
    }
}   // Functions for calculating mold index
void moldIn(vector<Result>){
    for (int i = 0; i < inne.size(); i++)
    {
        if(inne[i].averageInTemp > 15 && inne[i].averageInHum > 78){
            inne[i].moldIndex = (((inne[i].averageInHum-78) * (inne[i].averageInTemp/15))) * 0.22/16.5;
        }
        if(inne[i].averageInTemp > 0 && inne[i].averageInTemp < 15 && inne[i].averageInHum > 78){
            (inne[i].moldIndex = ((inne[i].averageInHum-78) / 0.22)/16.5);
        }else{
            inne[i].moldIndex = 0;}
    }
    moldSorted(inne);   //Function for sorting mold index (min > max)
}
void moldOut(vector<Result>){
    for (int i = 0; i < ute.size(); i++)
    {
        if(ute[i].averageOutTemp > 15 && ute[i].averageOutHum > 78){
            ute[i].moldIndex = (((ute[i].averageOutHum-78) * (ute[i].averageOutTemp/15)) * 0.22)/ 16.5;
        }
        if(ute[i].averageOutTemp > 0 &&ute[i].averageOutTemp < 15 && ute[i].averageOutHum > 78){
            ute[i].moldIndex = ((ute[i].averageOutHum-78) / 0.22) /16.5;
        }else{
            ute[i].moldIndex = 0;}
    }
    moldSorted(ute);    // Function  for sorting mold index (min > max)
}
void autumnWinter(){
    int i = 0; int autumnDay = 0; int winterDay = 0;
    cout << "\t\t Meterologic\n " << "\t\t Autumn \t\t Winter" << endl;
    
    for (i = 0; i < ute.size(); i++){
        if(ute[i].averageOutTemp > 0.0 && ute[i].averageOutTemp < 10)
             autumnDay = 1;
            if(ute[i].averageOutTemp <= ute[i-1].averageOutTemp && autumnDay > 0)
                autumnDay++;
        if(out.averageOutTemp < 0 )
             winterDay = 1;
            if(ute[i].averageOutTemp <= ute[i-1].averageOutTemp && winterDay > 0)
                winterDay++;
          if(autumnDay == 5)
            cout << "\t\t " << ute[i-4].date << endl;
          if(winterDay == 5)
            cout << "\t\t " << ute[i-4].date << endl;
        }
}
