
#include "init.h" // for create_token
#include "lexer.h"

t_token *handle_basics_token(t_lexer *lexer) {
  char current;

  current = get_lexer(lexer);
  if (current == '\0')
    return (create_token(TOK_EOF, NULL));
  if (current == '\n') {
    advance_lexer(lexer);
    return (create_token(TOK_NEW_LINE, ft_strdup("\n")));
  }
  return (NULL);
}

t_token *handle_pipe_and_token(t_lexer *lexer) {
  char current;

  current = get_lexer(lexer);
  if (current == '|') {
    advance_lexer(lexer);
    if (get_lexer(lexer) == '|') {
      advance_lexer(lexer);
      return (create_token(TOK_OR, ft_strdup("||")));
    }
    return (create_token(TOK_PIPE, ft_strdup("|")));
  }
  if (current == '&') {
    advance_lexer(lexer);
    if (get_lexer(lexer) == '&') {
      advance_lexer(lexer);
      return (create_token(TOK_AND, ft_strdup("&&")));
    }
    return (create_token(TOK_ESP, ft_strdup("&")));
  }
  return (NULL);
}

t_token *handle_redir_from_and_to_token(t_lexer *lexer) {
  char current;

  current = get_lexer(lexer);
  if (current == '<') {
    advance_lexer(lexer);
    if (get_lexer(lexer) == '<') {
      advance_lexer(lexer);
      return (create_token(TOK_HERE_DOC_FROM, ft_strdup("<<")));
    }
    return (create_token(TOK_REDIR_FROM, ft_strdup("<")));
  } else if (current == '>') {
    advance_lexer(lexer);
    if (get_lexer(lexer) == '>') {
      advance_lexer(lexer);
      return (create_token(TOK_HERE_DOC_TO, ft_strdup(">>")));
    }
    return (create_token(TOK_REDIR_TO, ft_strdup(">")));
  }
  return (NULL);
}

// t_token	*handle_env_token(t_lexer *lexer)
// {
// 	char	*word;
// 	char	current;
//
// 	current = get_lexer(lexer);
// 	if (current == '$')
// 	{
// 		word = read_word_lexer(lexer);
// 		return (create_token(TOK_WORD, word));
// 	}
// 	return (NULL);
// }
