#pragma once
#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>
#include <iomanip>
#include "./Payment.cpp"
using namespace std;

class Vehicle
{
protected:
    Payment *payment;
    chrono::time_point<chrono::system_clock> parkedTime;

public:
    virtual string getType() = 0;
    virtual double calculateCost(double hours)
    {
        return payment->calculateCost(hours);
    }

    void setParkedTime()
    {

        parkedTime = chrono::system_clock::now();
    }

    chrono::time_point<chrono::system_clock> getParkedTime()
    {
        return parkedTime;
    }
};

class Car : public Vehicle
{
public:
    Car() { payment = new CarPayment(); }
    string getType()
    {
        return "Car";
    }
};

class Bike : public Vehicle
{
public:
    Bike() { payment = new BikePayment(); }
    string getType()
    {
        return "Bike";
    }
};

class HandicappedVehicle : public Vehicle
{
public:
    HandicappedVehicle() { payment = new HandicappedPayment(); }
    string getType()
    {
        return "Handicapped";
    }
};