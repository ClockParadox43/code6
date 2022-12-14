1.前置知识
    (1) pi = acos(-1)
    (2) 余弦定理: c² = a² + b² - 2abcos(θ) // a,b 为夹角
            - 特殊情况(勾股定理): c² = a² + b²
    (3) 正弦定理: a/sin(α) = b/sin(β) = c/sin(θ)

2. 浮点数比较(编程中的浮点数存储的不是精确值, 而是近似值, 在规定的误差之内相等就成立)
    const double eps = 1e-8 (根据题目需求写精确度)
    int sign(double x)  // 符号函数
    {
        if (fabs(x) < eps) return 0;   // 绝对值小于一个非常小的数就算是 0 
        if (x < 0) return -1;          // 小于 0 返回 -1 否则返回 1
        return 1;
    } 

    int cmp(double x, double y)     // 比较函数
    {
        if (fabs(x - y) < eps) reutrn 0;   // 两个数的差的绝对值小于一个非常小的数就算是 0 
        if (x < y) return -1;
        return 1;
    }

3. 向量
    3.1 向量的加减法和数乘运算
        - 加法: 向量A + 向量B = 向量C 
               (x₁ + y₁) + (x₂ + y₂) = (x₁ + x₂, y₁ + y₂) = 由平行四边形构成的对角线
        - 减法: 向量A - 向量B = 向量C (x₁ - x₂, y₁ - y₂)
               (x₁ - y₁) - (x₂ - y₂) = (x₁ - x₂, y₁ - y₂) = 由 A 指向 B 的向量
        - 数乘 向量A * b = (bx, by) = 在向量 A 的基础上延长 b 倍
          ps:乘上 -1 等价将向量反向

          加减法意义详见图片

    3.2 内积(点积) 向量A·向量B = |向量A||向量B|cos(θ) = (x₁x₂, y₁y₂)
        cos(θ): 由 向量A 逆时针转到 向量B 的角度
        
        (1) 几何意义: 一个向量在另一个向量上的投影与另一个向量的长度的乘积
        (2) 代码实现
            double dot(Point a, Point b)
            {
                return a.x * b.x + a.y * b.y;
            } 
        
    3.3 外积(叉乘) 向量Ax向量B = |向量A||向量B|sin(θ)
        (1) 向量A 与 向量B 组成的平行四边形的有向面积 (向量B 在向量A 逆时针方向为正)
        (2) 代码实现
            double cross(Point a, Point b)
            {
                return a.x * b.y - b.x * a.y;
            }
    
    3.4 常用函数
        3.4.1 取模
        |向量A| = √向量A·向量A = √x²+y²
        double get_length(Point a)  // 求向量长度可以用点击来求
        {
            reutrn sqrt(dot(a, a));
        }
        
        3.4.2 计算向量夹角
        ∵ 向量A·向量B = |向量A||向量B|cos(θ)
        ∴ cos(θ) = acos(向量A·向量B / |向量A||向量B|)
        double get_angle(Point a, Point b)
        {
            return acos(dot(A, B) / get_length(a) / get_length(b)); 
        }
        
        3.4.3 计算两个向量构成的平行四边形的有向面积
        double area(Point a, Point b, Point c)  
        {
            return cross(b - a, c - a); // a X b 就是平行四边形面积, a 是原点
        }
        
        3.4.5 向量A 顺时针旋转 θ 的角度:
        Point rotate(Point a, double angle)
        {
            return Point(a.x * cos(angle) + a.y * sin(angle), -a.x * sin(angle) + a.y * cos(angle));
        }

        常用函数详见图片

4. 点与线
    4.1 直线定理
        (1) 一般式 ax + by + c = 0;
        (2) 点向式 p0 + vt          // 大部分时候使用点向式
        (3) 斜截式 y = kx + b

    4.2 常用操作
        (1) 判断点在直线上 A X B = 0
        (2) 两直线相交求焦点 证明详见图
        // cross(v, w) == 0 则两直线平行或重合
        Point get_line_intersection(Point p, Vector v, Point q, vector w)
        {
            vector u = p - q;       // 一个点的距离减另一个点的距离, 求出辅助线的距离
            double t = cross(w, u) / cross(v, w);   // 因为相似, 求出两个三角形的比值
            return p + v * t;                       // p 到焦点的距离就是 t 倍的 向量v
        }

        (3) 点到直线的距离 详见图
        double distance_to_line(Point p, Point a, Point b)
        {
            vector v1 = b - a, v2 = p - a;      // 求出点到原点的距离
            return fabs(cross(v1, v2) / get_length(v1));    // 面积 / 底边 = 高(也就是顶点到底边的距离)
        }

        (4) 点到线段的距离
                 b
        p    
            a 
        double distance_to_segment(Point p, Point a, Point b)
        {
            if (a == b) return get_length(p - a);       // 如果线段只是一个点, a 和 b 相等, 那么直接返回 (点到线段的距离 = 点到点的距离)
            vector v1 = b - a, v2 = p - a, v3 = p - b; 
            if (sign(dot(v1, v2)) < 0) return get_length(v2);   // 判断 θ 值详见图
            if (sign(dot(v1, v3)) > 0) return get_length(v3);   
            return distance_to_line(p, a, b);
        }

        (5) 点在直线上投影
        Point get_line_projection(Point p, Point a, Point b)
        {
            Vector v = b - a;       // 求 a->b 的距离
            return a + v * (dot(v, p - a) / dot(v, v));   // p-a:求出 a->p 的距离 / 向量 v 的距离 * 向量v + a = 投影坐标
        }

        (6) 点是否在线段上
        bool on_segment(Point p, Point a, Point b)
        {
            return sign(cross(p - a, p - b)) == 0 && sign(dot(p - a, p - b)) <= 0;  // 保证共线或者不是在 p 的左边或者右边 (也就是反向在 pa 内部)
        }

        (7) 判断两线段是否相交
            - 叉乘后得到的两个面积符号必然相反
        bool segment_intersection(Point a1, Point a2, Point b1, Point b2)
        {
            double c1 = cross(a2 - a1, b1 - a1), c2 = cross(a2 - a1, b2 - a1);
            double c3 = cross(b2 - b1, a2 - b1), c4 = cross(b2 - b1, a1 - b1);
            return sign(c1) * sign(c2) <= 0 && sign(c3) * sign(c4) <= 0;        // 等于 0 意味着某个点 a2 或 a1 在线段上, 如果线段处相交不算, <= 变成 < 即可
        }

5. 多边形
    5.1 三角形
    5.1.1 面积
        (1) 叉积
        (2) 海伦公式 (只给了边)
            p = (a + b + c) / 2
            S = sqrt(p(p - a) * p(p - b) * p(p - c))
    5.1.2 三角形四心
        (1) 外心, 外接圆心
            三边中垂线交点, 到三角形单个顶点的距离相等
        (2) 内心, 内切圆圆心
            角平分线焦点, 到三边距离相等
        (3) 垂心
            三条垂线焦点
        (4) 重心
            三条中线交点 (到三角形三点距离的平方和最小点, 三角形内到三遍距离之积的最大点)
    详见图片

    5.2 普通多变形
        通常按逆时针存储的所有点
        5.2.1 定义
        (1) 多边形
            由在同一平面且不再同一直线上的多条线段首尾顺次连接且不相交组成的图形叫多边形
        (2) 简单多变形
            简单多变形是除相邻外其它边不相交的多变形
        (3) 凸多边形
            过多边形的任意一边做一条直线, 如果其他各个顶点都在这条直线的同侧, 则把这个多边形叫做凸多边形
            任意凸多边形外角和均为360° (向量从边出发正好转一圈所以是360°)
            任意凸多边形内角和为(n−2)180°
            (一个包含 n 条边的三角形, 除了两个邻边每条边都会对应一个三角形, 任意一个凸多边形可以进行三角剖分)

    5.2.2 常用函数
    (1) 求多边形面积(不一定是凸多边形)
        我们可以从第一个顶点除法把凸多边形分成 n-2 个三角形, 然后把面积加起来
    double polygon_area(Point p[], int n)
    {
        double s = 0;
        for (int i = 1; i + 1 < n; ++ i )
            s += cross(p[i] - p[0], p[i + 1] - p[i]);       // 枚举所有边构成的三角形的面积, 转一圈后多边形内部的面积都被算了一次, 外部面积都被抵消掉了
        return s / 2;       // 因为叉积算的是算的是三角形两倍所以要除以 2
    }

    (2) 判断点是否在多边形内(不一定是凸多边形)
        a.射线法, 从该点任意做一条和所有都不平行的射线, 交点个数为偶数, 则在多边形外, 为奇数则在多边形内
          多边形是一个封闭图形, 每穿过一条边都代表从内走到外或从外走到内
        b.转角法
    (3) 判断点是否在凸多边形内
        只需要断点是点是在所有边的左边(逆时针存储多边形)

    5.3 皮克定理
    皮克定理是指一个计算点阵中顶点在格点上的多边形面积公式该公式可以表示为:
        S = a + b/2 - 1
    其中a表示多边形内部的点数, b表示多边形边界上的点数, S表示多边形的面积

6. 圆
    (1) 圆与直线交点
    (2) 两圆交点
    (3) 点到圆的切线
    (4) 两圆公切线
    (5) 两圆相交面积