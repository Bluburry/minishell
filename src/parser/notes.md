Ordem de execução

1 - (Opcional)Executar todas a redirections (>, <, >>, <<) na ordem em aparecem na phrase
2 - (Opcional)Fazer o piping do out do exec para o proximo executavel
3 - Executar o exec dado
4 - Se execução retornar com codigo de erro 0, ir a próxima phrase



Percorro a list de tokens, conto o numero de pipes e de strings totais e salvo em n_pipes e n_strings
Crio uma array de tokens do tamanho de n_strings


> out0 exec0 arg00 arg01 < in0 | exec21 arg10 | exec2 >> out2 arg20

Tres variaveis, i = posição na string list, idx = posição atual na token array, max posição em que a proxima phrase vai começar


Leio ate achar um pipe, contando o numero de strings até ele 
mando a posição do primeiro item e o numero maximo de itens até o pipe para uma função que analisa a phrase
a função que analisa a phrase primeiro percore a lista procurando os quatro redirects
Caso achado, ele adiciana o redirect na token array, colocando o valor do proximo token como o arquivo de redirect
Caso não tenha proximo, erro
Uma função então adiciona o pipe na lista
Uma função percorre pela substring e conta o numero de argumentos
E ai, a função percorre de novo pelas strings, dessa vez ignorando redirects e o proximo item, e adicona o primeiro em um exec, e o resto a uma null terminated char ** de tamanho obtidido anteriormente + 1;
