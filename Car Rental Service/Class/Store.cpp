#pragma once
#include <bits/stdc++.h>
#include "Vehicle.cpp"
#include "Inventory.cpp"
using namespace std;

class Store
{

    vector<string> branches;

    Inventory inventory;

public:
    void addBranch(string branchName)
    {
        this->branches.push_back(branchName);
    }

    void addVehicle(string vehicleId, string vehicleType, string branchName)
    {
        this->inventory.addInventory(vehicleId, vehicleType, branchName);
    }

    void allocatePrice(string branchName, string vehicleType, int price)
    {
        this->inventory.allocatePrice(branchName, vehicleType, price);
    }

    void printInventory()
    {
        this->inventory.printInventory();
    }

    void bookVehicle(string vehicleType, int startTime, int endTime)
    {
        this->inventory.bookVehicle(vehicleType, startTime, endTime);
    }
};
