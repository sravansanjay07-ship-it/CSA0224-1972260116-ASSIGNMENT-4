#include <stdio.h>

#define MAX_ITEMS 3

struct Date
{
    int day, month, year;
};

enum ItemType
{
    PACKAGED,
    COOKED,
    COMBO
};

struct Item
{
    int id;
    char name[30];
    float price;
    int stock;
    float revenue;
    enum ItemType type;

    union
    {
        struct Date expiry;
        char preparedTime[10];

        struct
        {
            int item1, qty1;
            int item2, qty2;
        } combo;

    } details;
};

int dateValue(struct Date d)
{
    return d.year * 365 + d.month * 31 + d.day;
}

void showExpiry(struct Item items[], struct Date today)
{
    int i;

    printf("\nExpiry Warnings:\n");

    for (i = 0; i < MAX_ITEMS; i++)
    {
        if (items[i].type == PACKAGED)
        {
            int difference =
                dateValue(items[i].details.expiry) -
                dateValue(today);

            if (difference >= 0 && difference <= 2)
            {
                printf("%s is expiring soon\n",
                       items[i].name);
            }
        }
    }
}

void sellItem(struct Item items[], int id, int quantity)
{
    int i;
    struct Item *p = NULL;

    for (i = 0; i < MAX_ITEMS; i++)
    {
        if (items[i].id == id)
        {
            p = &items[i];
            break;
        }
    }

    if (p == NULL || quantity <= 0)
    {
        printf("Invalid item or quantity\n");
        return;
    }

    if (p->type == COMBO)
    {
        struct Item *a = &items[p->details.combo.item1 - 1];
        struct Item *b = &items[p->details.combo.item2 - 1];

        if (p->stock < quantity ||
            a->stock < p->details.combo.qty1 * quantity ||
            b->stock < p->details.combo.qty2 * quantity)
        {
            printf("Insufficient stock for %s\n", p->name);
            return;
        }

        a->stock -= p->details.combo.qty1 * quantity;
        b->stock -= p->details.combo.qty2 * quantity;
    }
    else
    {
        if (p->stock < quantity)
        {
            printf("Insufficient stock for %s\n", p->name);
            return;
        }

        p->stock -= quantity;
    }

    p->stock -= (p->type == COMBO) ? quantity : 0;
    p->revenue += p->price * quantity;

    printf("Sale successful: %s x %d\n",
           p->name, quantity);
}

void showSummary(struct Item items[])
{
    int i, j;
    struct Item temp;

    for (i = 0; i < MAX_ITEMS - 1; i++)
    {
        for (j = 0; j < MAX_ITEMS - i - 1; j++)
        {
            if (items[j].revenue < items[j + 1].revenue)
            {
                temp = items[j];
                items[j] = items[j + 1];
                items[j + 1] = temp;
            }
        }
    }

    printf("\nDaily Revenue Summary:\n");

    for (i = 0; i < MAX_ITEMS; i++)
    {
        printf("%s - Rs. %.2f\n",
               items[i].name, items[i].revenue);
    }
}

int main(void)
{
    struct Date today;

    struct Item items[MAX_ITEMS] =
    {
        {1, "Milk", 30, 10, 0, PACKAGED,
         {.expiry = {22, 11, 2026}}},

        {2, "Dosa", 20, 10, 0, COOKED,
         {.preparedTime = "09:30"}},

        {3, "Combo", 45, 10, 0, COMBO,
         {.combo = {1, 1, 2, 1}}}
    };

    int n, id, quantity, i;

    printf("Enter today's date (dd mm yyyy): ");
    scanf("%d %d %d",
          &today.day, &today.month, &today.year);

    showExpiry(items, today);

    printf("\nEnter number of sales: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {
        printf("Enter item ID and quantity: ");
        scanf("%d %d", &id, &quantity);

        sellItem(items, id, quantity);
    }

    showSummary(items);

    return 0;
}
