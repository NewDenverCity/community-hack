		// replace menu text to spell PokeNav instead of PokeDex
		//.org 0x0841627D
		//.byte 0xCA, 0xC9, 0xC5, 0x1B, 0xC8, 0xBB, 0xD0, 0xFF
		
		// replace menu item description for Pokedex with Pokenav
		//.org 0x08419F76
		//.byte 0xBB, 0xE2, 0x00, 0xD9, 0xE0, 0xD9, 0xD7, 0xE8, 0xE6, 0xE3, 0xE2, 0xDD, 0xD7, 0x00, //0xD8, 0xD9, 0xEA, 0xDD, 0xD7, 0xD9, 0x00, 0xD7, 0xE3, 0xE2, 0xE8, 0xD5, 0xDD, 0xE2, 0xDD, //0xE2, 0xDB, 0x00, 0xD7, 0xE3, 0xE2, 0xEA, 0xD9, 0xE2, 0xDD, 0xD5, 0xE2, 0xE8, 0x00, 0xD5, //0xE4, 0xE4, 0xE0, 0xDD, 0xD7, 0xD5, 0xE8, 0xDD, 0xE3, 0xE2, 0xE7, 0xAD, 0xFF
		
		.org 0x083A7378
		.word prelaunch_pokenav_setup|1
		
		.org 0x0806F3C4
		.word prelaunch_pokenav_setup|1
		
		.org 0x80F799A
		.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
		