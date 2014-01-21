/* 
*  This file is part of GT3rm.

*  GT3rm is free software: you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation, either version 3 of the License, or
*  (at your option) any later version.

*  GT3rm is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.

*  You should have received a copy of the GNU General Public License
*  along with GT3rm.  If not, see <http://www.gnu.org/licenses/>.
*/

/* final edit by 1eekai, Jan.21st, 2014   */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int findStrInTheMatrix(char** matrix, char* array){       /* find the string in the 2D char array. This function was used to search the user's arguments.  */
	int num=0;
	while (matrix[num]!=0){
		if (strcmp(matrix[num],array)==0)	return num;
		num++;
	}
	return 65535;
}

void version(void){
	fprintf(stdout,
		"%s\n%s\n%s\n%s\n%s\n",
		"GT3rm, Just a translator of gnome-terminal.",
		"Because of the commands of gnome-terminal did not fit the code::blocks' calling (-e arguments without \" signal, xterm-like), so I wrote this. Cheers code::blocks!",
		"GT3rm obeys GNU GPLv3 license(http://www.gnu.org/licenses/gpl.txt).",
		"You can change and redistribute this freely, but you must obey the terms which declared in the GNU GPL v3.",
		"GT3rm comes with absolutely no warranty, to the extends permitted by applicable law."
		);
}

int main(int argc, char** argv){
	char* passcmd;
	int counter;
	int longs_of_execute=0;   /* shows how long did user gives with the parameters. The program will allocate the memory by this.  */
	if (findStrInTheMatrix(argv,"--version")!=65535){
		version();
		return 0;
	}
	if (findStrInTheMatrix(argv,"-e")==65535 || findStrInTheMatrix(argv,"-t")==65535){ 
		fprintf(stderr,
			"%s\n",
			"You need to pass an valid arguments." /* test if user gives the -t or -e arguments. If not, the program will exit. */
			);
		return 1;
	}
	for (counter=findStrInTheMatrix(argv,"-e")+1;counter<argc;counter++){
		if (argv[counter]==0){
			break;
		}
		longs_of_execute+=strlen(argv[counter]);
		if (counter!=argc-1)	longs_of_execute++;
	}
	passcmd=(char *)malloc(sizeof(char)*longs_of_execute);
	if (passcmd==NULL){
		fprintf(stderr,
			"%s",			/* Set this to set the fail-safe of memory alloctaion in case of failure */
			"Memory low. Exiting." 
			);
		return 1;
	}
	memset(passcmd,'\0',sizeof(passcmd));
	for (counter=findStrInTheMatrix(argv,"-e")+1;counter<argc;counter++){
		if (argv[counter]==0){
			break;
		}
		if (counter==4)	strcpy(passcmd,argv[counter]);
		else	strcat(passcmd,argv[counter]);
		if (counter!=argc-1)	strcat(passcmd," ");
	}
	execlp("gnome-terminal", "gnome-terminal","-t", argv[findStrInTheMatrix(argv,"-t")+1], "-e", passcmd, NULL);
	/*fprintf(stdout,
		"%s\n%s\n%s\n%s\n",
		"-t will shows",
		argv[findStrInTheMatrix(argv,"-t")+1],
		"-e will shows",
		passcmd
		);
	*/
	free(passcmd);
	return 0;
}
