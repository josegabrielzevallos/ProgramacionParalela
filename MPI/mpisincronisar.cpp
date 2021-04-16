#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc,char *argv[])
{
	//Es un rank asignado para cada proceso en una comunicacion
	int rank;
	//total de nuemos de ranks
	int size;
	//la maquina en la qu estamos
	char name[80];
	//tamaño del nombre de la maquina
	int length;
	//inicialasiamos el mpi en la ejecucion
	MPI_Init(&argc,&argv);


	MPI_Comm_rank(MPI_COMM_WORLD,&rank);


	MPI_Comm_size(MPI_COMM_WORLD,&size);

	MPI_Get_processor_name(name,&length);

//paquete de valoresjunto dentro un string
	
/////////////////////////////////////////////////////////////////////////////////////////
	int buffer_len=150;
	char buffer[buffer_len];
	sprintf(buffer,"Hola, MPI! Rank: %d Total: %d Machine %s",rank,size,name);

	if(rank==0){
		printf("%s\n",buffer );
		for(int i=1;i<size;i++){

			MPI_Recv(buffer,buffer_len,MPI_CHAR,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,MPI_STATUS_IGNORE);

			printf("%s\n",buffer );
		}	
	}else{
		MPI_Send(buffer,buffer_len,MPI_CHAR,0,rank,MPI_COMM_WORLD);
	}
///////////////////////////////////////////////////////////////////////////////////////////////
	//cout<<"Hola,MPI! Rank "<< rank << " size " << size << " name " << name << endl;

	MPI_Finalize();

	return 0;
}