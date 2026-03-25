#include <iostream>
#include <fstream>
using namespace std; 

class Display
{ 
 public:  
    Display(int **p, int rows, int cols, string fileName) {
      fstream inFile("./data/html/canvas.dat",ios::in);
      fstream outFile(fileName + ".html",ios::out);
      if (inFile.fail()) cout << "Cannot open file";    
      string line;

      outFile << "<html>" << endl;
      outFile << "<body>" << endl;
      outFile << "<canvas id='CANVAS_ID' width ='" << cols << "' height='" << rows << "'></canvas>" << endl;
      outFile << "<script>" << endl;
      outFile << "var com     =  4 ; //:4 components( RGBA )" << endl;
      outFile << "var wid     = " << cols << ";" << endl;
      outFile << "var hig     = " << rows << ";" << endl;

      getline(inFile,line);
      while (inFile) {
        outFile << line << endl;
        getline(inFile,line);
      }

      outFile << "var array = [";
      for (int row = 0; row < rows; row++)
          for (int col = 0; col < cols; col++)
            outFile << p[row][col] << ",";  

      outFile.seekp(-1,ios::cur);
      outFile << "];" << endl << endl;

      outFile << "	for( pi = 0; pi < array.length; pi++ ){" << endl;
      outFile << "		ci = pi * com;" << endl;
      outFile << "		u8a[ ci + 0 ] = array[pi]; //:Red" << endl;
      outFile << "		u8a[ ci + 1 ] = array[pi]; //:Green" << endl;
      outFile << "		u8a[ ci + 2 ] = array[pi]; //:Blue" << endl;
      outFile << "		u8a[ ci + 3 ] = 255; //:Alpha" << endl;
      outFile << "	}" << endl;
      outFile << "}" << endl;
      outFile << "</script>" << endl;
      outFile << "</body>" << endl;
      outFile << "</html>" << endl;

      inFile.close();
      outFile.close();  
    }
};
