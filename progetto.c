
#include "stdio.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define L 1024
#define C1 18
#define C25 19
#define C3 14
#define C4 13
#define INT_MAX 2147483647
#define HASH_SIZE 1000000
char c1[C1] = "aggiungi-stazione";
char c2[C25] = "demolisci-stazione";
char c3[C3] = "aggiungi-auto";
char c4[C4] = "rottama-auto";
char c5[C25] = "pianifica-percorso";

typedef struct stazione {
    int key;
    int n_car;
    int* car;
    struct stazione* next;
    struct stazione* prev;
    

}stazione;

typedef struct autostrada {
    int conta_n;
    struct stazione* testa;
    struct stazione* coda;
}autostrada;

typedef struct hash_node {
    int key;
    struct stazione* stazione;
    struct hash_node* next;
} hash_node;

typedef struct hash_table {
    hash_node** table;
} hash_table;


void inizializza_hash(hash_table* map) {
    
    map->table = (hash_node**)malloc(sizeof(hash_node*) * HASH_SIZE);
    for (int i = 0; i < HASH_SIZE; i++) {
        map->table[i] = NULL;
    }
    
}

void inserisci_in_hash(hash_table* map, stazione* staz) {
    int index = staz->key % HASH_SIZE;
    hash_node* new_node = (hash_node*)malloc(sizeof(hash_node));
    new_node->key = staz->key;
    new_node->stazione = staz;
    new_node->next = map->table[index];
    map->table[index] = new_node;
    
}

stazione* cerca_stazione(hash_table* map, int key) {
    int index = key % HASH_SIZE;
    hash_node* current = map->table[index];
    while (current != NULL) {
        if (current->key == key) {
            return current->stazione;
        }
        current = current->next;
    }
    return NULL; 
}


void cancella_da_hash(hash_table* map, int key) {
    int index = key % HASH_SIZE;
    hash_node* current = map->table[index];
    hash_node* prev = NULL;
    while (current != NULL) {
        if (current->key == key) {
            if (prev == NULL) {
                map->table[index] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }

    
    
}


void delete_list(autostrada *list){
    stazione *n1, *n2;
    n1 = list->testa;

    
    while (n1 != NULL)
    {
        n2 = n1->next;
        free(n1->car);
        free(n1);
        
        n1 = n2;
    }
}

void swap(int* var1, int* var2) {
    int aiuto;

    aiuto = *var1;
    *var1 = *var2;
    *var2 = aiuto;


}

void max_heapify(int* car, int n_car, int i) {
    int max = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left<n_car && car[left]>car[max]) {
        max = left;
    }
    if (right<n_car && car[right]>car[max]) {
        max = right;
    }
    if (max != i) {
        swap(&car[i], &car[max]);
        max_heapify(car, n_car, max);
    }
}

void build_max_heap(int* car, int n_car) {
    for (int i = n_car / 2 - 1; i >= 0; i--) {
        max_heapify(car, n_car, i);
    }
}

void heap_sort(int* car, int n_car) {
    build_max_heap(car, n_car);
    for (int i = n_car - 1; i >= 0; i--) {
        swap(&car[0], &car[i]);
        max_heapify(car, i, 0);
    }
}



void add_stazione(autostrada* lista, int key, int n_car, int* car, hash_table *mappa) {
    stazione* nodo=NULL, *cur=NULL ,*prev=NULL;
    
    nodo = malloc(sizeof(stazione));
    if(nodo==NULL){
        printf("non aggiunta\n");
        return;
    }
    nodo->car = (int*)malloc(n_car * sizeof(int));
    nodo->key = key;
    nodo->n_car = n_car;
    nodo->next = NULL;
    if (n_car <= L / 2) {
        for (int i = 0; i < n_car; i++) {
            nodo->car[i] = car[i];
        }
        heap_sort(nodo->car, n_car);
    
    }else {
        printf("non aggiunta\n");
        return;
    }

    if (lista->conta_n == 0) {
        nodo->prev = NULL;
        nodo->next=NULL;
        lista->testa = lista->coda = nodo;
        printf("aggiunta\n");
        inserisci_in_hash(mappa, nodo);
        lista->conta_n++;
    }else {
        for(cur=lista->testa,prev=NULL;cur!=NULL && nodo->key>cur->key;prev=cur,cur=cur->next); 
        if(cur!=NULL && nodo->key ==cur->key){
            printf("non aggiunta\n");
            free(nodo->car);
            free(nodo);
            return;
        }
        if(cur==NULL){
            prev->next=nodo;
            nodo->prev=prev;
            lista->coda=nodo;
        }else{
        nodo->next=cur;
        cur->prev=nodo;
    
        if(prev==NULL){
            lista->testa=nodo;
        }else{
           prev->next=nodo;
           nodo->prev=prev;
        }
        }
        
        lista->conta_n++;
        inserisci_in_hash(mappa, nodo);
        printf("aggiunta\n");
    }

   lista->testa->prev=NULL;
   lista->coda->next=NULL;


}

int scelta_comando(char* str) {
    int res = 0;
    if (strcmp(str, c1) == 0) res = 1;
    if (strcmp(str, c2) == 0) res = 2;
    if (strcmp(str, c3) == 0) res = 3;
    if (strcmp(str, c4) == 0) res = 4;
    if (strcmp(str, c5) == 0) res = 5;
    
    return res;
}

void init_autostrada(autostrada* lista) {
    lista->conta_n = 0;
    lista->testa = lista->coda = NULL;

}

void demolisci_stazione(autostrada *lista,hash_table *mappa) {
    int key;
    assert(scanf("%d", &key));
    stazione* nodo = cerca_stazione(mappa, key);
    if (nodo == NULL) {
        printf("non demolita\n");
        return;
    }
    else {
        if (nodo->prev != NULL) {
            nodo->prev->next = nodo->next;
        }
        else {
            lista->testa = nodo->next;
        }
        if (nodo->next != NULL) {
            nodo->next->prev = nodo->prev;
        }
        else {
            lista->coda = nodo->prev;
        }
        cancella_da_hash(mappa,nodo->key);
        free(nodo->car);
        free(nodo);
        lista->conta_n--;
        printf("demolita\n");
    }

}

void aggiungi_auto(hash_table *mappa) {
    int key = 0;
    int key_a = 0;

    assert(scanf("%d", &key));
    assert(scanf("%d", &key_a));

    stazione* nodo = cerca_stazione(mappa, key);;

    if (nodo == NULL || nodo->n_car == (L / 2)) {
        printf("non aggiunta\n");
        return;
    }
    nodo->n_car++;
    nodo->car = realloc(nodo->car, nodo->n_car * sizeof(int));
    nodo->car[nodo->n_car - 1] = key_a;
    heap_sort(nodo->car, nodo->n_car);
    printf("aggiunta\n");
}


void rottama_auto(hash_table *mappa) {
    int key = 0;
    int key_a = 0;
    assert(scanf("%d", &key));
    assert(scanf("%d", &key_a));
    stazione* nodo = cerca_stazione(mappa, key);;
    if (nodo == NULL) {
        printf("non rottamata\n");
        return;
    }
    
    int i = 0;
    while(i < nodo->n_car) {
        if (nodo->car[i] == key_a) {
            nodo->car = realloc(nodo->car, L * sizeof(int));
            if(i!=nodo->n_car-1){
              for (int j = i; j < nodo->n_car; j++) {
                 nodo->car[j] = nodo->car[j + 1];
                }
            }

            nodo->n_car--;
            nodo->car = realloc(nodo->car, nodo->n_car * sizeof(int));
            printf("rottamata\n");
            return;
        }
        i++;
       
    }
   printf("non rottamata\n");
    
}

int cerca_percorso(autostrada* lista, stazione* nodo, int partenza, int* percorso, int j, int* v) {
    int min = -1;

    stazione* nodo_prev = nodo->prev;
    stazione* nuovo_arrivo = NULL;
    while (nodo_prev != NULL && nodo_prev->key >= partenza) {

        if (nodo_prev->n_car && nodo_prev->car[nodo_prev->n_car - 1] >= (nodo->key - nodo_prev->key)) {
            min = nodo_prev->key;
            nuovo_arrivo = nodo_prev;
            
        }
        nodo_prev = nodo_prev->prev;
    }

    if (min == -1) {
        printf("nessun percorso\n");
        *v = -1;
        return 0;
    }
    percorso[j + 1] = min;
    j++;


    if (min > partenza) {
        int y = j;
        j = cerca_percorso(lista, nuovo_arrivo, partenza, percorso, y, v);
    }


    return j;

}

int cerca_percorso_2(autostrada* lista, stazione* nodo, int arrivo, int* percorso, int j, int* v) {
    int min = -1;
    stazione* nodo_prev = nodo->prev;
    int min_dist = INT_MAX;
    stazione* nuova_partenza = NULL;
    if(nodo->n_car!=0){
        if (nodo->key - nodo->car[nodo->n_car - 1] <= arrivo) {
           percorso[j + 1] = arrivo;
           j++;
           return j;
       }
    }else{
        
        if (nodo->key <= arrivo) {
           percorso[j + 1] = arrivo;
           j++;
           return j;
       }
    }
    
    if(nodo->n_car!=0){
      while (nodo_prev != NULL && nodo_prev->key >= arrivo && nodo->car[nodo->n_car - 1] >= (nodo->key - nodo_prev->key)) {
        if(nodo_prev->n_car!=0){
        if (nodo_prev->key - nodo_prev->car[nodo_prev->n_car - 1] < min_dist) {
            min_dist = nodo_prev->key - nodo_prev->car[nodo_prev->n_car - 1];
            min = nodo_prev->key;
            nuova_partenza = nodo_prev;
        }
        }
        nodo_prev = nodo_prev->prev;
      }
    }

    if (min == -1) {
        printf("nessun percorso\n");
        *v = -1;
        return 0;
    }
    percorso[j + 1] = min;
    j++;

    if (min > arrivo) {
        int y = j;
        j = cerca_percorso_2(lista, nuova_partenza, arrivo, percorso, y, v);
    }


    return j;

}

void fix_stazioni(hash_table *map, int* percorso, int j) {

    for (int i = j; i > 1; i--) {
        stazione* nodo_prec = cerca_stazione(map, percorso[i - 2]);
        if(nodo_prec->n_car!=0){
         int autonomia = nodo_prec->car[nodo_prec->n_car - 1];
         while (percorso[i - 2] - autonomia <= nodo_prec->key) {
            nodo_prec = nodo_prec->prev;
          }
        }else{
         while (percorso[i - 2] <= nodo_prec->key) {
            nodo_prec = nodo_prec->prev;
          }
        }
        nodo_prec = nodo_prec->next;
        
        while (nodo_prec->key < percorso[i - 1]) {
           if(nodo_prec->n_car!=0){
            if (nodo_prec->key - nodo_prec->car[nodo_prec->n_car - 1] <= percorso[i]) {
          
                percorso[i - 1] = nodo_prec->key;
                break;
            }
           }else{
            if (nodo_prec->key <= percorso[i]) {
          
                percorso[i - 1] = nodo_prec->key;
                break;
            }
           } 
            nodo_prec = nodo_prec->next;
        }
    }
}

void pianifica_percorso(autostrada *lista , hash_table *mappa) {
    int partenza = 0, arrivo = 0;
    if (scanf("%d", &partenza))
        if (scanf("%d", &arrivo))

            if (arrivo > partenza) {
                int j = 0;
                int v = 0;
                stazione* nodo_arrivo = cerca_stazione(mappa, arrivo);
                

                int* percorso = (int*)malloc(L* sizeof(int));
                percorso[0] = nodo_arrivo->key;

                j = cerca_percorso(lista, nodo_arrivo, partenza, percorso, j, &v);
                if (v == -1) {
                    free(percorso);
                    return;
                }
                percorso = realloc(percorso, (j + 1) * sizeof(int));
                for (int i = j; i >= 0; i--) {
                    if (i != 0) {
                        printf("%d ", percorso[i]);
                    }
                    else {
                        printf("%d\n", percorso[i]);
                    }

                }

                free(percorso);

            }

    if (arrivo < partenza) {
        int j = 0;
        int v = 0;
        stazione* nodo_partenza = cerca_stazione(mappa, partenza);

        int* percorso = (int*)malloc(L* sizeof(int));
        percorso[0] = nodo_partenza->key;

        j = cerca_percorso_2(lista, nodo_partenza, arrivo, percorso, j, &v);

        if (v == -1) {
            free(percorso);
            return;
        }

        percorso = realloc(percorso, (j + 1) * sizeof(int));
        fix_stazioni(mappa, percorso, j);



        for (int i = 0; i <= j; i++) {
            if (i != j) {
                printf("%d ", percorso[i]);
            }
            else {
                printf("%d\n", percorso[i]);
            }

        }

        free(percorso);
    }

    if (partenza == arrivo) {
        printf("%d\n", partenza);
    }

}



int main(int argc, char* argv[]) {
    
    autostrada autostrada;
    hash_table mappa;
    inizializza_hash(&mappa);

    
    init_autostrada(&autostrada);
    int n_auto = 0;
    int key = 0;
    char* str = (char*)malloc(L * sizeof(char));
    while (scanf("%s", str) != EOF) {
        
        int* car = (int*)malloc((L / 2)*sizeof(int));
        switch (scelta_comando(str)) {
        case 1:
            assert(scanf("%d", &key));
            assert(scanf("%d", &n_auto));
            for (int i = 0; i < n_auto; i++) {
                assert(scanf("%d", &car[i]));

            }
            add_stazione(&autostrada, key, n_auto, car, &mappa);
            
            break;
        case 2:
            demolisci_stazione(&autostrada,&mappa);

            break;
        case 3:
            aggiungi_auto(&mappa);
            
            break;
        case 4:
            rottama_auto(&mappa);

            break;
        case 5:
            
            pianifica_percorso(&autostrada,&mappa);
           
            break;
        }
      free(car);
        
    }
   
    delete_list(&autostrada);
    free(str);
    return 0;
}
