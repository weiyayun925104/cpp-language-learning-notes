#include <iostream>
#include <new>
#include <cstring>

const int STRUCTSIZE = 2;
const int BUFFSIZE = 512;
char buffer[BUFFSIZE];

struct chaff
{
    char dross[32];
    int slag;
};

void show_chaff(const chaff &chf);
void set_chaff(chaff &chf, const char *name, int qlty);

int main()
{
    chaff *pchaff = new (buffer) chaff[STRUCTSIZE];
    char name[32];
    int quantity = 0;

    for (int i = 0; i < STRUCTSIZE; i++)
    {
        std::cout << "Enter name: ";
        std::cin.getline(name, 32);
        std::cout << "Enter the quantity: ";
        (std::cin >> quantity).get();
        set_chaff(pchaff[i], name, quantity);
    }
    std::cout << pchaff << ", " << (void *)buffer << std::endl;
    for (int i = 0; i < STRUCTSIZE; i++)
    {
        std::cout << "Chaff " << i + 1 << std::endl;
        show_chaff(pchaff[i]);
    }

    return 0;
}

void show_chaff(const chaff &chf)
{
    std::cout << "Dross : " << chf.dross << std::endl;
    std::cout << "Slag : " << chf.slag << std::endl;
}

void set_chaff(chaff &chf, const char *name, int qlty)
{
    strcpy(chf.dross, name);
    chf.slag = qlty;
}
