#include <iostream>
#include <vector>

template <bool is_oriented = false>
class Tree {
 public:
  explicit Tree() = default;

  explicit Tree(size_t num_of_vertices)
      : list_edges_(num_of_vertices), num_of_vertices_(num_of_vertices) {}

  void AddEdge(int from, int to) {
    list_edges_[from].emplace_back(to);
    if constexpr (!is_oriented) {
      list_edges_[to].emplace_back(from);
    }
  }

  void CountTimeDFS(int vertex, int& timer, std::vector<bool>& visited) {
    tin_[vertex] = timer++;
    visited[vertex] = true;
    for (const auto& i : list_edges_[vertex]) {
      if (!visited[i.to]) {
        CountTimeDFS(i.to, timer, visited);
      }
    }
    tout_[vertex] = timer++;
  }

  void SetRoot(int root) { root_ = root; }

  void CheckTime() {
    if (tin_.empty()) {
      tin_.resize(num_of_vertices_);
      tout_.resize(num_of_vertices_);
      int timer = 0;
      auto used(std::vector<bool>(num_of_vertices_, false));
      CountTimeDFS(root_, timer, used);
    }
  }

  std::vector<int> GetTin() {
    CheckTime();
    return tin_;
  }
  std::vector<int> GetTout() {
    CheckTime();
    return tout_;
  }

  bool IsAncestor(int assumed_ancestor, int vertex) {
    CheckTime();
    return tin_[assumed_ancestor] < tin_[vertex] &&
           tout_[assumed_ancestor] > tout_[vertex];
  }

 private:
  struct Edge {
    int to = -1;
    Edge() = default;
    explicit Edge(int to) : to(to) {}
    ~Edge() = default;
  };
  std::vector<std::vector<Edge>> list_edges_;
  std::vector<int> tin_;
  std::vector<int> tout_;
  int root_ = 0;
  size_t num_of_vertices_ = 0;
};

std::vector<bool> GetRequestsAns(
    const std::vector<int>& vertices,
    const std::vector<std::pair<int, int>>& requests) {
  Tree<true> tree(vertices.size());
  for (size_t i = 0; i < vertices.size(); ++i) {
    if (vertices[i] == 0) {
      tree.SetRoot(static_cast<int>(i));
    } else {
      tree.AddEdge(vertices[i] - 1, static_cast<int>(i));
    }
  }
  std::vector<bool> requests_ans(requests.size());
  for (size_t i = 0; i < requests.size(); ++i) {
    requests_ans[i] =
        tree.IsAncestor(requests[i].first - 1, requests[i].second - 1);
  }
  return requests_ans;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int number_of_vertices;
  std::cin >> number_of_vertices;
  std::vector<int> vertices(number_of_vertices);
  for (int i = 0; i < number_of_vertices; ++i) {
    std::cin >> vertices[i];
  }
  int number_of_requests;
  std::cin >> number_of_requests;
  std::vector<std::pair<int, int>> requests(number_of_requests);
  for (int i = 0; i < number_of_requests; ++i) {
    std::cin >> requests[i].first >> requests[i].second;
  }

  for (const auto& i : GetRequestsAns(vertices, requests)) {
    std::cout << i << '\n';
  }
}
