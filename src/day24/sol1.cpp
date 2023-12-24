#include <cstdio>
#include <cassert>
#include <vector>
using namespace std;

namespace Geometry {
  const double eps = 1e-2;
  const double pi = acos(-1.0);

  inline int sign(double x) {
    if (fabs(x) < eps) return 0;
    else return x < 0 ? -1 : 1;
  }
  inline int dcmp(double x, double y) {
    return sign(x - y);
  }
  inline int zero(double x) {
    return fabs(x) < eps;
  }

  // x 在 [l, r] 内或 [r, l] 内
  inline int inMid(double l, double r, double x) {
    return dcmp(l, x) * dcmp(r, x) <= 0;
  }

  struct Point {
    double x, y;

    Point(long long x, long long y): x(x), y(y) {}
    Point(double x = 0, double y = 0): x(x), y(y) {}

    void read() { scanf("%lf%lf", &x, &y); }

    Point operator + (const Point& b) const { return Point(x + b.x, y + b.y); }
    Point operator - (const Point& b) const { return Point(x - b.x, y - b.y); }
    Point operator * (double p) { return Point(x * p, y * p); }
    Point operator / (double p) { return Point(x / p, y / p); }

    bool operator == (const Point& b) const { return dcmp(x, b.x) == 0 && dcmp(y, b.y) == 0; }
    bool operator < (const Point& b) const {
      int f = dcmp(x, b.x);
      if (f == -1) return 1;
      else if (f == 1) return 0;
      else return dcmp(y, b.y) == -1;
    }

    double abs() { return sqrt(x * x + y * y); }
    double abs2() { return x * x + y * y; }
    double distance(const Point& b) { return (*this - b).abs(); }

    // 逆时针旋转
    Point rot90(){ return Point(-y, x); }
    Point rot(double r) {
      return Point(x * cos(r) - y * sin(r), x * sin(r) + y * cos(r));
    }
    Point unit() { return *this / abs(); }
  };

  // ostream& operator<<(ostream& out, const Point& u) {
  //   return out << "(" << u.x << ", " << u.y << ")";
  // }
  // istream& operator>>(istream& in, Point& u) {
  //   return in >> u.x >> u.y;
  // }

  double dot(Point a, Point b) { return a.x * b.x + a.y * b.y; }
  double angle(Point a, Point b) { return acos(dot(a, b) / a.abs() / b.abs()); }
  double cross(Point a, Point b) { return a.x * b.y - a.y * b.x; }
  double cross(Point a, Point b, Point c) { return cross(b - a, c - a); }

  // C 在 B 的逆时针方向 1, 顺时针方向 -1, 共线 0
  int clockwise(Point a, Point b, Point c) { return sign(cross(b - a, c - a)); }

  // p[0] -> p[1]
  struct Line {
    Point p[2];
    Line() {}
    Line(Point a, Point b) { p[0] = a; p[1] = b; }

    void read() { p[0].read(); p[1].read(); }
    Point& operator [](int i) { return p[i]; }
    Point dir() { return p[1] - p[0]; }

    // q 在直线上的投影点
    Point projection(const Point& q) {
      Point k = p[1] - p[0];
      return p[0] + k * (dot(q - p[0], k) / k.abs2());
    }
    // q 在直线上的对称点
    Point reflection(const Point& q) {
      return projection(q) * 2 - q;
    }
  };

  // q 是否在线段 L 上
  bool onSegment(Line l, const Point& q) {
    return sign(cross(q - l[0], l[1] - l[0])) == 0 &&
      inMid(l[0].x, l[1].x, q.x) && inMid(l[0].y, l[1].y, q.y);
  }
  // q 是否在线段 AB 上
  bool onSegment(Point a, Point b, Point q) {
    return onSegment(Line(a, b), q);
  }
  // 直线 L1 和 L2 是否平行
  bool isParallel(Line l1, Line l2) {
    return sign(cross(l1.dir(), l2.dir())) == 0;
  }
  // 射线 L1 和 L2 的方向是否相同
  bool isSameDir(Line l1, Line l2) {
    return isParallel(l1, l2) && sign(dot(l1.dir(), l2.dir())) == 1;
  }
  // 直线 L1 和 L2 是否正交
  bool isOrthogonal(Line l1, Line l2) {
    return sign(dot(l1.dir(), l2.dir())) == 0;
  }

  // 区间 [l1, r1] 和 [l2, r2] 是否相交
  bool intersect(double l1, double r1, double l2, double r2) {
    if (l1 > r1) swap(l1, r1);
    if (l2 > r2) swap(l2, r2);
    return !(dcmp(r1, l2) == -1 || dcmp(r2 ,l1) == -1);
  }
  // 线段 P1P2 和 Q1Q2 是否相交
  bool isSegmentIntersect(Point p1, Point p2, Point q1, Point q2) {
    return intersect(p1.x, p2.x, q1.x, q2.x) &&
      intersect(p1.y, p2.y, q1.y, q2.y) &&
      sign(cross(p1, p2, q1)) * sign(cross(p1, p2, q2)) <= 0 &&
      sign(cross(q1, q2, p1)) * sign(cross(q1, q2, p2)) <= 0;
  }
  // 线段 L1 和 L2 是否相交
  bool isSegmentIntersect(Line l1, Line l2) {
    return isSegmentIntersect(l1[0], l1[1], l2[0], l2[1]);
  }

  // 获取直线 P1P2 和 Q1Q2 的交点
  Point getLineIntersection(Point p1, Point p2, Point q1, Point q2) {
    double a1 = cross(q1, q2, p1), a2 = -cross(q1, q2, p2);
    return (p1 * a2 + p2 * a1) / (a1 + a2);
  }
  // 获取直线 L1 和 L2 的交点
  Point getLineIntersection(Line l1, Line l2) {
    return getLineIntersection(l1[0], l1[1], l2[0], l2[1]);
  }

  // 获取点 Q 到线段 L 的距离
  double disPointSegment(Point q, Line l) {
    Point k = l.projection(q);
    if (onSegment(l, k)) {
      return q.distance(k);
    } else {
      return min(q.distance(l[0]), q.distance(l[1]));
    }
  }
  // 获取线段 L1 和 L2 的距离
  double disSegment(Line l1, Line l2) {
    if (isSegmentIntersect(l1, l2)) return 0.0;
    return min(min(disPointSegment(l2[0], l1), disPointSegment(l2[1], l1)),
      min(disPointSegment(l1[0], l2), disPointSegment(l1[1], l2)));
  }
}
using namespace Geometry;

const double L = 200000000000000;
const double R = 400000000000000;

struct Stone {
  long long x, y, z;
  long long vx, vy, vz;
};

bool isSameDir2(Line l1, Line l2) {
  return sign(dot(l1.dir(), l2.dir())) == 1;
}

bool check(Stone& a, Stone& b) {
  Line l1 { { a.x, a.y }, { a.x + a.vx, a.y + a.vy } };
  Line l2 { { b.x, b.y }, { b.x + b.vx, b.y + b.vy } };
  if (isParallel(l1, l2)) {
    // puts("?");
  } else {
    Point x = getLineIntersection(l1, l2);
    if (L - eps < x.x && x.x < R + eps && L - eps < x.y && x.y < R + eps) {
      if (isSameDir2(l1, { { a.x, a.y }, x }) && isSameDir2(l2, { { b.x, b.y }, x })) {
        {
          Point d1 = l1.dir().unit();
          Point d2 = (x - Point(a.x, a.y)).unit();
          // printf("(%.2lf,%.2lf) - (%.2lf,%.2lf): %.10lf \n", d1.x, d1.y, d2.x, d2.y, cross(d1, l2.dir()));
          // assert(sign(dot(d1, d2)) == 1);
          // assert(isParallel(l1, { { a.x, a.y }, x }));
          // assert(isParallel(l2, { { b.x, b.y }, x }));
          // printf("%.2lf %.2lf\n", x.x, x.y);
        }
        return true;
      } else {
        // Point d1 = l1.dir().unit();
        // Point d2 = (x - Point(a.x, a.y)).unit();
        // printf("(%.2lf,%.2lf) - (%.2lf,%.2lf)\n", d1.x, d1.y, d2.x, d2.y);
      }
    }
  }
  return false;
  // if (a.vx - b.vx == 0 && a.vy - b.vy == 0) {
  //   return a.x == b.x && a.y == b.y;
  // }
  // printf("%.3lf %.3lf\n", 1.0 * (b.x - a.x) / (a.vx - b.vx), 1.0 * (b.y - a.y) / (a.vy - b.vy));
  // if (a.vx - b.vx == 0) {
  //   double t = 1.0 * (b.y - a.y) / (a.vy - b.vy);
  //   double x = a.x + t * a.vx;
  //   double y = a.y + t * a.vy;
  //   return t > -eps && L - eps < x && x < R + eps && L - eps < y && y < R + eps;
  // }
  // if (a.vy - b.vy == 0 || 1ll * (b.x - a.x) * (a.vy - b.vy) == 1ll * (b.y - a.y) * (a.vx - b.vx)) {
  //   printf("YES?\n");
  //   double t = 1.0 * (b.x - a.x) / (a.vx - b.vx);
  //   double x = a.x + t * a.vx;
  //   double y = a.y + t * a.vy;
  //   return t > -eps && L - eps < x && x < R + eps && L - eps < y && y < R + eps;
  // }
  // return false;
}

int main() {
  vector<Stone> points;
  long long x, y, z, vx, vy, vz;
  while (scanf("%lld, %lld, %lld @ %lld, %lld, %lld", &x, &y, &z, &vx, &vy, &vz) == 6) {
    points.push_back({ x, y, z, vx, vy, vz });
  }
  int ans = 0;
  for (int i = 0; i < points.size(); i++) {
    for (int j = i + 1; j < points.size(); j++) {
      if (check(points[i], points[j])) {
        printf("%lld %lld %lld %lld\n", points[i].x, points[i].y, points[j].x, points[j].y);
        ans++;
      }
    }
  }
  printf("%d\n", ans);
  return 0;
}