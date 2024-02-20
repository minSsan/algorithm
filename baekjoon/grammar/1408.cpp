#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string start_time, end_time;
    cin >> start_time >> end_time;

    int hours, minutes, seconds;
    vector<int> start_time_int;
    vector<int> end_time_int;

    hours = ((end_time[0] - '0') * 10 + (end_time[1] - '0')) - ((start_time[0] - '0') * 10 + (start_time[1] - '0'));
    minutes = ((end_time[3] - '0') * 10 + (end_time[4] - '0')) - ((start_time[3] - '0') * 10 + (start_time[4] - '0'));
    seconds = ((end_time[6] - '0') * 10 + (end_time[7] - '0')) - ((start_time[6] - '0') * 10 + (start_time[7] - '0'));

    if (seconds < 0) {
        seconds += 60;
        minutes -= 1;
    }

    if (minutes < 0) {
        minutes += 60;
        hours -= 1;
    }

    if (hours < 0) {
        hours += 24;
    }

    if (hours < 10) {
        cout << '0' << hours << ':';
    } else {
        cout << hours << ':';
    }

    if (minutes < 10) {
        cout << '0' << minutes << ':';
    } else {
        cout << minutes << ':';
    }

    if (seconds < 10) {
        cout << '0' << seconds << '\n';
    } else {
        cout << seconds << '\n';
    }

    return 0;
}