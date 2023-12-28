#include <algorithm>
#include <iostream> // cout, stoi
#include <random> // time, srand
#include <vector> // vector

using std::cout;
using std::endl;
using std::cerr;

void dbg_out() { cerr << endl; }
template <typename Head, typename... Tail> void dbg_out(Head H, Tail... T) {
  cerr << ' ' << H;
  dbg_out(T...);
}
#ifdef NEAL_DEBUG
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

struct apartment{
  int ID;
  int remaining;
  double quality;
};

struct student{
  double ID;
  double quality;
};

class Queue {
  public:
    Queue(int);
    ~Queue() { delete [] values; } // destructor

    bool IsEmpty(void);
    bool IsFull(void);
    bool Enqueue(student);
    bool Dequeue(student &);
    int size(void);
  private:
    int front, rear, counter, maxSize;
    student * values; // element array
};

Queue::Queue(int n){
  maxSize = n*4;
  values = new student[maxSize];
  front = 0;
  rear = -1;
  counter = 0;
}

bool Queue::IsEmpty(){
  if(counter) return false;
  else return true;
}

bool Queue::IsFull(){
  if(counter < maxSize) return false;
  else return true;
}

bool Queue::Enqueue(student x){
  if(IsFull()) return false;
  else {
    rear = (rear+1) % maxSize; 
    values[rear] = x;
    counter++;
  }
  return true;
}

bool Queue::Dequeue(student & x){
  if(IsEmpty()) return false;
  else {
    x = values[front];
    front = (front+1) % maxSize;
    counter--;
  }
  return true;
}

int Queue::size(){
  return counter;
}


int main(int argc, char** argv){
  std::ios::sync_with_stdio(false);
#ifndef NEAL_DEBUG
  std::cin.tie(nullptr);
#endif

  if(argc == 3){
    int N = std::stoi(argv[1]), k = std::stoi(argv[2]);
    
    std::vector<apartment> apartments;
    apartments.reserve(N);

    std::random_device rand;
    std::mt19937 gen(rand());
    std::uniform_real_distribution<> dist(0.0, 1.0);
    std::uniform_real_distribution<> years(1, 4);

    apartment apt;
    for(int i = 0; i < N; i++){
      apt.ID = i;
      apt.remaining = 0;
      apt.quality = dist(rand);
      apartments.push_back(apt);
    }

    student stu;
    Queue waitlist(k);
    for(int i = 0; i < k; i++){
      stu.ID = double(i+1);
      stu.quality = dist(rand);
      waitlist.Enqueue(stu);
    }
    
    int sim = 4;
    while(sim-- > 0){
      int cnt = waitlist.size(), rej = 0;
      for(auto& apt : apartments){
        while(cnt == waitlist.size()){
          student temp;
          if(!apt.remaining && waitlist.Dequeue(temp)){
            if(temp.quality > apt.quality)
              apt.remaining = years(rand);
            else
              temp.quality *= 0.9, waitlist.Enqueue(temp), ++rej;
            
            if(rej == cnt){
              cout<<"apartment: "<< apt.ID<<" rejected in year "<<sim<<endl;
              rej = 0;
              break;
            }
          } else {
            break;
          }
        }
        apt.remaining = (apt.remaining-1 >= 0) ? apt.remaining-- : apt.remaining;
      }

      for(int i = 0; i < k; i++){
        stu.ID = double(i+1);
        stu.quality = dist(rand);
        waitlist.Enqueue(stu);
      }
    }
  } else {
    cout<<"Usage: ./main N k\nN: the number of apartments, k: the number of students."<<endl;
    return -1;
  }

  return 0;
}