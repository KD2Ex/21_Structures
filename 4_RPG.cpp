#include <iostream>
#include <string>
#include <ostream>
#include <fstream>
#include <vector>
#include <ctime>
using namespace std;

const int PLAYER_INDEX = 0;

struct Character {
    int health;
    int armor;
    int damage;
    string name;
    struct Coordinates {
        int x;
        int y;
    } coordinates;
    bool isPlayer;
};

enum Directions {
    LEFT,
    TOP,
    RIGHT,
    BOTTOM
};


void printGameMap (vector<Character> characters) {
    char GameMap [40][40];
    cout << " ";
    for (int i = 0; i < 40; i++)
    {
        cout << i;
    }
    cout << endl;
    for (int i = 0; i < 40; i++)
    {
        cout << i;
        for (int j = 0; j < 40; j++)
        {
            if (j == characters[0].coordinates.x && i == characters[0].coordinates.y) {
                cout << "P";
                GameMap[i][j] = 'P';
            } else {
                bool f = false;
                for (int k = 1; k < characters.size(); k++)
                {
                    if (j == characters[k].coordinates.x && i == characters[k].coordinates.y) {
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
        << " Armor: " << player.armor 
        << " Damage: " << player.damage << endl;
}

void printEnemyInfo(Character enemy) {
    cout << enemy.name << " have" << endl
        << "Health: " << enemy.health 
        << " Armor: " << enemy.armor 
        << " Damage: " << enemy.damage << endl;
}

int foundCharacterIndex (int x, int y, vector<Character>& characters) {
    for (int i = 0; i < characters.size(); i++) {
        if (x == characters[i].coordinates.x && y == characters[i].coordinates.y) return i;
    }
    return -1;
}

vector<int> enemyCoordinates(Character player, int direction) {
    vector<int> coordinates(2);
    switch (direction) {
        case LEFT:
            coordinates[0] = player.coordinates.x - 1;
            coordinates[1] = player.coordinates.y;
            break;
        case TOP:
            coordinates[0] = player.coordinates.x;
            coordinates[1] = player.coordinates.y - 1;
            break;
        case RIGHT:
            coordinates[0] = player.coordinates.x + 1;
            coordinates[1] = player.coordinates.y;
            break;
        case BOTTOM:
            coordinates[0] = player.coordinates.x;
            coordinates[1] = player.coordinates.y + 1;
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
        str != "bottom" &&
        str != "save" &&
        str != "load") {
        cout << "Wrong direction!" << endl;
        return false;
    } 
    return true;
}

void damageCalculation (Character& attacker, Character& defender) {
    defender.armor -= attacker.damage;
    if (defender.armor < 0) {
        defender.health += defender.armor;
        defender.armor = 0;
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
            if (character.coordinates.x == 0) return true;
            break;
        case TOP:
            if (character.coordinates.y == 0) return true;
            break;
        case RIGHT:
            if (character.coordinates.x == 39) return true;
            break;
        case BOTTOM:
            if (character.coordinates.y == 39) return true;
            break;
    }

    return false;
}

bool isPlayerAhead(int direction, vector<Character> characters, int index = 0) {

    int x = characters[index].coordinates.x;
    int y = characters[index].coordinates.y;
    int playerX = characters[PLAYER_INDEX].coordinates.x;
    int playerY = characters[PLAYER_INDEX].coordinates.y;
    switch (direction) {
        case LEFT:
            if (playerX == x - 1 && playerY == y) return true;
            break;
        case TOP:
            if (playerX == x && playerY == y - 1) return true;
            break;
        case RIGHT:
            if (playerX == x + 1 && playerY == y) return true;
            break;
        case BOTTOM:
            if (playerX == x && playerY == y + 1) return true;
            break;
    }
    return false;
}

bool isSquareClear(int x, int y, vector<Character> characters) {
    for (int i = 0; i < characters.size(); i++) {
        if (characters[i].coordinates.x == x && characters[i].coordinates.y == y) return false;
    }
    return true;
}

bool isCharacterAhead(int direction, vector<Character> characters, int index = 0) {
    int x = characters[index].coordinates.x;
    int y = characters[index].coordinates.y;
    switch (direction) {
        case LEFT:
            if (!isSquareClear(x - 1, y, characters))
                return true;
            break;
        case TOP:
            if (!isSquareClear(x, y - 1, characters)) 
                return true;
            break;
        case RIGHT:
            if (!isSquareClear(x + 1, y, characters)) 
                return true;
            break;
        case BOTTOM:
            if (!isSquareClear(x, y + 1, characters)) 
                return true;
            break;
    }

    return false;
}

void playerAttack(Character& player, Character& enemy) {
    cout << "You've engaged the " << enemy.name << endl;
    printEnemyInfo(enemy);
    damageCalculation(player, enemy);
    cout << "You've dealt " << player.damage << endl;
}

void enemyAttack(Character& enemy, Character& player) {
    cout << enemy.name << " engaging you\n";
    printEnemyInfo(enemy);
    damageCalculation(enemy, player);
    printPlayerInfo(player);
}

void move (Character& character, int direction) {
    switch (direction) {
        case LEFT:
            character.coordinates.x--;
            break;
        case TOP:
            character.coordinates.y--;
            break;
        case RIGHT:
            character.coordinates.x++;
            break;
        case BOTTOM:
            character.coordinates.y++;
            break;
    }
}

bool endOfGame(vector<Character> characters) {
    if (isDead(characters[0])) {
        cout << "You died";
        return true;
    } 
    else if (characters.size() == 1) {
        cout << "You won!";
        return true; 
    } 
    else return false;
}

void dataInitialisation(vector<Character>& characters) {
    Character player;
    player.isPlayer = true;

    cout << "Enter the name\n";
    cin >> player.name;
    cout << "Enter the stats of your character: [Health] [Armor] [Damage]\n";
    cin >> player.health >> player.armor >> player.damage;

    player.coordinates.x = rand() % 40;
    player.coordinates.y = rand() % 40;
    characters.push_back(player);
    
    for (int i = 1; i < 6; i++)
    {
        Character enemy;
        int enemyX;
        int enemyY;
        do {
            enemyX = rand() % 40;
            enemyY = rand() % 40;
        } while(!isSquareClear(enemyX, enemyY, characters));
        enemy.coordinates.x = enemyX;
        enemy.coordinates.y = enemyY;
        enemy.isPlayer = false;
        enemy.health = rand() % 100 + 50;
        enemy.armor = rand() % 50;
        enemy.damage = rand() % 15 + 15;
        enemy.name = "Enemy #" + to_string(i);
        characters.push_back(enemy);
    }
}

void saveCharacter(ofstream& file, vector<Character>& characters) {
    int charactersCount = characters.size();
    file.write((char*)&charactersCount, sizeof(charactersCount));
    for (int i = 0; i < charactersCount; i++) {
        int len = characters[i].name.length();
        file.write((char*)&len, sizeof(len));
        file.write(characters[i].name.c_str(), characters[i].name.length());
        file.write((char*)&characters[i].health, sizeof(characters[i].health));
        file.write((char*)&characters[i].armor, sizeof(characters[i].armor));
        file.write((char*)&characters[i].damage, sizeof(characters[i].damage));
        file.write((char*)&characters[i].coordinates.x, sizeof(characters[i].coordinates.x));
        file.write((char*)&characters[i].coordinates.y, sizeof(characters[i].coordinates.y));
        file.write((char*)&characters[i].isPlayer, sizeof(characters[i].isPlayer));
    }
    
}

void loadCharacter(ifstream& file, vector<Character>& characters) {
    int charactersCount = 0;
    file.read((char*)&charactersCount, sizeof(charactersCount));
    characters.clear();
    characters.resize(charactersCount);
    for (int i = 0; i < characters.size(); i++) {
        int len;
        file.read((char*)&len, sizeof(len));
        characters[i].name.resize(len);
        file.read((char*)characters[i].name.c_str(), len);
        file.read((char*)&characters[i].health, sizeof(characters[i].health));
        file.read((char*)&characters[i].armor, sizeof(characters[i].armor));
        file.read((char*)&characters[i].damage, sizeof(characters[i].damage));
        file.read((char*)&characters[i].coordinates.x, sizeof(characters[i].coordinates.x));
        file.read((char*)&characters[i].coordinates.y, sizeof(characters[i].coordinates.y));
        file.read((char*)&characters[i].isPlayer, sizeof(characters[i].isPlayer));
    }
}

//Character getCharacterByCoordinates(int x, int y, vector<Character> characters) {
//    Character character;
//    for (int i = 0; i < characters.size(); i++)
//    {
//        if (x == characters[i].coordinates.x && y == characters[i].coordinates.y) character = characters[i];
//    }
//    return character;
//}

int main() {
    srand(time(nullptr));
    vector<Character> characters;
    dataInitialisation(characters);

    while (!endOfGame(characters)) {
        printGameMap(characters);
        cout << "Choose one of 4 directions: [left|top|right|bottom]\n";
        string inputDirection;
        int direction;

        do {
            cin >> inputDirection;
        } while (!isInputRight(inputDirection));

        if (inputDirection == "left") {
            direction = LEFT;
        } else if (inputDirection == "top") {
            direction = TOP;
        } else if (inputDirection == "right") {
            direction = RIGHT;
        } else if (inputDirection == "bottom") {
            direction = BOTTOM;
        } else if (inputDirection == "save") {
            ofstream saveFile("save.bin", ios::binary);
            if (saveFile.is_open()) {
                saveCharacter(saveFile, characters);
                saveFile.close();
            } else {
                cout << "Cannot open the file\n";
            }
            continue;
        } else if (inputDirection == "load") {
            ifstream loadFile("save.bin", ios::binary);
            if (loadFile.is_open()) {
                loadCharacter(loadFile, characters);
                loadFile.close();
            } else {
                cout << "Cannot open the file\n";
            }
            continue;
        }

        if (!isEndOfMapReached(direction, characters[0])) {
            if (!isCharacterAhead(direction, characters, PLAYER_INDEX)) {
                move(characters[0], direction);
            } else {
                vector<int> coord = enemyCoordinates(characters[0], direction);
                int enemyIndex = foundCharacterIndex(coord[0], coord[1], characters);
                playerAttack(characters[0], characters[enemyIndex]);
                if (isDead(characters[enemyIndex])) {
                    cout << characters[enemyIndex].name << " has been slain" << endl;
                    characters.erase(characters.begin() + enemyIndex);
                }
            }   
        }

        for (int i = 1; i < characters.size(); i++) {
            int enemyMove = rand() % 4;
            if (!isEndOfMapReached(enemyMove, characters[i])){
                if(!isCharacterAhead(enemyMove, characters,i)) {
                    move(characters[i], enemyMove);
                } else {
                    if (isPlayerAhead(enemyMove, characters,i)) {
                        enemyAttack(characters[i], characters[0]);
                    }
                }
            }
        }
    }
}