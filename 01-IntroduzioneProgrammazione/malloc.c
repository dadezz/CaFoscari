/*reversed: restituisce l'array a ordine inverso*/

int * reversed (int * A, int N){

    int * REV = (int*) malloc (N *sizeof(int));//riservami N per 4 byte ocnsecutuvi co puntatore alla prima pos
    return REV; // è un puntstore a un'area di memoria grande N
}

//malloc sopravvive agli scope.
//esiste la funzione free che serve proprio a deallocare la memoria (importante operazione di pulizia)