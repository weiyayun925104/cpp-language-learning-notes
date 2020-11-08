#include <iostream>
#include <cstring>

struct stringy
{
    char *str;
    int ct;
};

void set(stringy &beany, const char *testing);
void show(const char *string, int size = 1);
void show(const stringy &beany, int size = 1);
void clear_memory(stringy &beany);

int main()
{
    stringy beany;
    char testing[] = "Reality isn't what it used to be.";
    set(beany, testing);
    show(beany);
    show(beany, 2);
    clear_memory(beany);

    testing[0] = 'D';
    testing[1] = 'u';

    show(testing);
    show(testing, 3);
    show("Done!");

    return 0;
}

void set(stringy &beany, const char *testing)
{
    beany.ct = strlen(testing);
    beany.str = new char[beany.ct + 1];
    strcpy(beany.str, testing);
}

void show(const char *string, int size)
{
    for (int i = 0; i < size; i++)
    {
        std::cout << string << std::endl;
    }
}

void show(const stringy &beany, int size)
{
    for (int i = 0; i < size; i++)
    {
        std::cout << beany.str << std::endl;
    }
}

void clear_memory(stringy &beany)
{
    delete [] beany.str;
}
