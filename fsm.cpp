#include <iostream>
#include <unistd.h>
#include <thread>
#include <semaphore.h>

using namespace std;

class FinalStateMachine
{
private:
   bool fsm[3];

   void turnStatesBackOn(char c)
   {
      switch (c)
      {
      case 'A':
         sleep(2);
         turnOn(2);
      case 'B':
         sleep(2);
         turnOn(1);

      case 'C':
         sleep(2);
         turnOn(0);
      default:
         break;
      }
   }

public:
   FinalStateMachine()
   {
      fsm[0] = true;
      fsm[1] = true;
      fsm[2] = true;
   }
   void printStates()
   {
      cout << "A " << (fsm[2] ? "upaljeno" : "ugaseno") << endl;
      cout << "B " << (fsm[1] ? "upaljeno" : "ugaseno") << endl;
      cout << "C " << (fsm[0] ? "upaljeno" : "ugaseno") << endl;
      cout << "....." << endl;
   }

   void turnOff(int x)
   {
      fsm[x] = false;
   }

   void turnOn(int x)
   {
      fsm[x] = true;
   }

   void updateStates(char c)
   {
      switch (c)
      {
      case 'A':
         sleep(2);
         turnOff(2); //turnOff A
         //cout << "C je: "<< fsm[0] << endl;

      case 'B':
         sleep(2);
         turnOff(1); //turnOff B
         //cout << "C je: "<< fsm[0] << endl;

      case 'C':
         sleep(2);
         turnOff(0); //turnOff C
         //cout << "C je: "<< fsm[0] << endl;
         turnStatesBackOn(c);
         break;
      default:
         cout << "not a state " << endl;
         break;
      }
   }
};

FinalStateMachine fsm;
sem_t semaphore;

void print(void){
   sem_post(&semaphore);   
    while(1){
      sem_wait(&semaphore);
      fsm.printStates();
      sem_post(&semaphore);   
      sleep(5);
   }
}
void enter(void){
   char state;
   while(1){
      cin >> state;
      //sem_wait(&semaphore);
      cout << "Gasenje " << state << endl << "....." << endl;
      //sem_post(&semaphore);
      fsm.updateStates(state);
   }
}



int main()
{
   thread th1(print);
   thread th2(enter);
   sem_init(&semaphore, 0, 1);

   th1.join();
   th2.join();

   sem_destroy(&semaphore);

   return 0;
}