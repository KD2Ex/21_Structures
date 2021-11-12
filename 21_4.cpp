#include <iostream>
#include <string>
#include <vector>
using namespace std;

char GameMap [40][40];

struct Character {
    int health;
    int armor;
    int damage;
    string name;
    struct Coordinats {
        int x;
        int y;
    } coordinats;
    bool isPlayer;
};

enum Directions {
    LEFT,
    TOP,
    RIGHT,
    BOTTOM
};


void printGameMap (vector<Character> characters) {
    for (int i = 0; i < 40; i++)
    {
        for (int j = 0; j < 40; j++)
        {
            if (j == characters[0].coordinats.x && i == characters[0].coordinats.y) {
                cout << "P";
                GameMap[i][j] = 'P';
            } else {
                bool f = false;
                for (int k = 1; k < 6; k++)
                {
                    if (j == characters[k].coordinats.x && i == characters[k].coordinats.y) {
                        cout << "E";
                        GameMap[i][j] = 'E';
                        f = true;
                        break;
                    }
                }
                if (!f) {
                    cout << ".";
                    GameMap[i][j] = '.';
                }
            }
        }
        cout << endl;
    }
}

void printPlayerInfo(Character player) {
    cout << "~~~Player's stats~~~" << endl
        << "Health: " << player.health 
        << "Armor: " << player.armor;
}

void printEnemyInfo(Character enemy) {
    cout << enemy.name << " have" << endl
        << "Health: " << enemy.health
        << "Armor: " << enemy.armor;
}

Character& enemyFound (int x, int y, vector<Character>& enemies) {
    for (int i = 1; i < 6; i++)
    {
        if (x == enemies[i].coordinats.x && y == enemies[i].coordinats.y) return enemies[i];
    }
}

int* enemyCoordinates(Character player, int direction) {
    int coordinates[2];
    switch (direction) {
    case LEFT:
        coordinates[0] = player.coordinats.x - 1;
        coordinates[1] = player.coordinats.y;
        break;
    case TOP:
        coordinates[0] = player.coordinats.x;
        coordinates[1] = player.coordinats.y - 1;
        break;
    case RIGHT:
        coordinates[0] = player.coordinats.x + 1;
        coordinates[1] = player.coordinats.y;
        break;
    case BOTTOM:
        coordinates[0] = player.coordinats.x;
        coordinates[1] = player.coordinats.y + 1;
        break;
    default:
        break;
    }
    return coordinates;
}

bool isInputRight(string str) {
    if (str != "left" &&
        str != "right" &&
        str != "top" &&
        str != "bottom") {
        cout << "Wrong direction!" << endl;
        return false;
    }
    return true;
}

void damageCalculation (Character& attacker, Character& defender) {
    defender.armor -= attacker.damage;
    if (defender.armor < 0) {
        defender.health -= defender.armor + attacker.damage;
    }
}

bool isDead (Character& character) {
    if (character.health <= 0) {
        return true;
    } else {
        return false;
    }
}

bool isEndOfMapReached(int direction, Character character) {
    switch (direction) {
    case LEFT:
        if (character.coordinats.x == 0) return false;
    case TOP:
        if (character.coordinats.y == 0) return false;
    case RIGHT:
        if (character.coordinats.x == 39) return false;
    case BOTTOM:
        if (character.coordinats.y == 39) return false;
    }
    // if (!character.isPlayer) {
    //     if ()
    // }

    return true;
}

bool isCharacterAhead(int direction, Character character) {
    switch (direction) {
    case LEFT:
        if (GameMap[character.coordinats.y][character.coordinats.x - 1] != '.') return true;
    case TOP:
        if (GameMap[character.coordinats.y - 1][character.coordinats.x] != '.') return true;
    case RIGHT:
        if (GameMap[character.coordinats.y][character.coordinats.x + 1] != '.') return true;
    case BOTTOM:
        if (GameMap[character.coordinats.y + 1][character.coordinats.x] != '.') return true;
    }
    return false;
}

void attack(Character& character1, Character& character2) {
    cout << "You've engage the " << character2.name << endl;
    damageCalculation(character1, character2);
    printEnemyInfo(character2);
    printPlayerInfo(character1);
}

void move (Character& character, int direction) {
    switch (direction) {
    case LEFT:
        character.coordinats.x--;
        break;
    case TOP:
        character.coordinats.y--;
        break;
    case RIGHT:
        character.coordinats.x++;
        break;
    case BOTTOM:
        character.coordinats.y++;
        break;
    }
}

bool endOfGame(vector<Character> characters) {
    if (isDead(characters[0])) return true;
    else if (characters.size() == 1) return true; 
    else return false;
}



void dataInitialisation(vector<Character>& characters) {
    Character player;
    // string pName;
    // int pArmor;
    // int pHealth;
    // int pDamage;
    player.isPlayer = true;
    cout << "Enter the name\n";
    cin >> player.name;
    cout << "Enter the stats of your character: [Health] [Armor] [Damage]\n";
    cin >> player.health >> player.armor >> player.damage;
    player.coordinats.x = rand() % 40;
    player.coordinats.y = rand() % 40;
    characters.push_back(player);
    
    for (int i = 1; i < 6; i++)
    {
        Character enemy;
        enemy.isPlayer = false;
        enemy.health = rand() % 100 + 50;
        enemy.armor = rand() % 50;
        enemy.damage = rand() % 15 + 15;
        enemy.coordinats.x = rand() % 40;
        enemy.coordinats.y = rand() % 40;
        enemy.name = "Enemy #" + i;
        characters.push_back(enemy);
    }
}

int main() {
    srand(time(NULL));
    vector<Character> characters;
    dataInitialisation(characters);

    printGameMap(characters);

    while (!endOfGame(characters)) {
        cout << "Choose one of 4 directions: [left|top|right|bottom]\n";
        string inputDirecton;
        int direction;
        do {
            cin >> inputDirecton;
        } while (!isInputRight(inputDirecton));
        if (inputDirecton == "left") {
            direction = LEFT;
        } else if (inputDirecton == "top") {
            direction = TOP;
        } else if (inputDirecton == "right") {
            direction = RIGHT;
        } else {
            direction = BOTTOM;
        } 
        if (!isEndOfMapReached(direction, characters[0])) {
            if (!isCharacterAhead(direction, characters[0])) {
                move(characters[0], direction);
            } else {
                int* coord;
                coord = enemyCoordinates(characters[0], direction);
                attack(characters[0], enemyFound(coord[0], coord[1], characters));
            }   
        }
        for (int i = 1; i < 6; i++) {
            int enemyMove = rand() % 4;
            if (!isEndOfMapReached(enemyMove, characters[i])){
                if(!isCharacterAhead(direction, characters[i])) {
                    move(characters[i], enemyMove);
                } else {
                    attack(characters[i], character[0]);
                }
            }
        }
    }
}