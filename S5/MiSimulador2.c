#include "CacheSim.h"

/* Posa aqui les teves estructures de dades globals
 * per mantenir la informacio necesaria de la cache
 * */
#include <stdio.h>
unsigned int total_hit; // Comptadors
unsigned int total_miss;
unsigned char valid[64]; // vector que indica quines linies d'un conjunt son valids: (0 = cap, 1 = només linia via 0, 2 = totes dues)
unsigned char LRU[64]; // vector que indica quina ha sigut l'ultima linia utilitzada per cada conjunt
unsigned int tags0[64]; // vector que guarda les etiquetes de les linies de la via 0
unsigned int tags1[64]; // vector que guarda les etiquetes de les linies de la via 1



/* La rutina init_cache es cridada pel programa principal per
 * inicialitzar la cache.
 * La cache es inicialitzada al començar cada un dels tests.
 * */
void init_cache ()
{
    totaltime=0.0;
	/* Escriu aqui el teu codi */
	// Simulem una cache buida
	total_hit = 0;
	total_miss = 0;
	for (int i = 0; i < 64; ++i) {
		valid[i] = 0;
		LRU[i] = 0;
		tags0[i] = 0;
		tags1[i] = 0;
	}
}

/* La rutina reference es cridada per cada referencia a simular */ 
void reference (unsigned int address)
{
	unsigned int byte;
	unsigned int bloque_m; 
	unsigned int conj_mc;
	unsigned int via_mc;
	unsigned int tag;
	unsigned int miss;	   // boolea que ens indica si es miss
	unsigned int replacement;  // boolea que indica si es reemplaça una linia valida
	unsigned int tag_out;	   // TAG de la linia reemplaçada
	float t1,t2;		// Variables per mesurar el temps (NO modificar)
	
	t1=GetTime();
	/* Escriu aqui el teu codi */
	// Calcul de les variables d'acord a les caracteristiques de la memoria cache
	byte = address & 0b11111;
	bloque_m = address >> 5;
	conj_mc = bloque_m & 0b111111;
	tag = address >> 11;
	if (valid[conj_mc] == 0) { // Cas cap linia d'un conjunt es valida
		via_mc = 0; // (suposem per enunciat que es guarda a via 0)
		// En el cas inicial, LRU = 0 aixi que no cal actualtizar LRU[]
		miss = 1;
		replacement = 0;
		valid[conj_mc] = 1; // linia via 0 valida, assignem tag
		tags0[conj_mc] = tag;
		++total_miss;
	}
	else if (valid[conj_mc] == 1) { // Cas linia via 0 es valida
		if (tags0[conj_mc] == tag) { // HIT
			via_mc = 0;
			miss = 0;
			replacement = 0;
			++total_hit;
			// En el cas inicial, LRU = 0 aixi que no cal actualtizar LRU[]
		}
		else { // MISS, com que linia via 1 no es valida, guardem la dada en aquesta
			via_mc = 1;
			miss = 1;
			replacement = 0;
			valid[conj_mc] = 2; // Ambdues linies del conjunt pasaran a ser valides, assignem tag
			tags1[conj_mc] = tag;
			LRU[conj_mc] = 1; // L'ultima linia utilitzada sera la de la via 1
			++total_miss;
		}
	} else { // Cas ambdues linies son valides
		if (tags0[conj_mc] == tag) { // HIT a via 0
			via_mc = 0;
			miss = 0;
			replacement = 0;
			++total_hit;
			LRU[conj_mc] = 0; // Ultima linia utilitzada: via 0
		}
		else if (tags1[conj_mc] == tag) { // HIT a via 1
			via_mc = 1;
			miss = 0;
			replacement = 0;
			++total_hit;
			LRU[conj_mc] = 1; // Ultima linia utiltizada: via 1
		}
		else { // MISS en el conjunt
			via_mc = !LRU[conj_mc]; // Es guardara la dada a la via contraria a l'ultima utilitzada
			miss = 1;
			replacement = 1;
			if (via_mc == 0) {
				LRU[conj_mc] = 0; // Ultima linia utilitzada: via 0
				tag_out = tags0[conj_mc]; // Treiem tag antic i actualitzem "tag" a la via corresponent
				tags0[conj_mc] = tag;
			}
			else {
				LRU[conj_mc] = 1; // Ultima linia utilitzada: via 1
				tag_out = tags1[conj_mc];
				tags1[conj_mc] = tag;
			}
			++total_miss;
		}
	}
	/* La funcio test_and_print escriu el resultat de la teva simulacio
	 * per pantalla (si s'escau) i comproba si hi ha algun error
	 * per la referencia actual. També mesurem el temps d'execució
	 * */
	t2=GetTime();
	totaltime+=t2-t1;
	test_and_print2 (address, byte, bloque_m, conj_mc, via_mc, tag,
			miss, replacement, tag_out);
}

/* La rutina final es cridada al final de la simulacio */ 
void final ()
{
 	/* Escriu aqui el teu codi */ 
  	printf("TOTAL HITS = %d, TOTAL MISSES = %d\n", total_hit, total_miss);
}
