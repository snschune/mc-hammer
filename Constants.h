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
    double tolerance = std::numeric_limits<double>::epsilon();
    bool locked;
    
public:
    Constants() {};
    
    int getNumGroups()
    {
        return numGroups;
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
    
    void lock()
    {
        locked = true;
    }
    
};

#endif

