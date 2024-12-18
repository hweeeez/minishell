#include "minishell.h"

void freetree(t_node** tree)
{
    t_node* current;
    t_node* next;

    current = *tree;
    if (tree == NULL || *tree == NULL)
        return;
    while (current != NULL)
    {
        if (current->right != NULL)
            next = current->right;
        else
            next = NULL;
        if ((current)->left != NULL)
        {
            free(current->left);
            current->left = NULL;
        }
        free(current);
        current = next;
    }
}

void traversetree()
{

    
}