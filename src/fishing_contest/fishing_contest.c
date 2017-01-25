#include <pokeagb/pokeagb.h>
#include "fishing_contest.h"

static const struct Contestant fishing_contestants[] =
{
  {SPECIES_MAGIKARP, 1, 1, 5},
	{SPECIES_GYARADOS, 2, 20, 30},
	{SPECIES_WAILORD, 3, 50, 60}
	/* just an example tbh */
};

static void fishing_contest(u8 entry_number)
{
    u32 *contestants;
    struct Pokemon* contestants = malloc_and_clear(sizeof(Pokemon) * entry_number); /* treat contestants like an array */
    memcpy(*contestants[0], *party_opponent[0], sizeof(Pokemon)); /* the 0th entry is you */
    for (i = 0; i < entry_number - 1; i++); /* generate a pokemon from the fishing_contestants list, make the pokemon from that list */
    {
        u8 table_slot = rand() % number_of_encounters;
        u16 entrant_species = fishing_contestants[table_slot]->species;
        u8 entrant_level = get_generated_level(entrant_species);
        make_pokemon_full(*contestants[i + 1], entrant_species, entrant_level, 0x21, 1, 0, 2, 0); /* don't use the given PID or TID */
    }
    judge_all_fishing_contestants(*contestants, entry_number); /* get the stuff and store the results into vars */
    return;
}

u8 get_generated_level(u16 entrant_species)
{
    u8 entrant_level = (rand() % (fishing_contestants[table_slot]->max_level - fishing_contestants[table_slot]->min_level) + fishing_contestants[table_slot]->min_level);
    return entrant_level;
}

static void judge_all_fishing_contestants(struct Pokemon* contestants, u8 entry_number)
{
    for (u8 i = 0; i < entry_number; i++) /* get the score from the pointer, buffer them in var8000 and up */
                                          /* score; pokemon; something somehow used to determine who it belongs to */
    {
        u16 score = fishing_contest_score_pokemon(*contestants[i]);
        u16 species = pokemon_getattr(*contestants[i], REQUEST_SPECIES, NULL);
        if (score > var8000)
        {
            var8000 = score;
            var8001 = species;
            var8002 = rand(); /* not done yet */
        }
    }
    return;
}
