//
// Created by Jose Ignacio de la Barra Cortés on 10-06-22.
//

#include "main.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_SIZE 1024


struct node {
    char nombre[50];
    int dan_cat;
    float att_prob;
    struct node *left;
    struct node *right;
    int height;
};

int max(int a, int b)
{
    return (a > b)? a : b;
}

int height(struct node *node)
{
    if (node == NULL) {
        return 0;
    }
    return 1 + max(height(node->left), height(node->right));
}
int balance(struct node *node)
{
    if (node == NULL) {
        return 0;
    }
    return height(node->left) - height(node->right);
}
struct node *rightRotate(struct node *y)
{
    // x es el pivote (nueva raiz)
    struct node *x = y->left;
    // OJO: z podria ser NULL (lo cual no es un problema)
    struct node *z = x->right;

    // rotamos a la derecha
    x->right = y;
    y->left = z;

    // actualizamos el height de y e x
    // (height de los otros nodos no cambia; no hay que actualizar)
    y->height = height(y);
    x->height = height(x);

    return x;
}

struct node *leftRotate(struct node *x)
{
    // y es el pivote (nueva raiz)
    struct node *y = x->right;
    // OJO: z podria ser NULL (lo cual no es un problema)
    struct node *z = y->left;

    // rotamos a la izquierda
    y->left = x;
    x->right = z;

    // actualizamos el height de y e x
    // (height de los otros nodos no cambia; no hay que actualizar)
    y->height = height(y);
    x->height = height(x);

    return y;
}

struct node *insert(struct node *node, char* nombre, int dan_cat, float att_prob)
{
    if (node == NULL) { // caso arbol vacio
        struct node *tmp = (struct node *)malloc(sizeof(struct node));
        strcpy(tmp->nombre, nombre);
        tmp->dan_cat = dan_cat;
        tmp->att_prob = att_prob;
        tmp->left = NULL;
        tmp->right = NULL;
        tmp->height = 1;
        return tmp;
    }
    if (dan_cat <= node->dan_cat) {
        if (dan_cat==node->dan_cat){
            if(att_prob < node->att_prob){
                node->left = insert(node->left, nombre, dan_cat, att_prob);
            }
            else{
                node->right = insert(node->right, nombre, dan_cat, att_prob);
            }
        }
        else{
            node->left = insert(node->left, nombre, dan_cat, att_prob);
        }
    }
    else {
        if(att_prob < node->att_prob){
            node->left = insert(node->left, nombre, dan_cat, att_prob);
        } else{
            node->right = insert(node->right, nombre, dan_cat, att_prob);
        }
    }
    /*
    node->height = height(node);
    // calculamos balance de node
    // si balance > 1 o balance < -1, el nodo esta desbalanceado
    int node_balance = balance(node);

    // caso left left
    if (node_balance > 1 && dan_cat < node->left->dan_cat) {
        return rightRotate(node);
    }
    // caso right right
    if (node_balance < -1 && dan_cat >= node->right->dan_cat) {
        return leftRotate(node);
    }
    // caso left right
    if (node_balance > 1 && dan_cat >= node->left->dan_cat) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    // caso right left
    if (node_balance < -1 && dan_cat < node->right->dan_cat) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }*/
    return node;
}

void show_nodes_inorder(struct node *root)
{
    if (root == NULL) {
        return;
    }
    show_nodes_inorder(root->left);
    printf("%s ", root->nombre);
    show_nodes_inorder(root->right);
}
// muestra los nodos postorder (I, D, R)
void show_nodes_postorder(struct node *root)
{
    if (root == NULL) {
        return;
    }
    show_nodes_postorder(root->left);
    show_nodes_postorder(root->right);
    printf("%s ", root->nombre);

}

int main(int argc, char *argv[]) {
    int i = 0;
    FILE *fp = fopen("/Users/josedelabarra/CLionProjects/tarea4/mensaje.txt", "r");

    char line[MAX_LINE_SIZE];
    char *token;
    struct node *atacantes = NULL;
    // Leemos linea a linea
    while (fgets(line, MAX_LINE_SIZE, fp) != NULL) // el arreglo line se rellena con los caracteres de la linea
    {
        // strtok(line, ",") entrega el substring desde el comienzo hasta la primera aparicion del delimitador "," (excluyendolo)
        // Copiamos el substring al campo palabra de la estructura

        char nombre[50];
        int danger;
        float attack;
        strcpy(nombre, strtok(line, ","));
        // Obtenemos el siguiente substring
        token = strtok(NULL, ",");
        if (strcmp(token, "\n") == 0) // caso que no hay int
            danger = -1;
        else
            danger = atoi(token); // atoi convierte un string a int
        token = strtok(NULL, ",");
        if (strcmp(token, "\n") == 0) // caso que no hay int
            attack = -1;
        else {
            attack = atof(token); // atoi convierte un string a int
        }

        if(i==1) {          //Se salta las cabeceras
            atacantes = insert(atacantes, nombre, danger, attack);
        }
        else{
            insert(atacantes, nombre, danger, attack);
        }
        i++;
    }
    show_nodes_postorder(atacantes);
}
