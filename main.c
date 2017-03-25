#include <stdio.h>
#include <math.h>


int pow10(int x);
double analyseline(FILE *txtfile);

#define nrofQ 2

int main(void) {
	FILE *riksdagout, *website;
	char holder[120];
	int cnt, cnt2;
	double result[8][8] = { 0 };

	errno_t err;

	err = fopen_s(&website, "C:\\Users\\John\\documents\\visual studio 2015\\Projects\\Changing_output\\website.txt", "w");
	err += fopen_s(&riksdagout,"C:\\Users\\John\\documents\\visual studio 2015\\Projects\\Changing_output\\part.txt", "r");

	if (err == 0)
	{
		fgets(holder, 120, riksdagout); //{
		fgets(holder, 120, riksdagout); // "VOtering: [

		for (cnt = 0; cnt < nrofQ; cnt++) {
			fgets(holder, 120, riksdagout); //{
			fgets(holder, 120, riksdagout); //Votes

			for (cnt2 = 0; cnt2 < 8; cnt2++) {
				result[cnt][cnt2] += analyseline(riksdagout);
			}

			fprintf(website, "[%f, %f, %f, %f, %f, %f, %f, %f],\n", result[cnt][1], result[cnt][7], result[cnt][0], 
				result[cnt][2], result[cnt][3], result[cnt][4], result[cnt][6], result[cnt][5]);

			fgets(holder, 120, riksdagout); //},
			fgets(holder, 120, riksdagout); //POint
			fgets(holder, 120, riksdagout); //document code
			fgets(holder, 120, riksdagout); //},

		}

		fclose(website);


	}

	return 1;
}

double analyseline(FILE *txtfile) {
	char out[125];
	int cnt,cnt2;
	int ja = 0, nej = 0, steps = 0;
	double temp = 0, avstar = 0;
	
	fgets(out, 120, txtfile); //SD

	for (cnt = 0; cnt < 120; cnt++) {
		if (out[cnt] == ':') {
			break;
		}
	}

	cnt++; // space
	cnt++; //"
	cnt++; //Now it is JA
	steps = 0;

	if (out[cnt + 1] != '-') {
		steps++;
		if (out[cnt + 2] != '-') {
			steps++;
		}
	}

	for (cnt2 = 0; cnt2 <= steps; cnt2++) {
		ja += (out[cnt + cnt2] - 48)*pow10(steps - cnt2);
	}
	

	cnt += steps; //Last number
	cnt++; //-
	cnt++; //Now it is AVSTÅR
	steps = 0;

	if (out[cnt + 1] != '-') {
		steps++;
		if (out[cnt + 2] != '-') {
			steps++;
		}
	}

	for (cnt2 = 0; cnt2 <= steps; cnt2++) {
		avstar += (out[cnt + cnt2] - 48)*pow10(steps - cnt2);
	}
	
	cnt += steps; //Last number
	cnt++; //-
	cnt++; //Now it is NEJ
	steps = 0;
	
	if (out[cnt + 1] != '\"') {
		steps++;
		if (out[cnt + 2] != '\"') {
			steps++;
		}
	}

	for (cnt2 = 0; cnt2 <= steps; cnt2++) {
		nej += (out[cnt+cnt2] - 48)* pow10(steps - cnt2);
	}



	printf("JA = %i och NEJ = %i\n",ja,nej);

	if (ja != 0 && nej == 0 && avstar == 0) {
		return 1;
	}
	else if (ja == 0 && nej != 0 && avstar == 0) {
		return -1;
	}
	else if (ja > nej) {
		temp = ja / (ja + nej + avstar);
		return temp;
	}
	else if (ja < nej) {
		temp = -nej / (ja + nej + avstar);
		return temp;
	}
	else {
		printf("return 0 som fan\n");
		return 0;
	}
		

}

int pow10(int x) {
	int i;
	int ans=1;

	if (x == 0) {
		return 1;
	}

	for (i = 1; i <= x; i++) {
		ans *= 10;
	}

	return ans;
}