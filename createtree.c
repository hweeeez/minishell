#include "minishell.h"


void	inittree(t_tree** tree, t_token* tokens)
{
	t_token* current;

	current = tokens;
	while (current)
	{
		parsetoken(current, tree);
		//int fd = access(current->value, R_OK & X_OK);

		current = current->next;
	}
}

void	parsetoken(t_token* token, t_tree** tree, char** envp)
{
	t_redir* redir;
	t_node* newnode;
	char* commandpath;
	char** args;
	t_node* curr_command_node;

	newnode = (t_node*)malloc(sizeof(t_node));
	if (token->type == 2 || token->type == 3) // < or >
	{
		//add redir to command node
		redir = (t_redir*)malloc(sizeof(t_redir));
		redir->type = (*token).type;
		redir->file = (*token).next->value;
		token = (*token).next->next;
		if (curr_command_node->redirections == NULL)
		{
			curr_command_node->redirections = redir;
		}
		else
			curr_command_node->redirections->next = redir;
	}
	if (token->type == 1) // |
	{
		//create redir
		newnode->pipe = (t_pipe*)malloc(sizeof(t_pipe));
		token = (*token).next->next;
	}
	if (token->type == 1) // |
	{
		//add command node'
		commandpath = ft_find_cmd_path(token->value, &args, envp);
		if (commandpath != NULL)
		{
			curr_command_node = (t_node*)malloc(sizeof(t_node));
			curr_command_node->type = 1;
			addnode(tree, curr_command_node);
		}
	}
}

void	addnode(t_node** currentnode, t_node* newnode)
{
	if (!(*currentnode))
		return;
	if ((*currentnode)->left != NULL)
	{
		(*currentnode)->left = newnode;
		(*currentnode) = (*currentnode)->left;
	}
	else if ((*currentnode)->right != NULL)
	{
		(*currentnode)->right = newnode;
		(*currentnode) = (*currentnode)->right;
	}
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
