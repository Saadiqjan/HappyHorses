/* Author: Saadiq Shahsamand
 * Creation Date: Aug 3, 2026
 * Modified Date: Aug 3, 2026
 * Filename: OamManager.h
 * Project Name: HappyHorses
 * Description: Header file for OAM manager
 */

#pragma once
#include <nds.h>
#include <array>

using std;

class OamManager {
    public:
        static constexpr MAX_SPRITES = 128;
        static constexpr int MAX_AFFINE = 32;

        explicit OamManager(OamState *oam);

        int allocate();
        void free(int index);

        int allocateAffine();
        void freeAffine(int index);

        bool isAllocated() const;
        int freeCount() const;

        OamState* getOam() const;
    private:
        OamState *oam;

        array<bool, MAX_SPRITES> usedSlots{};
        array<bool, MAX_AFFINE>  usedAffine{};
};