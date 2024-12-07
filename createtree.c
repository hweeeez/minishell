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
	static t_node* newnode;
	char* word;
	static char** args;
	static int	noargs;

	if (token->type == 2 || token->type == 3) // < or >
	{
		//add redir to command node
		redir = (t_redir*)malloc(sizeof(t_redir));
		redir->type = (*token).type;
		redir->file = (*token).next->value;
		token = (*token).next->next;
		if (newnode->redirections == NULL)
		{
			newnode->redirections = redir;
		}
		else
			newnode->redirections->next = redir;
	}
	if (token->type == 1) // |
	{
		//create redir
		newnode = (t_node*)malloc(sizeof(t_node));
		newnode->type = 0;
		token = (*token).next->next;
		addnode(tree, newnode);
	}
	if (token->type == 1) // word
	{
		//add command node'
		word = ft_find_cmd_path(token->value, &args, envp);
		if (word != NULL)
		{
			word = (t_node*)malloc(sizeof(t_node));
			word->type = 1;
			addnode(tree, newnode);
			nowords = 0;
			args = NULL;
		}
		else
		{
			nowords++;
			free(args);
			args = (char**)malloc(sizeof(char*) * nowords);

		}
	}
}

void copyarray()
{
	//temp array
	//duplicate into temp
	//realloc array
	//copy temp back into array
	//add new element
	//free temp
}

void	addnode(t_node** currentnode, t_node* newnode)
{
	t_node prevnode;

	prevnode = currentnode;
	if (!(*currentnode))
		return;
	if ((*currentnode)->left != NULL)
	{
		(*currentnode)->left = newnode;
		(*currentnode) = (*currentnode)->left;
		(*currentnode)->prev = prevnode;
	}
	else if ((*currentnode)->right != NULL)
	{
		(*currentnode)->right = newnode;
		(*currentnode) = (*currentnode)->right;
		(*currentnode)->prev = prevnode;
	}
	else
	{
		(*currentnode) = (*currentnode)->prev;
		addnode(currentnode, newnode);
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
