#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>


struct vec
{
    float x, y;
};


struct segment
{
    vec p1, p2;
};


vec vec_sum(vec a, vec b)
{
    vec c;
    c.x = a.x - b.x;
    c.y = a.y - b.y;
    return c;
}

struct line
{
    float a, b, c;
    line(int k, int d)
    {
        a = k;
        b = -1;
        c = d;
    }
    line(vec av, vec bv)
    {
        a = av.y - bv.y;
        b = bv.x - av.x;
        c = av.x * bv.y - av.y * bv.x;
    }
    std::pair<int, int> kxd()
    {
        std::pair<int, int> kd;
        kd.first = -a / b;
        kd.second = -c / b;
        return kd;
    }
};

float dist_p_l(vec a, line l)
{
    //std::cout << std::abs(l.a * a.x + l.b * a.y + l.c) << " " << sqrt(l.a * l.a + l.b * l.b);
    return std::abs(l.
    a * a.x + l.b * a.y + l.c) / sqrt(l.a * l.a + l.b * l.b);
}


float dist_p_p(vec a, vec b)
{
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}


struct circle
{
    vec center;
    int r;
};


std::pair<std::pair<bool, bool>, std::pair<int, int>> intercec(line l1, line l2)
{
    float d, d1, d2;
    d = l1.a * l2.b - l2.a * l1.b;
    d1 = -l1.c * l2.b + l1.b * l2.c;
    d2 = -l2.c * l1.a + l2.a * l1.c;
    if (d != 0) return {{0, 0}, {d1 / d, d2 / d}};
    float k;
    if (l1.a != 0)
    {
        k = l2.a / l1.a;
        if (l1.b * k == l2.b && l1.c * k == l2.c)
        {
            return {{1, 0}, {0, 0}};
        }
    }
    else if(l1.b != 0)
    {
        k = l2.b / l1.b;
        if (l1.a * k == l2.a && l1.c * k == l2.c)
        {
            return {{1, 0}, {0, 0}};
        }
    }
    return {{0, 1}, {0, 0}};
}

enum circle_intersection_type
{
    nothing, touching, intersection
};

int intercec_cir_l(circle o, line l)
{
    float dist = dist_p_l(o.center, l);
    if (dist > o.r) return nothing;
    if (dist == o.r) return touching;
    return intersection;
}


int are_on_one_side(line l, vec p1, vec p2)
{
    float q1 = l.a * p1.x + l.b * p1.y + l.c;
    float q2 = l.a * p2.x + l.b * p2.y + l.c;
    if (q1 == 0 || q2 == 0)
    {
        return 0;
    }
    if ((q1 > 0 && q2 < 0) || (q1 < 0 && q2 > 0))
    {
        return -1;
    }
    return 1;
}


bool is_point_in_triangle(vec p1, vec p2, vec p3, vec q)
{
    line l1(p3, p2);
    line l2(p1, p3);
    line l3(p1, p2);
    return are_on_one_side(l1, p1, q) >= 0 && are_on_one_side(l2, p2, q) >= 0 && are_on_one_side(l3, p3, q) >= 0;
}


bool is_ear(vec main_p, vec p1, vec p2)
{
    vec q1;
    q1.x = p1.x - main_p.x;
    q1.y = p1.y - main_p.y;
    vec q2;
    q2.x = p2.x - main_p.x;
    q2.y = p2.y - main_p.y;
    if (q1.x * q2.y - q2.x * q1.y >= 0)
    {
        return 1;
    }
    return 0;
}


void triangulation(std::vector<vec> polygon, std::vector<segment>& ans)
{
    if (polygon.size() < 4)
    {
        return;
    }
    int main_p_num = 1;
    while (!is_ear(polygon[main_p_num % polygon.size()], polygon[(main_p_num - 1) % polygon.size()], polygon[(main_p_num + 1) % polygon.size()]))
    {
        main_p_num++;
    }
    int ans1 = main_p_num - 1;
    int ans2 = main_p_num + 1;
    float dist_ans = 1e9;
    for (int i = 0; i < main_p_num - 1; i++)
    {
        if (is_point_in_triangle(polygon[main_p_num], polygon[main_p_num - 1], polygon[main_p_num + 1], polygon[i]) && dist_p_p(polygon[i], polygon[main_p_num]) < dist_ans)
        {
            ans1 = main_p_num;
            ans2 = i;;
            dist_ans = dist_p_p(polygon[i], polygon[main_p_num]);
        }
    }
    for (int i = main_p_num + 2; i < polygon.size(); i++)
    {
        if (is_point_in_triangle(polygon[main_p_num], polygon[main_p_num - 1], polygon[main_p_num + 1], polygon[i]) && dist_p_p(polygon[i], polygon[main_p_num]) < dist_ans)
        {
            ans1 = main_p_num;
            ans2 = i;;
            dist_ans = dist_p_p(polygon[i], polygon[main_p_num]);
        }
    }
    ans.push_back({polygon[ans1], polygon[ans2]});
    std::vector<vec> polygon1, polygon2;
    for (int i = ans1; i <= ans2; i++)
    {
        polygon1.push_back(polygon[i]);
    }
    for (int i = 0; i <= ans1; i++)
    {
        polygon2.push_back(polygon[i]);
    }
    for (int i = ans2; i < polygon.size(); i++)
    {
        polygon2.push_back(polygon[i]);
    }
    triangulation(polygon1, ans);
    triangulation(polygon2, ans);
    return;
}


int main()
{
    int n;
    float x, y;
    std::cin >> n;
    std::vector<vec> polygon(n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> x >> y;
        polygon[i] = {x, y};
    }
    std::vector<segment> ans;
    triangulation(polygon, ans);
    for (int i = 0; i < ans.size(); i++)
    {
        std::cout << ans[i].p1.x << ',' << ans[i].p1.y << " - " << ans[i].p2.x << ',' << ans[i].p2.y << '\n'; 
    }
}