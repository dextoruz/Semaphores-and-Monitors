#include <pthread.h>
#include <iostream>

using namespace std;

static pthread_mutex_t monitor = PTHREAD_MUTEX_INITIALIZER;
class account {
  private:
    int balance = 0;
  public:

    void *deposit(int amount) {
      pthread_mutex_lock(&monitor);
      balance = balance + amount;
      cout<<"deposited : "<<amount<<endl;
      printBalance();
      pthread_mutex_unlock(&monitor);
    }

    void *withdraw(int amount) {
      pthread_mutex_lock(&monitor);
      if(balance <= 0 ){
        cout<<"empty account\n";
      }
      else{
        balance = balance - amount;
        cout<<"withdrawed : "<<amount<<endl;
      }
      printBalance();
      pthread_mutex_unlock(&monitor);
    }
    void printBalance(){
      cout<<"Current balance: "<<balance<<endl;
      return;
    }

};

struct arguments{
  account *person;
  int amount;
};

class temp_account {
public:
  static void *deposit_helper(void *arg){
     return ((arguments *)arg)->person->deposit(((arguments *)arg)->amount);
  }

  static void *withdraw_helper(void *arg){
     return ((arguments *)arg)->person->withdraw(((arguments *)arg)->amount);
  }

};




int main(int argc, char const *argv[]) {

  arguments argument1,argument2;
  pthread_t t,t1,t2,t3;
  account c;
  temp_account temp;

  int x=10000;
  int y = 500;

  argument1.person = &c;
  argument1.amount = x;

  argument2.person = &c;
  argument2.amount = y;

  pthread_create(&t, NULL, &temp.deposit_helper, &argument1);
  pthread_create(&t1, NULL, &temp.withdraw_helper, &argument2);
  pthread_create(&t2, NULL, &temp.deposit_helper, &argument1);
  pthread_create(&t3, NULL, &temp.deposit_helper, &argument2);

  pthread_join(t,NULL);
  pthread_join(t1,NULL);
  pthread_join(t2,NULL);
  pthread_join(t3,NULL);

  cout<<endl<<endl;
  c = *(argument1.person);
  c.printBalance();
  c = *(argument2.person);
  c.printBalance();

  return 0;
}
