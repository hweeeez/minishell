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

static void	printarray(char **args)
{
 int i = 0;

 while (args[i] != NULL)
 {
	printf("%s\n", args[i]);
	i++;
 }
}

void	cleantree(t_node **node)
{
	t_node	*prevnode;
	t_node	*leftnode;

	if ((*node) == NULL)
		return ;
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
			prevnode->right = leftnode;
			if (leftnode)
				leftnode->prev = prevnode;
		}
	}
}