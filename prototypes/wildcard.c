//chatGPT generated :_)

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>

bool	isMatch(char *t, char *p)
{
    size_t n = strlen(t);
    size_t m = strlen(p);
    size_t i = 0, j = 0, startIndex = -1, match = 0;


    while (i < n) {
        
        // Characters match or '?' in pattern matches
        // any character.
        if (j < m && (p[j] == '?' || p[j] == t[i])) {          
            i++;
            j++;
        }
        else if (j < m && p[j] == '*') {
          
            // Wildcard character '*', mark the current
            // position in the pattern and the text as a
            // proper match.
            startIndex = j;
            match = i;
            j++;
        }
      
        else if (startIndex != SIZE_MAX) {
            // No match, but a previous wildcard was found.
            // Backtrack to the last '*' character position
            // and try for a different match.
            j = startIndex + 1;
            match++;
            i = match;
        }
        else {
            // If none of the above cases comply, the
            // pattern does not match.
            return false;
        }
    }

    // Consume any remaining '*' characters in the given
    // pattern.
    while (j < m && p[j] == '*') {
        j++;
    }

    // If we have reached the end of both the pattern and
    // the text, the pattern matches the text.
    return j == m;
}

int main()
{
    char	*t = "baaabab";
    char	*p = "*****ba*****ab";

    printf("%s\n", isMatch(t, p) ? "Yes" : "No");

	return 0;
}
