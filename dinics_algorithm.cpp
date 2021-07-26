//O(V^2*E)-for general graph

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


struct edge {

	ll from;
	ll to;
	ll res_flow;
	ll back_edge;
};

ll n, m, sink, source, u, v, c;
vector<pair<ll, ll> > adj[10001];
vll residual[10001];
vector<edge> arr;


bool bfs(vll& level) {

	queue<ll>q;
	q.push(source);
	level[source] = 1;


	while (!q.empty()) {

		ll node = q.front();
		q.pop();

		for (auto ele : residual[node]) {
			if (level[arr[ele].to] == 0 && arr[ele].res_flow > 0) {
				level[arr[ele].to] = level[node] + 1;
				q.push(arr[ele].to);
			}
		}
	}
	//for (ll i = 1; i <= n; i++)cout << level[i] << " "; cout << "\n";
	if (level[sink]) return true;
	return false;
}


ll dfs(ll node, ll pushed, vll& next, vll& level) {

	if (node == sink)return pushed;

	for (ll& id = next[node]; id < (ll)residual[node].size(); id++) {
		ll ele = residual[node][id];

		if (level[arr[ele].to] == level[node] + 1 && arr[ele].res_flow > 0) {
			ll path_cap = dfs(arr[ele].to, min(pushed, arr[ele].res_flow), next, level);
			if (path_cap > 0) {
				arr[ele].res_flow -= path_cap;
				arr[arr[ele].back_edge].res_flow += path_cap;
				return path_cap;
			}
		}
	}
	return 0;
}

ll dinics() {

	ll max_flow = 0, cc = 0;

	for (ll node = 1; node <= n; node++)
		for (auto ele : adj[node])
			residual[node].pb(cc), residual[ele.first].pb(cc + 1), arr.pb({node, ele.first, ele.second, cc + 1}), arr.pb({ele.first, node, 0, cc}), cc += 2;


	while (true) {
		vll level(n + 1); vll next(n + 1);
		if (!bfs(level))return max_flow;

		ll blocking_flow = 0;
		while (ll path_cap = dfs(source, LLONG_MAX, next, level))
			blocking_flow += path_cap;

		max_flow += blocking_flow;
	}
	return max_flow;
}


int main() {

	cin >> n >> m >> source >> sink;
	for (ll i = 1; i <= m; i++)cin >> u >> v >> c, adj[u].pb({v, c});

	cout << dinics() << "\n";

}