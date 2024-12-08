#include "minishell.h"

t_node*	createnode()
{
	t_node*	node;
	
	node = (t_node*)malloc(sizeof(t_node));
    node->left = NULL;
    node->right = NULL;
    node->type = 0;
    node->prev = NULL;
    node->redirections = NULL;
    node->args = NULL;
    node->argc = 0;
    return node;
}

void	inittree(t_node** tree, t_token* tokens, char** envp)
{
	t_token* current;

	current = tokens;
	while (current)
	{
		parsetoken(current, tree, envp);
		current = current->next;
	}
}

void	parsetoken(t_token* token, t_node** tree, char** envp)
{
	t_redir* redir;
	static t_node* newnode;
	char* word;
	static char** args;
	static int	nowords;

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
		newnode = createnode();
		token = (*token).next->next;
		addnode(tree, newnode);
	}
	if (token->type == 0) // word
	{
		//add command node
		word = ft_find_cmd_path(token->value, &args, envp);
		if (word != NULL)
		{
			newnode = createnode();
			newnode->type = 1;
			addnode(tree, newnode);
			args = NULL;
			newnode->args = args;
			nowords = 0;
			copyarray(&args, nowords, token->value);
			nowords++;
		}
		else
		{
			copyarray(&args, nowords, token->value);
			nowords++;
		}
	}
}

void copyarray(char ***tocopy, int size, char* toadd)
{
	char**	temp;
	int	i;
	
	i = 0;
	temp = (char**)malloc(sizeof(char*) * (size + 2));
	if (*tocopy != NULL)
	{
		while ((*tocopy)[i]!= NULL)
		{
			temp[i]= (*tocopy)[i];
			i++;
		}
		free(*tocopy);
	}
	temp[i] = toadd;
	temp[i + 1] = NULL;
	*tocopy = temp;
}

void	addnode(t_node** currentnode, t_node* newnode)
{
	t_node* prevnode;

	prevnode = *currentnode;
	if (!(*currentnode))
		return;
	if ((*currentnode)->type == 0)
	{
		if ((*currentnode)->left == NULL)
		{
			(*currentnode)->left = newnode;
			newnode->prev = (*currentnode);
		}
		else if ((*currentnode)->right == NULL)
		{
			if (newnode->type == 0){
				(*currentnode)->right = newnode;
				newnode->prev = (*currentnode);
			}
			else
			{
				(*currentnode)->right = createnode();
				(*currentnode)->right->prev = (*currentnode);
				(*currentnode)->right->left = newnode;
				newnode->prev = (*currentnode)->right;
				(*currentnode) = (*currentnode)->right->left;
			}
		}
		if (newnode->type == 0)
		{
			(*currentnode) = newnode;
			(*currentnode)->prev = prevnode;
		}
	}
	else
	{
		(*currentnode) = (*currentnode)->prev;
		addnode(currentnode, newnode);
	}
}

void	cleantree(t_node** node)
{
	t_node* prevnode;

	prevnode = (*node)->prev;
	if ((*node) != NULL)
	{
		if ((*node)->type == 0)
		{
			if ((*node)->right == NULL)
			{
				(*node)->prev->right = (*node)->left;
				free(*node);
				(*node) = prevnode;
				(*node)->right->prev = (*node);
			}
			else
				(*node) = (*node)->right;
			cleantree(node);
		}
	}
}

static int getTreeHeight(t_node* root) {
    if (root == NULL)
        return 0;
    
    int leftHeight = getTreeHeight(root->left);
    int rightHeight = getTreeHeight(root->right);
    
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

// Function to print spaces before nodes
static void printSpaces(int count) {
    for (int i = 0; i < count; i++)
        printf("  ");
}

void printTree(t_node* root) {
    if (root == NULL)
        return;

    // Get the height of the tree to determine spacing
    int height = getTreeHeight(root);
    
    // Array to store levels
    t_node* currentLevel[1024] = {root};
    t_node* nextLevel[1024];
    int currentLevelCount = 1;
    int level = 0;

    while (currentLevelCount > 0) {
        int nextLevelCount = 0;
        
        // Print spacing based on level and tree height
        printSpaces(pow(2, height - level - 1));

        // Process current level
        for (int i = 0; i < currentLevelCount; i++) {
            if (currentLevel[i] != NULL) {
                printf("%d", currentLevel[i]->type);
                
                // Prepare next level
                nextLevel[nextLevelCount++] = currentLevel[i]->left;
                nextLevel[nextLevelCount++] = currentLevel[i]->right;
                
                // Add space between nodes
                if (i < currentLevelCount - 1)
                    printSpaces(pow(2, height - level));
            } else {
                printf(" ");
                
                // Add placeholder for null nodes in next level
                nextLevel[nextLevelCount++] = NULL;
                nextLevel[nextLevelCount++] = NULL;
                
                if (i < currentLevelCount - 1)
                    printSpaces(pow(2, height - level));
            }
        }
        printf("\n");

        // Check if all nodes in next level are NULL
        int allNull = 1;
        for (int i = 0; i < nextLevelCount; i++) {
            if (nextLevel[i] != NULL) {
                allNull = 0;
                break;
            }
        }
        
        // If all nodes are NULL, break the loop
        if (allNull)
            break;

        // Copy next level to current level
        for (int i = 0; i < nextLevelCount; i++) {
            currentLevel[i] = nextLevel[i];
        }
        currentLevelCount = nextLevelCount;
        level++;
    }
}

/*void cleantree(t_node** node)
{
    if (*node == NULL) {
        return; // Base case: nothing to clean if the node is NULL
    }

    t_node* prevnode = (*node)->prev;

    if ((*node)->type == 0) {  // Check if node type is 0 (or any specific type condition)
        if ((*node)->right == NULL) {
            // If the node has no right child, we link the parent to the left child
            if ((*node)->prev != NULL) {
                (*node)->prev->right = (*node)->left;
            }

            // If the left child exists, set its prev pointer to the parent
            if ((*node)->left != NULL) {
                (*node)->left->prev = (*node)->prev;
            }

            // Free the current node
            free(*node);
            
            // Move to the previous node
            *node = prevnode;

            // If the previous node's right child is not NULL, update its prev pointer
            if (*node != NULL && (*node)->right != NULL) {
                (*node)->right->prev = *node;
            }
        } else {
            // If the node has a right child, move to the right child
            *node = (*node)->right;
            cleantree(node); // Recursively clean the right subtree
        }
    }
}
*/