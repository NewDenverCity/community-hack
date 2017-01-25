#ifndef FISHING_CONTEST_H
#define FISHING_CONTEST_H

#include <pokeagb/pokeagb.h>

u8 number_of_encounters = 3 /* example */

struct Contestant
{
    u16 species;
    u8 rarity;
    u8 min_level;
    u8, max_level;
};

u16 fishing_contest_score_pokemon(struct Pokemon* pokemon)

#endif /* FISHING_CONTEST_H */
