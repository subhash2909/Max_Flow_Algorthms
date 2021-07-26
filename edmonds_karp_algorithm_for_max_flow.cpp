//time complexity-->O(V.E^2)
//if multiple edges are present,simply merge them in residual graph
//self loops should be get ridden(since they don't contribute anything )
//sample test case-->
/*4 5
1 4
1 2 1000000000
1 3 1000000000
2 3 1
2 4 1000000000
3 4 1000000000
output--> 2000000000*/

#include<bits/stdc++.h>
using namespace std;
#define IOS ios_base::sync_with_stdio(false),cin.tie(NULL)
#define mod 1000000007
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<bool> vb;
typedef vector<vi >vvi;
typedef vector<ll> vll;
typedef vector<vll >vvll;
#define  pb push_back



//O(V+E)space (using adj list of edges)

struct edge {
	int from;
	int to;
	int res_flow;
	int back_edge;
};
vector<pair<int, int> >adj[10001];
vector<int>residual[10001];
vector<edge>arr;
int n, m, c, u, v, source, sink;
int max_flow = 0;


bool bfs(vi&parent) {

	vector<bool>vis(n + 1);
	queue<int>q;
	q.push(source);
	vis[source] = true;

	while (!q.empty()) {
		int temp = q.front();
		q.pop();
		for (auto ele : residual[temp])
			if (!vis[arr[ele].to] && arr[ele].res_flow > 0)
				vis[arr[ele].to] = true, q.push(arr[ele].to), parent[arr[ele].to] = ele;

		if (vis[sink])return true;
	}

	return false;
}



int edmonds_karp() {

	int cc = 0;
	for (int node = 1; node <= n; node++)
		for (auto ele : adj[node])
			residual[node].pb(cc), arr.pb({node, ele.first, ele.second, cc + 1}), residual[ele.first].pb(cc + 1), arr.pb({ele.first, node, 0, cc}), cc += 2;

	// for (auto ele : arr)cout << ele.from << " " << ele.to << " " << ele.res_flow << " " << ele.back_edge << "\n";
	// cout << "\n";
	// for (int i = 1; i <= n; i++) {
	// 	for (auto ele : residual[i])
	// 		cout << ele << " ";
	// 	cout << "\n";
	// }

	vi parent(n + 1);

	while (bfs(parent)) {
		int path_capacity = INT_MAX;

		for (int v2 = sink; v2 != source; v2 = arr[parent[v2]].from)
			path_capacity = min(path_capacity, arr[parent[v2]].res_flow);

		for (int v2 = sink; v2 != source; v2 = arr[parent[v2]].from) {
			arr[parent[v2]].res_flow -= path_capacity;
			arr[arr[parent[v2]].back_edge].res_flow += path_capacity;
		}
		max_flow += path_capacity;
	}

	return max_flow;
}

int main() {

	cin >> n >> m >> source >> sink;
	for (int i = 1; i <= m; i++) {
		cin >> u >> v >> c;
		if (u != v)adj[u].pb({v, c});
	}

	cout << edmonds_karp();

}








/*
//O(V*2) space (using adj matrix to capacities of residual graph)

vector<pair<int, int> > adj[10001];
int n, m, c, u, v, source, sink;

int maxflow = 0;
int cap[1001][1001];//vvi cap(n + 1, vi(n + 1, 0));
vi residual[10001];

bool bfs(vi&parent) {

	vector<bool>vis(n + 1);
	queue<int>q;
	q.push(source);
	vis[source] = true;

	while (!q.empty()) {
		int temp = q.front();
		q.pop();

		for (auto ele : residual[temp])
			if (!vis[ele] && cap[temp][ele] > 0)
				vis[ele] = true, q.push(ele), parent[ele] = temp;

		if (vis[sink])return true;
	}
	return false;
}


int edmonds_karp() {

	for (int node = 1; node <= n; node++)
		for (auto ele : adj[node])
			residual[node].pb(ele.first), residual[ele.first].pb(node), cap[node][ele.first] = ele.second;


	vi parent(n + 1);

	while (bfs(parent)) {
		int path_capacity = INT_MAX;

		for (int v2 = sink; v2 != source; v2 = parent[v2])
			path_capacity = min(path_capacity, cap[parent[v2]][v2]);

		for (int v2 = sink; v2 != source; v2 = parent[v2]) {
			cap[parent[v2]][v2] -= path_capacity;
			cap[v2][parent[v2]] += path_capacity;
		}
		maxflow += path_capacity;
	}

	return maxflow;
}




int main()
{
	cin >> n >> m >> source >> sink;

	for (int i = 1; i <= m; i++){
	   cin >> u >> v >> c;
	   if(u!=v)adj[u].pb({v, c});
	}

	cout << edmonds_karp();

}
*/