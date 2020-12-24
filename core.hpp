#pragma once
#include <bits/stdc++.h>
#define all(v) (v).begin(), (v).end()
#define revall(v) (v).rbegin(), (v).rend()
#define rep(i, a, b) for(int i = (a); i < (b); i++)
using namespace std;
using ll = long long;

template<typename T>
void chmax(T &x, const T &v) {
    if (x < v) x = v;
}

template<typename T>
void chmin(T &x, const T &v) {
    if (x > v) x = v;
}

template<typename T>
int len(const T &x) {
    return (int)(x.size());
}

// DEBUG
int recur_depth = 0;
#ifdef DEBUG
#define dbg(x) {++recur_depth; auto x_=x; --recur_depth; cerr<<string(recur_depth, '\t')<<"\e[91m"<<__func__<<":"<<__LINE__<<"\t"<<#x<<" = "<<x_<<"\e[39m"<<endl;}
#else
#define dbg(x)
#endif
template<typename Ostream, typename Cont>
typename enable_if<is_same<Ostream,ostream>::value, Ostream&>::type operator<<(Ostream& os,  const Cont& v){
	os<<"[";
	for(auto& x:v){os<<x<<", ";}
	return os<<"]";
}
template<typename Ostream, typename ...Ts>
Ostream& operator<<(Ostream& os,  const pair<Ts...>& p){
	return os<<"{"<<p.first<<", "<<p.second<<"}";
}
// END DEBUG

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