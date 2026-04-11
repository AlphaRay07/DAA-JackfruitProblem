# DAA - Jackfruit Problem - Question 2 - Solution

def compute_lps(pattern):
    
    # Construct the Longest Prefix Suffix (LPS) array.
    # lps[i] = length of the longest proper prefix which is also a suffix for pattern[0..i]

    m = len(pattern)
    lps = [0] * m

    length = 0  # length of previous longest prefix suffix
    i = 1

    while i < m:
        if pattern[i] == pattern[length]:
            length += 1
            lps[i] = length
            i += 1
        else:
            if length != 0:
                length = lps[length - 1]
            else:
                lps[i] = 0
                i += 1

    return lps


def kmp_search(text, pattern):

    # Perform KMP pattern matching.
    # Returns list of starting indices where pattern is found in text.

    n = len(text)
    m = len(pattern)

    if m == 0:
        return []

    lps = compute_lps(pattern)

    i = 0  # index for text
    j = 0  # index for pattern

    result = []

    while i < n:
        if text[i] == pattern[j]:
            i += 1
            j += 1

        if j == m:
            result.append(i - j)
            j = lps[j - 1]

        elif i < n and text[i] != pattern[j]:
            if j != 0:
                j = lps[j - 1]
            else:
                i += 1

    return result


def brute_force_search(text, pattern):
    
    # Brute-force string matching.
    # Returns list of starting indices where pattern is found in text.

    n = len(text)
    m = len(pattern)

    result = []

    for i in range(n - m + 1):
        match = True
        for j in range(m):
            if text[i + j] != pattern[j]:
                match = False
                break
        if match:
            result.append(i)

    return result


if __name__ == "__main__":
    text = "ABABDABACDABABCABAB"
    pattern = "ABABCABAB"

    print("Text:", text)
    print("Pattern:", pattern)

    # Compute LPS
    lps = compute_lps(pattern)
    print("\nLPS Array:", lps)

    # KMP Search
    kmp_result = kmp_search(text, pattern)
    print("\nKMP Matches at indices:", kmp_result)

    # Brute Force Search
    brute_result = brute_force_search(text, pattern)
    print("Brute Force Matches at indices:", brute_result)