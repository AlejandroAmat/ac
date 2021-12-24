#include "CacheSim.h"
/* Posa aqui les teves estructures de dades globals
 * per mantenir la informacio necesaria de la cache
 * */
#include <stdio.h>
unsigned char valid[128]; // Vector per saber si una linea de la cache es valida o no
unsigned int tags[128]; // Vector per guardar les etiquetes de la cache
unsigned int total_hit; // Comptadors
unsigned int total_miss;


/* La rutina init_cache es cridada pel programa principal per
 * inicialitzar la cache.
 * La cache es inicialitzada al començar cada un dels tests.
 * */
void init_cache ()
{
    totaltime=0.0;
	/* Escriu aqui el teu codi */
	// Simulem una cache buida
	for (int i = 0; i < 128; ++i) {
		valid[i] = 0;
		tags[i] = 0;
	}
	total_hit = 0;
	total_miss = 0;

}

/* La rutina reference es cridada per cada referencia a simular */ 
void reference (unsigned int address)
{
	unsigned int byte;
	unsigned int bloque_m; 
	unsigned int linea_mc;
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
	linea_mc = bloque_m & 0b1111111;
	tag = address >> 12;

	if (valid[linea_mc] == 0) { // Cas referencia a una linea no valida
		miss = 1;
		replacement = 0;
		valid[linea_mc] = 1;  // La linea passa a ser valida amb "tag" = tag
		tags[linea_mc] = tag;
		++total_miss;
	}
	else { // Cas referencia a una linea valida
		if (tags[linea_mc] == tag) { // Cas match
			miss = 0;
			replacement = 0;
			++total_hit;
		}
		else { // Cas no match
			miss = 1;
			replacement = 1;
			tag_out = tags[linea_mc]; // tag_out = tag anterior, "tag" = tag nou
			tags[linea_mc] = tag;
			++total_miss;
		}
	}



	/* La funcio test_and_print escriu el resultat de la teva simulacio
	 * per pantalla (si s'escau) i comproba si hi ha algun error
	 * per la referencia actual. També mesurem el temps d'execució
	 * */
	t2=GetTime();
	totaltime+=t2-t1;
	test_and_print (address, byte, bloque_m, linea_mc, tag,
			miss, replacement, tag_out);
}

/* La rutina final es cridada al final de la simulacio */ 
void final ()
{
 	/* Escriu aqui el teu codi */ 
  	printf("TOTAL HITS = %d, TOTAL MISSES = %d\n", total_hit, total_miss);
  
}
