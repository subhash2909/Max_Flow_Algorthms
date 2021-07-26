//elementary math problem-(from)kattis

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

ll n, m, sink = 2, source = 1, n1, n2;
vector<pair<ll, ll> > adj[100001];
vll residual[100001];
vector<edge> arr;

unordered_map<ll, ll>map1;
vector<pair<ll, ll> >store;
ll total, distinct, cc;


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

	cin >> total;
	cc = 2 + total;

	for (ll i = 1; i <= total; i++)adj[source].pb({i + 2, 1});
	for (ll i = 3; i < total + 3; i++) {
		cin >> n1 >> n2;
		store.pb({n1, n2});
		if (map1.find(n1 + n2) == map1.end())distinct++, map1.insert({n1 + n2, ++cc}), adj[i].pb({cc, 1});
		else adj[i].pb({map1[n1 + n2], 1});
		if (map1.find(n1 - n2) == map1.end())distinct++, map1.insert({n1 - n2, ++cc}), adj[i].pb({cc, 1});
		else adj[i].pb({map1[n1 - n2], 1});
		if (map1.find(n1 * n2) == map1.end())distinct++, map1.insert({n1 * n2, ++cc}), adj[i].pb({cc, 1});
		else adj[i].pb({map1[n1 * n2], 1});
	}
	for (ll i = 1; i <= distinct; i++)adj[i + total + 2].pb({sink, 1});

	n = 2 + total + distinct;
	ll max_flow = dinics();
	if (max_flow != total) {cout << "impossible\n"; return 0;}

	/*for (ll i = 3; i < total + 3; i++) {
		cout << i << "--->";
		for (auto ele : adj[i]) {
			cout << ele.first << " ";
		} cout << "\n";
	} cout << "\n";

	for (ll i = 3; i < total + 3; i++) {
		cout << i << "--->";
		for (auto ele : residual[i]) {
			cout << arr[ele].to << " ";
		} cout << "\n";
	}*/

	for (ll node = 3; node < total + 3; node++) {
		//cout << residual[node].size() << "\n";
		for (auto ele : residual[node]) {
			if (arr[ele].to != source && arr[arr[ele].back_edge].res_flow == 1) {
				n1 = store[node - 3].first, n2 = store[node - 3].second;
				if (arr[ele].to == map1[n1 + n2]) {cout << n1 << " + " << n2 << " = " << n1 + n2 << "\n"; break;}
				else if (arr[ele].to == map1[n1 - n2]) {cout << n1 << " - " << n2 << " = " << n1 - n2 << "\n"; break;}
				else if (arr[ele].to == map1[n1 * n2]) {cout << n1 << " * " << n2 << " = " << n1*n2 << "\n"; break;}
			}
		}
	}
}