/*
 Author: Blake
 Date: 12/22/17
 */

#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#include <limits>
#include <iostream>

using std::cout;
using std::endl;

class Constants
{
private:
    int numGroups;
    unsigned long long numHis;
    double tolerance = std::numeric_limits<double>::epsilon();
    bool allTets = false;
    bool locked;
    
public:
    Constants() {};
    int getNumHis()
    {
        return numHis;
    }
    
    int getNumGroups()
    {
        return numGroups;
    }

    bool getAllTets()
    {
        return allTets;
    } 
    
    double tol()
    {
        return tolerance;
    }
    
    void setNumGroups(int numGroupsi)
    {
        if(!locked)
        {
            numGroups = numGroupsi;
        }
        else
        {
            cout << "Access denied. Constants are locked." << endl;
        }
    }
    
    void setNumHis(int numHisi)
    {
        if(!locked)
        {
            numHis = numHisi;
        }
        else
        {
            cout << "Access denied. Constants are locked." << endl;
        }
    }
    void setAllTets()
    {
        if(!locked)
        {
            allTets = true;
        }
        else
        {
            cout << "Access denied. Constants are locked." << endl;
        }
    }
    
    void lock()
    {
        locked = true;
    }
    
};

#endif

