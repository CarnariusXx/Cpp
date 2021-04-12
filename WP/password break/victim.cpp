#include <cstring>

// victim function
bool test_pass(char *user_pass)
{
    const char *passwd = "HUtaMtRUAJLsqC2J";

    int passwd_len = strlen(passwd);

    for (int i = 0; i <= passwd_len; i++)
    {
        if (passwd[i] != user_pass[i])
        {
            return false;
        }
    }

    return true;
}

