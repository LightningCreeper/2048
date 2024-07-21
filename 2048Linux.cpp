#include <bits/stdc++.h>
#include <termio.h>
using namespace std;

int a[4][4], score, step;

int getch(void) {
    struct termios tm, tm_old;
    int fd = 0, ch;

    if (tcgetattr(fd, &tm) < 0) {
        return -1;
    }

    tm_old = tm;
    cfmakeraw(&tm);
    if (tcsetattr(fd, TCSANOW, &tm) < 0) {
        return -1;
    }

    ch = getchar();
    if (tcsetattr(fd, TCSANOW, &tm_old) < 0) {
        return -1;
    }

    return ch;
}

bool isvalid() {
    bool res = false;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            res |= !a[i][j];
    return res;
}

void makenew() {
    vector<pair<int, int>> vec;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (!a[i][j])
                vec.push_back(make_pair(i, j));

    auto [x, y] = vec[rand() % vec.size()];
    a[x][y] = rand() % 2 + 1;
}

vector<int> get(vector<int> x) {
    vector<int> vec;
    if (x.size() == 4) {
        if (x[0] == x[1]) {
            vec.push_back(x[0] + 1), score += 1 << (x[0] + 1);
            if (x[2] == x[3])
                vec.push_back(x[2] + 1), score += 1 << (x[2] + 1);
            else {
                vec.push_back(x[2]);
                vec.push_back(x[3]);
            }
        } else if (x[1] == x[2]) {
            vec.push_back(x[0]);
            vec.push_back(x[1] + 1), score += 1 << (x[1] + 1);
            vec.push_back(x[3]);
        } else if (x[2] == x[3]) {
            vec.push_back(x[0]);
            vec.push_back(x[1]);
            vec.push_back(x[2] + 1), score += 1 << (x[2] + 1);
        } else {
            vec = x;
        }
    } else if (x.size() == 3) {
        if (x[0] == x[1])
            vec = { x[0] + 1, x[2] }, score += 1 << (x[0] + 1);
        else if (x[1] == x[2])
            vec = { x[0], x[1] + 1 }, score += 1 << (x[1] + 1);
        else
            vec = x;
    } else if (x.size() == 2) {
        if (x[0] == x[1])
            vec = { x[0] + 1 }, score += 1 << (x[0] + 1);
        else
            vec = x;
    } else
        vec = x;
    while (vec.size() < 4)
        vec.push_back(0);
    return vec;
}

void operate_up() {
    for (int j = 0; j < 4; j++) {
        vector<int> vec;
        for (int i = 0; i < 4; i++)
            if (a[i][j] > 0)
                vec.push_back(a[i][j]);
        vec = get(vec);
        for (int i = 3; i >= 0; i--) {
            a[i][j] = vec.back();
            vec.pop_back();
        }
    }
}

void operate_down() {
    for (int j = 0; j < 4; j++) {
        vector<int> vec;
        for (int i = 3; i >= 0; i--)
            if (a[i][j] > 0)
                vec.push_back(a[i][j]);
        vec = get(vec);
        for (int i = 0; i < 4; i++) {
            a[i][j] = vec.back();
            vec.pop_back();
        }
    }
}

void operate_left() {
    for (int i = 0; i < 4; i++) {
        vector<int> vec;
        for (int j = 0; j < 4; j++)
            if (a[i][j] > 0)
                vec.push_back(a[i][j]);
        vec = get(vec);
        for (int j = 3; j >= 0; j--) {
            a[i][j] = vec.back();
            vec.pop_back();
        }
    }
}

void operate_right() {
    for (int i = 0; i < 4; i++) {
        vector<int> vec;
        for (int j = 3; j >= 0; j--)
            if (a[i][j] > 0)
                vec.push_back(a[i][j]);
        vec = get(vec);
        for (int j = 0; j < 4; j++) {
            a[i][j] = vec.back();
            vec.pop_back();
        }
    }
}

void operate() {
    char c;
    c = getch();

    if (c == 'w')
        operate_up();
    if (c == 's')
        operate_down();
    if (c == 'a')
        operate_left();
    if (c == 'd')
        operate_right();

    step++;
}

void print() {
    system("clear");
    cout << "+---------+" << endl;

    for (int i = 0; i < 4; i++) {
        cout << "| ";
        for (int j = 0; j < 4; j++) {
            if (a[i][j] == 0)
                cout << " ";
            else if (a[i][j] > 9)
                cout << char(a[i][j] - 10 + 'A');
            else
                cout << a[i][j];
            cout << " ";
        }
        cout << "|" << endl;
    }
    cout << "+---------+" << endl;

    cout << "score : " << score << endl;
    cout << "step : " << step << endl;
}

void checkwon() {
    bool flag = 0;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (a[i][j] >= 12)
                flag = true;
    if (!flag)
        return;

    system("clear");
    cout << "# # # ### # # #" << endl
         << "# # # # # # # #" << endl
         << " # #  ###  # #  " << endl;
    cout << "You WON!" << endl;
    cout << "You spend " << step << " steps, earn " << score << " points." << endl;
}

void checkfailed() {
    system("clear");

    int x = 0;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            x = max(x, a[i][j]);

    cout << "You lose!" << endl;
    cout << "You spend " << step << " steps, earn " << score << " points, get the largest number with " << (1 << x) << "!" << endl;
}

int main() {
    srand(time(NULL));
    while (isvalid()) {
        makenew();
        print();
        operate();
        checkwon();
    }
    checkfailed();

    return 0;
}
