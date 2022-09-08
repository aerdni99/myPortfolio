/*

COPYRIGHT (C) Angelo Indre (4680213) All rights reserved
Final Project
Author. Angelo Indre
        adi19@zips.uakron.edu
Purpose.Entertain with a fun story game

*/

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>

using std::cout;
using std::cin;
using std::array;
using std::endl;
using std::ifstream;
using std::string;
using std::vector;

// Function prototypes

void intro();
void characterBuilder(string a[]);
bool listValidation(string choice, string list);
bool rangeValidation(string choice, string list);
int gameplayType();
string gameplayAction(int type);
int inventory(vector<int> &inv);
void startingArea(string sheet[], vector<int> inv);
void fohrReztTown(string sheet[], vector<int> inv);
void townSquare(string sheet[], vector<int> inv);

int main()
{
    intro();

    string characterSheet[5] = {"Angelo", "male", "blonde", "74", "140"};
    vector<int> inventory = {1, 2, 3, 4};
    characterBuilder(characterSheet);

    // for now, im making the character sheet on the stack because if i make it in character builder, i'll have to run the whole
    // function every test. later, when the game is done, i'll try to allocate it on the heap and use pointers.

     startingArea(characterSheet, inventory);

    // fohrReztTown(characterSheet, inventory);

    return 0;
}
// console out the intro for the game.
void intro()
{
    cout << "_______________________________________________________________________________" << endl;          //title page
    cout << "   Welcome to ASK FOR DIRECTIONS! A short adventure game that uses input and   " << endl;          //The game is not finished story wise, but all the code
    cout << "      output to let you continue your journey home from life on the road.      " << endl;          //constructs are implemented. I did not have time to
    cout << "_______________________________________________________________________________" << endl << endl;  //write and code the whole story into the game
    cout << "                             press enter to start.                             " << endl << endl;  //so this could be considered a demo
    cin.get();
}
/*
the character builder function uses a file containing possible character data and compares it to choices made by the player.
choices are validated and stored in an array that contains all the traits and the name of the character.
This sheet was intended to unlock special gameplay options based on your appearance ie. if you are short enough, you
can fit into really tight spaces. sadly, the story was not developed enough to implement these types of choices.
But with this function already written, these comparisons could easily be implemented in a full game.
*/
void characterBuilder(string a[])       //Character Builder
{
    cout << "Enter your character's name: ";
    cin >> a[0];                                        // All character data will be stored in an array for reference later
    cout << "Create your character:" << endl << endl;
    ifstream traits;
    int i = 1;
    string currentTrait, choice;  // Holds a list of traits, and holds the user's choice
    bool flag = false;  // for validating character info
    traits.open("Character.txt");  // Character file contains the options for your character's appearance.
    if (traits.fail())  //test file opening
        cout << "that didn't work";
    getline(traits, currentTrait);
    while (!traits.eof())
    {
        bool range = false;  // tests for range-based traits height/weight instead of list-based.
        if ((currentTrait == "height (inches)") || (currentTrait == "weight (pounds)"))
        {
            cout << "Choose an integer between the following for your ";
            range = true;
        }
        else
            cout << "Choose one of the following for your ";
        cout << currentTrait << endl;
        getline(traits, currentTrait);
        cout << currentTrait << endl;
        do
        {
            if (flag)
                cout << "please select something from the list: ";
            cin >> a[i];
            if (range)
                flag = rangeValidation(a[i], currentTrait);  // 2 different validation functions for range v.s. list
            else
                flag = listValidation(a[i], currentTrait);
        } while(flag);
        i++; // increment which trait we are choosing
        getline(traits, currentTrait);
    }
    traits.close();
    cout << "Your character sheet reads: " << endl << a[0] << ": ";  // Display choices
    for (i = 1; i < 5; i++)
        cout << a[i] << " ";
    cout << endl << endl;
    cout << "Minus a few of the finer details, your character looks something like this" << endl;
    cout << " O " << endl << "-|-" << endl << " A " << endl;
}
// Accepts a string choice and a string list, compares them to see if the choice is on the list.
bool listValidation(string choice, string list)  // returns true if choice is bad
{

    int test;
    test = list.find(choice);
    if (test == -1)
        return true;
    else
        return false;
}
// Accepts a string choice and a string list, compares them to see if the choice is in the range.
bool rangeValidation(string choice, string range)
{
    int digits = range.find(" ");
    int min, max, intChoice;
    min = stoi(range.substr(0, digits));  // converts the range from string to int for a comparison test.
    max = stoi(range.substr((digits + 1), digits));
    intChoice = stoi(choice);
    if ((min <= intChoice) && (max >= intChoice))
        return false;
    else
        return true;

}
int gameplayType()
{
    bool flag;
    int type;
    while (!flag)  // validation
    {
        cout << "Choose a number for how to proceed." << endl;                          // THE FIRST MAIN DECISION CONSTRUCT FOR GAMEPLAY***
        cout << " __________ __________ __________ __________ __________"  << endl;
        cout << "/          V          V          V          V          \\ " << endl;
        cout << "| 1.Fight  |  2.Move  |3.Interact| 4.search |  5.Item  | " << endl;
        cout << "\\__________A__________A__________A__________A__________/ " << endl;
        cin >> type;
        cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
        if ((1 > type) || (5 < type))
            cout << "Choose from the options.";
        else
            flag = true;
    }
    return type;
}
/*
gamePlay action recieves one of the five base gameplay options from the gameplaychoice function and asks for user input into a string variable.
the function returns any string entered by a player to the room function you are currently in. There, the submission is compared to valid keywords
and gameplay progresses with proper keywords.
*/
string gameplayAction(int type)
{
    static int firstTimer = 0;  // Keeps track of how many times decisions are made, like a tutorial that ends after a timer.
    string action;
    switch (type)  // Each case represents the second branch of the decision construct*** CORE GAMEPLAY
    {
        case 1:
            cout << "How do you wish to fight?" << endl << endl;
            if (firstTimer < 15)
            {
                cout << "a couple standard options are hit, block, dodge, and shoot." << endl;      // tutorial messages based on counter above.
                cout << "Some situations present opportunities for outside the box thinking" << endl;
                cout << "but the game is playable with only standard options" << endl << endl;
                firstTimer++;
            }
            cin >> action;
            cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
            return action;
            break;
        case 2:
            cout << "Where to?" << endl << endl;
            if (firstTimer < 15)
            {
                cout << "You can try to move forward, back, left, or right" << endl << endl;
                firstTimer++;
            }
            cin >> action;
            cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
            return action;
            break;
        case 4:
            cout << "Searching..." << endl << endl;
            cin.get();
            if (firstTimer < 15)
            {
                cout << "Searching is an interesting option because you notice things that aren't clear" << endl;
                cout << "at first glance of a location. Sometimes, searching creates new opportunities or items." << endl;
                firstTimer++;
            }
            action = "searching";
            cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
            return action;
        case 3:
            cout << "with whom?" << endl << endl;
            if (firstTimer < 15)
            {
                cout << "there may come a time when you need to talk to someone in order to get information or trade." << endl << endl;
                firstTimer++;
            }
            cin >> action;
            cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
            return action;
        case 5:
            cout << "opening inventory" << endl << endl;
            if (firstTimer < 15)
            {
                cout << "the inventory is set up in 2 columns. one for the item name, and one for the description" << endl;
                cout << "Choose an item by its number.";
                firstTimer++;
            }
            action = "inventory";
            cout << endl << endl;
            return action;
    }
}
/*
The inventory function was probably the hardest to create, determining which functions needed access to the inventory was difficult, what to store the
inventory in... I decided to use a vector to hold the inventory, and a file to hold all the item data. The file is read one line at a time, and
an item id is compared to all the items in your inventory. If an item ID matches one in your inventory, then the item info comes up, and you have
access to that item. ALl items consume after being interacted with in the inventory function. Even the donkey! They are changed to '-1' once used.
*/
int inventory(vector<int> &inv)
{
    ifstream itemList;
    int check, choice;
    bool itemInList = false;
    string itemDescription;
    itemList.open("Items.txt");
    cout << "____________________________________________________________" << endl;
    while (itemList >> check)
    {
        getline(itemList, itemDescription);
        for (int i = 0; i < inv.size(); i++)
        {
            if (check == inv[i])
            {
                cout << check;
                cout << "  " << itemDescription << endl;
            }
        }
    }
    cout << "____________________________________________________________";
    itemList.close();
    cout << endl << "enter a number from the list to use an item. Enter 0 to exit." << endl;
    cin >> choice;
    if (choice == 0)
        return 0;
    for (int i = 0; i < inv.size(); i++)
    {
        if (choice == inv[i])
        {
            cout << "you used item #" << choice << endl;
            itemInList = true;
            inv[i] = -1;
            return choice;
        }
    }
    if (!itemInList)
        cout << "You do not have that item." << endl;
    return 0;
}
                        // Every function from here down would be an area function.
                        // They are similar, at the very bottom, there is
                        // a template for the branch decisions that would be used for future areas.

/*
the starting area can be revisited with no change to the environment. every standard option has a response
and there is one non-standard option introduced so players know what to look for for these.
The only place you can go from here is Fohr-Rezt Town.
*/
void startingArea(string sheet[], vector<int> inv)
{
    bool noKey = true;
    while (noKey)
    {
        cout << "Traveling down a riverside path, you and Clementine, your trusty donkey companion/best friend," << endl; //room desc.
        cout << "come across a tree with a posted sign." << endl << endl;
        cout << std::setw(50);
        cout << "Fohr-rezt Town straight ahead." << endl << endl;

        int typeChoice = gameplayType();  // Call to gameplay decision construct funcitons.
        string actionChoice = gameplayAction(typeChoice);
        switch (typeChoice)  // These are the unique results of each choice depending on where you are in the game.
        {
            case 1:
                if (actionChoice == "hit")
                {
                    cout << "You swing your mighty sword through the air with great strength" << endl << endl;
                    cout << "cutting the air in two, yet it still does not fall at your feet." << endl << endl;
                    cin.ignore();
                    cin.get();

                }
                if (actionChoice == "block")
                {
                    cout << "You stand ready for anything. After all, you never know who might attack." << endl << endl;
                    cin.ignore();
                    cin.get();
                }
                if (actionChoice == "dodge")
                {
                    cout << "You roll like a tumbleweed across the path." << endl << endl;
                    cout << "Some squirrels judge you from the bushes." << endl << endl;
                    cin.ignore();
                    cin.get();
                }
                if (actionChoice == "shoot")
                {
                    cout << "Embarrassed, you realize you forgot your bow at home." << endl << endl;
                    cout << "You make finger guns to fill the void" << endl << endl;
                    cin.ignore();
                    cin.get();
                }
                break;
            case 2:
                if (actionChoice == "forward")
                {
                    cout << "You urge Clementine forward. She carries you happily towards town." << endl << endl;
                    cout << "Hopefully, someone there can give you directions." << endl << endl;
                    noKey = false;  // This bool ends the while loop meaning that you did something that lets you leave the area.
                    cin.ignore();
                    cin.get();
                }
                if (actionChoice == "back")
                {
                    cout << "Home is definitely not that way." << endl << endl;
                    cin.ignore();
                    cin.get();
                }
                if (actionChoice == "left")
                {
                    cout << "You look to the left at the icy cold river." << endl << endl;
                    cout << "Now is not a good time for a bath." << endl << endl;
                    cin.ignore();
                    cin.get();
                }
                if (actionChoice == "right")
                {
                    cout << "Some squirrels scurry around the forest floor." << endl << endl;
                    cout << "Stay on the path." << endl << endl;
                    cin.ignore();
                    cin.get();
                }
                if (actionChoice == "climb")
                {
                    cout << "Up in the top of the tree you can see two villages. One is close by, with quaint small homes." << endl << endl;
                    cout << "The other looks more like a garbage dump mixed with a campsite. It protrudes from the town like" << endl << endl;
                    cout << "a tumor. You climb back down to the path." << endl << endl;
                    cin.ignore();
                    cin.get();
                }
                break;
            case 3:
                cout << "Life on the road seemed like such a peaceful way to live." << endl << endl;
                cout << "Sadly, I have no one to talk to." << endl << endl;
                cin.ignore();
                cin.get();
                break;
            case 4:
                cout << "You find a nice looking tree that looks very climbable. Almost as if you could MOVE over to it" << endl << endl;
                cout << "and CLIMB to the top." << endl << endl;
                break;
            case 5:
                int selection = inventory(inv);
                if (selection > 0)
                {
                    cout << "Surprisingly, the item consumed. Hopefully that was your intention" << endl << endl;
                }
                cin.ignore();
                cin.get();
                cout << endl << endl;
                break;
        }
    }
    fohrReztTown(sheet, inv);
}
/*
forest town has two states you can enter it in determined by static bool variable scene1. Whether or not you are in scene1 determines whether or not the baker
is present. You are able to die in this area by hitting yourself. When you do, scene1 is set to true so the baker comes back, but your inventory is
not affected.
From here, you can either progress to the final location town square, or go back to the starting area.
Since Town square is a game-ending prison, the only way to break out of scene1 is to go back to the starting area.
*/
void fohrReztTown(string sheet[], vector<int> inv)
{
    static bool scene1 = true;
    bool noKey = true;
    string target, actionChoice;
    int typeChoice;
    if (scene1)
    {
        cout << "Walking into the town, the first thing you see is the remnants of a bakery, smashed and burned." << endl << endl;
        cout << "The BAKER stands at the ruined store front." << endl << endl;
        cin.get();
    }
    else
    {
        cout << "the baker is gone" << endl << endl;
    }
    while (noKey)
    {
        cout << "A sign reads:" << endl << endl;
        cout << std::setw(50);
        cout << "   Welcome to Fohr-Rezt Town!  " << endl << endl;
        cout << std::setw(50);
        cout << "Best bakery in town right here!" << endl << endl;
        cout << std::setw(50);
        cout << "  Town square straight ahead.  " << endl << endl;
        typeChoice = gameplayType();
        actionChoice = gameplayAction(typeChoice);
        switch (typeChoice)
        {
            case 1:
                if (actionChoice == "hit")
                {
                    cout << "Who gets hit?" << endl << endl;
                    cin >> target;
                    if ((target == "me") || (target == sheet[0]))
                    {
                        cout << endl << "You died." << endl << endl << "returning to starting area" << endl << endl;
                        scene1 = true;
                        noKey = false;
                        cin.ignore();
                        cin.get();
                    }
                    if (target == "baker")
                    {
                        cout << "Seeing the sorry state of the baker, your conscience does not allow you to strike." << endl << endl;
                        cin.ignore();
                        cin.get();
                    }
                }
                if (actionChoice == "block")
                {
                    cout << "You stand ready for anything. After all, you never know who might attack." << endl << endl;
                    cin.ignore();
                    cin.get();
                }
                if (actionChoice == "dodge")
                {
                    cout << "Now is not a good time to be fooling around." << endl << endl;
                    cin.ignore();
                    cin.get();
                }
                if (actionChoice == "shoot")
                {
                    cout << "Still no bow :(" << endl << endl;
                    cin.ignore();
                    cin.get();
                }
                break;
            case 2:
                if (actionChoice == "forward")
                {
                    cout << "Maybe someone further in town can give me directions." << endl << endl;
                    cout << "Clementine carries you steadily towards the center of town" << endl << endl;
                    noKey = false;
                    cin.ignore();
                    cin.get();
                }
                if (actionChoice == "back")
                {
                    cout << "You feel too awkward to support the poor Baker in any way." << endl << endl;
                    noKey = false;
                    cin.ignore();
                    cin.get();
                }
                if (actionChoice == "left")
                {
                    cout << "To the left you see a couple houses lucky to have avoided whatever" << endl << endl;
                    cout << "destroyed the bakery." << endl << endl;
                    cin.ignore();
                    cin.get();
                }
                if (actionChoice == "right")
                {
                    cout << "To the right is the Bakery, or what is left of it." << endl << endl;
                    cin.ignore();
                    cin.get();
                }
                break;
            case 3:
                cout << "with whom?" << endl << endl;
                cin >> target;
                if ((target == "baker") && (scene1))
                {
                    cout << "Baker: *sobbing*" << endl;
                }
                else
                    cout << "not a valid target" << endl;
                cin.ignore();
                cin.get();
                break;
            case 4:
                static bool firstLook = true;
                if (firstLook)
                {
                    cout << "Inside the rubble, you uncover a slightly charred, but functional rolling pin." << endl << endl;
                    cout << "Maybe the BAKER could use this ITEM still?";
                    inv.push_back(5);
                    firstLook = false;
                }
                cin.ignore();
                cin.get();
                break;
            case 5:
                int selection = inventory(inv);
                if (selection == 5)
                {
                    cout << "The baker is warmed by your gesture. Even though things are bad, you cheered him up. Good Job!" << endl << endl;
                    selection = 0;
                }
                if (selection > 0)
                {
                    cout << "Surprisingly, the item consumed. Hopefully that was your intention" << endl << endl;
                }
                cin.ignore();
                cin.get();
                break;
        }
    }
    scene1 = false;
    if ((target == "me") || (actionChoice == "back") || (target == sheet[0]))
        startingArea(sheet, inv);
    if (actionChoice == "forward")
        townSquare(sheet, inv);
}
/*
Town square basically constitutes the end of the intro to the game, and also the end of this demo.
once you enter you cannot leave, This function does not lead anywhere and ends the program.
*/
void townSquare(string sheet[], vector<int> inv)
{
    static bool scene1 = true;
    bool noKey = true;
    string target, actionChoice;
    int typeChoice;
    if (scene1)
    {
        cout << "Walking further into the town, you notice a conflict happening at Town Square." << endl << endl;
        cout << "A ROGUE is shaking down a MERCHANT " << endl << endl;
        cout << "ROGUE: Where's the rest of it old man?!" << endl << endl;
        cin.get();
        cout << "MERCHANT: P-please sir I promise that's all I have!" << endl << endl;
        cin.get();
        cout << "ROGUE: You'd better not be lying, I'd hate to repeat what happened to the bakery..." << endl << endl;
        cin.get();
        cout << "MERCHANT: No please! I'm telling the truth!" << endl << endl;
        cin.get();
        cout << "As the rouge is about to rough up the merchant, he notices you riding towards them." << endl << endl;
        cout << "ROGUE: This guy looks more than happy to pay your debts!" << endl << endl;
        cin.get();
        cout << "The rogue advances towards you to fight!" << endl << endl;
        cin.get();
    }
    else
    {
        cout << "The merchant stands at his shop." << endl << endl;
    }
    while (noKey)
    {
        cout << "Town square isn't very big, a merchant table stands next to the WELL in the center." << endl << endl;
        typeChoice = gameplayType();
        actionChoice = gameplayAction(typeChoice);
        switch (typeChoice)
        {
            case 1:
                if (actionChoice == "hit")
                {
                    cout << "Who gets hit?" << endl << endl;
                    cin >> target;
                    if ((target == "me") || (target == sheet[0]))
                    {
                        cout << endl << "You died." << endl << endl << "returning to starting area" << endl << endl;
                        scene1 = true;
                        noKey = false;
                        cin.ignore();
                        cin.get();
                    }
                    if (target == "merchant")
                    {
                        cout << "No way am i hitting this poor old merchant." << endl << endl;
                        cin.ignore();
                        cin.get();
                    }
                    if (target == "rogue")
                    {
                        cout << "you move quickly to strike the rogue, but he has the strength advantage and throws you to the ground." << endl << endl;
                        noKey = false;
                    }
                }
                if (actionChoice == "block")
                {
                    cout << "You raise your shield ready to intercept the rogue's attack, but from behind! a second rogue tackles you!" << endl << endl;
                    noKey = false;
                    cin.ignore();
                    cin.get();
                }
                if (actionChoice == "dodge")
                {
                    cout << "After dodging the first attack, the rogue is ready with a second to throw you to the ground." << endl << endl;
                    noKey = false;
                    cin.ignore();
                    cin.get();
                }
                if (actionChoice == "shoot")
                {
                    cout << "Still no bow :(" << endl << endl;
                    cin.ignore();
                    cin.get();
                }
                break;
            case 2:
                if (actionChoice == "forward")
                {
                    cout << "There is nowhere else to go" << endl << endl;
                    cin.ignore();
                    cin.get();
                }
                if (actionChoice == "back")
                {
                    cout << "There is nowhere else to go" << endl << endl;
                    noKey = false;
                    cin.ignore();
                    cin.get();
                }
                if (actionChoice == "left")
                {
                    cout << "There is nowhere else to go" << endl << endl;
                    cin.ignore();
                    cin.get();
                }
                if (actionChoice == "right")
                {
                    cout << "There is nowhere else to go" << endl << endl;
                    cin.ignore();
                    cin.get();
                }
                break;
            case 3:
                cout << "Not available" << endl << endl;
                cin.ignore();
                cin.get();
                break;
            case 4:
                cout << "there's no time for that" << endl << endl;
                cin.ignore();
                cin.get();
                break;
            case 5:
                cout << "There's no time for that" << endl << endl;
                cin.ignore();
                cin.get();
                break;
        }
    }
    cout << "Wow, all the fight knocked out of you after one blow?" << endl << endl;
    cout << "As your consciousness is fading, you see the rogues taking everything you own.";
    inv.clear();
    cin.get();
    cout << endl << endl << endl << endl;
    cout << "That's all the story we have so far! I hope you enjoyed." << endl << endl;
    cout << "If you're curious, you would wake up with your inventory emptied and a quest to retrieve your donkey in the full game." << endl;
    cin.get();
}

/*
ROOM TEMPLATE

bool noKey = true;
    while (noKey)
    {
        cout << "" << endl << endl;
        int typeChoice = gameplayType();
        string actionChoice = gameplayAction(typeChoice);
        switch (typeChoice)
        {
            case 1:
                if (actionChoice == "hit")
                {
                    cout << "" << endl << endl;
                    cin.ignore();
                    cin.get();
                }
                if (actionChoice == "block")
                {
                    cout << "" << endl << endl;
                    cin.ignore();
                    cin.get();
                }
                if (actionChoice == "dodge")
                {
                    cout << "" << endl << endl;
                    cin.ignore();
                    cin.get();
                }
                if (actionChoice == "shoot")
                {
                    cout << "" << endl << endl;
                    cin.ignore();
                    cin.get();
                }
                break;
            case 2:
                if (actionChoice == "forward")
                {
                    cout << "" << endl << endl;
                    cin.ignore();
                    cin.get();
                }
                if (actionChoice == "backward")
                {
                    cout << "" << endl << endl;
                    cin.ignore();
                    cin.get();
                }
                if (actionChoice == "left")
                {
                    cout << "" << endl << endl;
                    cin.ignore();
                    cin.get();
                }
                if (actionChoice == "right")
                {
                    cout << "" << endl << endl;
                    cin.ignore();
                    cin.get();
                }
                break;
            case 3:
                cout << "";
                cin.ignore();
                cin.get();
                break;
            case 4:
                cout << "";
                cin.ignore();
                cin.get();
                break;
            case 5:
                inventory();
                cin.ignore();
                cin.get();
                break;
        }
    }
*/







