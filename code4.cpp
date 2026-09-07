#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define pll pair<ll, ll>

vector<ll> L, H, R;

void add(vector<pll> &c, ll x, ll h) {
    if (c.empty()) {
        if (h > 0) c.pb({x, h});
        return;
    }
    if (c.back().second == h) return;
    c.pb({x, h});
}

vector<pll> go(ll lo, ll hi) {
    vector<pll> c;
    if (lo >= hi) return c;
    if (hi - lo == 1) {
        c.pb({L[lo], H[lo]});
        c.pb({R[lo], 0});
        return c;
    }

    ll mid = lo + (hi - lo) / 2;
    vector<pll> a = go(lo, mid);
    vector<pll> b = go(mid, hi);

    ll i = 0, j = 0, n = a.size(), m = b.size();
    ll p = 0, q = 0;

    while (i < n && j < m) {
        ll x;
        if (a[i].first < b[j].first) {
            x = a[i].first;
            p = a[i].second;
            i++;
        } else if (b[j].first < a[i].first) {
            x = b[j].first;
            q = b[j].second;
            j++;
        } else {
            x = a[i].first;
            p = a[i].second;
            q = b[j].second;
            i++;
            j++;
        }
        add(c, x, max(p, q));
    }

    while (i < n) { add(c, a[i].first, a[i].second); i++; }
    while (j < m) { add(c, b[j].first, b[j].second); j++; }

    return c;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string t = "", ln;
    while (getline(cin, ln)) t += ln + " ";

    vector<ll> a;
    ll cur = 0, sg = 1;
    bool on = false;
    for (ll i = 0; i < (ll)t.size(); i++) {
        char c = t[i];
        if (c >= '0' && c <= '9') {
            cur = cur * 10 + (c - '0');
            on = true;
        } else {
            if (on) a.pb(sg * cur);
            cur = 0;
            on = false;
            sg = (c == '-') ? -1 : 1;
        }
    }
    if (on) a.pb(sg * cur);

    ll st = (a.size() % 3 == 1) ? 1 : 0;

    for (ll k = st; k + 2 < (ll)a.size(); k += 3) {
        ll l = a[k], h = a[k + 1], r = a[k + 2];
        if (l < r && h > 0) {
            L.pb(l);
            H.pb(h);
            R.pb(r);
        }
    }

    vector<pll> s = go(0, L.size());

    for (ll i = 0; i < (ll)s.size(); i++)
        cout << "(" << s[i].first << ", " << s[i].second << ")\n";

    return 0;
}
