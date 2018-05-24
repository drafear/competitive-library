using ld = double;
using Point = complex<ld>;
namespace std {
    bool operator<(const Point &lhs, const Point &rhs) {
        if (lhs.real() < rhs.real() - eps) return true;
        if (lhs.real() > rhs.real() + eps) return false;
        return lhs.imag() < rhs.imag();
    }
}

Point input_point() {
    ld x, y;
    cin >> x >> y;
    return Point(x, y);
}

bool eq(ld a, ld b) {
    return (abs(a - b) < eps);
}

ld dot(Point a, Point b) {
    return real(conj(a) * b);
}

ld cross(Point a, Point b) {
    return imag(conj(a) * b);
}

class Line {
public:
    Point a, b;
    Line () : a(Point(0, 0)), b(Point(0, 0)) {}
    Line (Point a, Point b) : a(a), b(b) {}
};

class Circle {
public:
    Point p;
    ld r;
    Circle () : p(Point(0, 0)), r(0) {}
    Circle (Point p, ld r) : p(p), r(r) {}
};

int ccw (Point a, Point b, Point c) {
    b -= a; c -= a;
    if (cross(b, c) > eps) return 1;
    if (cross(b, c) < -eps) return -1;
    if (dot(b, c) < 0) return 2;
    if (norm(b) < norm(c)) return -2;
    return 0;
}

bool isis_ll (Line l, Line m) {
    return !eq(cross(l.b - l.a, m.b - m.a), 0);
}

bool isis_ls (Line l, Line s) {
    return isis_ll(l, s) &&
        (cross(l.b - l.a, s.a - l.a) * cross(l.b - l.a, s.b - l.a) < eps);
}

bool isis_ss(Line s, Line t) {
    return ccw(s.a, s.b, t.a) * ccw(s.a, s.b, t.b) <= 0 &&
        ccw(t.a, t.b, s.a) * ccw(t.a, t.b, s.b) <= 0;
}

bool isis_lp (Line l, Point p) {
    return (abs(cross(l.b - p, l.a - p)) < eps);
}

bool isis_sp (Line s, Point p) {
    return (abs(s.a - p) + abs(s.b - p) - abs(s.b - s.a) < eps);
}

Point proj (Line l, Point p) {
    ld t = dot(p - l.a, l.a - l.b) / norm(l.a - l.b);
    return l.a + t * (l.a - l.b);
}

Point is_ll (Line s, Line t) {
    Point sv = s.b - s.a, tv = t.b - t.a;
    assert(cross(sv, tv) != 0);
    return s.a + sv * cross(tv, t.a - s.a) / cross(tv, sv);
}

ld dist_lp (Line l, Point p) {
    return abs(p - proj(l, p));
}

ld dist_ll (Line l, Line m) {
    return isis_ll(l, m) ? 0 : dist_lp(l, m.a);
}

ld dist_ls (Line l, Line s) {
    return isis_ls(l, s) ? 0 : min(dist_lp(l, s.a), dist_lp(l, s.b));
}

ld dist_sp (Line s, Point p) {
    Point r = proj(s, p);
    return isis_sp(s, r) ? abs(r - p) : min(abs(s.a - p), abs(s.b - p));
}

ld dist_ss (Line s, Line t) {
    if (isis_ss(s, t)) return 0;
    return min({dist_sp(s, t.a), dist_sp(s, t.b), dist_sp(t, s.a), dist_sp(t, s.b)});
}

vector<Point> is_cc (Circle c1, Circle c2){
    vector<Point> res;
    ld d = abs(c1.p - c2.p);
    ld rc = (d * d + c1.r * c1.r - c2.r * c2.r) / (2 * d);
    ld dfr = c1.r * c1.r - rc * rc;
    if (abs(dfr) < eps) dfr = 0.0;
    else if (dfr < 0.0) return res;
    ld rs = sqrt(dfr);
    Point diff = (c2.p - c1.p) / d;
    res.push_back(c1.p + diff * Point(rc, rs));
    if (dfr != 0.0) res.push_back(c1.p + diff * Point(rc, -rs));
    return res;
}

vector<Point> is_lc (Circle c, Line l){
    vector<Point> res;
    ld d = dist_lp(l, c.p);
    if (d < c.r + eps){
        ld len = (d > c.r) ? 0.0 : sqrt(c.r * c.r - d * d);
        Point nor = (l.a - l.b) / abs(l.a - l.b);
        res.push_back(proj(l, c.p) + len * nor);
        res.push_back(proj(l, c.p) - len * nor);
    }
    return res;
}

vector<Point> is_sc(Circle c, Line l){
    vector<Point> v = is_lc(c, l), res;
    for (Point p : v)
        if (isis_sp(l, p)) res.push_back(p);
    return res;
}

vector<Line> tangent_cp(Circle c, Point p) {
    vector<Line> ret;
    Point v = c.p - p;
    ld d = abs(v);
    ld l = sqrt(norm(v) - c.r * c.r);
    if (isnan((long double)l)) { return ret; }
    Point v1 = v * Point(l / d,	c.r / d);
    Point v2 = v * Point(l / d, -c.r / d);
    ret.push_back(Line(p, p + v1));
    if (l < eps) return ret;
    ret.push_back(Line(p, p + v2));
    return ret;
}

vector<Line> tangent_cc(Circle c1, Circle c2) {
    vector<Line> ret;
    if (abs(c1.p - c2.p) - (c1.r + c2.r) > -eps) {
        Point center = (c1.p * c2.r + c2.p * c1.r) / (c1.r + c2.r);
        ret = tangent_cp(c1, center);
    }
    if (abs(c1.r - c2.r) > eps) {
        Point out = (-c1.p * c2.r + c2.p * c1.r) / (c1.r - c2.r);
        vector<Line> nret = tangent_cp(c1, out);
        ret.insert(ret.end(), all(nret));
    }
    else {
        Point v = c2.p - c1.p;
        v /= abs(v);
        Point q1 = c1.p + v * Point(0,	1) * c1.r;
        Point q2 = c1.p + v * Point(0, -1) * c1.r;
        ret.push_back(Line(q1, q1 + v));
        ret.push_back(Line(q2, q2 + v));
    }
    return ret;
}

typedef vector<Point> Polygon;

ld area(const Polygon &p) {
    ld res = 0;
    int n = p.size();
    REP(j,n) res += cross(p[j], p[(j+1)%n]);
    return res / 2;
}

bool is_counter_clockwise (const Polygon &poly) {
    ld angle = 0;
    int n = poly.size();
    REP(i,n) {
        Point a = poly[i], b = poly[(i+1)%n], c = poly[(i+2)%n];
        angle += arg((c - b) / (b - a));
    }
    return angle > eps;
}

int is_in_polygon (const Polygon &poly, Point p) {
    ld angle = 0;
    int n = poly.size();
    REP(i,n) {
        Point a = poly[i], b = poly[(i+1)%n];
        if (isis_sp(Line(a, b), p)) return 1;
        angle += arg((b - p) / (a - p));
    }
    return eq(angle, 0) ? 0 : 2;
}

Polygon convex_hull(vector<Point> ps) {
    int n = ps.size();
    int k = 0;
    sort(ps.begin(), ps.end());
    Polygon ch(2 * n);
    for (int i = 0; i < n; ch[k++] = ps[i++])
        while (k >= 2 && ccw(ch[k - 2], ch[k - 1], ps[i]) <= 0) --k;
    for (int i = n - 2, t = k + 1; i >= 0; ch[k++] = ps[i--])
        while (k >= t && ccw(ch[k - 2], ch[k - 1], ps[i]) <= 0) --k;
    ch.resize(k - 1);
    return ch;
}

Polygon convex_cut(const Polygon &ps, Line l) {
    int n = ps.size();
    Polygon Q;
    REP(i,n) {
        Point A = ps[i], B = ps[(i+1)%n];
        Line m = Line(A, B);
        if (ccw(l.a, l.b, A) != -1) Q.push_back(A);
        if (ccw(l.a, l.b, A) * ccw(l.a, l.b, B) < 0 && isis_ll(l, m))
            Q.push_back(is_ll(l, m));
    }
    return Q;
}

void add_point(vector<Point> &ps, Point p) {
    for (Point q : ps) if (abs(q - p) < eps) return;
    ps.push_back(p);
}

typedef int Weight;

struct Edge { int from, to; Weight weight; };

typedef vector<Edge> Edges;
typedef vector<Edges> Graph;

void add_edge(Graph &g, int from, int to, Weight weight) {
    g[from].push_back((Edge){from, to, weight});
}

Graph segment_arrangement(const vector<Line> &s, const vector<Point> &p) {
    int n = p.size(), m = s.size();
    Graph g(n);
    REP(i,m) {
        vector<pair<ld,int>> vec;
        REP(j,n) if (isis_sp(s[i], p[j]))
            vec.emplace_back(abs(s[i].a - p[j]), j);
        sort(all(vec));
        REP(j,vec.size()-1) {
            int from = vec[j].second, to = vec[j+1].second;
            add_edge(g, from, to, abs(p[from] - p[to]));
        }
    }
    return g;
}

Graph circle_arrangement(const vector<Circle> &c, const vector<Point> &p) {
    int n = p.size(), m = c.size();
    Graph g(n);
    REP(i,m) {
        vector<pair<ld,int>> vec;
        REP(j,n) if (abs(abs(c[i].p - p[j]) - c[i].r) < eps)
            vec.emplace_back(arg(c[i].p - p[j]), j);
        sort(all(vec));
        REP(j,vec.size()-1) {
            int from = vec[j].second, to = vec[j+1].second;
            ld angle = vec[j+1].first - vec[j].first;
            add_edge(g, from, to, angle * c[i].r);
        }
        if (vec.size() >= 2) {
            int from = vec.back().second, to = vec.front().first;
            ld angle = vec.front().first - vec.back().first;
            add_edge(g, from, to, angle * c[i].r);
        }
    }
    return g;
}

vector<vector<int>> polygon;
vector<int> seg2p[1024][1024];

Graph dual_graph(const vector<Line> &s, const vector<Point> &p) {
    int N = p.size();
    polygon.clear();
    REP(i,1024) REP(j,1024) seg2p[i][j].clear();
    vector<vector<tuple<ld,int,bool>>> tup(N);
    REP(i,s.size()) {
        int a = -1, b = -1;
        REP(j,N) if (abs(s[i].a - p[j]) < eps) a = j;
        REP(j,N) if (abs(s[i].b - p[j]) < eps) b = j;
        assert(a >= 0 && b >= 0);
        tup[a].emplace_back(arg(s[i].b - s[i].a), b, false);
        tup[b].emplace_back(arg(s[i].a - s[i].b), a, false);
    }
    REP(i,N) sort(all(tup[i]));
    REP(i,N) {
        REP(j,tup[i].size()) {
            ld angle; int pos = j, from = i, to; bool flag;
            tie(angle, to, flag) = tup[i][j];
            if (flag) continue;
            vector<int> ps;
            while (!flag) {
                ps.push_back(from);
                get<2>(tup[from][pos]) = true;
                seg2p[from][to].push_back(polygon.size());
                seg2p[to][from].push_back(polygon.size());
                angle += pi + eps;
                if (angle > pi) angle -= 2 * pi;
                auto it = lower_bound(all(tup[to]), make_tuple(angle, 0, false));
                if (it == tup[to].end()) it = tup[to].begin();
                from = to; tie(angle, to, flag) = *it;
                pos = it - tup[from].begin();
            }
            polygon.push_back(ps);
        }
    }
    Graph g(polygon.size());
    REP(i,N) REP(j,i) {
        if (seg2p[i][j].size() == 2) {
            int from = seg2p[i][j][0], to = seg2p[i][j][1];
            g[from].push_back((Edge){from, to});
            g[to].push_back((Edge){to, from});
        }
    }
    return g;
}

const ld zoom = 25;
const ld centerX = 6;
const ld centerY = 5;

void change_color(int r, int g, int b) {
    fprintf(stderr, "c.strokeStyle = 'rgb(%d, %d, %d)';\n", r, g, b);
}

int cordx(Point p) { return 400 + zoom * (p.real() - centerX); }
int cordy(Point p) { return 400 - zoom * (p.imag() - centerY); }

#define cord(p) cordx(p),cordy(p)

void draw_point(Point p) {
    fprintf(stderr, "circle(%d, %d, %d)\n", cord(p), 2);
}

void draw_segment(Line l) {
    fprintf(stderr, "line(%d, %d, %d, %d)\n", cord(l.a), cord(l.b));
}

void draw_line(Line l) {
    Point v = l.b - l.a;
    Line m(l.a - v * Point(1e4, 0), l.b + v * Point(1e4, 0));
    fprintf(stderr, "line(%d, %d, %d, %d)\n", cord(m.a), cord(m.b));
}

void draw_polygon(const Polygon &p) {
    int n = p.size();
    REP(i,n) draw_segment(Line(p[i], p[(i+1)%n]));
}

void draw_circle(Circle c) {
    fprintf(stderr, "circle(%d, %d, %d)\n", cord(c.p), (int)(zoom * c.r));
}
