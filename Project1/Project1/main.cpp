#include <iostream>
#include <cstdlib>
#include <ctime> 
#include "lib.h"
#include "viewer.h"
#include "simulation.h"
#include "controller.h"

#define MAX_ANGLE 359.9
#define AUX_LEN 20 
#define EOT '\0'
#define SPEED 1
#define NO_DATA -1
#define RECIEVED_DATA 1

#define PRINT_PAJAROS for (int i = 0; i < N_PAJAROS; i++){ pos = birds[i].getPos(); cout << "POSX:"<<pos.posx << endl; cout << "POSY:"<< pos.posy << endl; cout << "DIR:" << birds[i].getDir() << endl;}
using namespace std;

// Estructuras para recepcion de datos //
// ---------------------------------- //
typedef struct {
	unsigned int value;
	int flag;
} data_set;

typedef struct { 
	data_set bird_cnt_data;
	data_set eyeSight_data;
	data_set randomJiggle_data;
}cmd_data;
// ---------------------------------- //

// lowerize_word: pasa toda una palabra a minusculas a un arreglo auxiliar
void lowerize_word(char *src, char dst_arr[], unsigned int size);

// look_on_table: busca la opcion indicada en la tabla
int look_on_table(char arr[]);

const char *lookup_table[] = { "birds", "eyesight", "randomjiggle", "EOTABLE" };
int parseCallback(char *key, char *value, void *userData);

int main(int argc, char *argv[])
{
	srand((unsigned)time(NULL)); 
	cmd_data sim_data; // Estructura de datos recibidos del cmd

	// Inicializo flags de recepcion de datos
	sim_data.bird_cnt_data.flag = NO_DATA;
	sim_data.eyeSight_data.flag = NO_DATA;
	sim_data.randomJiggle_data.flag = NO_DATA;
	
	char *test[] = { "FileName", "-birds", "15", "-eyesight", "3", "-randomjiggle", "2"};
	int cmd_ans = 0;
	
	cmd_ans = parseCmdLine(7, test, parseCallback, &sim_data);

	if (!cmd_ans) {
		cout << "Los datos ingresados no son correctos" << endl;
		return -1;
	}
	else if (cmd_ans < 3) {
		cout << "Faltan datos" << endl;
		return -1;
	}

	Bird *birds = new Bird[sim_data.bird_cnt_data.value]; // Construccion de pajaros

	for (int i = 0; i < sim_data.bird_cnt_data.value; i++) // Inicializacion de pajaros
	{
		birds[i].initRandom(sim_data.eyeSight_data.value, SPEED); // Velocidad predeterminada inicial
	}

	controller control1;
	control1.birds = birds;
	control1.birdcount = sim_data.bird_cnt_data.value;

	simulation sim;

	viewer view(100, 70, birds, sim_data.bird_cnt_data.value);
	view.init_allegro();
	if (!view.is_init_ok()) {
		return -2;
	}

	if (control1.justinit()) { // solo debe ser llamada 1 sola vez
		delete[] birds;
		return -1;
	} 

	control1.display = view.display; // controller necesita de un puntero al display para poder registrarlo
	
	if (control1.register_events()) {
		delete[] birds;
		return -1;
	}

	while (control1.isnotexit()) { // Main loop //
		control1.update_ctrl();
		sim.update(birds, sim_data.bird_cnt_data.value);
		view.update_display();
		//cout << birds->getSpeed() << "-" << birds->getMaxRandomJiggle() << endl;
	}

	control1.destroy_controller_utils();
	delete[] birds;
	return 0;
}


int parseCallback(char *key, char *value, void *userData) {

	cmd_data *birdSim_data = (cmd_data*)userData;
	int ret = 1, i = 0; // Si no pasa nada ret se mantiene en 1
	unsigned int aux_value = 0;
	char aux_key[AUX_LEN];

	if (key == NULL) {
		ret = 0; // Solo recibe opciones, no parametros
	}
	else {
		lowerize_word(key, aux_key, AUX_LEN); // Paso todo a minusculas
		i = look_on_table(aux_key);
		if (i == -1) {
			ret = 0;
		}
		else {
			if (!strcmp(aux_key, "birds")) { // Cantidad de pajaros
				if (birdSim_data->bird_cnt_data.flag == NO_DATA) {
					aux_value = atoi(value);
					if (aux_value <= 0) {
						ret = 0;
					}
					else {
						birdSim_data->bird_cnt_data.value = aux_value;
						birdSim_data->bird_cnt_data.flag = RECIEVED_DATA;
					}
				}
				else{
					ret = 0; // Ya se paso este valor
				}

			}
			else if (!strcmp(aux_key, "eyesight")) { // Eyesight de los pajaros
				if (birdSim_data->eyeSight_data.flag == NO_DATA) {
					aux_value = atoi(value);
					if (aux_value <= 0) {
						ret = 0;
					}
					else {
						birdSim_data->eyeSight_data.value = aux_value;
						birdSim_data->eyeSight_data.flag = RECIEVED_DATA;
					}
				}
				else {
					ret = 0; // Ya se paso este valor
				}

			}
			else if (!strcmp(aux_key, "randomjiggle")) { // Random Jiggle de los pajaros
				if (birdSim_data->randomJiggle_data.flag == NO_DATA) {
					aux_value = atoi(value);
					if (aux_value <= 0) {
						ret = 0;
					}
					else {
						birdSim_data->randomJiggle_data.value = aux_value;
						birdSim_data->randomJiggle_data.flag = RECIEVED_DATA;
					}
				}
				else {
					ret = 0; // Ya se paso este valor
				}


			}
		}
	}
	return ret;
}

void lowerize_word(char *src, char dst_arr[], unsigned int size) {

	for (int i = 0; (i < (AUX_LEN - 1)); i++) {
		dst_arr[i] = (char)tolower(src[i]); // Pasamos todo a minusculas
		if (src[i] == EOT)
			dst_arr[i] = EOT;
	}
}

int look_on_table(char arr[]) { 

	unsigned int k = 0;

	while ((lookup_table[k] != "EOTABLE") && (strcmp(lookup_table[k], arr)))
	{
		k++;
	}

	return ((lookup_table[k] == "EOTABLE") ? -1 : k);
}



//int main()
//{
//	srand((unsigned)time(NULL));
//	Bird birds[N_PAJAROS];
//	position pos;
//	for (int i = 0; i < N_PAJAROS; i++)
//	{
//		birds[i].initRandom(USER_DATA_EYESIGHT, USER_DATA_SPEED);
//	}
//	PRINT_PAJAROS
//	for (int k = 0; k < N_PAJAROS; k++)
//	{
//		birds[k].calculateNewDir(birds, N_PAJAROS);
//	}
//	for (int j = 0; j < N_PAJAROS; j++)
//	{
//		birds[j].move();
//	}
//	PRINT_PAJAROS
//	//Prueba de impresion de pajaros
//	viewer view(100, 70, birds, N_PAJAROS);
//	view.init_allegro();
//	if (!view.is_init_ok()) {
//		return -2;
//	}
//	view.update_display();
//
//	getchar();
//	return 0;
//}


//Prueba de impresion de pajaros
/*viewer view(100, 70, birds, N_PAJAROS);
view.init_allegro();
if (!view.is_init_ok()) {
return -2;
}
view.update_display();*/