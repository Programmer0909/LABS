// #include <bits/stdc++.h>
// #define endl "\n"
// using namespace std;

// struct process
// {
//     char name;
//     int AT = 0, BT, WT = 0, TAT = 0, RT = 0, CT = 0;
// };

// int n;

// int main()
// {

// #ifndef ONLINE_JUDGE
//     freopen("input.txt", "r", stdin);
//     freopen("output.txt", "w", stdout);
// #endif

//     cin >> n;
//     int tq1 = 2, tq2 = 4, flag = 0;
//     char c;
//     queue<process> q[3];
//     vector<process> completed[3];
//     for (int i = 0; i < n; i++)
//     {
//         char c;
//         cin >> c;
//         int ti;
//         cin >> ti;
//         process p;
//         p.AT = 0;
//         p.BT = ti;
//         p.name = c;
//         p.RT = p.BT;
//         q[0].push(p);
//     }

//     int cpu1 = 8, cpu2 = 16, cpu3 = 32;
//     int time = 0;
//     map<char, int> provided;
//     while (time < cpu1 and q[0].size() > 0)
//     {
//         int sz = q[0].size();
//         for (int i = 0; i < sz; i++)
//         {
//             process p = q[0].front();
//             q[0].pop();
//             // cout<<p.name<<" ";
//             if (time < cpu1)
//             {
//                 if (p.RT <= tq1 and time + p.RT <= cpu1)
//                 {
//                     if (provided.find(p.name) == provided.end())
//                     {
//                         provided[p.name] = time;
//                     }
//                     time += p.RT;
//                     p.TAT = time - p.AT;
//                     p.WT = p.TAT - p.BT;
//                     p.CT = time;
//                     p.RT = 0;
//                     completed[0].push_back(p);
//                 }
//                 else if (p.RT <= tq1)
//                 {
//                     if (provided.find(p.name) == provided.end())
//                     {
//                         provided[p.name] = time;
//                     }
//                     int rem = cpu1 - time;
//                     time += rem;
//                     p.RT -= rem;
//                     q[1].push(p);
//                 }
//                 else
//                 {
//                     if (provided.find(p.name) == provided.end())
//                     {
//                         provided[p.name] = time;
//                     }
//                     time += tq1;
//                     p.RT -= tq1;
//                     q[0].push(p);
//                 }
//             }
//             else
//             {
//                 q[1].push(p);
//             }
//         }
//     }
//     int sz = q[0].size();
//     for (int i = 0; i < sz; i++)
//     {
//         process p = q[0].front();
//         q[0].pop();
//         q[1].push(p);
//     }

//     int r = 0;
//     while (r < cpu2 and q[1].size() > 0)
//     {
//         int sz = q[1].size();
//         for (int i = 0; i < sz; i++)
//         {
//             process p = q[1].front();
//             q[1].pop();
//             if (r < cpu2)
//             {
//                 if (p.RT <= tq2 and r + p.RT <= cpu2)
//                 {
//                     if (provided.find(p.name) == provided.end())
//                     {
//                         provided[p.name] = time;
//                     }
//                     r += p.RT;
//                     time += p.RT;
//                     p.TAT = time - p.AT;
//                     p.WT = p.TAT - p.BT;
//                     p.RT = 0;
//                     p.CT = time;
//                     completed[1].push_back(p);
//                 }
//                 else if (p.RT <= tq2)
//                 {
//                     if (provided.find(p.name) == provided.end())
//                     {
//                         provided[p.name] = time;
//                         p.WT = time - p.AT;
//                     }
//                     int rem = cpu2 - r;
//                     r += rem;
//                     time = cpu2;
//                     p.RT -= rem;
//                     q[2].push(p);
//                 }
//                 else
//                 {
//                     if (provided.find(p.name) == provided.end())
//                     {
//                         provided[p.name] = time;
//                     }
//                     time += tq2;
//                     r += tq2;
//                     p.RT -= tq2;
//                     q[1].push(p);
//                 }
//             }
//             else
//             {
//                 q[2].push(p);
//             }
//         }
//     }
//     sz = q[1].size();
//     for (int i = 0; i < sz; i++)
//     {
//         process p = q[1].front();
//         q[1].pop();
//         q[2].push(p);
//     }

//     vector<process> uncompleted;
//     int ftime = 0;
//     for (int i = 0; i < q[2].size(); i++)
//     {

//         process p = q[2].front();
//         q[2].pop();
//         if (ftime > cpu3)
//         {
//             uncompleted.push_back(p);
//         }
//         else
//         {
//             ftime += p.RT;
//             time += p.RT;
//             p.TAT = time - p.AT;
//             p.WT = p.TAT - p.BT;
//             p.RT = 0;
//             p.CT = time;
//             completed[2].push_back(p);
//         }
//     }

//     if (completed[0].size() > 0)
//     {
//         cout << "process completed in queue 1: \n"
//              << endl;
//         cout << "name  TAT  WT  Response time" << endl;
//         for (int i = 0; i < completed[0].size(); i++)
//         {
//             cout << completed[0][i].name << "     " << completed[0][i].TAT << "     " << completed[0][i].WT << "     " << provided[completed[0][i].name] << endl;
//         }
//     }
//     else
//     {
//         cout << "No process is completed in queue 1";
//     }
//     cout << endl;
//     cout << "**********************************************" << endl;
//     if (completed[1].size() > 0)
//     {
//         cout << "process completed in queue 2: \n"
//              << endl;
//         cout << "name  TAT  WT  Response time" << endl;
//         for (int i = 0; i < completed[1].size(); i++)
//         {
//             cout << completed[1][i].name << "     " << completed[1][i].TAT << "     " << completed[1][i].WT << "     " << provided[completed[1][i].name] << endl;
//         }
//     }
//     else
//     {
//         cout << "No process is completed in queue 2";
//     }
//     cout << endl;
//     cout << "**********************************************" << endl;

//     if (completed[2].size() > 0)
//     {
//         cout << "process completed in queue 3: \n"
//              << endl;
//         cout << "name  TAT  WT Response time" << endl;
//         for (int i = 0; i < completed[2].size(); i++)
//         {
//             cout << completed[2][i].name << "     " << completed[2][i].TAT << "    " << completed[2][i].WT << "     " << provided[completed[2][i].name] << endl;
//         }
//     }
//     else
//     {
//         cout << "No process is completed in queue 3";
//     }
//     cout << endl;

//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PROCESSES 100

struct Process
{
    char name;
    int AT;
    int BT;
    int WT;
    int TAT;
    int RT;
    int CT;
};

int n;

int main()
{
    int tq1 = 2, tq2 = 4, flag = 0;
    char c;
    struct Process q[3][MAX_PROCESSES];
    struct Process completed[3][MAX_PROCESSES];
    int completed_count[3] = {0};
    int cpu1 = 8, cpu2 = 16, cpu3 = 32;
    int time = 0;
    char provided[MAX_PROCESSES] = {0};

    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        char c;
        int ti;
        scanf(" %c %d", &c, &ti);

        q[0][i].name = c;
        q[0][i].AT = 0;
        q[0][i].BT = ti;
        q[0][i].RT = ti;
    }

    int r = 0;

    while (r < cpu2)
    {
        int sz = 0;
        for (int i = 0; i < n; i++)
        {
            if (q[0][i].RT > 0 && r < cpu2)
            {
                struct Process p = q[0][i];
                sz++;
                if (p.RT <= tq1 && r + p.RT <= cpu2)
                {
                    if (provided[p.name] == 0)
                    {
                        provided[p.name] = time;
                    }
                    r += p.RT;
                    time += p.RT;
                    p.TAT = time - p.AT;
                    p.WT = p.TAT - p.BT;
                    p.RT = 0;
                    p.CT = time;
                    completed[0][completed_count[0]++] = p;
                }
                else if (p.RT <= tq1)
                {
                    if (provided[p.name] == 0)
                    {
                        provided[p.name] = time;
                    }
                    int rem = cpu1 - time;
                    r += rem;
                    time += rem;
                    p.RT -= rem;
                    for (int j = 0; j < n; j++)
                    {
                        if (q[0][j].name == p.name)
                        {
                            q[1][j] = p;
                            break;
                        }
                    }
                }
                else
                {
                    if (provided[p.name] == 0)
                    {
                        provided[p.name] = time;
                    }
                    time += tq1;
                    r += tq1;
                    p.RT -= tq1;
                    for (int j = 0; j < n; j++)
                    {
                        if (q[0][j].name == p.name)
                        {
                            q[0][j] = p;
                            break;
                        }
                    }
                }
            }
        }
        for (int i = 0; i < n; i++)
        {
            if (q[0][i].RT > 0)
            {
                q[0][i] = q[0][i];
                sz++;
            }
        }
        if (sz == 0)
        {
            break;
        }
    }

    int uncompleted_count = 0;
    int ftime = 0;

    for (int i = 0; i < n; i++)
    {
        struct Process p = q[2][i];
        if (ftime > cpu3)
        {
            q[2][i] = p;
            uncompleted_count++;
        }
        else
        {
            ftime += p.RT;
            time += p.RT;
            p.TAT = time - p.AT;
            p.WT = p.TAT - p.BT;
            p.RT = 0;
            p.CT = time;
            completed[2][completed_count[2]++] = p;
        }
    }

    if (completed_count[0] > 0)
    {
        printf("process completed in queue 1:\n\n");
        printf("name  TAT  WT  Response time\n");
        for (int i = 0; i < completed_count[0]; i++)
        {
            struct Process p = completed[0][i];
            printf("%c     %d     %d     %d\n", p.name, p.TAT, p.WT, provided[p.name]);
        }
    }
    else
    {
        printf("No process is completed in queue 1");
    }
    printf("\n");
    printf("**********************************************\n");

    if (completed_count[1] > 0)
    {
        printf("process completed in queue 2:\n\n");
        printf("name  TAT  WT  Response time\n");
        for (int i = 0; i < completed_count[1]; i++)
        {
            struct Process p = completed[1][i];
            printf("%c     %d     %d     %d\n", p.name, p.TAT, p.WT, provided[p.name]);
        }
    }
    else
    {
        printf("No process is completed in queue 2");
    }
    printf("\n");
    printf("**********************************************\n");

    if (completed_count[2] > 0)
    {
        printf("process completed in queue 3:\n\n");
        printf("name  TAT  WT  Response time\n");
        for (int i = 0; i < completed_count[2]; i++)
        {
            struct Process p = completed[2][i];
            printf("%c     %d     %d     %d\n", p.name, p.TAT, p.WT, provided[p.name]);
        }
    }
    else
    {
        printf("No process is completed in queue 3");
    }
    printf("\n");

    return 0;
}
