#include <stdio.h>

void MyWeirdFunction(void * data, int typ){
  int* data_int = nullptr;
  float* data_float = nullptr;
  char* data_char = nullptr;
  switch (typ) {
  case 0:
    data_int = (int*) data;
    *data_int = *data_int + 1;
    break;

  case 1:
    data_float = (float*) data;
    *data_float = *data_float - 0.01f;
    break;

  case 2:
    data_char = (char*) data;
    printf("%s",data_char);
    break;
  default:
    break;
  }
}


int Add       (int x, int y){ return x + y;}
int Substract (int x, int y){ return x - y;}
int Multiply  (int x, int y){ return x * y;}

int Operation (int x, int y, int(*functocall)(int, int)){
  return functocall(x,y);
}

int main(){
  int m,n,o;
  m = Operation(7,5, &Add);
  n = Operation(20, m , &Substract);
  o = Operation(n, m, &Multiply);

  printf("%d, %d, %d", m,n,o);
  
  return 0;
}
/* 
int main(){

  int a = 42;
  float f = 3.14f;
  char s[5] = "BUBU";
  MyWeirdFunction(&a,0);
  MyWeirdFunction(&f,1);
  MyWeirdFunction(s,2);
  printf("\n%d", a);
  printf("\n%f", f);
  return 0;
} */