#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Constants
const int map_size = 11;

const string space_ship = " S ";
const string space = " - ";
const string meteor = " M ";

// Variables
int score = 0;
int player_x = 5;
int player_y = 5;
int meteor_spawn_x;
int meteor_spawn_rate = 5;
int do_meteor_spawn;

char move;

bool collision = false;

// Map
string map[map_size][map_size];

// Meteor locations
string meteor_map[map_size][map_size];

// Map generation
void map_generate() {
    for (int y = 0; y < map_size; ++y) {
        for (int x = 0; x < map_size; ++x) {
            map[y][x] = space;
        }
    }
}

// Map drawing
void map_draw() {
    system("cls");
    map[player_y][player_x] = space_ship;
    for (int y = 0; y < map_size; ++y) {
        for (int x = 0; x < map_size; ++x) {
            cout << map[y][x];
        }
        cout << endl;
    }
    cout << "=-==-==-==-= Score: " << score << " =-==-==-==-=" << endl;
    cout << "Use w, s, a, and d to move: ";
}

// Player movement
void player_movement() {
    map[player_y][player_x] = space;

    cin >> move;

    if (move == 'w') {
        if (player_y != 0) {
            player_y -= 1;
        }
    } else if (move == 's') {
        if (player_y != map_size - 1) {
            player_y += 1;
        }
    } else if (move == 'a') {
        if (player_x != 0) {
            player_x -= 1;
        }
    } else if (move == 'd') {
        if (player_x != map_size - 1) {
            player_x += 1;
        }
    } else {
        cout << "Invalid input! Please use w, s, a, or d." << endl;
    }
    score += 1;
}

// Meteor spawning
void meteor_spawn() {
    for (int x = 0; x < map_size; ++x) {
    	do_meteor_spawn = rand() % meteor_spawn_rate;
    	if (do_meteor_spawn == 1) {
    		map[0][x] = meteor;
		}
	}
}

// Meteor movement
void move_meteors_down() {
    for (int y = map_size - 1; y >= 0; --y) {
        for (int x = 0; x < map_size; ++x) {
            if (map[y][x] == meteor) {
                map[y][x] = space;
                if (y < map_size - 1) {
                    map[y + 1][x] = meteor;
                }
            }
        }
    }
}

// Check if meteor pos == player pos
void check_collision() {
    if (map[player_y][player_x] == meteor) {
        collision = true;
        cout << endl << "Collision with meteor! Game Over!" << endl;
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    map_generate();

    while (!collision) {
        map_draw();
        move_meteors_down();
        meteor_spawn();
        check_collision();
        player_movement();
        check_collision();
    }

    return 0;
}

