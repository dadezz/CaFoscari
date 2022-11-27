#include<stdlib.h>
#include<stdio.h>
#include<time.h>

int ask_mod();
int ask_default();
void map_scan_from_input(char* map, int rows, int columns);
void random_ins_chars (int N, char* map, int map_size, char c);
int char_counter (char* map, int map_size, char c);
void do_you_need_bonuses(int map_size, char* map);
char* map_input_creation(int *rows, int *columns);
int find_char(char* map, int size, char c_to_be_found);
int forward_IA(int position, int direction, int columns);
int right_IA(int position,int  direction, int columns);
int find_start_direction_IA(char*map, int position, int rows, int columns);
void print_IA_output(int direction);
void mod_ai (char* map, int rows, int columns);
void play_challenge ();
void map_print_INTER(char* x, int rows, int columns, int* points, int* bonuses, int*taxes, int*drill);
void input_char_INTER(char* x);
int next_position_INTER (int input_char, int position, int columns);
void INTER_control (char* x, int rows, int columns, int *position, int input_char, int *game, int* bonuses, int* taxes, int* drill);
void mod_interactive(char* map, int rows, int columns);