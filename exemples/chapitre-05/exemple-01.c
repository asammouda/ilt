#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/time.h>


int main(int argc, char * argv[])
{
	int priorite;
	struct sched_param param;
	struct timeval debut;
	struct timeval heure;
	long long int duree;
	long long int compteur;

	if ((argc != 2) || (sscanf(argv[1], "%d", & priorite) != 1)) {
		fprintf(stderr, "usage: %s priorite\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	param.sched_priority = priorite;
	if (sched_setscheduler(0, SCHED_RR, & param) != 0) {
		perror("setscheduler");
		exit(EXIT_FAILURE);
	}

	// Attendre la prochaine seconde avant de demarrer la boucle de comptage	
	gettimeofday(& debut, NULL);
	while (1) {
		gettimeofday(& heure, NULL);
		if (heure.tv_sec != debut.tv_sec)
			break;
		usleep(1000);
	}
	// Demarrer la boucle
	debut = heure;
	compteur = 0;
	while (1) {
		gettimeofday(& heure, NULL);
		duree  = heure.tv_sec - debut.tv_sec;
		duree *= 1000000; // en microsecondes
		duree += heure.tv_usec - debut.tv_usec;
		if (duree >= 3000000)
			break;
		compteur ++;
	}
	fprintf(stdout, "[%d] Priorite = %d, compteur = %lld\n",
	                 getpid(), priorite, compteur);
	return EXIT_SUCCESS;
}

