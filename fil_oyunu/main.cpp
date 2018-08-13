//#define _CRT_SECURE_NO_WARNINGS
//#define _HAS_ITERATOR_DEBUGGING 0
#include <fstream>
#include <iostream>
#include <math.h>
#include <cstring>
#include <list>
#include <string>
#include <vector>
#define FILENAME "input.txt"
#define MIN 2
#define MAX 64
#define X 8
#define Y 8
using namespace std;

class piece {
public:
	int x = -1, y = -1;
	int id = 0;
	bool situation = false; // put on the board or not
};

void print(piece[Y][X]);
void solution();
void right_top();
void left_top();
void right_bottom();
void left_bottom();
bool flag = false;
list <piece> P;
piece newp, target, temp_target;
piece Board[Y][X];
piece temp[Y][X];
vector<piece>result;
int N = 0;

int main()
{
	setlocale(LC_ALL, "Turkish"); // türkçe karakter
	string buffer;
	ifstream input;
	input.open(FILENAME);
	int i = 0, loc = 0;
	while (getline(input, buffer))
	{
		if (i == 0) {
			i++;
			N = stoi(buffer);
			if ((N < MIN) || (N > MAX)) return 0;
		}
		else {
			loc = buffer.find(' ');
			newp.y = stoi(buffer.substr(0, loc)) - 1;
			newp.x = stoi(buffer.substr(loc)) - 1;
			newp.situation = true;
			newp.id = i;
			Board[newp.y][newp.x] = newp;
			Board[newp.y][newp.x].id = i;
			P.push_back(newp);
			i++;
		}
	}
	for (int i = 0; i < N; i++) {
		solution(); // recursively
		//cout << "-------------------------------" << endl;
	}
	if (result.size() == N) {
		for (size_t i = 0; i < result.size(); i++) {
			if (i == N - 1) cout << result[i].id << endl;
			else cout << result[i].id << "-";
		}
	}
	else cout << "Bütün Taþlarý Alabilecek Bir Hamle Bulunamadý" << endl;
	input.close();
	getchar();
	return 0;
}

void print(piece B[Y][X]) {
	for (int i = 0; i < Y; i++) {
		for (int j = 0; j < X; j++) {
			if (B[i][j].situation == false) cout << "* ";
			else cout << B[i][j].id << " ";
		}
		cout << i << endl;
	}
	for (int j = 0; j < X; j++) cout << j << " ";
	cout << endl;
}

void solution() {
	if (flag == false) {
		if (result.size() == N) {
			/* FOUND A WAY TO GET ALL PIECES */
			return;
		}
		result.clear();
		target = P.front();
		P.pop_front();
		result.push_back(target);
		temp_target = target;
		for (int i = 0; i < Y; i++) for (int j = 0; j < X; j++) temp[i][j] = Board[i][j];
		print(temp);
		temp[temp_target.y][temp_target.x].situation = false;
	}
	flag = false;
	right_bottom();
	left_top();
	left_bottom();
	right_top();
	temp_target = target;
}

void right_top() {
	flag = false;
	temp_target = target;

	while ((temp_target.x - 1 > -1) && (temp_target.y + 1 < Y)) {
		if (temp[temp_target.y + 1][temp_target.x - 1].situation == false) {
			/* NOT FOUND ANY PIECE */
			temp_target.x--; // rt
			temp_target.y++;
		}
		else {
			/* FOUND A PIECE */
			temp[target.y][target.x].situation = false;
			temp_target = temp[temp_target.y + 1][temp_target.x - 1];
			result.push_back(temp_target);
			temp[temp_target.y + 1][temp_target.x - 1].situation = false;
			temp_target.x--;
			temp_target.y++;
			temp_target = result.back();
			target = temp_target;
			//print(temp);
			flag = true;
			solution();
		}
	}
}

void left_top() {
	flag = false;
	temp_target = target;
	while ((temp_target.x - 1 > -1) && (temp_target.y - 1 > -1)) {
		if (temp[temp_target.y - 1][temp_target.x - 1].situation == false) {
			temp_target.x--; // lt
			temp_target.y--;
		}
		else {
			temp[target.y][target.x].situation = false;
			temp_target = temp[temp_target.y - 1][temp_target.x - 1];
			result.push_back(temp_target);
			temp[temp_target.y - 1][temp_target.x - 1].situation = false;
			temp_target.x--;
			temp_target.y--;
			temp_target = result.back();
			target = temp_target;
			//print(temp);
			flag = true;
			solution();
		}
	}
}

void right_bottom() {
	while ((temp_target.x + 1 < X) && (temp_target.y + 1 < Y)) {
		if (temp[temp_target.y + 1][temp_target.x + 1].situation == false) {
			temp_target.x++; // rb
			temp_target.y++;
		}
		else {
			temp[target.y][target.x].situation = false;
			temp_target = temp[temp_target.y + 1][temp_target.x + 1];
			result.push_back(temp_target);
			temp[temp_target.y + 1][temp_target.x + 1].situation = false;
			temp_target.x++;
			temp_target.y++;
			temp_target = result.back();
			target = temp_target;
			//print(temp);
			flag = true;
			solution();
		}
	}
}

void left_bottom() {
	flag = false;
	temp_target = target;
	while ((temp_target.x + 1 < X) && (temp_target.y - 1 > -1)) {
		if (temp[temp_target.y - 1][temp_target.x + 1].situation == false) {
			temp_target.x++; // lb
			temp_target.y--;
		}
		else {
			temp[target.y][target.x].situation = false;
			temp_target = temp[temp_target.y - 1][temp_target.x + 1];
			result.push_back(temp_target);
			temp[temp_target.y - 1][temp_target.x + 1].situation = false;
			temp_target.x++;
			temp_target.y--;
			temp_target = result.back();
			target = temp_target;
			//print(temp);
			flag = true;
			solution();
		}
	}
}