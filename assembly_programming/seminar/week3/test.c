#include <stdio.h>

int validate(int user, int key)
{
    if (key == user * 5 - 1)
    {
        return 1;
    }
    return 0;
}

int main()
{
    int user, key;
    printf("Enter user: ");
    scanf("%d", &user);
    printf("Enter key: ");
    scanf("%d", &key);
    if (validate(user, key))
    {
        printf("Registered!\n");
    }
    else
    {
        printf("Failed!\n");
    }
    getchar();
    getchar();
    return 0;
}
