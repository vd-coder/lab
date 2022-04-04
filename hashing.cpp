
#include <bits/stdc++.h>

using namespace std;

class Bucket
{
public:
    int ld;
    set<int> keys;
};

// Global variables
int gd;
vector<Bucket *> Buckets;

string DecToBinary(int num)
{
    string str;
    while (num)
    {
        if (num & 1)
            str += '1';
        else
            str += '0';
        num >>= 1;
    }
    return str;
}

vector<Bucket *> createHash(int gd, int size)
{
    vector<Bucket *> dir;
    int k = 1 << gd;

    Bucket *B = new Bucket[k];
    for (int i = 0; i < k; i++)
    {
        B[i].ld = gd;
        dir.push_back(&B[i]);
        Buckets.push_back(&B[i]);
    }

    return dir;
}

vector<Bucket *> insert(int val, int size, vector<Bucket *> dir)
{
    int k = 1 << gd;
    int index = val % k;

    if (dir[index]->keys.find(val) != dir[index]->keys.end())
        return dir;

    if (dir[index]->keys.size() == size && dir[index]->ld == gd)
    {
        // double directory
        if (gd == 20)
        {
            gd = -1;
            return dir;
        }

        gd++;
        int n1 = dir.size();
        for (int i = 0; i < n1; i++)
        {
            dir.push_back(dir[i]);
        }

        dir = insert(val, size, dir);
    }
    else if (dir[index]->keys.size() == size)
    {
        // new bucket
        Bucket *B1 = new Bucket();
        set<int> s0, s1;
        string str = DecToBinary(index);

        for (auto it = dir[index]->keys.begin(); it != dir[index]->keys.end(); it++)
        {
            int f = *it;
            string f1 = DecToBinary(f);
            for (int m = f1.size(); m < 21; m++)
                f1 += '0';

            if (f1[dir[index]->ld] == '1')
            {
                s1.insert(f);
            }
            else
            {
                s0.insert(f);
            }
        }

        B1->keys = s1;
        dir[index]->ld++;
        B1->ld = dir[index]->ld;

        int l1 = dir[index]->ld;
        int k1 = 1 << l1;

        int i1 = index ^ (k1 / 2);
        if (str[l1 - 1] == '1')
        {
            dir[index] = B1;
            dir[i1]->keys = s0;
        }
        else
        {
            dir[i1] = B1;
            dir[index]->keys = s0;
        }

        for (int a = k1; i1 + a < k; a += k1)
        {
            dir[i1 + a] = dir[i1];
        }

        for (int a = k1; i1 - a >= 0; a += k1)
        {
            dir[i1 - a] = dir[i1];
        }

        for (int a = k1; index + a < k; a += k1)
        {
            dir[index + a] = dir[index];
        }

        for (int a = k1; index - a >= 0; a += k1)
        {
            dir[index - a] = dir[index];
        }

        Buckets.push_back(B1);

        dir = insert(val, size, dir);
    }
    else
    {
        dir[index]->keys.insert(val);
    }

    return dir;
}

bool search(int val, vector<Bucket *> dir)
{
    int k = 1 << gd;
    int index = val % k;

    if (dir[index]->keys.find(val) != dir[index]->keys.end())
        return true;
    else
        return false;
}

vector<Bucket *> deleteKey(int val, vector<Bucket *> dir)
{
    int k = 1 << gd;
    int index = val % k;

    if (dir[index]->keys.find(val) == dir[index]->keys.end())
        return dir;

    dir[index]->keys.erase(val);
    int l1 = dir[index]->ld;
    if (dir[index]->keys.size() == 0 && gd > 1 && l1 > 1)
    {
        l1--;
        int k1 = 1 << l1;
        int i1 = index ^ k1;
        if (dir[index]->ld != dir[i1]->ld)
            return dir;

        Bucket *B1 = dir[index];
        dir[i1]->ld = l1;
        dir[index] = dir[i1];
        for (int p = 0; p < dir.size(); p++)
        {
            if (dir[p] == B1)
                dir[p] = dir[i1];
        }

        for (auto it = Buckets.begin(); it != Buckets.end(); it++)
        {
            if (*it == B1)
            {
                Buckets.erase(it);
                break;
            }
        }

        int j = 0;
        for (; j < dir.size(); j++)
        {
            if (dir[j]->ld == gd)
                break;
        }
        if (j == dir.size())
        {
            for (int n1 = 0; n1 < j / 2; n1++)
                dir.pop_back();

            gd--;
        }

        // delete B1;
    }

    return dir;
}

void print(vector<Bucket *> dir)
{
//     cout << dir.size() << endl;
    cout << gd << endl;
    cout << Buckets.size() << endl;
    for (int i = 0; i < Buckets.size(); i++)
    {
        cout << Buckets[i]->keys.size() << " " << Buckets[i]->ld << endl;
//         for (auto it = Buckets[i]->keys.begin(); it != Buckets[i]->keys.end(); it++)
//             cout << *it << " ";
//         cout << endl;
    }

    return;
}

int main()
{
    int capacity;
    cin >> gd >> capacity;

    vector<Bucket *> dir = createHash(gd, capacity);

    int n;
    while (cin >> n)
    {
        if (n == 2)
        {
            // Insert
            int val;
            cin >> val;

            dir = insert(val, capacity, dir);
            if (gd == -1)
            {
                cout << "Can't add" << endl;
                gd = 20;
            }
        }
        else if (n == 3)
        {
            // search
            int val;
            cin >> val;

            bool p = search(val, dir);
            if (p)
                cout << "Found " << val << endl;
            else
                cout << "Not Found " << val << endl;
        }
        else if (n == 4)
        {
            // delete
            int val;
            cin >> val;

            dir = deleteKey(val, dir);
        }
        else if (n == 5)
        {
            // print
            print(dir);
        }
        else if (n == 6)
        {
            break;
        }
    }

    return 0;
}
