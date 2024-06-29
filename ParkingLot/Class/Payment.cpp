#pragma once
using namespace std;

class Payment
{
public:
    virtual double calculateCost(double hours) = 0;
};

class CarPayment : public Payment
{
public:
    double calculateCost(double hours) { return hours * 2; }
};

class BikePayment : public Payment
{
public:
    double calculateCost(double hours) { return hours * 1; }
};

class HandicappedPayment : public Payment

{
public:
    double calculateCost(double hours) { return 0; }
};
