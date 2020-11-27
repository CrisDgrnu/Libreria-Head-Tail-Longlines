#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define LEN 1024

//////////////ESTRUCTURA DINAMICA AUXILIAR USADA PARA TAIL Y LONGLINES//////////////

typedef struct Node{
    char line[LEN];
    struct Node* next;
} Node;

typedef struct List{
    Node* head;
} List;


//////////////OPERACIONES DE LA ESTRUCTURA DINAMICA//////////////

//FUNCIONES CONSTRUCTORAS DE LA ESTRUCTURA
Node* createNode(char l[LEN]){
    Node* node = (Node *) malloc(sizeof(Node));
    strcpy(node->line,l);
    node->next = NULL;
    return node;
}

List* buildList(){
    List* list = (List *) malloc(sizeof(List));
    list->head = NULL;
}

//COMPRUEBA SI LA ESTRUCTURA ESTA VACIA
int isEmpty(List* list){
    return list->head == NULL;
}

//MOSTRAR Y LIBERAR MEMORIA
void show(List* List){
    Node* suc = List->head;
    Node* ant = suc;
    while (suc != NULL){
        printf("%s",suc->line);
        suc = suc->next;
        free(ant);
        ant = suc;
    }
}

//AÑADIR POR CABEZA
void add(List* list,char l[LEN]){
    Node* node = createNode(l);
    node->next = list->head;
    list->head = node;
}

//AÑADIR AL FINAL
void addLast(List* list, char l[LEN]){
    Node* node = createNode(l);
    Node* suc;

    if (isEmpty(list)){         //Si es vacia el nuevo nodo sera la cabeza
        list->head = node;
    } else {                    //En caso contrario se recorre y se añade al final
        suc = list->head;
        while ((suc->next)){
            suc = suc->next;
        }
        suc->next = node;
    }
}

//AÑADIR DESPUES DE UNA POSICION CONCRETA
void addAfter(List* list,Node* ant,char l[LEN]){
    Node* node = createNode(l);
    node->next = ant->next;
    ant->next = node;
}

//AÑADIR EN ORDEN EN FUNCION DE LA LONGITUD
void addInOrder(List* list, char l[LEN]){
    Node* node = createNode(l);
    Node* suc;
    Node* ant;
    if (isEmpty(list)){         //Si la lista es vacia el nuevo nodo sera la cabeza
        list->head = node;
    } else {                    //En caso contrario estara en la cola de la lista
        suc = list->head;
        if (strlen(node->line)>strlen(list->head->line)){   //Si el nodo es mayor que la cabeza este sera la nueva cabeza
            add(list,l);
        } else {                                            //En caso contrario se añade despues del elemento de menor longitud que el
            suc = suc->next;
            ant = list->head;
            if (suc == NULL){                               //Si la lista solo tiene un elemento y es NULL se añade al final
                addLast(list,l);
            } else {                                        //En caso contrario se busca y se añade despues del elemento de menor longitud que el
                while ((strlen(node->line) < strlen(suc->line)) && suc != NULL){
                    suc =suc->next;
                    ant = ant->next;
                }
                addAfter(list,ant,l);
            }
        }
    }
}

//////////////FUNCIONES DE LIBRERIA//////////////

//SACA LAS N PRIMERAS LINEAS LEIDAS POR ENTRADA ESTANDAR 
void head(int N){
   int i = 0;
   char line[LEN];

   while ((i<N)) {                                  
       if (fgets(line,LEN,stdin) == NULL){          //Si a leido todas las lineas activa al condicion de salida
           i = N;   
       } else {                                     //En caso contrario sigue mostrando lineas y aumentando el contado de estas
           fputs(line,stdout);
           i++;
       }
   }
}

//SACA LAS N ULTIMAS LINEAS LEIDAS POR ENTRADA ESTANDAR 
void tail(int N){
    Node *suc;
    Node *ant;
    List* list = buildList();
    int lines_to_show = 0;
    int start = 0;
    char buffer[LEN];

    while (fgets(buffer,LEN,stdin)){                //Añade las lineas a la estructura por el final
        addLast(list,buffer);
        lines_to_show++;
    }

    if (lines_to_show<N){                           //Si las lineas a mostrar son mayores que el tamaño de la estructura, muestra todas
        show(list);
    } else {                                        //En caso contrario muestra las N primeras lineas              
        start = lines_to_show-N;                          
        lines_to_show = 0;
        suc = list->head;
        while (suc != NULL){                        //Recorre la lista
            ant = suc;
            lines_to_show++;
            if (lines_to_show > start){             //Empieza a mostrar a partir de la posicion de inicio (Inicio = Lineas a mostrar - Total de lineas)
                printf("%s",suc->line);
            }
            suc = suc->next;
            free(ant);
        }
    }
}


//SACA LAS N LINEAS MAS LARGAS LEIDAS POR ENTRADA ESTANDAR 
void longlines(int N){
    Node *suc;
    Node *ant;
    List* list = buildList();
    int lines_to_show = 0;
    char buffer[LEN];

    while (fgets(buffer,LEN,stdin)){                //Añade las lineas a la estructura en orden
        addInOrder(list,buffer);
        lines_to_show++;
    }

    if (lines_to_show<N){                           //Si las lineas a mostrar son mayores que el tamaño de la estructura, muestra todas
        show(list);
    } else {                                        //En caso contrario muestra las N primeras lineas  (Estan ordenadas)
        lines_to_show = 0;
        suc = list->head;
        while (suc != NULL){                        //Recorre la lista
            ant = suc;
            lines_to_show++;
            if (lines_to_show <=N){                 //Muestra desde el principio de la lista hasta N
                printf("%s",suc->line);
            }
            suc = suc->next;
            free(ant);
        }
    }
}

