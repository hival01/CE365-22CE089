#include <stdio.h>
#include <string.h>

int main()
{
    char s[100];
    while (1)
    {

        int i, f = 0;
        printf("Enter String: ");
        gets(s);

        if (s[0] == '\0')
        {
            printf("Invalid input: String cannot be empty!\n");
            continue;
        }

        for (i = 0; i < strlen(s); i++)
        {
            if (s[i] == 'a')
            {
                continue;
            }
            else
            {
                if (s[i] == 'b' && s[i + 1] == 'b' && s[i + 2] == '\0')
                {
                    printf("Valid String!!");
                    f = 1;
                    break;
                }
                else
                {
                    printf("Invalid String!");
                    f = 1;
                    break;
                }
            }
        }
        if (f == 0)
        {
            printf("Invalid String!");
        }
        printf("\n");
    }
    return 0;
}