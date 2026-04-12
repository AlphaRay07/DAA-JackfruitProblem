#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Compute LPS (Longest Prefix Suffix) array
void compute_lps(const char *pattern, int m, int *lps)
{
    int length = 0;
    lps[0] = 0;

    int i = 1;
    while (i < m)
    {
        if (pattern[i] == pattern[length])
        {
            length++;
            lps[i] = length;
            i++;
        }
        else
        {
            if (length != 0)
            {
                length = lps[length - 1];
            }
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// KMP Search
void kmp_search(const char *text, const char *pattern)
{
    int n = strlen(text);
    int m = strlen(pattern);

    if (m == 0)
        return;

    int *lps = (int *)malloc(m * sizeof(int));
    compute_lps(pattern, m, lps);

    int i = 0; // index for text
    int j = 0; // index for pattern

    printf("\nKMP Matches at indices: ");

    while (i < n)
    {
        if (text[i] == pattern[j])
        {
            i++;
            j++;
        }

        if (j == m)
        {
            printf("%d ", i - j);
            j = lps[j - 1];
        }
        else if (i < n && text[i] != pattern[j])
        {
            if (j != 0)
            {
                j = lps[j - 1];
            }
            else
            {
                i++;
            }
        }
    }

    free(lps);
}

// Brute-force search
void brute_force_search(const char *text, const char *pattern)
{
    int n = strlen(text);
    int m = strlen(pattern);

    printf("\nBrute Force Matches at indices: ");

    for (int i = 0; i <= n - m; i++)
    {
        int match = 1;

        for (int j = 0; j < m; j++)
        {
            if (text[i + j] != pattern[j])
            {
                match = 0;
                break;
            }
        }

        if (match)
        {
            printf("%d ", i);
        }
    }
}

int main()
{
    char text[] = "ABABDABACDABABCABAB";
    char pattern[] = "ABABCABAB";

    int m = strlen(pattern);
    int *lps = (int *)malloc(m * sizeof(int));

    printf("Text: %s\n", text);
    printf("Pattern: %s\n", pattern);

    // Compute LPS
    compute_lps(pattern, m, lps);

    printf("\nLPS Array: ");
    for (int i = 0; i < m; i++)
    {
        printf("%d ", lps[i]);
    }
    printf("\n");

    // KMP Search
    kmp_search(text, pattern);

    // Brute Force Search
    brute_force_search(text, pattern);

    free(lps);
    return 0;
}