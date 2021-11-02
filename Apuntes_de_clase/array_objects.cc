#include <stdio.h>

class Car {
public:
  int doors_;
  float gas_;
  Car();
  ~Car();
  void Innit(int doors, float gas);
};

void Car::Innit(int doors, float gas){
  doors_ = doors;
  gas_ = gas;
}
Car::Car() {

}

Car::~Car(){
  printf("Borrado Car\n");
}

const int numero_de_coches = 10;
void ArrayDeCars(){
  Car coches[numero_de_coches];

  for (int i = 0; i < numero_de_coches; i++) {
    if (i % 6 == 0){
      coches[i].Innit(3,10);
    } else {
      coches[i].Innit(4,5.8f);

    }
  }
  for (int i = 0; i < numero_de_coches; i++) {
    printf("Coche :%d Ruedas:%d Listros:%.3f\n",i, coches[i].doors_, coches[i].gas_);
  }
}

void PunteroDeCars(){
  Car *coche1 = new Car();
  Car *coche2 = new Car();
  Car *coche3 = new Car();

  coche1->Innit(2,6.4f);
  coche2->Innit(5,41.4f);
  coche3->Innit(3,23.5f);

  printf("Coche :%d Ruedas:%d Listros:%.3f\n",1, coche1->doors_, coche1->gas_);
  printf("Coche :%d Ruedas:%d Listros:%.3f\n",2, coche2->doors_, coche2->gas_);
  printf("Coche :%d Ruedas:%d Listros:%.3f\n",3, coche3->doors_, coche3->gas_);

  delete coche1;
  delete coche2;
  delete coche3;
}

void ArrayDeCarsConNew(){
  Car *coches = new Car[numero_de_coches];
  
  for (int i = 0; i < numero_de_coches; i++) {
    if (i % 6 == 0){
      coches[i].Innit(3,10);
    } else {
      coches[i].Innit(4,5.8f);

    }
  }
}

int main(){

  // ArrayDeCars();
  PunteroDeCars();

  return 0;
}