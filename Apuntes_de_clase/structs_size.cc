#include <stdio.h>
#include <stdint.h>
struct Enemy {
int id;
short int team;
float range_attack;
char name;
};

struct Enemy2 {
float range_attack;
int id;
short int team;
char name;
};

int main() {
Enemy e;
Enemy2 e2;
printf("Size : %d\n", sizeof(e));
printf("Size : %d\n", sizeof(e2));
}