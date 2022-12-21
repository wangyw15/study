#include <string>
#include <cstring>

bool isBigger(char *a, char *b)
{
    size_t aLength = strlen(a), bLength = strlen(b);
    if (aLength > bLength)
    {
        return true;
    }
    else if (aLength < bLength)
    {
        return false;
    }
    else
    {
        for (int i = 0; i < aLength; i++)
        {
            if (a[i] != b[i])
            {
                return (a[i] > b[i]);
            }
        }
    }
}