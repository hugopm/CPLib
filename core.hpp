#pragma once
#include <bits/stdc++.h>
using namespace std;

// Utilities

using ll = long long;
const int m197 = 1000000007;
const int m998 = 998244353;

#define all(v) (v).begin(), (v).end()
#define rall(v) (v).rbegin(), (v).rend()
#define rep(i, a, b) for(int i = (a); i < (b); i++)

template<typename T>
void chmax(T &x, const T &v) {
	if (x < v) {
		x = v;
	}
}

template<typename T>
void chmin(T &x, const T &v) {
	if (x > v) {
		x = v;
	}
}

template<typename T>
int len(const T &x) {
	return (int)(x.size());
}

// Debug

void dbg_out() {
	cout << endl;
}

template<typename Head, typename... Tail>
void dbg_out(Head H, Tail... T) {
	cout << ' ' << H;
	dbg_out(T...);
}

#ifdef DEBUG
#define dbg(...) cout << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

template<typename Ostream, typename Cont>
typename enable_if<is_same<Ostream,ostream>::value, Ostream&>::type
operator<<(Ostream& os,  const Cont& v){
	os << "[";
	for (auto &x : v) {
		os << x << ", ";
	}
	return os << "]";
}

template<typename Ostream, typename ...Ts>
Ostream& operator<<(Ostream& os,  const pair<Ts...>& p) {
	return os << "{" << p.first << ", " << p.second << "}";
}

// Multi-dimensional vector

template<int D, typename T>
struct Vec : public vector<Vec<D - 1, T>> {
	static_assert(D >= 1, "Vector dimension must be greater than zero!");
	template<typename... Args>
		Vec(int n, Args... args) : vector<Vec<D - 1, T>>(n, Vec<D - 1, T>(args...)) {}
};

template<typename T>
struct Vec<1, T> : public vector<T> {
	Vec(int n, const T& val = T()) : vector<T>(n, val) {}
};

// Recursive lambda

template<class Fun>
class letrec_result {
	Fun fun_;
public:
	template<class T>
		explicit letrec_result(T &&fun): fun_(std::forward<T>(fun)) {}

	template<class ...Args>
		decltype(auto) operator()(Args &&...args) {
			return fun_(ref(*this), std::forward<Args>(args)...);
		}
};

template<class Fun>
decltype(auto) letrec(Fun &&fun) {
	return letrec_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}

// Input / Output

ll nxt() {
	ll x;
	cin >> x;
	return x;
}

template<typename T>
vector<T> read_vector(int n) {
	vector<T> v(n);
	for (T &x : v) {
		cin >> x;
	}
	return v;
}

vector<int> rv32(int n) { return read_vector<int>(n); }
vector<ll> rv64(int n) { return read_vector<ll>(n); }

template<typename T>
void print_vector(vector<T> data, bool print_size, bool new_line) {
	int n = data.size();
	if (print_size) {
		cout << n << '\n';
	}
	for (int i = 0; i < n; ++i) {
		cout << data[i] << " \n"[i+1 == n || new_line];
	}
}
