
#include <stdio.h>
//#include <iostream>
//#include "strdef.h"
#include "strdef2.h"

using namespace std;

int main()
{
  MXTCMD p;
  short a;
  int b;
  float c;
  double d;
  
  printf("u_short=%ld, rtdata=%ld, POSE=%ld, JOINT=%ld, PULSE=%ld, rtdata=%ld\n",sizeof(p.Command), sizeof(p.dat), sizeof(p.dat.pos), sizeof(p.dat.jnt), sizeof(p.dat.pls), sizeof(p.dat));
printf("long=%ld, long8=%ld, short=%ld, int=%ld, float=%ld, double=%ld\n ",sizeof(p.dat.lng1[0]), sizeof(p.dat.lng1),sizeof(a), sizeof(b),sizeof(c), sizeof(d));
  printf("MXTCMD=%ld\n", sizeof(p));

  return 0;
}
