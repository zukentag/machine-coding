#pragma once
#include <iostream>
#include <vector>
#include <chrono>
#include "Vehicle.cpp"

using namespace std;

class ParkingLot
{
private:
    vector<vector<vector<Vehicle *>>> spots;
    int floors;
    int rows;
    int spotsPerRow;

public:
    ParkingLot(int floors, int rows, int spotsPerRow)
    {
        this->floors = floors;
        this->rows = rows;
        this->spotsPerRow = spotsPerRow;
        spots.resize(floors);
        for (int i = 0; i < floors; i++)
        {
            spots[i].resize(rows);
            for (int j = 0; j < rows; j++)
            {
                spots[i][j].resize(spotsPerRow);
            }
        }
    }

    bool park(Vehicle *v, int floor, int row, int spot)
    {
        if (spots[floor][row][spot] == nullptr)
        {
            spots[floor][row][spot] = v;

            cout << v->getType() << " parked successfully at floor " << floor << ", row " << row << ", spot " << spot << "." << "\n";

            return true;
        }
        else
        {
            cout << "Spot already occupied." << endl;
            return false;
        }
    }

    bool leave(Vehicle *v)
    {
        for (int i = 0; i < floors; i++)
        {
            for (int j = 0; j < rows; j++)
            {
                for (int k = 0; k < spotsPerRow; k++)
                {
                    if (spots[i][j][k] == v)
                    {
                        double hours = calculateHoursParked(spots[i][j][k]);
                        double cost = spots[i][j][k]->calculateCost(hours);
                        spots[i][j][k] = nullptr;
                        string type = v->getType();
                        cout << type << " left successfully. Total cost: " << cost << endl;
                        return true;
                    }
                }
            }
        }
        cout << (v->getType()) << " not found." << endl;
        return false;
    }

    int availableSpots(int floor)
    {
        int count = 0;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < spotsPerRow; j++)
            {
                if (spots[floor][i][j] == nullptr)
                {
                    count++;
                }
            }
        }
        return count;
    }

    int handicappedSpots(int floor)
    {
        int count = 0;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < spotsPerRow; j++)
            {
                if (dynamic_cast<HandicappedVehicle *>(spots[floor][i][j]) != nullptr)
                {
                    count++;
                }
            }
        }
        return count;
    }

    double calculateHoursParked(Vehicle *v)
    {
        for (int i = 0; i < floors; i++)
        {
            for (int j = 0; j < rows; j++)
            {
                for (int k = 0; k < spotsPerRow; k++)
                {
                    if (spots[i][j][k] == v)
                    {
                        // get the current time
                        auto now = chrono::system_clock::now();
                        // get the time the vehicle was parked
                        auto parkedTime = spots[i][j][k]->getParkedTime();
                        // calculate the difference in hours
                        auto duration = chrono::duration_cast<chrono::milliseconds>(now - parkedTime);

                        return duration.count();
                    }
                }
            }
        }
        return 0;
    }
};
