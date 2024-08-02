#include <iostream>
#include <deque>
#include <queue>

struct mid_queue {
  std::queue<int> q_pt1;
  std::deque<int> q_pt2;
  void correct() {
    while (q_pt1.size() < q_pt2.size()) {
      q_pt1.push(q_pt2.front());
      q_pt2.pop_front();
    }
  }
  void push_back(int a) {
    q_pt2.push_back(a);
    correct();
  }
  void push_mid(int a) {
    q_pt2.push_front(a);
    correct();
  }
  void pop() {
    correct();
    q_pt1.pop();
    correct();
  }
  int front() {
    correct();
    return q_pt1.front();
  }
};

int main() {
  int n;
  std::cin >> n;
  mid_queue a;
  for (int i = 0; i < n; ++i) {
    char b;
    std::cin >> b;
    if (b == '+') {
      int c;
      std::cin >> c;
      a.push_back(c);
    } else if (b == '*') {
      int c;
      std::cin >> c;
      a.push_mid(c);
    } else {
      std::cout << a.front() << "\n";
      a.pop();
    }
  }
}
 
