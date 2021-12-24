#include "CacheSim.h"

/* Posa aqui les teves estructures de dades globals
 * per mantenir la informacio necesaria de la cache
 * */
#include <stdio.h>
int tags[128];
char dirty[128]; // Si dirty[linea_mc] == true, vol dir que el bloc ha estat modificat
unsigned int total_hit, total_miss;


/* La rutina init_cache es cridada pel programa principal per
 * inicialitzar la cache.
 * La cache es inicialitzada al comen�ar cada un dels tests.
 * */
void init_cache ()
{
	/* Escriu aqui el teu codi */
	for (int i = 0; i < 128; ++i) {
		tags[i] = -1;
		dirty[i] = false;
	}
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
				if (dirty[linea_mc] == true) { // Es comprova si el bloc que sera reemplaçat ha sigut modificat
					esc_mp = true;
					mida_esc_mp = 32;
				}
				else {
					esc_mp = false;
				}
				dirty[linea_mc] = false;
				replacement = true;
				tag_out = tags[linea_mc];
				tags[linea_mc] = tag;
				++total_miss;
			}
		}
	}
	else {
		if (tags[linea_mc] == -1) { // Cas escriptura en linia buida
			miss = true;
			lec_mp = true;
			mida_lec_mp = 32;
			esc_mp = false;
			replacement = false;
			tags[linea_mc] = tag;
			dirty[linea_mc] = true;
			++total_miss;
		}
		else {
			if (tags[linea_mc] == tag) { // Cas hit en escriptura
				miss = false;
				lec_mp = false;
				esc_mp = false;
				replacement = false;
				dirty[linea_mc] = true;
				++total_hit;
			}
			else { // Cas miss en escriptura
				miss = true;
				lec_mp = true;
				mida_lec_mp = 32;
				if (dirty[linea_mc] == true) { // Es comprova si el bloc que sera reemplaçat ha sigut modificat 
					esc_mp = true;
					mida_esc_mp = 32;
				}
				else {
					esc_mp = false;
				}
				replacement = true;
				tag_out = tags[linea_mc];
				tags[linea_mc] = tag;
				dirty[linea_mc] = true;
				++total_miss;
			}
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
