// how could I do this in a dumb manner?
// Discover diameter size;
// For all nodes, dfs() find how many paths == diameter O(N^2)
// then just divide the answer by 2 to remove repeats
//
//
// TODO fix count_deepest to actually perform a dfs and
// see how many paths in a subtree actually have the max depth;
// Right now I'm multiplying subtrees by subtrees and I'm not accounting
// for all paths inside a subtree that have that depth.

#include <algorithm>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

#define MAX_N 50001

int n;
vector<int> adj[MAX_N];
vector<int> centers;
bool mark[MAX_N];
bool is_center[MAX_N];
int dist[MAX_N];

int get_node_with_max_dist() {
  int node = 0;
  for (int i = 1; i <= n; i++) {
    if (dist[i] > dist[node]) {
      node = i;
    }
  }

  return node;
}

void calc_dist(int curr, int parent) {
  if (parent != 0)
    dist[curr] = 1 + dist[parent];
  for (auto node : adj[curr]) {
    if (node == parent)
      continue;
    calc_dist(node, curr);
  }
}

bool found_path = false;
void mark_diameter_path(int curr, int end, int parent = 0) {
  if (curr == end) {
    found_path = true;
    mark[curr] = true;
    return;
  }

  for (auto node : adj[curr]) {
    if (node == parent)
      continue;
    mark_diameter_path(node, end, curr);
    if (found_path)
      break;
  }

  if (found_path) {
    mark[curr] = true;
  }
}

void clear_dists() {
  for (int i = 1; i <= n; i++) {
    dist[i] = 0;
  }
}

void find_centers(int curr, int diam2, int parent, int path_size = 1) {
  if (!mark[curr])
    return;

  int nodes_in_diam = dist[diam2] + 1;
  if (nodes_in_diam % 2 == 0) {
    if (path_size == nodes_in_diam / 2 || path_size == nodes_in_diam / 2 + 1) {
      centers.push_back(curr);
    }
  } else {
    if (path_size == nodes_in_diam / 2 + 1) {
      centers.push_back(curr);
    }
  }

  for (auto node : adj[curr]) {
    if (node == parent)
      continue;
    find_centers(node, diam2, curr, path_size + 1);
  }
}

int depth[MAX_N];
void calc_depth(int curr, int prev = 0) {
  int ans = 1;
  for (auto node : adj[curr]) {
    if (node == prev || is_center[node])
      continue;
    calc_depth(node, curr);
    ans = max(ans, 1 + depth[node]);
  }

  depth[curr] = ans;
}

void clear_depth() {
  for (int i = 1; i <= n; i++) {
    depth[i] = 0;
  }
}

int count_deepest(int curr, int root, int parent = 0, int curr_depth = 1) {
  if (curr_depth == depth[root]) {
    return 1;
  }
  int count = 0;
  for (auto node : adj[curr]) {
    if (is_center[node] || node == parent) continue;
    count += count_deepest(node, root, curr, curr_depth + 1);
  }

  return count;
}

int count_second_deepest(int root) {
  int count = 0;
  int second_max_depth = 0;
  for (auto node : adj[root]) {
    if (depth[node] != depth[root] && depth[node] > second_max_depth) {
      second_max_depth = depth[node];
      count = 1;
    } else if (depth[node] != depth[root] && depth[node] == second_max_depth) {
      count++;
    }
  }

  return count;
}

int max_height_subtree[MAX_N];

void count_max_height(int curr, int parent, int subtree_root, int height = 2) {
 	if (height == depth[subtree_root] + 1) {
		max_height_subtree[subtree_root]++;
		return;
	}

	for (auto node : adj[curr]) {
		if (node == parent) continue;
		count_max_height(node, curr, subtree_root, height + 1);
	}
}

void calculate_deepest_subtree_paths(int root) {
  // for each subtree of root
  //   calculate_number_of_deepest_nodes(subtree) 
  for (auto node : adj[root]) {
    if (is_center[node]) continue;
    count_max_height(node, root, node);  
  }
}

int height[MAX_N];
void calc_height(int curr, int parent = 0) {
  for (auto node : adj[curr]) {
    if (node == parent) continue;
    height[node] = 1 + height[curr]; 
    calc_height(node, curr);
  }
}

int main() {
  cin >> n;
  for (int i = 0; i < n - 1; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  // first, I've got to find my centers
  // option A: take away all leaves until I'm left with either 1 or
  // 2 nodes
  //
  // option B: find dimater, calculate its size, if size is odd pick the
  // middle node, if size if even pick the middle 2 nodes
  //
  // Let's go with B.

  calc_dist(1, 0);
  int diam1 = get_node_with_max_dist();
  clear_dists();
  calc_dist(diam1, 0);
  int diam2 = get_node_with_max_dist();
  int diam_size = dist[diam2];
  mark_diameter_path(diam1, diam2);
  find_centers(diam1, diam2, 0);

  // cout << centers.size() << endl;

  cout << diam_size + 1 << endl;
  if (diam_size + 1 == 1) {
    cout << 1 << endl;
    return 0;
  }
  
  if (centers.size() == 1) {
    calc_depth(centers[0]);
    height[centers[0]] = 1;
    calc_height(centers[0]);
    int deepest_count = count_deepest(centers[0], centers[0]);
    if (deepest_count == 1) {
      int second_deepest_count = count_second_deepest(centers[0]);
      cout << deepest_count * second_deepest_count << endl;
    } else {
      calculate_deepest_subtree_paths(centers[0]);
	  int ans = 0;
	  int total_starts = 0;
	  for (auto node : adj[centers[0]]) {
		  ans += total_starts * max_height_subtree[node];
		  total_starts += max_height_subtree[node];
	  }
	  cout << ans << endl;;
    }

  } else if (centers.size() == 2) {
    for (auto c : centers) {
      is_center[c] = true;
    }

    calc_depth(centers[0]);
    int deepest_count_1 = count_deepest(centers[0], centers[0]);
    clear_depth();
    calc_depth(centers[1]);
    int deepest_count_2 = count_deepest(centers[1], centers[1]);

    cout << deepest_count_2 * deepest_count_1 << endl;
  }

  return 0;
}

