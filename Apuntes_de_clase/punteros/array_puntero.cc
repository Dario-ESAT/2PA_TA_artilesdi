#include <stdlib.h>
#include <stdio.h>

struct Obj {
  int a;
  char c;
};

void f1(Obj o){
  o.a = 42;
  o.c = 'C';
}

void f2(Obj *o){
  o->a = 42;
  o->c = 'C';
}

int main(){
  Obj o;
  f1(o);
  f2(&o);
  return 0;
}
// int main(){
//   int array[5] = {1,2,3,4,5};
//   int *puntero;
//   puntero = array;
//   for (int i = 0; i < 10; i++) {
//     printf("%p-> %d\n",puntero,*puntero);
//     ++puntero;
//   }
  
//   return 0;
// }