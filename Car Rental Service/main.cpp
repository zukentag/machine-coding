#include <bits/stdc++.h>
#include "./Class/Store.cpp"

using namespace std;

int main()
{
    Store store;

    store.addBranch("Vasant Vihar Branch");
    store.addBranch("CP branch");

    store.addVehicle("VVBS1", "Sedan", "Vasant Vihar Branch");
    store.addVehicle("VVBSH1", "Hatchback", "Vasant Vihar Branch");

    store.addVehicle("CPBS1", "SUV", "CP branch");
    store.addVehicle("CPBS2", "SUV", "CP branch");
    store.addVehicle("CPBS3", "SUV", "CP branch");

    //
    store.addVehicle("CPBE4", "EV", "CP branch");

    store.addBranch("CP branch");

    //  Cp - > 3 Suv
    //  Vasant vihar has - > 1 Sedan, 1 hatchBack

    store.printInventory();

    store.allocatePrice("CP branch", "SUV", 1000);

    store.allocatePrice("Vasant Vihar Branch", "Sedan", 2000);
    store.allocatePrice("Vasant Vihar Branch", "Hatchback", 2500);

    // store.allocatePrice("Vasant Vihar Branch", "Sedan", 3000);

    store.bookVehicle("SUV", 2, 4);
    store.bookVehicle("SUV", 2, 4);
    store.bookVehicle("SUV", 2, 2);
    store.bookVehicle("SUV", 2, 4);

    //  1 car
    store.bookVehicle("Sedan", 1, 4);
    store.bookVehicle("Sedan", 5, 6);
    store.bookVehicle("Sedan", 8, 10);
    store.bookVehicle("Sedan", 0, 2);

    store.bookVehicle("Hatchback", 1, 4);
    store.bookVehicle("Hatchback", 1, 4);

    store.bookVehicle("EV", 23, 2);

    return 0;
}
