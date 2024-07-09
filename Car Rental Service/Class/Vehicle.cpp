#pragma once
#include <bits/stdc++.h>
using namespace std;

class Vehicle
{
    string id;
    string type;
    int price;
    bool booked;
    int startTime;
    int endTime;

public:
    Vehicle(string id, string type)
    {
        this->id = id;
        this->type = type;
        this->price = 0;
        this->booked = false;
        this->startTime = -1;
        this->endTime = -1;
    }

    void addPrice(int price)
    {
        this->price = price;
    }
    int getPrice()
    {
        return this->price;
    }
    void bookVehicle(int startTime, int endTime)
    {
        this->booked = true;
        this->startTime = startTime;
        this->endTime = endTime;
    }
    bool getBookingStatus()
    {
        return this->booked;
    }
    int getBookingEndTime()
    {
        return this->endTime;
    }

    void setToDefault()
    {
        this->booked = false;
        this->startTime = -1;
        this->endTime = -1;
    }
    void printVehicleDetails()
    {
        cout << "BookingStatus: " << this->booked << "\n"
             << " Start Time : " << startTime << "\n"
             << " EndTime : " << endTime << "\n";
    }
};
