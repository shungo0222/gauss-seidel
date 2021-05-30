#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int n;
double **a, *b, *ans;

void input(void) {
    printf("How many unknown variables? n = ");
    scanf("%d", &n);

    a = malloc(sizeof(double *) * n);
    for (int i=0; i<n; i++) {
        a[i] = malloc(sizeof(double) * n);
    }
    b = malloc(sizeof(double) * n);
    ans = malloc(sizeof(double) * n);
    
    printf("a =\n");
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            scanf("%lf", &a[i][j]);
        }
    }
    printf("b =\n");
    for (int i=0; i<n; i++) {
        scanf("%lf", &b[i]);
    }
    printf("\nWhat are initial variables?\n");
    printf("x0 =\n");
    for (int i=0; i<n; i++) {
        scanf("%lf", &ans[i]);
    }
}

void release_memory(void) {
    for (int i=0; i<n; i++) {
        free(a[i]);
    }
    free(a);
    free(b);
    free(ans);
}

void get_params(void) {
    for (int i=0; i<3*n; i++) printf("-");
    printf("\n");
    
    printf("Check the parameters\n\n");
    
    printf("a =\n");
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            printf("%lf ", a[i][j]);
        }
        printf("\n");
    }
    printf("b =\n");
    for (int i=0; i<n; i++) {
        printf("%lf ", b[i]);
    }
    printf("\n");

    for (int i=0; i<3*n; i++) printf("-");
    printf("\n");
}

void solve(double threshold) {
    double max_error; // a variable that stores the biggest error in one update
    double ans_copy_for_error[n]; // a copy of ans list for calculating error

    do {
        for (int i=0; i<n; i++) {
            ans_copy_for_error[i] = ans[i];
        }

        for (int i=0; i<n; i++) {
            double right_side_sum = 0, left_side_sum = 0;
            for (int j=i+1; j<n; j++) {
                right_side_sum += -a[i][j] * ans[j];
            }
            right_side_sum += b[i];
            for (int j=0; j<i; j++) {
                left_side_sum += a[i][j] * ans[j];
            }
            ans[i] = (right_side_sum - left_side_sum) / a[i][i]; // update ans

            // calcurate an error
            if (i == 0) {
                max_error = fabs(ans[i] - ans_copy_for_error[i]);
            } else if (fabs(ans[i] - ans_copy_for_error[i]) > max_error) {
                max_error = fabs(ans[i] - ans_copy_for_error[i]);
            }
        }
    } while (max_error > threshold);
}

void get_ans(void) {
    printf("\nThe answer is\n");
    printf("x = ");
    for (int i=0; i<n; i++) {
        printf("%lf ", ans[i]);
    }
    printf("\n\n");
}

int main(void) {
    double threshold = 1e-5;

    printf("Let's solve simultaneous linear equations (ax=b) with gauss seidel!!\n");
    input();
    solve(threshold);
    get_ans();
    release_memory();

    return 0;
}