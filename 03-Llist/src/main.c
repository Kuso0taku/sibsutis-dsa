#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "data_list.h"
#include "utils.h"

// ---------- Safe input functions ----------

static int safe_input_int_single(const char *prompt, int *value, int min, int max,
                                  struct list_head *head) {
    int code;
    char ch;
    printf("%s", prompt);
    while ((code = scanf("%d", value)) != 1 || (min != max && (*value < min || *value > max))) {
        if (code == EOF) {
            printf("EOF ERROR! ABORTING.\n");
            if (head) {
                list_clear(head);
                free(head);
            }
            return -1;
        }
        while ((ch = getchar()) != '\n' && ch != EOF);
        printf("Invalid input! Try again: ");
    }
    return 0;
}

static int safe_input_int_array(const char *prompt, int *value, int min, int max,
                                 struct list_head **lists, size_t num_lists) {
    int code;
    char ch;
    printf("%s", prompt);
    while ((code = scanf("%d", value)) != 1 || (min != max && (*value < min || *value > max))) {
        if (code == EOF) {
            printf("EOF ERROR! ABORTING.\n");
            for (size_t i = 0; i < num_lists; i++) {
                list_clear(lists[i]);
                free(lists[i]);
            }
            free(lists);
            return -1;
        }
        while ((ch = getchar()) != '\n' && ch != EOF);
        printf("Invalid input! Try again: ");
    }
    return 0;
}

static int safe_input_key_value(int *key, double *value) {
    int code;
    char ch;
    printf("Enter key (int) and value (double): ");
    while ((code = scanf("%d %lf", key, value)) != 2) {
        if (code == EOF) return -1;
        while ((ch = getchar()) != '\n' && ch != EOF);
        printf("Invalid input! Try again: ");
    }
    return 0;
}

// ---------- Core functions ----------

int load_from_file(struct list_head *head, const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        fprintf(stderr, "Cannot open file '%s'\n", filename);
        return -2;
    }
    int key, count = 0;
    double value;
    while (fscanf(f, "%d %lf", &key, &value) == 2) {
        data_add_tail(head, key, value);
        count++;
    }
    fclose(f);
    printf("Loaded %d elements from file.\n", count);
    return count;
}

void list_print(struct list_head *head) {
    struct list_head *pos;
    printf("The list:\n");
    list_for_each(pos, head) {
        struct data *entry = container_of(pos, struct data, list);
        printf(",key = %d, value = %.2f\n", entry->key, entry->value);
    }
}

int add_multiple(struct list_head *head, void (*add_func)(struct list_head*, int, double)) {
    int n;
    if (safe_input_int_single("How many elements to add? ", &n, 1, 1000000, head) != 0)
        return -1;

    for (int i = 0; i < n; i++) {
        int key;
        double value;
        if (safe_input_key_value(&key, &value) != 0) {
            printf("EOF ERROR! ABORTING.\n");
            list_clear(head);
            free(head);
            return -1;
        }
        add_func(head, key, value);
        printf("Added!\n");
    }
    return 0;
}

int run_experiment(const char *filename) {
    printf("Starting experiment...\n");
    fflush(stdout);
    FILE *f = fopen(filename, "w");
    if (!f) {
        fprintf(stderr, "Cannot create file '%s'\n", filename);
        return -1;
    }
    srand(time(NULL));
    fprintf(f, "#,elements,list_add_tail,list_lookup\n");

    const size_t sizes[] = {50000, 100000, 150000, 200000, 250000,
                            300000, 350000, 400000, 450000, 500000};
    for (size_t idx = 0; idx < 10; idx++) {
        size_t n = sizes[idx];
        printf("Processing n=%zu...\n", n);
        fflush(stdout);
        struct list_head head;
        INIT_LIST_HEAD(&head);

        double add_time = 0.0, lookup_time = 0.0;

        for (size_t j = 0; j < n; j++) {
            int key = getrand_int(0, 2 * n);
            double val = getrand_double(0, n);
            double start = wtime();
            data_add_tail(&head, key, val);
            add_time += wtime() - start;
        }
        add_time /= n;

        for (size_t j = 0; j < n; j++) {
            int key = getrand_int(0, 2 * n);
            double start = wtime();
            data_lookup(&head, key);
            lookup_time += wtime() - start;
        }
        lookup_time /= n;

        fprintf(f, "%zu,%.9f,%.9f\n", n, add_time, lookup_time);
        list_clear(&head);
        printf("Finished n=%zu\n", n);
        fflush(stdout);
    }
    fclose(f);
    printf("Experiment results saved to %s\n", filename);
    return 0;
}

size_t new_list(struct list_head ***lists_ptr, size_t old_cnt) {
    struct list_head *new_head = malloc(sizeof(struct list_head));
    if (!new_head) {
        fprintf(stderr, "Allocation error\n");
        return old_cnt;
    }
    INIT_LIST_HEAD(new_head);

    struct list_head **tmp = realloc(*lists_ptr, (old_cnt + 1) * sizeof(struct list_head*));
    if (!tmp) {
        free(new_head);
        fprintf(stderr, "Reallocation error\n");
        return old_cnt;
    }
    *lists_ptr = tmp;
    (*lists_ptr)[old_cnt] = new_head;
    return old_cnt + 1;
}

void print_menu(void) {
    printf("\nChoose operation:\n");
    printf("1. Add element to the beginning\n");
    printf("2. Add element to the end\n");
    printf("3. Find element(s) by key\n");
    printf("4. Delete element(s) by key\n");
    printf("5. Print all elements\n");
    printf("6. Load elements from file\n");
    printf("7. Clear list\n");
    printf("8. Create new list\n");
    printf("9. Check available lists\n");
    printf("10. Change current list\n");
    printf("11. Run experiment\n");
    printf("0. Exit\n");
    printf("Your choice: ");
}

int main(void) {
    struct list_head **lists = NULL;
    size_t cnt = 0;
    size_t cur = 0;

    cnt = new_list(&lists, cnt);
    if (cnt == 0) return 1;
    struct list_head *head = lists[0];
    int error_occurred = 0;

    int choice;
    do {
        print_menu();
        if (scanf("%d", &choice) != 1) {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF);
            printf("Invalid input.\n");
            continue;
        }
        if (choice < 0 || choice > 11) {
            printf("Choice must be 0..11.\n");
            continue;
        }

        switch (choice) {
            case 0:
                for (size_t i = 0; i < cnt; i++) {
                    list_clear(lists[i]);
                    free(lists[i]);
                }
                free(lists);
                printf("Goodbye.\n");
                return 0;

            case 1:
                if (add_multiple(head, data_add_front) == -1) {
                    error_occurred = 1;
                }
                break;

            case 2:
                if (add_multiple(head, data_add_tail) == -1) {
                    error_occurred = 1;
                }
                break;

            case 3: {
                int n;
                if (safe_input_int_array("How many elements to find? ", &n, 1, 1000000, lists, cnt) != 0) {
                    error_occurred = 1;
                    break;
                }
                for (int i = 0; i < n; i++) {
                    int key;
                    printf("Enter key (int): ");
                    if (scanf("%d", &key) != 1) {
                        int ch;
                        while ((ch = getchar()) != '\n' && ch != EOF);
                        printf("Invalid input.\n");
                        break;
                    }
                    double val = data_lookup(head, key);
                    printf("Element with key %d ", key);
                    if (val == -1.0) printf("not found\n");
                    else printf("found: value = %.2f\n", val);
                }
                break;
            }

            case 4: {
                int n;
                if (safe_input_int_array("How many elements to delete? ", &n, 1, 1000000, lists, cnt) != 0) {
                    error_occurred = 1;
                    break;
                }
                for (int i = 0; i < n; i++) {
                    int key;
                    printf("Enter key (int): ");
                    if (scanf("%d", &key) != 1) {
                        int ch;
                        while ((ch = getchar()) != '\n' && ch != EOF);
                        printf("Invalid input.\n");
                        break;
                    }
                    int deleted = data_delete(head, key);
                    printf("Element with key %d %s\n", key, deleted ? "deleted" : "not found");
                }
                break;
            }

            case 5:
                list_print(head);
                break;

            case 6: {
                char filename[256];
                printf("Enter filename: ");
                if (scanf("%255s", filename) != 1) {
                    int ch;
                    while ((ch = getchar()) != '\n' && ch != EOF);
                    printf("Invalid input.\n");
                    break;
                }
                load_from_file(head, filename);
                break;
            }

            case 7:
                list_clear(head);
                printf("List cleared.\n");
                break;

            case 8: {
                size_t new_cnt = new_list(&lists, cnt);
                if (new_cnt == cnt) {
                    printf("Failed to create new list.\n");
                } else {
                    cnt = new_cnt;
                    cur = cnt - 1;
                    head = lists[cur];
                    printf("New list created. Total lists: %zu. Switched to list #%zu.\n", cnt, cur+1);
                }
                break;
            }

            case 9:
                printf("Available lists:\n");
                for (size_t i = 0; i < cnt; i++)
                    printf("%s list #%zu\n", (i == cur) ? " *" : "  ", i+1);
                break;

            case 10: {
                if (cnt == 0) { printf("No lists.\n"); break; }
                int new_cur;
                if (safe_input_int_array("Enter list number (1..%zu): ", &new_cur, 1, (int)cnt, lists, cnt) != 0) {
                    error_occurred = 1;
                    break;
                }
                cur = (size_t)new_cur - 1;
                head = lists[cur];
                printf("Current list changed to #%zu.\n", cur+1);
                break;
            }

            case 11: {
                char filename[256];
                printf("Enter filename for experiment: ");
                if (scanf("%255s", filename) != 1) {
                    int ch;
                    while ((ch = getchar()) != '\n' && ch != EOF);
                    printf("Invalid input.\n");
                    break;
                }
                run_experiment(filename);
                break;
            }

            default:
                break;
        }

        if (error_occurred) {
            for (size_t i = 0; i < cnt; i++) {
                list_clear(lists[i]);
                free(lists[i]);
            }
            free(lists);
            return 1;
        }
    } while (1);

    return 0;
}
