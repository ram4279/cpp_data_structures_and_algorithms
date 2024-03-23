#include <stdio.h>
#include <string.h>

char *
__strtok_r (char *s, const char *delim, char **save_ptr)
{
  char *end;

  if (s == NULL)
    s = *save_ptr;

  if (*s == '\0')
    {
      *save_ptr = s;
      return NULL;
    }

  /* Scan leading delimiters.  */
  s += strspn (s, delim);
  if (*s == '\0')
    {
      *save_ptr = s;
      return NULL;
    }

  /* Find the end of the token.  */
  end = s + strcspn (s, delim);
  if (*end == '\0')
    {
      *save_ptr = end;
      return s;
    }

  /* Terminate the token and make *SAVE_PTR point past it.  */
  *end = '\0';
  *save_ptr = end + 1;
  return s;
}

char *
strtok (char *s, const char *delim)
{
  static char *olds;
  return __strtok_r(s, delim, &olds);
}


static int last_ptr_index;
static char* static_str_ptr;

char *my_str_tok(char *string, const char *delimiters)
{
    char *start_ptr;
    if (string)
    {
        start_ptr = string;
        static_str_ptr = start_ptr;
    }
    else
    {
        if (static_str_ptr[last_ptr_index] == 0)
            return NULL;
        start_ptr = static_str_ptr + last_ptr_index;
    }
    char*  running_ptr = start_ptr;

    int delimiters_len = strlen(delimiters);
    
    while (*running_ptr)
    {
        for (int i = 0; i < delimiters_len; i++)
        {
            if (*running_ptr == delimiters[i])
            {
                *running_ptr = 0;
                last_ptr_index++;
                return start_ptr;
            }
        }
        last_ptr_index++;
        running_ptr++;
    }
    return start_ptr;
}

int main()
{
    char str[] = "THIS IS A WORD SEPARTED,BY COMMAS and COLONS:SEMICOLONS                          : ::  : :sauran";
    char *ptr = strtok(str, " :");
    while (ptr)
    {
        printf("%s\n", ptr);
        ptr = strtok(NULL, " ,:");
    }
    return 0;
}
