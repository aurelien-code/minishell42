# minishell42
As beautiful as a shell

To fix :
  -  cat sans rien apres fait une infinite loop
  -  cat avec un fichier derriere ne rend pas le prompt
  -  echo << test fait segfault
  -  les pipes ne fonctionnent pas (echo t | echo o -> doit print o mais print t), (cat x | grep y n'execute que cat x)
  
Not finished :
  - Errors handler in parser
