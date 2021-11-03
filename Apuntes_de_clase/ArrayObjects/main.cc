#include <stdio.h>

#include "car.h"
#include "plane.h"
#include "motorbike.h"

const int kNumeroDeCoches = 10;

void ArrayDeCars(){
  Car coches[kNumeroDeCoches];

  for (int i = 0; i < kNumeroDeCoches; i++) {
    if (i % 6 == 0){
      coches[i].Innit(3,10);
    } else {
      coches[i].Innit(4,5.8f);

    }
  }
  for (int i = 0; i < kNumeroDeCoches; i++) {
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
  Car *coches[kNumeroDeCoches];
  
  for (int i = 0; i < kNumeroDeCoches; i++) {
    coches[i] = new Car();
  }

  for (int i = 0; i < kNumeroDeCoches; i++) {
    if (i % 6 == 0){
      coches[i]->Innit(3,10);
    } else {
      coches[i]->Innit(4,5.8f);
    }
  }

  for (int i = 0; i < kNumeroDeCoches; i++) {
    printf("Coche :%d Ruedas:%d Listros:%.3f\n",i, coches[i]->doors_, coches[i]->gas_);
  }

}

void EjemploHerencia(){
  Car *coche = new Car();
  MotorBike *moto = new MotorBike();
  Plane *avion = new Plane();

  delete coche;
  delete moto;
  delete avion;
}

int main(){

  // ArrayDeCars();
  // PunteroDeCars();
  // ArrayDeCarsConNew();
  EjemploHerencia();
  return 0;
}