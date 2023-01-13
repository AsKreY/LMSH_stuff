#include <algorithm>
#include <iostream>
#include <optional>
#include <vector>

template <bool is_oriented = false>
class Graph {
 public:
  explicit Graph() = default;

  explicit Graph(int num_of_vertices)
      : list_edges_(num_of_vertices),
        vertex_colors_(num_of_vertices, White),
        prev_(num_of_vertices) {}

  void AddEdge(int from, int to) {
    list_edges_[from].emplace_back(to);
    if constexpr (!is_oriented) {
      list_edges_[to].emplace_back(from);
    }
  }

  std::optional<std::vector<int>> FindLoopDFS(int vertex) {
    vertex_colors_[vertex] = Gray;
    for (const auto& i : list_edges_[vertex]) {
      if (vertex_colors_[i.to] == Gray) {
        std::vector<int> loop;
        loop.push_back(i.to);
        for (int j = vertex; j != i.to; j = prev_[j]) {
          loop.push_back(j);
        }
        std::reverse(loop.begin(), loop.end());
        return loop;
      }
      if (vertex_colors_[i.to] == White) {
        prev_[i.to] = vertex;
        std::optional<std::vector<int>> loop = FindLoopDFS(i.to);
        if (loop) {
          return loop;
        }
      }
    }
    vertex_colors_[vertex] = Black;
    return std::nullopt;
  }

 private:
  enum Colors { White, Gray, Black };
  struct Edge {
    int to = -1;
    Edge() = default;
    explicit Edge(int to) : to(to) {}
    ~Edge() = default;
  };
  std::vector<std::vector<Edge>> list_edges_;
  std::vector<Colors> vertex_colors_;
  std::vector<int> prev_;
};

std::optional<std::vector<int>> GetPossibleLoop(
    int num_of_vertices, const std::vector<std::pair<int, int>>& edges) {
  Graph<true> graph(num_of_vertices);
  for (const auto& [from, to] : edges) {
    graph.AddEdge(from, to);
  }
  std::optional<std::vector<int>> loop;
  for (int i = 0; i < num_of_vertices; ++i) {
    loop = graph.FindLoopDFS(i);
    if (loop) {
      return loop;
    }
  }
  return std::nullopt;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int num_of_vertices;
  int num_of_edges;
  std::cin >> num_of_vertices >> num_of_edges;
  std::vector<std::pair<int, int>> edges(num_of_edges);
  for (int i = 0; i < num_of_edges; ++i) {
    int from;
    int to;
    std::cin >> from >> to;
    edges[i] = {from - 1, to - 1};
  }
  std::optional<std::vector<int>> loop =
      GetPossibleLoop(num_of_vertices, edges);
  if (loop) {
    std::cout << "YES\n";
    for (const auto& j : *loop) {
      std::cout << j + 1 << ' ';
    }
  } else {
    std::cout << "NO";
  }
}
