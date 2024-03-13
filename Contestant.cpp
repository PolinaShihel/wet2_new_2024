//
// Created by pshih on 12/03/2024.
//

#include "Contestant.h"

Contestant::Contestant(int entry, int strength) : entry(entry), strength(strength){};

int Contestant::get_strength() {
    return strength;
}
int Contestant::get_entry() {
    return entry;
}
void Contestant::set_entry(int entry) {
    this->entry = entry;
}