/*
 ============================================================================
 Name        : Publicaciones-Project.c
 Author      : Pugna
 Version     :
 Copyright   : copi derecha
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <commons/string.h>
#include <commons/log.h>

#define BUF_SIZE 100000

FILE* in;
FILE* out;
void obtenerPublicaciones();
void abrirArchivos();
void cerrarArchivos();

int main(void) {
	abrirArchivos();
	obtenerPublicaciones();
	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
	return EXIT_SUCCESS;
}

void abrirArchivos(){
	in = fopen("/home/lucas/Documentos/ML-Project/template.html","r");
	out = fopen("/home/lucas/workspace/ML-Publicaciones/resu.txt","w");
}

void cerrarArchivos(){
	fclose(in);
	fclose(out);
}

void obtenerPublicaciones(){
	char* buf = malloc(BUF_SIZE);
	char* pos = NULL;
	char* campo = NULL;
	char* fin = NULL;
	char* aux;

	fread(buf,sizeof(char),BUF_SIZE,in);

	pos=buf;
	campo=pos;

	int h;
	while(1){

	if((campo=strstr(pos,"list-view-item-title"))==NULL){
		printf("No encontrado");
		abort();
	}
	pos=campo;
	if((campo=strstr(pos,"<a href="))==NULL){
		cerrarArchivos();
		abort();
	}
		campo+=9;
		int i=0;
	fin=campo;
	if((fin=strstr(campo,"\">"))==NULL){
		cerrarArchivos();
		abort();
	}

	pos=fin+2;
	strcpy(fin,"\0");
	fwrite(campo,1,strlen(campo),out);
	fwrite(" ",1,1,out);
	fwrite("\\",1,1,out);
	campo=pos;
	fin=campo;

	//Busco titulo
	if((fin=strstr(campo,"</a>"))==NULL){
		cerrarArchivos();
		abort();
	}

	pos=fin+1;
	strcpy(fin,"\0");
	fwrite(campo,1,strlen(campo),out);
	fwrite(" ",1,1,out);
	fwrite("\\",1,1,out);
	campo=pos;
	fin=campo;

	//Busco Precio
	if((campo=strstr(fin,"ch-price"))==NULL){
		cerrarArchivos();
		abort();
	}
	campo+=10;

	if((fin=strstr(campo,"</strong"))==NULL){
		cerrarArchivos();
		abort();
	}
	pos=fin+1;
	strcpy(fin,"\0");
	fwrite(campo,1,strlen(campo),out);
	fwrite(" ",1,1,out);
	fwrite("\\",1,1,out);
	campo=pos;
	fin=campo;


	//Busco Lider
	if((pos=strstr(campo,"list-view-item-title"))==NULL){
		cerrarArchivos();
		abort();
	}
	strcpy(pos-1,"\0");
	aux=campo;
	if((campo=strstr(aux,"info-sold"))!=NULL){
	campo+=11;
	fin=strstr(campo,"vend");
	strcpy(fin,"\0");
	fwrite(campo,1,strlen(campo),out);
	}
	fwrite("\n",1,1,out);

	campo=pos;
	fin=campo;
	aux=NULL;
	}
		}
