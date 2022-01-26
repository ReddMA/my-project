#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <math.h>

struct Player
{
    char name[40];
    bool is_jailed;
    int money;
    int position;
    int owner_num;
    int reno_num;
    bool is_bankrupt;
};

void set_up_players(struct Player *player1, struct Player *player2)
{
    strcpy_s(player1->name, sizeof(player1->name), "Player 1");
    player1->is_jailed = false;
    player1->money = 200;
    player1->position = 0;
    player1->owner_num = 1;
    player1->reno_num = 3;
    player1->is_bankrupt = false;
    strcpy_s(player2->name, sizeof(player2->name), "Player 2");
    player2->is_jailed = false;
    player2->money = 200;
    player2->position = 0;
    player2->owner_num = 2;
    player2->reno_num = 4;
    player2->is_bankrupt = false;
}

void print_property_desc(struct Player *player, int* property_tracker)
{
    int cost = (player->position % 7) * 20;
    int resell = cost / 2;
    int property_num = 0;
    int temp = *property_tracker;
    switch (player->position) {
        case 0:
        {
            break;
        }
        case 1:
        {
            printf("Renovate cost: $50\n");
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
            printf("Renovate cost: $50\n");
            break;
        }
        case 4:
        {
            break;
        }
        case 5:
        {
            printf("Renovate cost: $50\n");
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
            printf("Renovate cost: $50\n");
            break;
        }
        case 9:
        {
            printf("Renovate cost: $50\n");
            break;
        }
    }
    if(player->position == 6)
    {
        system("pause");
    }
    else if(player->position == 4)
    {
        system("pause");
    }
    else if(player->position == 0)
    {
        system("pause");
    }else
    {
        printf("Cost: $%d\n", cost);
        printf("Resell: $%d\n", resell);
        for (int i = 0; i < player->position; i++) {
            property_num = *property_tracker % 10;
            *property_tracker /= 10;
        }
        if (property_num == 1 || property_num == 3) {
            printf("Owner: Player 1\n");
        } else if (property_num == 2 || property_num == 4) {
            printf("Owner: Player 2\n");
        } else {
            printf("Owner: Bank\n");
        }
        *property_tracker = temp;
    }
}

int move(struct Player *player, int *property_tracker)
{
    int die = (rand()%6) + 1;
    printf("You rolled %d\n", die);
    player->position += die;
    if(player->position > 9)
    {
        player->position -= 10;
        player->money += 200;
        printf("You recieved $200!\n");
        printf("New balance: $%d\n", player->money);
    }
    printf("You are at Position %d: ", player->position);
    int i = player->position;
    switch (i) {
            case 0: {
                printf("Go\n");               
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
    print_property_desc(player, property_tracker);
    return die;
}

void buy(struct Player *player, int *property_tracker)
{
    int choice = 0;
    do
    {
        printf("[1] Buy\n");
        printf("[2] End turn\n");
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
                }else
                {
                    printf("Not enough money.\n");
                }         
                break;
            }
            case 2: {
                if (player->money >= 150)
                {
                player->money -= 150;
                *property_tracker += property;
                }else
                {
                    printf("Not enough money.\n");
                }         
                break;
            }
            case 3: {
                if (player->money >= 20 * (i % 7))
                {
                player->money -= 20 * (i % 7);
                *property_tracker += property;
                }else
                {
                    printf("Not enough money.\n");
                }         
                break;
            }
            case 5: {
                if (player->money >= 20 * (i % 7))
                {
                player->money -= 20 * (i % 7);
                *property_tracker += property;
                }else
                {
                    printf("Not enough money.\n");
                }         
                break;
            }
            case 7: {
                if (player->money >= 100)
                {
                player->money -= 100;
                *property_tracker += property;
                }else
                {
                    printf("Not enough money.\n");
                }         
                break;
            }
            case 8: {
                if (player->money >= 20 * (i % 7))
                {
                player->money -= 20 * (i % 7);
                *property_tracker += property;
                }else
                {
                    printf("Not enough money.\n");
                }         
                break;
            }
            case 9: {
                if (player->money >= 20 * (i % 7))
                {
                player->money -= 20 * (i % 7);
                *property_tracker += property;
                }else
                {
                    printf("Not enough money.\n");
                }         
                break;
            }
        }
    }else
    {
        printf("You ended turn.\n");
    }
}

void renovate(struct Player *player, int *property_tracker)
{
    int choice = 0;
    do
    {
        printf("[1] Renovate\n");
        printf("[2] End turn\n");
        printf("Choice: ");
        scanf("%d", &choice);
    } while (choice != 1 && choice != 2);
    if(choice == 1)
    {
        int property = 2 * pow(10, player->position - 1);
        *property_tracker += property;
        
    }else
    {
        printf("You ended turn.\n");
    }
}

void sell(struct Player *player, int *property_tracker)
{
    int temp = *property_tracker;
    int property_num = 0;
    int properties_not_sold = 0;
    for(int i = 0; i < 9; i++)
    {
        property_num = *property_tracker % 10;
        if(property_num == player->owner_num || property_num == player->reno_num)
        {
            int choice = 0;
            do {
                printf("Sell: Property %d", property_num);
                printf("[1] Sell\n");
                printf("[2] Not Sell\n");
                printf("Choice: ");
                scanf("%d", &choice);
            } while (choice != 1 && choice != 2);
            if(choice == 1)
            {
                printf("Selling your property....");
                system("pause");
                temp -= (property_num * pow(10, i));
                if(i == 1)
                {
                    player->money += 100 / 2;
                }
                else if(i == 6)
                {
                    player->money += 150 / 2;
                }else
                {
                    player->money += (((i + 1) % 7) * 20) / 2;
                }
            }else
            {
                properties_not_sold++;
            }
        }
        *property_tracker /= 10;
    }
    *property_tracker = temp;
    if(properties_not_sold > 0 && player->money < 0)
    {
        printf("You have to sell since you dont have money.\n");
        system("pause");
        return sell(player, property_tracker);
    }
    else if(properties_not_sold == 0 && player->money < 0)
    {
        printf("You are bankrupt.\n");
        player->is_bankrupt = true;
    }
}

void rent(int die, struct Player *owner, struct Player *visitor, int *property_tracker, int property_num)
{
    int moneyOwned = 0;
    if(visitor->position = 2)
    {
        int moneyOwned = die * 8;
        visitor->money -= moneyOwned;
        owner->money += moneyOwned;
        printf("You paid rent for $%d\n", moneyOwned);
    }
    else if(visitor->position = 7)
    {
        moneyOwned = 35;
        visitor->money -= moneyOwned;
        owner->money += moneyOwned;
        printf("You paid rent for $%d\n", moneyOwned);
    }
    else
    {
        if(property_num == owner->owner_num)
        {
            moneyOwned = 20 * (visitor->position % 7) / 5;
            visitor->money -= moneyOwned;
            owner->money += moneyOwned;
            printf("You paid rent for $%d\n", moneyOwned);

        }
        else
        {
            moneyOwned = (20 * (visitor->position % 7) / 5) * 2 + 1;
            visitor->money -= moneyOwned;
            owner->money += moneyOwned;
            printf("You paid rent for $%d\n", moneyOwned);
        }
    }
    if(visitor->money < 0)
    {
        printf("You do not have enough money for rent.\n");
        sell(visitor, property_tracker);
    }
}

void check_property(struct Player *player, struct Player *opposingPlayer, int *property_tracker, int die)
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
        renovate(player, property_tracker);
    }else if(player->position != 0 && property_num == opposingPlayer->owner_num || property_num == opposingPlayer->reno_num) 
    {
        printf("Property Num: %d\n", property_num);
        rent(die, opposingPlayer, player, property_tracker, property_num);
    }
}

void jailed(struct Player *player)
{
    printf("=======================\n");
    printf("===[You are in Jail]===\n");
    printf("=======================\n");
    player->position = 4;
    player->is_jailed = true;
}

void lucky_chance(struct Player *player)
{
    printf("===============\n");
    printf("Test your Luck!\n");
    printf("===============\n");
    int luckyDie = (rand()%6) + 1;
    int takeMoney = (rand()%101) + 50;
    int giveMoney = (rand()%101) + 100;
    printf("You rolled %d\n", luckyDie);
    switch(luckyDie)
    {
        case 1:{
            printf("You have bad luck\n");
            jailed(player);
            break;
        }
        case 2:{
            printf("Blessed with good luck :>\n");
            player->money += giveMoney;
            printf("You are blessed with $%d\n", giveMoney);
            break;
        }
        case 3:{
            printf("You are just very lucky :>\n");
            player->money += giveMoney;
            printf("You found $%d while walking!\n", giveMoney);
            break;
        }
        case 4:{
            printf("Oof thats a bad roll.\n");
            player->money -= takeMoney;
            printf("You dropped $%d while running.\n", takeMoney);
            break;
        }
        case 5:{
            printf("You day must be good :>\n");
            player->money += giveMoney;
            printf("You were given $%d.\n", giveMoney);
            break;
        }
        case 6:{
            printf("sheeeeeesh give me your money.\n");
            player->money -= takeMoney;
            printf("You were robbed $%d.\n", takeMoney);
            break;
        }
    }
    
}

void turn(struct Player *player, struct Player *opposingPlayer, int *property_tracker)
{
        printf("|---%s---|\n", player->name);
    printf("Property Tracker: %d\n", *property_tracker);
    printf("Balance: $%d\n",player->money);
    if(player->is_jailed == false)
    {
        int die = move(player, property_tracker);
        if(player->position == 4)
        {
            jailed(player);
        }else if(player->position == 6)
        {
            lucky_chance(player);
        }
        else
        {
            check_property(player, opposingPlayer, property_tracker, die);
        }
    }
    else if(player->is_jailed == true)
    {
        printf("Lose your turn.\n");
        player->is_jailed = false;
    }
}


void game(struct Player *player1, struct Player *player2, int *property_tracker)
{
    set_up_players(player1, player2);
    while(player1->is_bankrupt == false && player2->is_bankrupt == false)
    {
        turn(player1, player2, property_tracker);
        turn(player2, player1, property_tracker);
    }
    if(player1->is_bankrupt == true)
    {
        printf("Congratulations Player 2!\n");
    }
    else if(player2->is_bankrupt == true)
    {
        printf("Congratulations Player 1!\n");
    }
}

int gameMenu(struct Player *p1, struct Player *p2, int *property_tracker)
{
    int menuInput;
    printf("%96sProperty.....Property\n");
    printf("Main Menu:\n");
    printf("(1)Start game\n(2)Start custom game\n(3)Exit game\n");
    printf("Input: ");
    scanf("%d", &menuInput);
    if(menuInput == 1)
    {
        game(p1, p2, property_tracker);
    }
    else if(menuInput == 2)
    {
        printf("Soon.");
    }
    else if(menuInput == 3)
    {
        printf("Exiting game.");
    }
    return menuInput;
}

int main()
{
    srand(time(0));
    struct Player p1, p2;
    int property_tracker = 0;
    int menuInput;
    while(menuInput != 3)
    {
        system("cls");
        menuInput = gameMenu(&p1, &p2, &property_tracker);
    }
}