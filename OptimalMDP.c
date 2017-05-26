#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>

int main(int argc, char **argv)
{
	char c;
	char * line = NULL;
	size_t len = 0;
	ssize_t read;
	int i, j, k;
	char * val;
	double valbest, valnow;
	FILE *fp = fopen(argv[1], "r");
	if (fp == NULL)
	{
		printf("File not exists\n");
		exit(0);
	}

	//read = getline(&line, &len, fp);
	int stateNum ;
	fscanf(fp,"%d",&stateNum);
	//printf("%d\n", stateNum);

	int actionNum;
	fscanf(fp,"%d",&actionNum);
	//printf("%d\n", actionNum);

	
	double **reward = (double **)malloc(stateNum * actionNum * sizeof(double *));

	for (i=0; i<stateNum * actionNum; i++)
		reward[i] = (double *)malloc(stateNum * sizeof(double));

	for(i=0; i< stateNum * actionNum; i++)
	{
		for (j=0; j<stateNum;j++)
		{
			fscanf(fp,"%lf",&reward[i][j]);
			//printf("%.10f\n", reward[i][j]);
		}
	}

	double **transition = (double **)malloc(stateNum * actionNum * sizeof(double *));

	for (i=0; i<stateNum * actionNum; i++)
		transition[i] = (double *)malloc(stateNum * sizeof(double));

	for(i=0; i< stateNum * actionNum; i++)
	{
		for (j=0; j<stateNum;j++)
		{
			fscanf(fp,"%lf",&transition[i][j]);
			//printf("%.10f\n", transition[i][j]);
		}
	}

	//read = getline(&line, &len, fp);
	double disFactor;
	fscanf(fp,"%lf",&disFactor);
	//printf("%lf\n", disFactor);

	int *action = (int *)malloc(stateNum * sizeof(int));
	double *value = (double *)malloc(stateNum * sizeof(double));
	bool changed = false;
	
	for(i=0; i<stateNum; i++)
	{
		action[i] = 1;
		value[i] = 0;
	}
	
	double sum = 0;
	int count = 0;
	double delta = 99999.0;
	while(!changed)
	{
		changed = true;

		//Policy evaluation

		while(delta > .000000001)
		{
			delta = 0;
			for(i = 0; i < stateNum; i++)
			{
				sum = 0;
				for(j = 0; j < stateNum; j++)
				{
					sum = sum + transition[i*actionNum + action[i]][j] * (reward[i * actionNum + action[i]][j] + (disFactor * value[j]));
				}
				delta = (delta < fabs(value[i]-sum)) ? fabs(value[i]-sum) : delta;
				value[i] = sum;

			}
			
		}


		//policy iteration
	
		for(i = 0; i < stateNum; i++)
		{
			valbest = value[i];
			for(j = 0; j < actionNum; j++)
			{
			
				valnow = 0;
				for(k = 0; k < stateNum; k++)
				{
					valnow = valnow + transition[i * actionNum + j][k] * (reward[i * actionNum + j][k] + (disFactor * value[k]));
				}
				if(valbest < valnow)
				{
					action[i] = j;
					valbest = valnow;
					changed = false;
					value[i] = valbest;
				}			
			}

		}
	}
	double m;
	long int n, rval;
	for(i = 0; i < stateNum; i++)
	{
		m = value[i]*pow(10,6);
		n = (long int) m;
		rval= (m < n+.5) ? m : m+1;
		printf("%.6f\t%d\n", rval/pow(10,6), action[i]);
	}
	return 0;
}
