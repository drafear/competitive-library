#include <bits/stdc++.h>

using namespace std;

class SA {
private:
	int n;
	string s;
	vector<bool> isL;
	vector<int> bsz, sbsz;

	void init() {
		isL = vector<bool>(n, false);
		for (int i = 0; i < (int)str.size()-1; ++i) {
			isL[i] = str[i] > str[i+1];
		}
		bsz = vector<int>(26, 0);
		for (int i = 0; i < str.size(); ++i) {
			res[(int)(str[i]-'a')]++;
		}
		vector<int> sbsz(27, 0);
		for (int i = 0; i < 26; ++i) {
			sbsz[i+1] = sbsz[i] + bsz[i];
		}
	}
	vector<int> is(const string& s, vector<int>& v) {
		int n = s.size();
		vector<int> next(n, -1);
		vector<bool> isL = cal_isL(s);
		vector<int> base(26, 0);
		vector<int> r(n, -1);
		for (int i = 1; i < v.size(); ++i) {
			if (v[i] < 0) continue;
			if (!isL[i-1]) continue;
			int cid = (int)(s[i-1]-'a');
			r[i-1] = sbsz[cid] + base[cid];
			++base[cid];
		}
		vector<int> rest = sbsz;
		for (int i = (int)r.size()-1; i >= 0; --i) {
			if (r[i] < 0) continue;
			if (isL[i+1]) continue;
			int cid = (int)(s[i+1]-'a');
			r[i+1] = sbsz[cid] + rest[cid]-1;
			--rest[cid];
		}
		return r;
	}
	vector<int> rev(const vector<int>& v) {
		vector<int> res(v.size(), -1);
		for (int i = 0; i < n; ++i) {
			if (r[i] < 0) continue;
			res[r[i]] = i;
		}
		return res;
	}
public:
	SA(const string& s) : s(s), n(s.size()) {
		init();
	}
	vector<int> sa() {
		vector<int> brest = bsz;
		vector<int> pos(n, -1);
		{
			vector<int> v(n, -1);
			vector<int> rest = sbsz;
			for (int i = 1; i < n; ++i) {
				if (isL[i-1] && !isL[i]) {
					int cid = (int)(str[i]-'a');
					int to = sbsz[cid] + rest[cid]-1;
					v[to] = i;
					rest[cid]--;
				}
			}
			vector<int> r = rev(is(s, v));
			rest = sbsz;
			for (int i = 0; i < r.size(); ++i) {

			}

			for (int i = 0; i < n; ++i) {
				if (v[i] < 0) continue;
				int cid = s[r[v[i]]]
				pos[rest[]] = i;
				rest[]
			}
		}
	}
};
vector<int> sa(const string& str) {

	{
		vector<int> v = is();
	}
}

int main() {
	string s; cin >> s;
	vector<int> v = sa(s);
	for (int i = 0; i < N; ++i) {
		cout << s.substr(v[i], (int)s.size()-v[i]) << endl;
	}
}
