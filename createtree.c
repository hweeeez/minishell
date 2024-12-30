#include "minishell.h"

static void	printarray(char **args){
 int i = 0;

 while (args[i] != NULL)
 {
	printf("%s\n", args[i]);
	i++;
 }
}
t_node*	createnode()
{
	t_node*	node;
	
	node = (t_node*)malloc(sizeof(t_node));
    node->left = NULL;
    node->right = NULL;
    node->type = 0;
    node->prev = NULL;
    node->redirs = NULL;
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
		parsetoken(&current, tree, envp);
		current = current->next;
	}
}

void	parsetoken(t_token** token, t_node** tree, char** envp)
{
	t_redir* redir;
	static t_node* newnode = NULL;
	char* word;
	static char** args;
	static int	nowords;

	if ((*tree)->left == NULL)
	{
		newnode = NULL;
		nowords = 0;
		args = NULL;
	}
	if ((*token)->type == 2 || (*token)->type == 3) // < or >
	{
		//add redir to command node
		if (newnode == NULL)
		{
			newnode = createnode();
			newnode->type = 1;
			addnode(tree, newnode);
		}
		redir = (t_redir*)malloc(sizeof(t_redir));
		redir->type = (*token)->type;
		redir->file = (*token)->next->value;
		redir->next = NULL;
		if (newnode->redirs == NULL)
		{
			newnode->redirs = redir;
			newnode->rootredir = redir;
		}
		else
		{	
			newnode->redirs->next = redir;
			newnode->redirs = newnode->redirs->next;
		}
		(*token) = (*token)->next;
		return;
	}
	if ((*token)->type == TOKEN_PIPE) // |
	{
		//create redir
		newnode = createnode();
		addnode(tree, newnode);
	}
	if ((*token)->type == 0) // word
	{
		//add command node
		word = ft_find_cmd_path((*token)->value, &args, envp);
		if (word != NULL)
		{
			if (newnode == NULL || newnode->type == 0)
			{
				newnode = createnode();
				newnode->type = 1;
				addnode(tree, newnode);
			}
			args = NULL;
			nowords = 0;
			copyarray(&args, nowords, word);
			newnode->args = args;
			nowords++;
		}
		else
		{
			if (newnode == NULL)
			{
				newnode = createnode();
				newnode->type = 1;
				addnode(tree, newnode);
			}
			copyarray(&args, nowords, (*token)->value);
			newnode->args = args;
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
			temp[i]= ft_strdup((*tocopy)[i]);
			free(*tocopy[i]);
			i++;
		}
		free(*tocopy);
	}
	temp[i] = ft_strdup(toadd);
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
				(*currentnode) = newnode;
			}
			else
			{
				(*currentnode)->right = createnode();
				(*currentnode)->right->prev = (*currentnode);
				(*currentnode)->right->left = newnode;
				newnode->prev = (*currentnode)->right;
				(*currentnode) = (*currentnode)->right;
			}
		}
		/*if (newnode->type == 0)
		{
			(*currentnode) = newnode;
			(*currentnode)->prev = prevnode;
		}*/
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
	t_node* leftnode;

	if ((*node) == NULL)
		return;
    if ((*node)->right)
        cleantree(&((*node)->right));
	prevnode = (*node)->prev;
	leftnode = (*node)->left;
	
	if ((*node)->type == 0 && (*node)->right == NULL)
	{
		if ((*node)->prev != NULL)
		{
			free(*node);
			(*node) = NULL;
			//printf("%p\n", leftnode);
			//if (prevnode->right == *node)
		    prevnode->right = leftnode;                   
		    if (leftnode)
		            leftnode->prev = prevnode;
			//printf("%p\n", prevnode->right);
			//printf("%d\n", prevnode->right->type);

			/*if ((*clean) == NULL)
			{
				(*clean) = (*node);
				(*clean)->next = NULL;
			}	
			else
			{
				(*clean)->next = (*node);
				(*clean) = (*clean)->next;
				(*clean)->next = NULL;
			}	*/	/*printf("dsd\n");
		printf("perevnode right: %p\n", prevnode->right);
		printf("prevnode: %p\n", prevnode);
		printf("left node: %p type: %d\n", leftnode, leftnode->type);
			printTree(prevnode);
			printf("adsd\n");
		printf("perevnode right: %p\n", prevnode->right);
		printf("prevnode: %p\n", prevnode);*/
        }
        /*
        cat a|cat b|cat c
                  0
            1             0
                       1       0 
                             1  NULL
                             
                             
        else if ((*node)->left)
        {
            t_node* leftChild = (*node)->left;
            leftChild->prev = NULL;
            *node = leftChild;
        }
        else
        {
        	free(*node);
        	*node = NULL;
        }*/
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
