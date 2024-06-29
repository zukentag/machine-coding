#include <iostream>
#include <vector>
#include "Class/Parkinglot.cpp"
#include "Class/Vehicle.cpp"

using namespace std;

int main()
{
    ParkingLot lot(3, 10, 20);
    Car car1, car2;
    Bike bike1, bike2;
    HandicappedVehicle hv1;

    car1.setParkedTime();
    lot.park(&car1, 0, 0, 0);
    car2.setParkedTime();

    lot.park(&car2, 0, 0, 1);
    bike1.setParkedTime();
    lot.park(&bike1, 0, 0, 2);
    hv1.setParkedTime();
    lot.park(&hv1, 2, 9, 19);

    cout << "Available spots on floor 0: " << lot.availableSpots(0) << endl;
    cout << "Handicapped spots on floor 2: " << lot.handicappedSpots(2) << endl;

    lot.leave(&car1);
    lot.leave(&bike2);

    cout << "Available spots on floor 0: " << lot.availableSpots(0) << endl;

    return 0;
}