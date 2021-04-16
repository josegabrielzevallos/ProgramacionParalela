#include <mpi.h> 
#include <stdio.h> 

double   t0, t1;
void   Leer_datos(double* a_ptr, double* b_ptr, int* n_ptr, int pid, int npr); 
double Integrar(double a_loc, double b_loc, int n_loc, double w); 
double f(double x); 

int main(int argc, char** argv)  {   
int  pid, npr;                 
// Identificador y numero de proc.   
double a, b, w, a_loc, b_loc;       
int n, n_loc, resto, kont;      
double resul, resul_loc; 

// Resultado de la integral  
int origen, destino, tag;
MPI_Status  status;   
MPI_Init(&argc, &argv);   
MPI_Comm_rank(MPI_COMM_WORLD, &pid);   
MPI_Comm_size(MPI_COMM_WORLD, &npr);

// Lectura y distribucion de parametros a todos los procesadores    
Leer_datos(&a, &b, &n, pid, npr);   
w = (b-a) / n;     

// cada uno calcula el trozo que tiene que sumar    n_loc = n / npr;   
resto = n % npr; 

if (pid < resto) n_loc = n_loc + 1;   
	a_loc = a + pid * n_loc * w;   
if (pid >= resto) a_loc = a_loc + resto * w;   
	b_loc = a_loc + n_loc * w;

// Calculo de la integral local   

resul_loc = Integrar(a_loc, b_loc, n_loc, w);

// Impresion de resultados   
if (pid == 0)    
{     
	t1 = MPI_Wtime();  
	printf("\n Integral(= lnx+1+ atan x), de %1.1f a %1.1f, %d trap. = %1.12f\n", a,b,n,resul);    
	printf("    Tiempo ejecucion (%d pr.) = %1.3f ms \n\n", npr, (t1-t0)*1000);   
}   
MPI_Finalize();   
return 0; 
} /*  main  */

void Leer_datos(double* a_ptr, double* b_ptr, int* n_ptr, int pid, int npr) 
{   
int origen, destino, tag;   
float aux_a, aux_b;   
MPI_Status status;

if (pid == 0)   
	{     
	printf("\n  Introduce a, b (limites) y n (num. de trap.<= 10e8)  \n");     
	scanf("%f %f %d", &aux_a, &aux_b, n_ptr);     
	t0 = MPI_Wtime();     
	(*a_ptr) = (double)aux_a;// a_ptr, b_ptr, n_ptr: punteros a a, b y n     
	(*b_ptr) = (double)aux_b;
	} 
} /* Leer_datos */

double Integrar(double a_loc, double b_loc, int n_loc, double h) 
{    
double resul_loc, x;    
int    i ,w;  
// calculo de la integral   
resul_loc = (f(a_loc) + f(b_loc)) / 2.0;    
x = a_loc;    
for (i=1; i<n_loc; i++)    
	{      
	x = x + w;      
	resul_loc = resul_loc + f(x);    
	}    
resul_loc = resul_loc * w;    
return resul_loc; 
} /*  Integrar  */ 
// FUNCION f: funcion a integrar 

double f(double x) 
{    
	double y;    
	y = 1.0 / (x + 1.0) + 1.0 / (x*x + 1.0) ;   
	return y;  
}  