/* Author: Saadiq Shahsamand
 * Creation Date: Aug 3, 2026
 * Modified Date: Aug 6, 2026
 * Filename: OamManager.cpp
 * Project Name: HappyHorses
 * Description: Keeps track of used slots in object attribute memory
 */

#include "core/OamManager.h"

using namespace std;

OamManager::OamManager(OamState* oam)
    : oam(oam)
{
}

int OamManager::allocate()
{

    for (int i = 0; i < MAX_SPRITES; ++i)
    {
        if (!usedSlots[i])
        {
            usedSlots[i] = true;
            return i;
        }
    }

    return -1;
}

void OamManager::free(int index)
{
    if (index < 0 || index >= MAX_SPRITES) 
    {
        return;
    }

    usedSlots[index] = false;
}

int OamManager::allocateAffine()
{
    for (int i = 0; i < MAX_AFFINE; ++i)
    {
        if (!usedAffine[i])
        {
            usedAffine[i] = true;
            return i;
        }
    }

    return -1;
}

void OamManager::freeAffine(int index)
{
    if (index < 0 || index >= MAX_AFFINE) 
    { 
        return;
    }
    
    usedAffine[index] = false;
}

bool OamManager::isAllocated(int index) const
{
    if (index < 0 || index >= MAX_SPRITES) 
    {
        return false;
    }

    return usedSlots[index];
}

int OamManager::freeCount() const
{
    int count = 0;

    for (bool used : usedSlots)
    {
        if (!used) 
        {
            count++;   
        }
    }

    return count;
}

OamState* OamManager::getOam() const
{
    return oam;
}