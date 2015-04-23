#include <iostream>
using namespace std;

int main ()
{
  int* m = nullptr;

  if (!m)
    cout << "null" << endl;
 
  if ( m == nullptr)
    cout << "longnull" << endl;

  int i = 2;
  m = &i;

  if (m)
    cout << "number" << endl;

  if (*m == i)
    cout << "longnumber " << endl;

  return 0;
}
