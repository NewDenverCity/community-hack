#include <pokeagb.h>

static u32 calculate_stat_total(struct Pokemon* pokemon)
{
    u32 stat_total = 0;
    for (u8 i = 0; i < 6; i++) {
        stat_total += pokemon_getattr(pokemon, REQUEST_TOTAL_HP + i, NULL);
    }

    return stat_total;
}

static u32 calculate_max_possible_stat_total(struct Pokemon* pokemon)
{
    enum PokemonSpecies species = pokemon_getattr(pokemon, REQUEST_SPECIES2, NULL);
    u8* base_stats = &pokemon_base_stats[species].hp;

    /* The best possible nature (i.e. the one that yields the highest
     * net stat increase) for a given Pokemon will increase the
     * Pokemon's highest stat, and decrease the lowest stat.
     * Therefore the minimum and maximum unadjusted stats need to be
     * found. Exclude HP because nature cannot affect it. */
    u8 max_stat = 0, min_stat = 0xFF;
    for (u8 i = 1; i < 6; i++) {
        if (base_stats[i] > max_stat) {
            max_stat = base_stats[i];
        }

        if (base_stats[i] < min_stat) {
            min_stat = base_stats[i];
        }
    }

    /* Lookup a nature that fits the above criteria. */
    enum PokemonNature nature;
    for (nature = 0; nature < NATURE_MAX; nature++) {
        if (nature_stat_bonuses[nature][max_stat - 1] == 1
            && nature_stat_bonuses[nature][min_stat - 1] == -1) {

            break;
        }
    }

    /* Calculate the maximum possible stat total for this Pokemon,
     * excluding EVs. The easiest way to do this is by creating a fake
     * Pokemon that represents the perfect version of the captured
     * Pokemon. */
    struct Pokemon perfect_pokemon = *pokemon;
    u32 max_iv = 31;
    u32 min_ev = 0;
    for (u8 i = 0; i < 6; i++) {
        pokemon_setattr(&perfect_pokemon, REQUEST_HP_IV + i, &max_iv);
        pokemon_setattr(&perfect_pokemon, REQUEST_HP_EV + i, &min_ev);
    }

    /* PID is used to determined nature: nature = pid % 25. Since
     * there are 25 natures, setting PID to a given nature index will
     * force that nature. */
    u32 pid = nature;
    pokemon_setattr(&perfect_pokemon, REQUEST_PID, &pid);

    recalculate_stats(&perfect_pokemon);
    return calculate_stat_total(&perfect_pokemon);
}

static u8 calculate_rarity(struct Pokemon* pokemon)
{
    enum PokemonSpecies species = pokemon_getattr(pokemon, REQUEST_SPECIES2, NULL);
    return pokemon_rarity[species];
}

extern u16 fishing_contest_score_pokemon(struct Pokemon* pokemon)
{
    u16 stat_total = calculate_stat_total(pokemon);
    u16 max_stat_total = calculate_max_possible_stat_total(pokemon);

    u16 score = (stat_total << 8) / max_stat_total;
    score *= calculate_rarity(pokemon);

    if (pokemon_is_shiny(pokemon)) {
        score *= 2;
    }

    return score;
}
