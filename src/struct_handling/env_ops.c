#include "minishell.h"

void	env_delone(t_envi *env)
{
	if (env)
		free(env);
}

void	env_clear(t_envi **env)
{
	t_envi	*helper;
	t_envi	*extra;

	if (env)
	{
		helper = *env;
		while (helper)
		{
			extra = helper->next;
			env_delone(helper);
			helper = extra;
		}
		*env = NULL;
	}
}

t_envi	*env_last(t_envi *env)
{
	if (!env)
		return (NULL);
	while (env->next)
		env = env->next;
	return (env);
}

void	env_add_back(t_envi **env, t_envi *new)
{
	t_envi	*helper;

	if (!*env && new)
		*env = new;
	else if (*env && new)
	{
		helper = env_last(*env);
		helper->next = new;
	}
}
