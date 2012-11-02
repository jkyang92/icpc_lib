#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;


char text[100000], pat[100];
int f[100];


/* kmpsetup: setup back tracking links, pat is the pattern,
back tracing links are recorded in f. */

void kmpsetup (char *pat, int* f) {
	int i, k, len = strlen(pat);
	for (f[0] = -1, i = 1; i < len; i++) {
		k = f[i-1];
		while (k >= 0)
			if (pat[k] == pat[i-1]) break;
			else k = f[k];
		f[i] = k + 1;
	}
}


/* kmpscan: find substring pat in string text using
back tracing link recorded in f. */

int kmpscan (char *pat, char *text, int *f) {
	int i, k, ret = -1, len = strlen(pat);
	for (i = k = 0; text[i];) {
		if (k == -1) { i++; k = 0; }
		else if (text[i] == pat[k]) {
			i++; k++;
			if (k >= len) { ret = i - len; break; }
		} else k = f[k];
	}
	return ret;
}

int main (void)
{
	int r;
	scanf ("%s %s", pat, text);
	kmpsetup (pat, f);
	r = kmpscan (pat, text, f);
	if (r == -1)
		printf ("Not Found\n");
	else
		printf ("substring starts at %d\n", r);
}
