#include "minishell.h"


void	inittree(t_tree** tree, t_token* tokens)
{
	t_token *current;

	current = tokens;
	while (current)
	{
		parsetoken(current, tree);
		//int fd = access(current->value, R_OK & X_OK);

		current = current->next;
	}
}

void	parsetoken(t_token* token, t_tree** tree)
{
	t_redir*	redir;
	t_node*		newnode;
	
	newnode = (t_node *)malloc(sizeof(t_node));
	if (token->type == 2 || token->type == 3) // < or >
	{
		//create redir
		redir = (t_redir*)malloc(sizeof(t_redir));
		redir->type = (*token).type;
		redir->file = (*token).next->value;
		token = (*token).next->next;
		if ((*tree)->left == NULL)
		{
			(*tree)->left = (t_node)malloc(sizeof(t_node));
			(*tree)->left->type = 1; //command
			if ((*tree)->left->redirs == NULL)
				(*tree)->left->redirs = redir;
			//else add to back
		}
	}
	if (token->type == 1) // |
	{
		//create redir
		newnode->pipe = (t_pipe *)malloc(sizeof(t_pipe));
		token = (*token).next->next;
	}
	addnode(tree, newnode);
}

void	addnode(t_tree** tree, t_node* new)
{
	t_tree	*temp;
	t_tree	*last;

	temp = *tree;
	if (!(*tree))
		return ;
	//else go up
}

void printTree(Node* root, int space) {
    if (root == NULL)
        return;

    space += 10;

    // First print the right child
    printTree(root->right, space);

    // Print the current node after space
    printf("\n");
    for (int i = 10; i < space; i++) {
        printf(" ");
    }
    printf("%d\n", root->data);

    // Then print the left child
    printTree(root->left, space);
}
