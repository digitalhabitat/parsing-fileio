// Parsing and File IO (Blackbelt version)
// Michael T. Miller
// This program uses fstream to open/create files
// sstream helps us access data from a string

// This version will help user create input.txt file if it is missing
// the program won't allow user input data to input.txt that could cause a format error
// and also notify user if input.txt file has format errors

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main(){
 
  // read a file stuff
  ifstream inFile;
  string currentLine;
  string subLine;
  stringstream current;
  stringstream converter;

  int num, sum, i, j;
  string word;
  char ans;

  // write a new file stuff
  // create instance ofstream(Output stream class) called outFile
  ofstream outFile;

  // call .open() method with a file name string as argument  
  inFile.open("input.txt");
  if (!inFile.is_open()){
    cout << "Could not open input.txt file" << endl;
    cout << "Do you want to create a input.txt file? [y/n]" << endl;
    cin >> ans;
    //clear buffer
    cin.ignore();
    // if user wants to write missing input.txt file
    if ( ans == 'y'){
      ofstream newFile;
      string userinput;
      newFile.open("input.txt");
      for(i = 0; i < 5; i++){
        for(j = 0; j < 3; j++){

          // verify integer input
          while(true){
            cout << "enter an interger: ";
            getline(cin, userinput);
            converter.clear();
            converter.str(userinput);
            // string stream pass int character 
            if (converter >> num){
              newFile << num;
              if (j < 2){
                // separte int with a comma
                newFile << ",";
              }
              // must break to exit while loop
              break;
            }
            cout << "Please try again" << endl;
          } // end while loop
        } // for j loop
        newFile << endl;
        
        // get a string for next line
        cout << "enter a single word: ";
        getline(cin, userinput);
        newFile << userinput << endl;
      }

      // Close ofstream input.txt
      newFile.close();
      cout << "Formated input.txt created" << endl;
      // Open instream input.txt for writing to output.txt
      inFile.open("input.txt");
    }
  }// end input.txt file open failure loop 

  // verify file correctly formated
  else{
    bool isformated = true;

    while(getline(inFile,currentLine) && isformated ){
      current.clear();
      current.str(currentLine);
      for(i = 0; i < 3; i++){
        // parse currentLine for comma separated integers
        getline(current,subLine,',');
        converter.clear();
        converter.str(subLine);
        // check if type is valid
        if (!(converter >> num)){
          // if string passed by converter is not int
          // stop verify loop and end program
          cout << "format error in input.txt detected" << endl;
          cout << subLine << " is not integer type" << endl;
          isformated = false;
          break;
        }  
      }
      // anything can be a string just call this and ignore
      // while loop should call again to verify next line of integers
      getline(inFile,currentLine);
    }
    // close files if not verified
    if(!isformated){
      inFile.close();
    }
    else{
      cout << "input.txt file sucessfully opened" << endl;
      cout << "data format verified" << endl;
    }
  } //end else/verify loop

  // If input.txt is open and properly formated
  if(inFile.is_open()){
  inFile.close();

  // Reopen file to start stream at first line
  inFile.open("input.txt");
  outFile.open("output.txt");

  // loads the string(currentLine) till delimiter character (\n) is foundi
  while(getline(inFile, currentLine)){ 
    // expecting to sum comma separated int data from currentLine
    sum = 0; 

    // set No errors to (current)
    // Load contents of string(currentLine) into stringstream(current)
    current.clear();
    current.str(currentLine);

    // extract characters from stringstream(current)
    // then store in string(subLine)
    // till delimiter ',' is found
    while(getline(current,subLine, ',')){      
      
      // set No errors to (converter);
      // pass subLine to converter then pass to num and perfrom math
      converter.clear();
      converter.str(subLine);
      converter >> num;
      sum += num;
    }

    // fetch second line which is assumed to always be a single (string)
    // loading contents into string(currentLine) again
    getline(inFile, currentLine);
  
    // iterate sum prints of string(currentLine) with a comma after each
    // this is passed to outFile object 
    for (i = 0; i < sum; i++){
      outFile << currentLine;
      if (i < sum - 1){
        outFile << ",";
      }
    } // end for
    outFile << endl;    

  } // end while
 
  inFile.close();
  outFile.close();
  cout << "writting data to output.txt" << endl;
  // Make sure to call the .close() method when done reading/writting 
  }
  else{
    cout << "Program ending" << endl;
  }
  return 0;

} // end main
 
