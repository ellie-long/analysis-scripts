#include <cstdio>
#include <iostream>

using namespace std;

int main( int argc, char* argv[]) {
  char line[200];
  cout << "Enter a line please:" << endl;
  gets(line);
  cout << " line looks like :"<<line<<":" << endl;
  int pos=0;
  int cpos=0;
  char* ptr=line;
  int linelength=strlen(line);
  cout << "linelength = " << linelength << endl;
  double g;
  while ( (ptr)<=(line+linelength) ) {
    cout << "looking, starting at :" << ptr << ':'<<endl;
    sscanf(ptr,"%lg%n",&g,&pos);
    cout << "positions " << cpos << " + " << pos << "characters. start at \"" << *ptr << "\" through  \"" << *(ptr+pos) << "\" " << endl;
    cout << " read a " << g << endl;
    if (pos==0) break;
    ptr+=pos;
    cpos+=pos;
  }
  return 0;
}
