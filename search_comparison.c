/* ============================================================
   Q5(b): Store department names in a searchable representation
   (sorted array) and compare Linear Search vs Binary Search.
   Number of comparisons is counted and printed for each search.
   ============================================================ */

#include <stdio.h>
#include <string.h>

#define N 8
#define NAME_LEN 30

/* Department names stored in SORTED order (required for Binary Search) */
char departments[N][NAME_LEN] = {
    "Backend", "CEO", "Development", "Finance",
    "Frontend", "HR", "IT", "Testing"
};

/* ---------------- Linear Search ---------------- */
int linearSearch(char arr[][NAME_LEN], int n, char *key, int *comparisons) {
    *comparisons = 0;
    for (int i = 0; i < n; i++) {
        (*comparisons)++;
        if (strcmp(arr[i], key) == 0)
            return i;
    }
    return -1;
}

/* ---------------- Binary Search (iterative) ---------------- */
int binarySearch(char arr[][NAME_LEN], int n, char *key, int *comparisons) {
    *comparisons = 0;
    int low = 0, high = n - 1;

    while (low <= high) {
        int mid = (low + high) / 2;
        (*comparisons)++;
        int cmp = strcmp(arr[mid], key);

        if (cmp == 0)
            return mid;
        else if (cmp < 0)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

void runSearch(char *key) {
    int linComp, binComp;

    int linIdx = linearSearch(departments, N, key, &linComp);
    int binIdx = binarySearch(departments, N, key, &binComp);

    printf("\nSearching for: \"%s\"\n", key);
    printf("  Linear Search : %s (index %d) | Comparisons = %d\n",
           (linIdx != -1) ? "FOUND" : "NOT FOUND", linIdx, linComp);
    printf("  Binary Search : %s (index %d) | Comparisons = %d\n",
           (binIdx != -1) ? "FOUND" : "NOT FOUND", binIdx, binComp);
}

int main() {
    printf("Sorted Department Array:\n");
    for (int i = 0; i < N; i++)
        printf("  [%d] %s\n", i, departments[i]);

    /* At least 3 test searches: best case, worst/near-worst case, not-found case */
    runSearch("HR");          /* near the middle for binary; middling for linear */
    runSearch("Backend");     /* first element sorted -> worst case for binary-ish, best for linear */
    runSearch("Testing");     /* last element -> worst case for linear */
    runSearch("Marketing");   /* not present -> worst case for both */

    return 0;
}
