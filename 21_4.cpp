#include <iostream>
#include <string>
#include <ostream>
#include <fstream>
#include <vector>
using namespace std;

char GameMap [10][10];
const int PLAYER_INDEX = 0;


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
    BOTTOM,
    WAIT
};


void printGameMap (vector<Character> characters) {
    cout << " ";
    for (int i = 0; i < 10; i++)
    {
        cout << i;
    }
    cout << endl;
    for (int i = 0; i < 10; i++)
    {
        cout << i;
        for (int j = 0; j < 10; j++)
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
    for (int i = 0; i < characters.size(); i++)
    {
        if (x == characters[i].coordinats.x && y == characters[i].coordinats.y) return i;
    }
    return -1;
}

vector<int> enemyCoordinates(Character player, int direction) {
    vector<int> coordinates(2);
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
        str != "bottom" && 
        str != "w" &&
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
        if (character.coordinats.x == 0) return true;
        break;
    case TOP:
        if (character.coordinats.y == 0) return true;
        break;
    case RIGHT:
        if (character.coordinats.x == 9) return true;
        break;
    case BOTTOM:
        if (character.coordinats.y == 9) return true;
        break;
    }
    // if (!character.isPlayer) {
    //     if ()
    // }

    return false;
}

bool isPlayerAhead(int direction, vector<Character> characters, int index = 0) {

    int x = characters[index].coordinats.x;
    int y = characters[index].coordinats.y;
    int playerX = characters[PLAYER_INDEX].coordinats.x;
    int playerY = characters[PLAYER_INDEX].coordinats.y;
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
    // switch (direction) {
    //     case LEFT:
    //         if (GameMap[character.coordinats.y][character.coordinats.x - 1] == 'P') return true;
    //         break;
    //     case TOP:
    //         if (GameMap[character.coordinats.y - 1][character.coordinats.x] == 'P') return true;
    //         break;
    //     case RIGHT:
    //         if (GameMap[character.coordinats.y][character.coordinats.x + 1] == 'P') return true;
    //         break;
    //     case BOTTOM:
    //         if (GameMap[character.coordinats.y + 1][character.coordinats.x] == 'P') return true;
    //         break;
    // }
    return false;
}

bool isSquareClear(int x, int y, vector<Character> characters) {
    for (int i = 0; i < characters.size(); i++) {
        if (characters[i].coordinats.x == x && characters[i].coordinats.y == y) return false;
    }
    return true;
}

bool isCharacterAhead(int direction, vector<Character> characters, int index = 0) {
//     if (character.isPlayer) {
//         switch (direction) {
//             case LEFT:
//                 if (GameMap[character.coordinats.y][character.coordinats.x - 1] == 'E') return true;
//             case TOP:
//                 if (GameMap[character.coordinats.y - 1][character.coordinats.x] == 'E') return true;
//             case RIGHT:
//                 if (GameMap[character.coordinats.y][character.coordinats.x + 1] == 'E') return true;
//             case BOTTOM:
//                 if (GameMap[character.coordinats.y + 1][character.coordinats.x] == 'E') return true;
//         }
//     } else {
//         switch (direction) {
//             case LEFT:
//                 if (GameMap[character.coordinats.y][character.coordinats.x - 1] == 'P') return true;
//             case TOP:
//                 if (GameMap[character.coordinats.y - 1][character.coordinats.x] == 'P') return true;
//             case RIGHT:
//                 if (GameMap[character.coordinats.y][character.coordinats.x + 1] == 'P') return true;
//             case BOTTOM:
//                 if (GameMap[character.coordinats.y + 1][character.coordinats.x] == 'P') return true;
//         }
//     }
    int x = characters[index].coordinats.x;
    int y = characters[index].coordinats.y;
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
    //printPlayerInfo(player);
    
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
        case WAIT:
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
    // string pName;
    // int pArmor;
    // int pHealth;
    // int pDamage;
    player.isPlayer = true;
    cout << "Enter the name\n";
    cin >> player.name;
    cout << "Enter the stats of your character: [Health] [Armor] [Damage]\n";
    cin >> player.health >> player.armor >> player.damage;
    player.coordinats.x = rand() % 10;
    player.coordinats.y = rand() % 10;
    characters.push_back(player);
    
    for (int i = 1; i < 6; i++)
    {
        Character enemy;
        int enemyX;
        int enemyY;
        do {
            enemyX = rand() % 10;
            enemyY = rand() % 10;
        } while(!isSquareClear(enemyX, enemyY, characters));
        enemy.coordinats.x = enemyX;
        enemy.coordinats.y = enemyY;
        enemy.isPlayer = false;
        enemy.health = rand() % 100 + 50;
        enemy.armor = rand() % 50;
        enemy.damage = rand() % 15 + 15;
        enemy.name = "Enemy #" + to_string(i);
        characters.push_back(enemy);
    }
}

int printedEnemiesCount() {

    int count = 0;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++)
        {
            if (GameMap[i][j] == 'E') count++;
        }
    }
    return count;
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
        file.write((char*)&characters[i].coordinats.x, sizeof(characters[i].coordinats.x));
        file.write((char*)&characters[i].coordinats.y, sizeof(characters[i].coordinats.y));
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
        file.read((char*)&characters[i].coordinats.x, sizeof(characters[i].coordinats.x));
        file.read((char*)&characters[i].coordinats.y, sizeof(characters[i].coordinats.y));
        file.read((char*)&characters[i].isPlayer, sizeof(characters[i].isPlayer));
    }
}

Character character(int x, int y, vector<Character> characters) {
    Character character;
    for (int i = 0; i < characters.size(); i++)
    {
        if (x == characters[i].coordinats.x && y == characters[i].coordinats.y) character = characters[i];
    }
    return character;
}

int main() {
    srand(time(nullptr));
    vector<Character> characters;
    dataInitialisation(characters);
    

    //saveCharacter(file, characters);
    
    //loadCharacter(file2, characters);
    while (!endOfGame(characters)) {
        printGameMap(characters);
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
        } else if (inputDirecton == "bottom") {
            direction = BOTTOM;
        } else if (inputDirecton == "save") {
            ofstream file("save.bin", ios::binary);
            saveCharacter(file, characters);
            file.close();
            continue;
        } else if (inputDirecton == "load") {
            ifstream file2("save.bin", ios::binary);
            loadCharacter(file2, characters);
            file2.close();
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
                    
                    //Delete enemy from vector;
                    cout << characters[enemyIndex].name << " has been slain" << endl;
                    characters.erase(characters.begin() + enemyIndex);
                    //characters.pop
                    //characters.resize(character.size() - 1);
                }
            }   
        }
        for (int i = 1; i < 6; i++) {
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
        // int size = characters.size();

        // if (printedEnemiesCount() != (size - 1) ) {
        //     for (int i = 0; i < characters.size(); i++)
        //     {
        //         cout << characters[i].name << endl;
        //         cout << characters[i].coordinats.x << " " << characters[i].coordinats.y << endl;
        //     }
            
        // }
    }
}