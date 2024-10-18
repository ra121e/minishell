//traversing node
while (node != NULL && node != seq)
{
//	syntax check while traversing
//	capture flags (get all info)(</> will be link lists)
//	rearrange tokens etc. to form a proper cmd
//	execute cmd
}
//	cmd mainly made up of: cmd args redirect(word)
//	eg:
//	echo hello
//	echo hello world > out
//	echo hello world > out > out2
//	echo hello world > out > out2 out3
//	>out echo hello world
	if (== redirect)
		redirect (check next token should be word)
		if (check)
				capture flag
	else
		cmd
		while (!= 0)
		{
			if (== redirect)
				redirect (check next token should be word)
				if (check)
						capture flag
			else
				add node to cmd link list
		}



//	dup2 last </> (1 each for in and out)
//	any prior </> file will be created but not dup
//	so either:
//	1) store in link list to process prior to execve
//	2) create the prior </> and store only a single </>

else
	left = traverse(cur->left);


int	traverse(type node)
{
//	traverse(cur);
	while (node)
	{
		//	code
		node = node->right;
	}
//	if (builtin)
//	fork();
//	execve(); in child process
//	return (waitpid()); in parent process
}
