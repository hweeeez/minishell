/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hui-lim <hui-lim@student.42singapore.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 18:45:38 by hui-lim           #+#    #+#             */
/*   Updated: 2024/11/23 18:47:54 by hui-lim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"
#include "tokenizer.h"
//cc -g main.c libft.c llist_utils.c string_utils.c token_utils.c tokenizer.c createtree.c ft_handle_direct_path.c ft_path.c treehelper.c traversetree.c ft_heredoc.c parse_utils.c exe_utils.c redir_utils.c signal_utils.c -lreadline


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

static void printTree(t_node* root) {
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

void handle_signal(int sig)
{
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

void get_pwd()
{
	char *dir;
	size_t size;
	char *buf;

	dir = getcwd(buf, size);
	printf("%s", dir);
}

int main(int argc, char **argv, char **envp)
{
	char *s;
	struct sigaction sa;
	struct sigaction quit;
	t_token *tokens;
	t_token *current;
	t_node *tree;
	t_node *root;

	quit.sa_handler = SIG_IGN;
	sa.sa_handler = handle_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGQUIT, &quit, NULL);
	if (sigaction(SIGINT, &sa, NULL) == -1)
		return (0);
	while (1)
	{
		s = readline(PROMPT);
		if (s != NULL)
		{
			add_history(s);
			tokens = tokenize(s);
			if (!tokens)
			{
				printf("Error: Failed to tokenize input\n");
				return (1);
			}
			current = tokens;
			tree = createnode();
			root = tree;
			inittree(&tree, current, envp);
			tree = root;
			if (execute(tree, envp) == 2)
			{
				if (ft_heredoc(tree, envp) > 0)
				{
					sigaction(SIGINT, &sa, NULL);
					rl_event_hook = NULL;
				}
			}
			freetree(&tree);
		}
		if (s == NULL)
		{
			rl_clear_history();
			exit(0);
		}
		free(s);
	}
}
