 /*
    Description: Property Property is a turn-based two-player game with 10 spaces.
    Programmed by: Rafael Antonio M. Austria S15B
    Last modified: 2/06/2022
    Version: 4
    [Acknowledgements: Learning random number generator- https://www.youtube.com/watch?v=ZaZxHzRn-AY&t=315s
                       Learning Structs- https://www.youtube.com/watch?v=7zXqMD6Fj_E&list=LL&index=12
                                       - https://www.youtube.com/watch?v=-Vy4qrl675E&t=76s
                       Learning to slow down code - https://www.youtube.com/watch?v=SjOPUr7Bkmo&list=LL&index=5
                                                  - https://www.youtube.com/watch?v=SGYPtfH5o-0]
    This is to certify that this project is my own work, based on my personal efforts in studying and applying the concepts
    learned. I have constructed the functions and their respective algorithms and corresponding code all by myself. The
    program was run, tested, and debugged by my own efforts. I further certify that I have not copied in part or whole
    or otherwise plagiarized the work of other students and/or persons.
    Rafael Antonio M. Austria 
    DLSU ID 12194085
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <unistd.h>

#define startingPosition 0;
#define ownerNumPlayer1 1;
#define renoNumPlayer1 3;
#define ownerNumPlayer2 2;
#define renoNumPlayer2 4;

/*
    This struct function houses the players variables with values that are defined in later functions
    Members//
    name is the displayed name of player.
    is_jailed is the state whether the player is jailed or not.
    money is the players currency in-game.
    position is the current location of the player's position.
    owner_num is the value of the players owned property.
    reno_num is the value of the players renovated property.
    is_bankrupt is the state whether the player is bankrupt or not.
*/
struct Player
{
    char name[40];
    bool is_jailed;
    bool is_bankrupt;
    int money;
    int position;
    int owner_num;
    int reno_num;
};

/*
    This function sets up the players with default values.
    @param player1 is the pointer variable for player 1.
    @param player2 is the pointer variable for player 2.
    /Members/
    is_jailed is the state whether the player is jailed or not.
    money is the players currency in-game.
    position is the current location of the player's position.
    owner_num is the value of the players owned property.
    reno_num is the value of the players renovated property.
    is_bankrupt is the state whether the player is bankrupt or not.
    name is the displayed name of player.
*/
void set_up_players(struct Player *player1, 
                    struct Player *player2)
{
    strcpy_s(player1->name, sizeof(player1->name), "Player 1");
    player1->is_jailed = false;
    player1->position = startingPosition;
    player1->owner_num = ownerNumPlayer1;
    player1->reno_num = renoNumPlayer1;
    player1->is_bankrupt = false;
    strcpy_s(player2->name, sizeof(player2->name), "Player 2");
    player2->is_jailed = false;
    player2->position = startingPosition;
    player2->owner_num = ownerNumPlayer2;
    player2->reno_num = renoNumPlayer2;
    player2->is_bankrupt = false;
}

/*
    This function shows the Cost of the property, renovation cost, and resell cost of a property if a user lands on that property.
    @param player is the pointer variable for the current player playing
    @param property_tracker is the pointer variable for the list of properties that are owned, unowned, and renovated by players
    @param renovateCost is the pointer variable for the value of the cost of the renovate
    Members//
    position is dependent on what to display for the current property
*/
void print_property_desc(struct Player *player, 
                        int* property_tracker, 
                        int *renovateCost)
{
    int cost = (player->position % 7) * 20;
    int resell = cost / 2;
    int property_num = 0;
    int temp = *property_tracker;
    switch (player->position) 
    {
        case 0:
        {
            break;
        }
        case 1:
        {
            printf("Renovate cost: $%d\n", *renovateCost);
            break;
        }
        case 2:
        {
            cost = 150;
            resell = cost / 2;
            break;
        }
        case 3:
        {
            printf("Renovate cost: $%d\n", *renovateCost);
            break;
        }
        case 4:
        {
            break;
        }
        case 5:
        {
            printf("Renovate cost: $%d\n", *renovateCost);
            break;
        }
        case 6:
        {
            break;
        }
        case 7:
        {
            cost = 100;
            resell = cost / 2;
            break;
        }
        case 8:
        {
            printf("Renovate cost: $%d\n", *renovateCost);
            break;
        }
        case 9:
        {
            printf("Renovate cost: $%d\n", *renovateCost);
            break;
        }
    }
    if(player->position == 6)
    {
        usleep(75000);
    }
    else if(player->position == 4)
    {
        usleep(75000);
    }
    else if(player->position == 0)
    {
        usleep(75000);
    }else
    {
        printf("Cost: $%d\n", cost);
        printf("Resell: $%d\n", resell);
        for (int i = 0; i < player->position; i++) 
        {
            property_num = *property_tracker % 10;
            *property_tracker /= 10;
        }
        if (property_num == 1 || property_num == 3) {
            printf("Player 1 owns this.\n");
        }else if (property_num == 2 || property_num == 4) {
            printf("Player 2 owns this.\n");
        }else {
            sleep(1);
        }
        *property_tracker = temp;
    }
}

/*
    This function updates the players position in the board after every turn and returns die for other functions.
    @param player is the pointer value for the current player
    @param property_tracker is the pointer variable for the list of properties that are owned,
    unowned, and renovated by players
    @param renovateCost is the pointer variable for the value of the cost of the renovate
    Members//
    position is updated with the value of die to give movement to the player
    money is updated if the player lands or passed by property 0
*/
int move(struct Player *player, 
        int *property_tracker, 
        int *renovateCost)
{
    int die = (rand()%6) + 1; 
    int r = 0;
    printf("Rolling");
    for (r = 0; r <= 3; r++)
    {
        usleep(500000);
        printf(".");
    }
    sleep(2);
    printf("You rolled %d!\n", die);
    sleep(1);
    player->position = 6;//+= die;
    if(player->position > 9)
    {
        player->position -= 10;
        player->money += 2;
        printf("You recieved $2!\n");
        sleep(1);
        printf("New balance: $%d\n", player->money);
        sleep(2);
    }
    printf("You landed at Position %d: ", player->position);
    int i = player->position;
    switch (i) {
            case 0: {
                printf("Go\n");
                system("pause");
                system("cls");               
                break;
            }
            case 1: {
                printf("Tree House\n");              
                break;
            }
            case 2: {
                printf("Electric Company\n");
                break;
            }
            case 3: {
                printf("Beach House\n");
                break;
            }
            case 4: {
                printf("Jail Time\n");
                break;
            }
            case 5: {
                printf("Castle\n");
                break;
            }
            case 6: {
                printf("Feelin' Luck\n");
                break;
            }
            case 7: {
                printf("Rail Road\n");
                break;
            }
            case 8: {
                printf("Igloo\n");
                break;
            }
            case 9: {
                printf("Farm House\n");
                break;
            }
        }
    print_property_desc(player, property_tracker, renovateCost);
    return die;
}

/*
    This function displays a choice whether to buy the property or end turn and updates the 
    property tracker if the current player buys the property.
    @param player is the pointer value for the current player
    @param property_tracker is the pointer variable for the list of properties that areowned,
    unowned, and renovated by players
    Members//
    position is dependent for the buy function to update the property_tracker
    owner_num replaces the value of the current property in the property_tracker from 0 to the 
    players owner value
*/
void buy(struct Player *player, 
        int *property_tracker)
{
    int choice = 0;
    do
    {
        sleep(1);
        printf("[1] Buy\n[2] End turn\n");
        printf("Choice: ");
        scanf("%d", &choice);
    } while (choice != 1 && choice != 2);
    if(choice == 1)
    {
        int property = player->owner_num * pow(10, player->position - 1);
        int i = player->position;
        switch (i) {
            case 1: {
                if (player->money >= 20 * (i % 7))
                {
                player->money -= 20 * (i % 7);
                *property_tracker += property;
                sleep(1);
                printf("You bought the Tree House!\n");
                }else
                {
                    printf("Not enough money.\n");
                }
                sleep(1);
                system("pause");
                system("cls");         
                break;
            }
            case 2: {
                if (player->money >= 150)
                {
                player->money -= 150;
                *property_tracker += property;
                sleep(1);
                printf("You bought the Electric Company!\n");
                }else
                {
                    printf("Not enough money.\n");
                }
                sleep(1); 
                system("pause");   
                system("cls");     
                break;
            }
            case 3: {
                if (player->money >= 20 * (i % 7))
                {
                player->money -= 20 * (i % 7);
                *property_tracker += property;
                sleep(1);
                printf("You bought the Beach House!\n");
                }else
                {
                    printf("Not enough money.\n");
                }  
                sleep(1);
                system("pause");
                system("cls");       
                break;
            }
            case 5: {
                if (player->money >= 20 * (i % 7))
                {
                player->money -= 20 * (i % 7);
                *property_tracker += property;
                sleep(1);
                printf("You bought the Castle!\n");
                }else
                {
                    printf("Not enough money.\n");
                }
                sleep(1);    
                system("pause");
                system("cls");     
                break;
            }
            case 7: {
                if (player->money >= 100)
                {
                player->money -= 100;
                *property_tracker += property;
                sleep(1);
                printf("You bought the Rail Road!\n");
                }else
                {
                    printf("Not enough money.\n");
                }
                sleep(1);
                system("pause");
                system("cls");    
                break;
            }
            case 8: {
                if (player->money >= 20 * (i % 7))
                {
                player->money -= 20 * (i % 7);
                *property_tracker += property;
                sleep(1);
                printf("You bought the Igloo!\n");
                }else
                {
                    printf("Not enough money.\n");
                }
                sleep(1);
                system("pause");
                system("cls");         
                break;
            }
            case 9: {
                if (player->money >= 20 * (i % 7))
                {
                player->money -= 20 * (i % 7);
                *property_tracker += property;
                sleep(1);
                printf("You bought the Farm House!\n");
                }else
                {
                    printf("Not enough money.\n");
                }
                sleep(1);
                system("pause");
                system("cls");         
                break;
            }
        }
    }else
    {
        sleep(1);
        printf("You ended turn.\n");
        system("cls");
    }
}

/*
    This function displays a choice whether the players owned property is to be renovated or 
    not and updates the property tracker if the player chooses to renovate.
    @param player is the pointer value for the current player
    @param property_tracker is the pointer variable for the list of properties that are owned, 
    unowned, and renovated by players 
    @param renovateCost is the pointer variable for the value of the cost of the renovate
    Members//
    position calls for the renovation function on a owned property to update the property_tracker 
    if the player chooses to renovate 
             and is exclusive to property 2 and 7 as they cannot be renovated
    owner_num replaces the value of the current property in the property_tracker from 0 to the 
    players owner value
*/
void renovate(struct Player *player, 
            int *property_tracker , 
            int *renovateCost)
{
    int choice = 0;
    if(player->position != 2 && player->position != 7)
    {
        do
        {
            sleep(1);
            printf("[1] Renovate\n[2] End turn\n");
            printf("Choice: ");
            scanf("%d", &choice);
        } while (choice != 1 && choice != 2);
        if(choice == 1 && player->money >= *renovateCost)
        {
            int property = 2 * pow(10, player->position - 1);
            *property_tracker += property;
            printf("You renovated property!\n");
        }
        else if(choice == 1 && player->money < *renovateCost)
        {
            sleep(1);
            printf("You do not have enough money for Renovation!\n");
            sleep(2);
        }else
        {
            sleep(1);
            printf("You ended turn.\n");
            sleep(2);
        }
    }else
    {
        printf("You cannot renovate this.\n");
    }
    system("pause");
    system("cls");
}

/*
    This function is only called if the players money is not enough for rent or for lucky die. It displays each property owned 
    by the player from the property_tracker and gives a choice on which one to sell
    and atleast one property is needed to be sold.
    @param player is the pointer value for the current player
    @param property_tracker is the pointer variable for the list of properties that are owned, 
    unowned, and renovated by players  
    Members//
    owner_num is the players owned property from the property_tracker.
    reno_num is the players renovated property from the property_tracker.
    money is updated only after the player chooses one of their properties to be sold.
*/
void sell(struct Player *player, 
        int *property_tracker)
{
    int temp = *property_tracker;
    int property_num = 0;
    int properties_not_sold = 0;
    int no_property_to_sell = 0;
    int choice = 0;
    for(int i = 1; i < 10; i++)
        {
            property_num = *property_tracker % 10;
            if(property_num == player->owner_num || property_num == player->reno_num)
            {
                do {
                    sleep(1);
                    printf("Sell: Property %d\n", i);
                    printf("[1] Sell\n[2] Not Sell\n");
                    printf("Choice: ");
                    scanf("%d", &choice);
                } while (choice != 1 && choice != 2);
                if(choice == 1)
                {
                    sleep(1);
                    printf("Selling your property");
                    for (int f = 0; f <= 3; f++)
                    {
                        sleep(1);
                        printf(".");
                    } 
                    sleep(1);
                    printf("You sold property %d!\n", i);
                    if(i == 2)
                    {
                        player->money += 100 / 2;
                        temp -= (property_num * pow(10, i-1));
                        i = 10;
                    }
                    else if(i == 7)
                    {
                        player->money += 100 / 2;
                        temp -= (property_num * pow(10, i-1));
                        i = 10;
                    }else
                    {
                        player->money += (((i + 1) % 7) * 20) / 2;
                        temp -= (property_num * pow(10, i-1));
                        i = 10; 
                    }
                    properties_not_sold = 0;
                }else
                {
                    properties_not_sold++;
                }
            }else
            {
                no_property_to_sell++;
            }
            *property_tracker /= 10;
        }
        *property_tracker = temp;
    if(properties_not_sold > 0)
    {
        printf("You have to sell since you dont have money.\n");
        sleep(1);
        sell(player, property_tracker);
    }
    else if(no_property_to_sell == 9)
    {
        sleep(1);
        printf("You have no property.\n");
        printf("You are bankrupt.\n");
        sleep(1);
        player->is_bankrupt = 1;
        system("pause");
    }
}

/* 
    This function is called when the player lands on the opposing players owned property and 
    displays that the current player has paid rent.
    @param die is the variable that adds to the players position to move
    @param owner is the pointer value of the opposing players owned property
    @param visitor is the pointer value of the player that lands on the opposing players owned 
    property
    @param property_tracker is the pointer variable for the list of properties that are owned, 
    unowned, and renovated by players 
    @param property_num is current number of the property in the property_tracker
    @param railroadRent is the pointer variable for the value of rail road
    @param elecMultiplier is the pointer variable for the value that the die is multiplied to 
    compute the rent for the electric company
    Members//
    position calls rent if the visitor lands on owner property
    money is subtracted from the visitor and is added to the owners balance

*/
void rent(int die, 
        struct Player *owner, 
        struct Player *visitor, 
        int *property_tracker, 
        int property_num, 
        int *railroadRent, 
        int *elecMultiplier)
{
    int canPay;
    int moneyOwned = 0;
    int electricMoneyOwned = die * *elecMultiplier;
    do{
        canPay = 1;
            if(visitor->position == 2 && visitor->money >= electricMoneyOwned)
            {
                visitor->money -= electricMoneyOwned;
                owner->money += electricMoneyOwned;
                sleep(1);
                printf("You paid rent for $%d\n", electricMoneyOwned);
                sleep(2);
                system("pause");
                system("cls");
            }else if(visitor->position == 7 && visitor->money >= *railroadRent)
            {
                int temp = *railroadRent;
                visitor->money -= *railroadRent;
                owner->money += *railroadRent;
                *railroadRent = temp;
                sleep(1);
                printf("You paid rent for $%d\n", *railroadRent);
                sleep(2);
                system("pause");
                system("cls");
            }else if(property_num == owner->owner_num && visitor->money >= 20 * (visitor->position % 7) / 5)
            {
                moneyOwned = 20 * (visitor->position % 7) / 5;
                visitor->money -= moneyOwned;
                owner->money += moneyOwned;
                sleep(1);
                printf("You paid rent for $%d\n", moneyOwned);
                sleep(2);
                system("pause");
                system("cls");
            }else if(property_num == owner->reno_num && visitor->money >= (20 * (visitor->position % 7) / 5) * 2 + 1)
            {
                moneyOwned = (20 * (visitor->position % 7) / 5) * 2 + 1;
                visitor->money -= moneyOwned;
                owner->money += moneyOwned;
                sleep(1);
                printf("You paid rent for $%d\n", moneyOwned);
                sleep(2);
                system("pause");
                system("cls");
            }else
            {
                canPay = 0;
                sleep(2);
                printf("You do not have enough money for rent.\n");
                if(canPay == 0)
                {
                    sell(visitor, property_tracker);
                }
            }
    }while(canPay == 0 && visitor->is_bankrupt == false);
}

/*  
    This function checks the property_tracker integer by integer to check if the property is owned, 
    unowned and renovated to know what functions to call.
    @param player is the pointer value for the current player.
    @param opposingPlayer is the pointer value of the opposing player
    @param property_tracker is the pointer variable for the list of properties that are owned, 
    unowned, and renovated by players
    @param property_num is current number of the property in the property_tracker
    @param railroadRent is the pointer variable for the value of rail road
    @param elecMultiplier is the pointer variable for the value that the die is multiplied to compute 
    the rent for the electric company
    Members\\
    position calls check_property each time it is updated
    owner_num calls the renovation function from the check_property function or calls rent if the 
    current player lands on the opposing players owner_num
    reno_num only displays that the property is renovated or calls rent if the current player lands 
    on the opposing players reno_num

*/
void check_property(struct Player *player, 
                    struct Player *opposingPlayer, 
                    int *property_tracker, 
                    int die, 
                    int *railroadRent, 
                    int *elecMultiplier, 
                    int *renovateCost)
{
    int temp = *property_tracker;
    int property_num = 0;
    for(int i = 0; i < player->position; i++)
    {
        property_num = *property_tracker % 10;
        *property_tracker /= 10;
    }
    *property_tracker =  temp;
    if(property_num == 0 && player->position != 0)
    {
        printf("Property Num: %d\n", property_num);
        buy(player, property_tracker);
    }else if(property_num == player->owner_num && player->position != 0)
    {
        printf("Property Num: %d\n", property_num);
        renovate(player, property_tracker, renovateCost);
    }else if(property_num == player->reno_num && player->position != 0)
    {
        printf("Property Num: %d\n", property_num);
        printf("It is already renovated.\n");
        system("pause");
        system("cls");
    }else if((player->position != 0 && property_num == opposingPlayer->owner_num) || property_num == opposingPlayer->reno_num) 
    {
        printf("Property Num: %d\n", property_num);
        rent(die, opposingPlayer, player, property_tracker, property_num, railroadRent, elecMultiplier);
    }
}

/*
    This function is only called if the player lands on property 4, which is jail, or is called from 
    the lucky chance function.
    @param player is the pointer value for the current player.
    Members//
    position is set to 4 if ever the chance the player is called to jail from other positions other than 4
    is_jailed is set to true
*/
void jailed(struct Player *player)
{
    sleep(1);
    printf("=======================\n");
    printf("===[You are in Jail]===\n");
    printf("=======================\n");
    player->position = 4;
    player->is_jailed = true;
    sleep(2);
    system("pause");
    system("cls");
}

/*
    This function is called only when the player lands on property 6 and depends on the roll 
    computation whether the player recieves money, loses money, or goes to jail.
    @param player is the pointer value of the current player
    @param minGiveMoney is the pointer variable of the minimum amount of money given
    @param maxGiveMoney is the pointer variable of the maximum amount of money given
    @param minTakeMoney is the pointer variable of the minimum amount of money taken
    @param maxTakemoney is the pointer variable of the maximum amount of money taken
    Members//
    money is added or subtracted depending the roll of the lucky die
*/
void lucky_chance(struct Player *player,
                    int *property_tracker,
                    int *minGiveMoney, 
                    int *maxGiveMoney, 
                    int *minTakeMoney, 
                    int *maxTakeMoney)
{
    sleep(1);
    printf("===============\n");
    printf("Test your Luck!\n");
    printf("===============\n");
    sleep(1);
    int luckyDie = 4;//(rand()%6) + 1;
    int takeMoney = (rand()%(*maxTakeMoney - *minTakeMoney + 1)) + *minTakeMoney;
    int giveMoney = (rand()%(*maxGiveMoney - *minGiveMoney + 1)) + *minGiveMoney;
    printf("Rolling Lucky Die");
    for (int i = 0; i <= 3; i++)
    {
        sleep(1);
        printf(".");
    }
    sleep(2);
    printf("You rolled %d!\n", luckyDie);
    switch(luckyDie)
    {
        case 1:{
            sleep(1);
            printf("You win a trip");
            for (int t = 0; t <= 2; t++)
                {
                    sleep(1);
                    printf(".");
                }
            printf("to jail.\n");
            jailed(player);
            break;
        }
        case 2:{
            sleep(1);
            printf("Blessed with good luck :>\n");
            player->money += giveMoney;
            sleep(1);
            printf("You are blessed with $%d\n", giveMoney);
            sleep(2);
            break;
        }
        case 3:{
            sleep(1);
            printf("You are just very lucky :>\n");
            player->money += giveMoney;
            sleep(1);
            printf("You found $%d while walking!\n", giveMoney);
            sleep(2);
            break;
        }
        case 4:{
            sleep(1);
            printf("Oof thats a bad roll.\n");
            player->money -= takeMoney;
            sleep(1);
            printf("You dropped $%d while running.\n", takeMoney);
            if(player->money < 0)
            {
                do{
                    sleep(1);
                    printf("Your money is not enough.\n");
                    sell(player, property_tracker);                       
                }while((player->money < 0) && player->is_bankrupt == false);
                sleep(1);
                printf("Good enough\n");
            }
            sleep(2);
            break;
        }
        case 5:{
            sleep(1);
            printf("Your day must be good :>\n");
            player->money += giveMoney;
            sleep(1);
            printf("You were given $%d.\n", giveMoney);
            sleep(2);
            break;
        }
        case 6:{
            sleep(1);
            printf("sheeeeeesh give me your money.\n");
            player->money -= takeMoney;
            sleep(1);
            printf("You were robbed $%d.\n", takeMoney);
            if(player->money < 0)
            {
                do{
                    sleep(1);
                    printf("Your money is not enough.\n");
                    sell(player, property_tracker);                      
                }while((player->money < 0) && player->is_bankrupt == false);
                sleep(1);
                printf("Good enough\n");
            }
            sleep(2);
            break;
        }
    }
    if(luckyDie != 1 && player->money > 0)
    {
        system("pause");
        system("cls");
    }
        
}

/*
    This function this function checks if the player is jailed or not. If the player is not jailed, 
    it calls the check_property function to show the player what they can do. If the
    case that the player lands on property 6, this function calls lucky_chance for the lucky dice function 
    and if the player lands on 4, it calls the jail function. If the player is 
    jailed, the function loses the players next turn.
    @param player is the pointer value for the current player
    @param opposingPlayer is the pointer value for the opposing player
    @param property_tracker is the pointer variable for the list of properties that are owned, 
    unowned, and renovated by players
    @param property_num is current number of the property in the property_tracker.
    @param railroadRent is the pointer variable for the value of rail road.
    @param elecMultiplier is the pointer variable for the value that the die is multiplied 
    to compute the rent for the electric company
*/
void turn(struct Player *player, 
        struct Player *opposingPlayer, 
        int *property_tracker, 
        int *railroadRent, 
        int *elecMultiplier, 
        int *renovateCost, 
        int *minGiveMoney, 
        int *maxGiveMoney, 
        int *minTakeMoney, 
        int *maxTakeMoney)
{
    sleep(1);
    printf("|-----%s-----|\n", player->name);
    printf("Property Tracker: %d\n", *property_tracker);
    printf("Balance: $%d\n",player->money);
    printf("Position: %d\n", player->position);
    if(player->is_jailed == false)
    {
        int die = move(player, property_tracker, renovateCost);
        if(player->position == 4)
        {
            jailed(player);
        }else if(player->position == 6)
        {
            lucky_chance(player, property_tracker,minGiveMoney, maxGiveMoney, minTakeMoney, maxTakeMoney);
        }else
        {
            check_property(player, opposingPlayer, property_tracker, die, railroadRent, elecMultiplier, renovateCost);
        }
    }else if(player->is_jailed == true)
    {
        printf("You are still jailed. ");
        printf("Lose your turn.\n");
        player->is_jailed = false;
        sleep(1);
        system("pause");
        system("cls");
    }
}

/*
    This function calls the turn function to let the game run. The variables are the default values 
    for the base game. The win conditions are also located here and goes
    back to the main menu screen after each game is concluded with everything resetting to its base values.
    @param player1 is the pointer value for player 1
    @param player2 is the pointer value for player 2
    @param property_tracker is the pointer variable for the list of properties that are owned, 
    unowned, and renovated by players. 
    Members//
    money is equated to default value of 200
    is_bankrupt is checked if it set to true or false during the game to determine the winner of the game
    
*/
void game(struct Player *player1, 
        struct Player *player2, 
        int *property_tracker)
{
    int railroadRent = 35;
    int elecMultiplier = 8;
    int renovateCost = 50;
    int minGiveMoney = 100;
    int maxGiveMoney = 200;
    int minTakeMoney = 50;
    int maxTakeMoney = 150;
    player1->money = 200;
    player2->money = 200;
    set_up_players(player1, player2);
    while(player1->is_bankrupt == false && player2->is_bankrupt == false)
    {
        if(!player2->is_bankrupt)
        {
            turn(player1, player2, property_tracker, &railroadRent, &elecMultiplier, &renovateCost, &minGiveMoney, &maxGiveMoney, &minTakeMoney, &maxTakeMoney);
        }
        if(!player1->is_bankrupt)
        {
            turn(player2, player1, property_tracker, &railroadRent, &elecMultiplier, &renovateCost, &minGiveMoney, &maxGiveMoney, &minTakeMoney, &maxTakeMoney);
        }
    }
    if(player1->is_bankrupt == true)
    {
        system("cls");
        sleep(1);
        printf("Game over! Congratulations Player 2!\n");
        sleep(2);
        *property_tracker = 0;
    }else if(player2->is_bankrupt == true)
    {
        system("cls");
        sleep(1);
        printf("Game over! Congratulations Player 1!\n");
        sleep(2);
        *property_tracker = 0;
    }else if(player1->is_bankrupt == true && player2->is_bankrupt == true)
    {
        system("cls");
        sleep(1);
        printf("Game over! Somehow both of you went bankrupt!");
        sleep(2);
        *property_tracker = 0;
    }
}

/*
    This function calls the turn function to let the game run. The variables are the set to the 
    configured values, default values if left unconfigured. The win conditions are 
    also located here and goes back to the main menu screen after each game is concluded with 
    everything resetting to its default values.
    @param player1 is the pointer value for player 1
    @param player2 is the pointer value for player 2
    @param property_tracker is the pointer variable for the list of properties that are owned, 
    unowned, and renovated by players
    @param railroadRent is the pointer variable for the configured value of rent of the rail road
    @param elecMultiplier is the pointer variable for the configured value of the multiplier for electric company
    @param renovateCost is the pointer variable for the configured value of the cost of the renovation
    @param minGiveMoney is the pointer variable of the configured minimum amount of money given
    @param maxGiveMoney is the pointer variable of the configured maximum amount of money given
    @param minTakeMoney is the pointer variable of the configured minimum amount of money taken
    @param maxTakemoney is the pointer variable of the configured maximum amount of money taken
    Members//
    is_bankrupt is checked if it set to true or false during the game to determine the winner of the game
*/
void customGame(struct Player *player1, 
                struct Player *player2, 
                int *property_tracker, 
                int *railroadRent, 
                int *elecMultiplier, 
                int *renovateCost, 
                int *minGiveMoney, 
                int *maxGiveMoney, 
                int *minTakeMoney, 
                int *maxTakeMoney)
{
    while(player1->is_bankrupt == false && player2->is_bankrupt == false)
    {
        if(!player2->is_bankrupt)
        {
            turn(player1, player2, property_tracker, railroadRent, elecMultiplier, renovateCost, minGiveMoney, maxGiveMoney, minTakeMoney, maxTakeMoney);
        }
        if(!player1->is_bankrupt)
        {
            turn(player2, player1, property_tracker, railroadRent, elecMultiplier, renovateCost, minGiveMoney, maxGiveMoney, minTakeMoney, maxTakeMoney);
        }
    }
    if(player1->is_bankrupt == true)
    {
        system("cls");
        sleep(1);
        printf("Game over! Congratulations Player 2!\n");
        sleep(2);
        *property_tracker = 0;
        system("pause");
        system("cls");
    }else if(player2->is_bankrupt == true)
    {
        system("cls");
        sleep(1);
        printf("Game over! Congratulations Player 1!\n");
        sleep(2);
        *property_tracker = 0;
        system("pause");
        system("cls");
    }else if(player1->is_bankrupt == true && player2->is_bankrupt == true)
    {
        system("cls");
        sleep(1);
        printf("Game over! Somehow both of you went bankrupt!");
        sleep(2);
        *property_tracker = 0;
        system("pause");
        system("cls");
    }
}

/*
    This function is where the player can configure the values of the given variables and start the 
    game with the configured values. The default values are defined here
    to reset the values each time the player starts a new game or goes back to main menu.
    @param p1 is the pointer value for player 1
    @param p2 is the pointer value for player 2
    @param property_tracker is the pointer variable for the list of properties that are owned, 
    unowned, and renovated by players
*/
void customGameMenu(struct Player *p1, 
                    struct Player *p2, 
                    int *property_tracker)
{   
        int railroadRent = 35;
        int elecMultiplier = 8;
        int renovateCost = 50;
        int minGiveMoney = 100;
        int maxGiveMoney = 200;
        int minTakeMoney = 50;
        int maxTakeMoney = 150;
        int customMoney1 = 200;
        int customMoney2 = 200;
        int Bchoice = 0;
        while(Bchoice != 6 && Bchoice != 7)
        {
            printf("|===CUSTOM GAME VALUES===|\n");
            do{
                printf("(1)Change Rail Road Rent\n(2)Change Electric Company number multiplier\n(3)Change Renovation cost\n(4)Change range of Feelin Lucky money\n(5)Change money start\n(6)Start Game\n(7)Back\n");
                printf("Input: ");
                scanf("%d", &Bchoice);
                system("cls");
            } while(Bchoice != 1 && Bchoice != 2 && Bchoice != 3 && Bchoice != 4 && Bchoice != 5 && Bchoice != 6 && Bchoice != 7);
            if(Bchoice == 1)
            {
                printf("Input value for Rail Road Rent\n");
                printf("Input: ");
                scanf("%d", &railroadRent);
                system("cls");
            }
            if(Bchoice == 2)
            {
                printf("Input value for Electric Company number multiplier\n");
                printf("Input: ");
                scanf("%d", &elecMultiplier);
                system("cls");
            }
            if(Bchoice == 3)
            {
                printf("Input value for Renovation Cost\n");
                printf("Input: ");
                scanf("%d", &renovateCost);
                system("cls");
            }
            if(Bchoice == 4)
            {
                printf("Input value minimum amount of money given\n");
                printf("Input: ");
                scanf("%d", &minGiveMoney);
                printf("Input value maximum amount of money given\n");
                printf("Input: ");
                scanf("%d", &maxGiveMoney);
                printf("Input value minimum amount of money taken\n");
                printf("Input: ");
                scanf("%d", &minTakeMoney);
                printf("Input value maximum amount of money given\n");
                printf("Input: ");
                scanf("%d", &maxTakeMoney);
                system("cls");
            }
            if(Bchoice == 5)
            {
                system("cls");
                printf("Input starting money for Player 1!\n");
                printf("Input: ");
                scanf("%d", &customMoney1);
                printf("Input starting money for Player 2!\n");
                printf("Input: ");
                scanf("%d", &customMoney2);
                system("cls");
            }
        }
        if(Bchoice == 6)
            {
                system("cls");
                set_up_players(p1, p2);
                p1->money = customMoney1;
                p2->money = customMoney2;
                customGame(p1, p2, property_tracker, &railroadRent, &elecMultiplier, &renovateCost, &minGiveMoney, &maxGiveMoney, &minTakeMoney, &maxTakeMoney);
            }
}

/*
    This function displays choices whether the player wants to start the base game, 
    the custom game, or exit the program.
    @param p1 is the pointer value for player 1
    @param p2 is the pointer value for player 2
    @param property_tracker is the pointer variable for the list of properties that are owned, 
    unowned, and renovated by players
*/
int gameMenu(struct Player *p1, 
            struct Player *p2, 
            int *property_tracker)
{
    int menuInput;
    printf(" ---------------------------------------\n");
    printf("|                                       |\n");
    printf("|   Property                            |\n");
    printf("|                                       |\n");
    printf("|                            Property   |\n");
    printf("|                                       |\n");
    printf(" ---------------------------------------\n");
    printf("                Main Menu:\n");
    printf("              (1)Play game\n              (2)Play custom game\n              (3)Exit game\n");
    printf("                Input: ");
    scanf("%d", &menuInput);
    if(menuInput == 1)
    {
        system("cls");
        game(p1, p2, property_tracker);
    }
    if(menuInput == 2)
    {   
        system("cls");
        customGameMenu(p1, p2, property_tracker);
    }
    if(menuInput == 3)
    {
        system("cls");
        printf("Thanks for playing.");
    }
    return menuInput;
}

/*
    The main function calls the game menu function to start the game or exit the program.
*/
int main()
{
    srand(time(0));
    struct Player p1, p2;
    int property_tracker = 000000000;
    int menuInput;
    printf("Loading");
    for (int i = 0; i <= 5; i++)
    {
        sleep(1);
        printf(".");
    }
    printf("\n");
    system("cls");
    while(menuInput != 3)
    {
        menuInput = gameMenu(&p1, &p2, &property_tracker);
    }
}
