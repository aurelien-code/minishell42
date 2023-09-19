# minishell42
As beautiful as a shell

To fix :
  -  cat sans rien apres fait une infinite loop
  -  cat avec un fichier derriere ne rend pas le prompt
  -  echo << test ~~fait segfault~~ ne lance pas heredoc
  -  les pipes ne fonctionnent pas (echo t | echo o -> doit print o mais print t), (cat x | grep y n'execute que cat x)
  -  exit renvoie exit : command not found
  -  pwd et echo font appel a la fonction reelle et pas la builtin, alors que cd unset mettent le msg que c'est une builtin
  
Not finished :
  - Errors handler in parser
