#include "minishell.h"

/**
 * @brief creates a new node of t_envi struct that takes 
 * two strings, the name of the variable and what it contains
 * @param var variable name
 * @param val value assigned to that variable
 * @return new t_envi node
*/
t_envi	*env_new(char *var, char *val)
{
	t_envi	*env;

	env = (t_envi *) malloc(sizeof(t_envi));
	if (!env)
		return (NULL);
	env->var = var;
	env->val = val;
	env->next = NULL;
	return (env);
}

/**
 * @brief initiates the double circular linked list of 
 * environmental variables
 * @param envp envp parameter main argument
 * @return first environmental variable
*/
t_envi	*get_env_var(char **envp)
{
	char	**vals;
	t_envi	*env;

	while (*envp != NULL)
	{
		vals = ft_split(*envp, '=');
		env_add_back(&env, env_new(vals[0], vals[1]));
		envp++;
	}
	return (env);
}