#include "CacheSim.h"

/* Posa aqui les teves estructures de dades globals
 * per mantenir la informacio necesaria de la cache
 * */
#include <stdio.h>
int tags[128];
unsigned int total_hit, total_miss;


/* La rutina init_cache es cridada pel programa principal per
 * inicialitzar la cache.
 * La cache es inicialitzada al comen�ar cada un dels tests.
 * */
void init_cache ()
{
	/* Escriu aqui el teu codi */
	for (int i = 0; i < 128; ++i) tags[i] = -1;
	total_hit = 0;
	total_miss = 0;

}

/* La rutina reference es cridada per cada referencia a simular */ 
void reference (unsigned int address, unsigned int LE)
{
	unsigned int byte;
	unsigned int bloque_m; 
	unsigned int linea_mc;
	unsigned int tag;
	unsigned int miss;
	unsigned int lec_mp;
	unsigned int mida_lec_mp;
	unsigned int esc_mp;
	unsigned int mida_esc_mp;
	unsigned int replacement;
	unsigned int tag_out;

	/* Escriu aqui el teu codi */
	byte = address & 0b11111;
	bloque_m = address >> 5;
	linea_mc = bloque_m & 0b1111111;
	tag = address >> 12;

	if (LE == lectura) {
		if (tags[linea_mc] == -1) { // Cas lectura de linia buida
			miss = true;
			lec_mp = true;
			mida_lec_mp = 32;
			esc_mp = false;
			replacement = false;
			tags[linea_mc] = tag;
			++total_miss;
		}
		else {
			if (tags[linea_mc] == tag) { // Cas hit en lectura
				miss = false;
				lec_mp = false;
				esc_mp = false;
				replacement = false;
				++total_hit;
			}
			else { // Cas miss en lectura
				miss = true;
				lec_mp = true;
				mida_lec_mp = 32;
				esc_mp = false;
				replacement = true;
				tag_out = tags[linea_mc];
				tags[linea_mc] = tag;
				++total_miss;
			}
		}
	}
	else {
		if (tags[linea_mc] == -1 || tags[linea_mc] != tag) { // Cas escriptura en linia buida o miss en escriptura (mateix comportament)
			miss = true;
			lec_mp = false;
			esc_mp = true;
			mida_esc_mp = 1;
			replacement = false;
			++total_miss;
		}
		else { // Cas hit en escriptura
			miss = false;
			lec_mp = false;
			esc_mp = true;
			mida_esc_mp = 1;
			replacement = false;
			++total_hit;
		}
	}


	/* La funcio test_and_print escriu el resultat de la teva simulacio
	 * per pantalla (si s'escau) i comproba si hi ha algun error
	 * per la referencia actual
	 * */
	test_and_print (address, LE, byte, bloque_m, linea_mc, tag,
			miss, lec_mp, mida_lec_mp, esc_mp, mida_esc_mp,
			replacement, tag_out);
}

/* La rutina final es cridada al final de la simulacio */ 
void final ()
{
 	/* Escriu aqui el teu codi */ 
	printf("TOTAL HITS = %d, TOTAL MISSES = %d\n", total_hit, total_miss);
  
}
