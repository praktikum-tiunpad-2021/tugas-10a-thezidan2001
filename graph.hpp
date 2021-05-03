#pragma once

#include <functional>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <vector>
#include <queue>

namespace strukdat
{

  template <typename VertexType>
  class graph
  {
    /**
   * @brief Tipe data dari adjacency list. (BOLEH DIUBAH)
   *
   * @note
   * Misal:
   *
   * adj_list_type adj_list =
   *
   * | map key  |             list_type
   * | - - - -  | - - - - - - - - - - - - - - - - -
   * | vertex_1 | vertex_2, vertex_5, vertex_4, ...
   * | vertex_2 | vertex_1, vertex_3
   * |   ...    |           ...
   *
   * maka,
   *
   * adj_list[vertex_2]; // { vertex_1, vertex_3 }
   */
    using list_type = std::unordered_set<VertexType>;
    using adj_list_type = std::unordered_map<VertexType, list_type>;

  public:
    /**
   * @brief Default constructor.
   *
   * @constructor
   */
    graph() {}

    /**
   * @brief Menambahkan vertex baru pada graph
   *
   * @param val nilai dari vertex yang akan ditambahkan
   */
    void add_vertex(const VertexType &val)
    {
      // Contoh implementasi. (BOLEH DIUBAH)
      // inisialisasi _adj_list[val] dengan list kosong
      _adj_list.insert(std::make_pair(val, list_type()));
    }

    void remove_vertex(const VertexType &val)
    {
      _adj_list.erase(val);
    }

    /**
   * @brief Menambahkan edge baru dari 2 vertex
   *
   * @param val1 nilai vertex 1
   * @param val2 nilai vertex 2
   */
    void add_edge(const VertexType &val1, const VertexType val2)
    {
      _adj_list[val1].insert(val2);
      _adj_list[val2].insert(val1);
    }

    /**
   * @brief Menghapus vertex baru pada graph
   *
   * @param val nilai dari vertex yang akan dihapus
   */
    void remove_edge(const VertexType &val1, const VertexType &val2)
    {
      auto it = std::find(_adj_list[val1].begin(), _adj_list[val1].end(), val2);
      if (it != _adj_list[val1].end())
      {
        _adj_list[val1].erase(it);
      }
      it = std::find(_adj_list[val2].begin(), _adj_list[val2].end(), val1);
      if (it != _adj_list[val2].end())
      {
        _adj_list[val2].erase(it);
      }
    }

    /**
   * @brief Mengembalikan ordo dari graph.
   *
   * @note
   * Ordo graph adalah jumlah node pada graph
   *
   * @return jumlah node pada graph
   */
    size_t order() const
    {
      return _adj_list.size();
    }

    /**
   * @brief Cek apakah 2 vertex bertetangga satu sama lain.
   *
   * @param val1 nilai vertex 1
   * @param val2 nilai vertex 2
   *
   * @return vertex-vertex saling bertetangga
   */
    bool is_edge(const VertexType &val1, const VertexType &val2) const
    {
      if (_adj_list.find(val2) == _adj_list.end())
      {
        return false;
      }

      if (_adj_list.find(val1) == _adj_list.end())
      {
        return false;
      }

      if (_adj_list.at(val1).find(val2) == _adj_list.at(val1).end())
      {
        return false;
      }

      if (_adj_list.at(val2).find(val1) == _adj_list.at(val1).end())
      {
        return false;
      }

      return true;
    }

    /**
   * @brief Melakukan BFS traversal pada graph
   *
   * @param root vertex awal
   * @param func fungsi yang akan dieksekusi pada setiap vertex
   */
    void bfs(const VertexType &root, std::function<void(const VertexType &)> func) const
    {
      std::unordered_map<VertexType, bool> visited;

      for (auto &it : _adj_list)
      {
        visited.insert(std::make_pair(it.first, false));
      }

      std::queue<VertexType> antrian;
      visited[root] = true;
      antrian.push(root);

      while (!antrian.empty())
      {
        VertexType bantu = antrian.front();
        func(bantu);
        antrian.pop();
        for (auto it : _adj_list.at(bantu))
        {
          if (!visited[it])
          {
            visited[it] = true;
            antrian.push(it);
          }
        }
      }
    }

    /**
   * @brief Melakukan BFS traversal pada graph
   *
   * @param root vertex awal
   * @param func fungsi yang akan dieksekusi pada setiap vertex
   */
    void dfs(const VertexType &root, std::function<void(const VertexType &)> func) const
    {
      std::unordered_map<VertexType, bool> visited;

      for (auto &it : _adj_list)
      {
        visited.insert(std::make_pair(it.first, false));
      }

      std::stack<VertexType> antrian;
      antrian.push(root);

      while (!antrian.empty())
      {

        VertexType bantu = antrian.top();
        antrian.pop();

        if (!visited[bantu])
        {
          func(bantu);
          visited[bantu] = true;
        }

        for (auto &it : _adj_list.at(bantu))
        {
          if (!visited[it])
          {
            antrian.push(it);
          }
        }
      }
    }

  private:
    /**
   * @brief Adjacency list dari graph
   *
   * @private
   */
    adj_list_type _adj_list;
  };

} // namespace strukdat