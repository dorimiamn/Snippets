struct UnionFind
{
    vi par;
    UnionFind(int N) : par(N, -1) {}
    int root(int x)
    {
        if (par[x] < 0)
            return x;
        return par[x] = root(par[x]);
    }
    void unite(int x, int y)
    {
        x = root(x);
        y = root(y);
        if (x == y)
            return;
        if (par[x] == par[y])
            swap(x, y);
        par[x] += par[y];
        par[y] = x;
    }
    bool same(int x, int y)
    {
        return root(x) == root(y);
    }
    int size(int x)
    {
        return -par[root(x)];
    }
};