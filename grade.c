#include <stdio.h>
char *checkgrd (int score) {
    if (score >= 80) {
        return "HD";
    } else if (score >= 70 && score < 80){
        return "DI";
    } else if (score >= 60 && score < 70){
        return "CR";
    } else if (score >= 50 && score < 60) {
        return "PA";
    } else if (score < 50) {
        return "NN";
    }
}
int main(int argc, char const *argv[]) {
    int n;
    float grade[5];
    float pct[5];
    float max[5];
    printf ("How many Assignment you have for the course?\n");
    scanf("%i" , &n);
    for (int i = 0; i < n; i++) {
        printf("Assignment %i max score: " , i+1);
        scanf("%f", &max[i]);
        printf("Assignment %i score: ", i+1);
        scanf ("%f", &grade [i]);
        printf("Assignment %i percentage: ", i+1);
        scanf ("%f", &pct[i]);
        printf("-------------------------------------\n");
    }
    float result;
    float ans[5];
    for (int i = 0; i < n; i++){
        ans [i] = (grade[i]/max[i])*100*(pct[i]/100);
        result = result + ans[i];
    }
    printf("Your percentage: %.2f %% \n", result);
    printf("Your grade: %s\n", checkgrd (result));
    return 0;
}
