#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int tsh_exit(char **args) { return 0; }
int tsh_help(char **args);

char *builtin_str[] = {"help", "exit"};

int (*builtin_func[])(char **) = {&tsh_help, &tsh_exit};

const int tsh_num_builtins = sizeof(builtin_str) / sizeof(char *);

int tsh_help(char **args) {
  printf("The following are built in:\n");

  for (int i = 0; i < tsh_num_builtins; i++) {
    printf("  %s\n", builtin_str[i]);
  }

  printf("Use the man command for information on other programs.\n");
  return 1;
}

int tsh_launch(char **args) {
  int status;

  pid_t pid = fork();
  if (pid == 0) {
    // Child process
    if (execvp(args[0], args) == -1) {
      perror("tsh");
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
    // Error forking
    perror("tsh error while forking.");
  } else {
    // Parent process
    do {
      waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}

int tsh_execute(char **args) {
  if (args[0] == NULL) {
    return 1;
  }

  for (int i = 0; i < tsh_num_builtins; i++) {
    if (strcmp(args[0], builtin_str[i]) == 0) {
      return (*builtin_func[i])(args);
    }
  }

  return tsh_launch(args);
}

char *tsh_read_line(void) {
  char *line = NULL;
  size_t bufsize = 0; // have getline allocate a buffer for us
  if (getline(&line, &bufsize, stdin) == -1) {
    if (feof(stdin)) {
      exit(EXIT_SUCCESS); // We received an EOF
    } else {
      perror("tsh: getline\n");
      exit(EXIT_FAILURE);
    }
  }
  return line;
}

const size_t TSH_TOK_BUFSIZE = 64;
const char *TSH_TOK_DELIM = " \t\r\n\a";

char **tsh_split_line(char *line) {
  int bufsize = TSH_TOK_BUFSIZE;
  size_t position = 0;
  char **tokens = malloc(bufsize * sizeof(char *));
  char *token, **tokens_backup;

  if (!tokens) {
    fprintf(stderr, "tsh: allocation error\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(line, TSH_TOK_DELIM);
  while (token != NULL) {
    tokens[position] = token;
    position++;

    if (position >= bufsize) {
      bufsize += TSH_TOK_BUFSIZE;
      tokens_backup = tokens;
      tokens = realloc(tokens, bufsize * sizeof(char *));
      if (!tokens) {
        free(tokens_backup);
        fprintf(stderr, "tsh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }

    token = strtok(NULL, TSH_TOK_DELIM);
  }
  tokens[position] = NULL;
  return tokens;
}

void tsh_loop(void) {
  char *line;
  char **args;
  int status;

  do {
    printf("> ");
    line = tsh_read_line();
    args = tsh_split_line(line);
    status = tsh_execute(args);

    free(line);
    free(args);
  } while (status);
}

int main(int argc, char *argv[]) {
  tsh_loop();

  return EXIT_SUCCESS;
}
