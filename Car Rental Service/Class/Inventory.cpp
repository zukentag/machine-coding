#pragma once
#include <bits/stdc++.h>
#include "Vehicle.cpp"
using namespace std;

class Inventory
{

public:
    //  branch   vechicleType    vechicleList
    map<string, map<string, vector<Vehicle *>>> inventory;

    void addInventory(string vehicleId, string vehicleType, string branchName)
    {
        Vehicle *v = new Vehicle(vehicleId, vehicleType);
        this->inventory[branchName][vehicleType].push_back(v);
    }

    void printInventory()
    {
        for (auto &it : inventory)
        {
            cout << it.first << " has vehicles of type \n";

            for (auto &sec : it.second)
            {
                cout << sec.first << " in " << sec.second.size() << " quantity\n";
            }
            cout << "\n";
        }
    }

    Vehicle *getVehicle(string vehicleType, int startTime, int endTime)
    {
        Vehicle *optimalVehicle = NULL;
        int minimumCost = INT_MAX;

        for (auto &it : inventory)
        {
            string branch = it.first;

            for (auto &sec : it.second)
            {
                string vehicleTypeInInventory = sec.first;

                if (vehicleTypeInInventory == vehicleType)
                {
                    if (sec.second.size() == 0)
                    {
                        cout << "No Vehicles Found of type " << vehicleType << " \n";
                        return NULL;
                    }
                    else
                    {
                        for (auto &vehicle : sec.second)
                        {
                            bool vechicleBookingStatus = vehicle->getBookingStatus();

                            if (vechicleBookingStatus != true)
                            {
                                int vehiclePrice = vehicle->getPrice();

                                if (vehiclePrice <= minimumCost)
                                {
                                    optimalVehicle = vehicle;
                                    minimumCost = vehiclePrice;
                                }
                            }
                            //  if vehicle s booked check if the booking end time is expired then the vehicle can be booked again
                            else
                            {
                                int bookingEndedTime = vehicle->getBookingEndTime();
                                if (bookingEndedTime < startTime)
                                {
                                    vehicle->setToDefault();
                                    int vehiclePrice = vehicle->getPrice();

                                    if (vehiclePrice <= minimumCost)
                                    {
                                        optimalVehicle = vehicle;
                                        minimumCost = vehiclePrice;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        return optimalVehicle;
    }

    void allocatePrice(string branchName, string vehicleType, int price)
    {

        for (auto &vechicle : inventory[branchName][vehicleType])
        {
            vechicle->addPrice(price);
        }
    }

    void bookVehicle(string vehicleType, int startTime, int endTime)
    {
        Vehicle *optimalVehicle = this->getVehicle(vehicleType, startTime, endTime);

        if (optimalVehicle)
        {

            optimalVehicle->bookVehicle(startTime, endTime);

            cout << "Vehicle Booked Successfullly of type " << vehicleType << " from " << startTime << " to " << endTime << "\n\n";

            return;
        }

        cout << "No Vehicle Found of type  " << vehicleType << " at current time \n\n";
    }
};
